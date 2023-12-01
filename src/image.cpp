#include "image.hpp"

static bool getBoundingRectangle(Image* _img, Vec2& _boxMin, Vec2& _boxMax,
		const Vec4& _v1, const Vec4& _v2, const Vec4& _v3);

Image* createImage(int _width, int _height)
{
	Image* new_image = new Image;
	new_image->width = _width;
	new_image->height = _height;

	new_image->r = new unsigned char[_width * _height];
	new_image->g = new unsigned char[_width * _height];
	new_image->b = new unsigned char[_width * _height];

	new_image->depth = new float[_width * _height];

	return new_image;
}

void deleteImage(Image* _img)
{
	delete[] _img->r;
	delete[] _img->g;
	delete[] _img->b;

	delete[] _img->depth;

	delete _img;
}

void clearImage(Image* _img, Pixel _color)
{
	float furthest_depth = -1; // depth vals should be between -1 and 1
	for(int i=0;i<_img->height;++i)
	{
		for(int j=0;j<_img->width;++j)
		{
			setPixel(_img, i, j, _color);
			_img->depth[i * _img->width + j] = furthest_depth;
		}
	}
}

Pixel getPixel(const Image* _img, int _row, int _col)
{
	int red_color = static_cast<int>(_img->r[_row * _img->width + _col]);
	int green_color = static_cast<int>(_img->g[_row * _img->width + _col]);
	int blue_color = static_cast<int>(_img->b[_row * _img->width + _col]);
	float depth = _img->depth[_row * _img->width + _col];

	return { red_color, green_color, blue_color, depth };
}

void setPixel(Image* _img, int _row, int _col, Pixel _px)
{
	unsigned char red_color = static_cast<unsigned char>(_px.red);
	unsigned char green_color = static_cast<unsigned char>(_px.green);
	unsigned char blue_color = static_cast<unsigned char>(_px.blue);

	_img->r[_row * _img->width + _col] = red_color;
	_img->g[_row * _img->width + _col] = green_color;
	_img->b[_row * _img->width + _col] = blue_color;
	_img->depth[_row * _img->width + _col] = _px.depth;
}

void exportImage(const char* _path, const Image* _img)
{
	std::ofstream file;
	file.open(_path);

	file << "P3\n";
	file << _img->width << " " << _img->height << "\n";
	file << "255\n";

	for(int i=0;i<_img->height;++i)
	{
		for(int j=0;j<_img->width;++j)
		{
			int get_index = i * _img->width + j;
			file << static_cast<unsigned int>(_img->r[get_index]) << " ";
			file << static_cast<unsigned int>(_img->g[get_index]) << " ";
			file << static_cast<unsigned int>(_img->b[get_index]) << " ";
		}
		file << "\n";
	}

	file.close();
}

void renderTriangle(Image* _img, Vec4 _v1, Vec4 _v2, Vec4 _v3, Pixel _color)
{
	// perform the perspective divide
	_v1 = _v1 / _v1.w;
	_v2 = _v2 / _v2.w;
	_v3 = _v3 / _v3.w;

	// calculate the rectangle around the triangle
	Vec2 bounding_box_min(0.f, 0.f);
	Vec2 bounding_box_max(0.f, 0.f);
	if(!getBoundingRectangle(_img, bounding_box_min, bounding_box_max, _v1, _v2, _v3))
		return;

	// calculate the matrix to convert to berycentric coordinates
	Vec2 v1_as_vec2(_v1.x, _v1.y);

	Vec4 v1_to_v2 = _v2 - _v1;
	Vec4 v1_to_v3 = _v3 - _v1;
	Mat2 berycentric_coord_mat(
			v1_to_v2.x, v1_to_v3.x,
			v1_to_v2.y, v1_to_v3.y
	);
	berycentric_coord_mat.inverse();

	// iterate through every pixel
	for(int i=bounding_box_min.y;i<=bounding_box_max.y;++i)
	{
		for(int j=bounding_box_min.x;j<=bounding_box_max.x;++j)
		{
			Vec2 current_point(
					  j / (_img->width / 2.f) - 1.f ,
					-(i / (_img->height / 2.f) - 1.f)
			);
			//current_point.print();
			Vec2 minus_v1 = current_point - v1_as_vec2;
			Vec2 berycentric_coord = berycentric_coord_mat * minus_v1;

			if(berycentric_coord.x < 0 || berycentric_coord.y < 0 ||
			   berycentric_coord.x + berycentric_coord.y > 1)
				continue;
			setPixel(_img, i, j, _color);
		}
	}
}

// static functions
static bool getBoundingRectangle(Image* _img, Vec2& _boxMin, Vec2& _boxMax,
		const Vec4& _v1, const Vec4& _v2, const Vec4& _v3)
{
	// calculate bounding box and normalize coordinate to 0-1
	float left = (std::min({ _v1.x, _v2.x, _v3.x }) + 1) / 2.f;
	float right = (std::max({ _v1.x, _v2.x, _v3.x }) + 1) / 2.f;
	float up = (std::max({ _v1.y, _v2.y, _v3.y }) + 1) / 2.f;
	float down = (std::min({ _v1.y, _v2.y, _v3.y }) + 1) / 2.f;

	if(left >= right || down >= up)
		return false;

	// y coordinate direction flips
	up = 1.f - up;
	down = 1.f - down;

	if(left < 0 || right > 1 || up < 0 || down > 1)
		return false;

	// set the bounding box coordinates to range x: [0, width], y: [0: height]
	left *= _img->width;
	right *= _img->width;
	up *= _img->height;
	down *= _img->height;

	// make sure they stay within the image
	left = std::max(0, static_cast<int>(left));
	right = std::min(_img->width - 1, static_cast<int>(right));
	up = std::max(0, static_cast<int>(up));
	down = std::min(_img->height - 1, static_cast<int>(down));

	_boxMin.x = left;
	_boxMin.y = up;
	_boxMax.x = right;
	_boxMax.y = down;

	return true;
}
