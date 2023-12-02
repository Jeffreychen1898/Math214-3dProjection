#include "parser.hpp"

static void trimString(std::string& _str);
static void splitString(char _splitChar, std::string& _str, std::vector<std::string>& _list);
static bool parseLine(std::string& _str, Shapes* _shape);
static bool parseVertex(std::string& _vertexName, std::string& _str, Shapes* _shape);
static bool parseTriangle(std::string& _str, Shapes* _shape);

static std::map<std::string, int>* VertexTracker = nullptr;

Shapes* loadShapes(const char* _path)
{
	// attempt to open the file
	std::ifstream file;
	file.open(_path);
	if(!file.is_open())
		throw std::ios_base::failure("Unable to open file");

	VertexTracker = new std::map<std::string, int>();
	// create the shape
	Shapes* new_shape = new Shapes;
	new_shape->vertices = new std::vector<Vec4>();
	new_shape->verticesColor = new std::vector<Vec3>();
	new_shape->indices = new std::vector<unsigned int>();

	std::string line;
	while(std::getline(file, line))
	{
		trimString(line);
		if(line.size() == 0) // ignore empty strings
			continue;
		if(line.at(0) == '#') // ignore comments
			continue;
		
		if(!parseLine(line, new_shape))
		{
			delete VertexTracker;
			VertexTracker = nullptr;
			deleteShapes(new_shape);
			throw std::invalid_argument("Unable to parse!");
		}
	}
	file.close();

	delete VertexTracker;
	VertexTracker = nullptr;

	return new_shape;
}

void deleteShapes(Shapes* _shape)
{
	if(_shape == nullptr)
		return;

	delete _shape->vertices;
	delete _shape->verticesColor;
	delete _shape->indices;

	delete _shape;
}

int getShapeTriangleCount(const Shapes* _shape)
{
	if(_shape->indices == nullptr)
		return 0;
	return _shape->indices->size() / 3;
}

void getShapeTriangles(const Shapes* _shape, Triangle* _triangles)
{
	for(int i=0;i<_shape->indices->size();i+=3)
	{
		unsigned int vertex_one_index = _shape->indices->at(i);
		unsigned int vertex_two_index = _shape->indices->at(i + 1);
		unsigned int vertex_three_index = _shape->indices->at(i + 2);

		_triangles[i/3].vertex1 = _shape->vertices->at(vertex_one_index);
		_triangles[i/3].vertex2 = _shape->vertices->at(vertex_two_index);
		_triangles[i/3].vertex3 = _shape->vertices->at(vertex_three_index);

		Vec3 vertex_1_color = _shape->verticesColor->at(vertex_one_index);
		Vec3 vertex_2_color = _shape->verticesColor->at(vertex_two_index);
		Vec3 vertex_3_color = _shape->verticesColor->at(vertex_three_index);

		_triangles[i/3].vertexColor1 = {
			static_cast<int>(vertex_1_color.x),
			static_cast<int>(vertex_1_color.y),
			static_cast<int>(vertex_1_color.z)
		};
		_triangles[i/3].vertexColor2 = {
			static_cast<int>(vertex_2_color.x),
			static_cast<int>(vertex_2_color.y),
			static_cast<int>(vertex_2_color.z)
		};
		_triangles[i/3].vertexColor3 = {
			static_cast<int>(vertex_3_color.x),
			static_cast<int>(vertex_3_color.y),
			static_cast<int>(vertex_3_color.z)
		};
	}
}

// static functions
bool parseLine(std::string& _str, Shapes* _shape)
{
	// split by ':'
	std::vector<std::string> split_line_colon;
	splitString(':', _str, split_line_colon);
	if(split_line_colon.size() != 2)
		return false;

	// trim
	trimString(split_line_colon[0]);
	trimString(split_line_colon[1]);

	if(split_line_colon[0] == "t")
		return parseTriangle(split_line_colon[1], _shape);
	else
		return parseVertex(split_line_colon[0], split_line_colon[1], _shape);
}

bool parseVertex(std::string& _vertexName, std::string& _str, Shapes* _shape)
{
	std::vector<std::string> split_nums;
	splitString(' ', _str, split_nums);

	if(split_nums.size() != 6)
		return false;

	int vertex_index = _shape->vertices->size();

	Vec4 position_vectors(0.f, 0.f, 0.f, 1.f);
	Vec3 colors(0.f, 0.f, 0.f);

	position_vectors.x = std::stof(split_nums.at(0));
	position_vectors.y = std::stof(split_nums.at(1));
	position_vectors.z = std::stof(split_nums.at(2));

	colors.x = std::stof(split_nums.at(3));
	colors.y = std::stof(split_nums.at(4));
	colors.z = std::stof(split_nums.at(5));

	_shape->vertices->push_back(position_vectors);
	_shape->verticesColor->push_back(colors);

	VertexTracker->insert({ _vertexName, vertex_index });

	return true;
}

bool parseTriangle(std::string& _str, Shapes* _shape)
{
	std::vector<std::string> split_vertices;
	splitString(' ', _str, split_vertices);

	if(split_vertices.size() != 3)
		return false;

	auto vertex_1_iter = VertexTracker->find(split_vertices[0]);
	auto vertex_2_iter = VertexTracker->find(split_vertices[1]);
	auto vertex_3_iter = VertexTracker->find(split_vertices[2]);

	if(
		vertex_1_iter == VertexTracker->end() ||
		vertex_2_iter == VertexTracker->end() ||
		vertex_3_iter == VertexTracker->end()
	)
		return false;

	_shape->indices->push_back(static_cast<unsigned int>(vertex_1_iter->second));
	_shape->indices->push_back(static_cast<unsigned int>(vertex_2_iter->second));
	_shape->indices->push_back(static_cast<unsigned int>(vertex_3_iter->second));

	return true;
}

void trimString(std::string& _str)
{
	int begin_index = 0;
	int back_index = _str.size() - 1;

	while(begin_index <= back_index)
	{
		bool empty_at_front = isspace(_str.at(begin_index));
		bool empty_at_back = isspace(_str.at(back_index));

		if(!empty_at_front && !empty_at_back)
			break;

		if(empty_at_front)
			++ begin_index;
		if(empty_at_back)
			-- back_index;
	}

	if(begin_index > back_index)
	{
		_str = "";
		return;
	}
	int string_length = back_index - begin_index + 1;
	_str = _str.substr(begin_index, string_length);
}

static void splitString(char _splitChar, std::string& _str, std::vector<std::string>& _list)
{
	std::istringstream string_stream(_str);
	std::string chunk;

	if(_splitChar == ' ')
	{
		while(string_stream >> chunk)
			_list.push_back(chunk);

		return;
	}

	while(std::getline(string_stream, chunk, _splitChar))
		_list.push_back(chunk);
}
