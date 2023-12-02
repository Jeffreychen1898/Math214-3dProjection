#include "linalg.hpp"

#define LINALG_EPSILON 0.001

// vec4 implementations
Vec4::Vec4()
	: x(0.f), y(0.f), z(0.f)
{}

Vec4::Vec4(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{}

Vec4& Vec4::operator=(const Vec4& _other)
{
	x = _other.x;
	y = _other.y;
	z = _other.z;
	w = _other.w;

	return *this;
}

Vec4 Vec4::operator+(Vec4 _other) const
{
	return Vec4(x + _other.x, y + _other.y, z + _other.z, w + _other.w);
}

Vec4 Vec4::operator-(Vec4 _other) const
{
	return Vec4(x - _other.x, y - _other.y, z - _other.z, w - _other.w);
}

Vec4 Vec4::operator*(float _scalar) const
{
	return Vec4(x * _scalar, y * _scalar, z * _scalar, w * _scalar);
}

Vec4 Vec4::operator/(float _scalar) const
{
	return Vec4(x / _scalar, y / _scalar, z / _scalar, w / _scalar);
}

void Vec4::print() const
{
	std::cout << "( " << x << " : " << y << " : " << z << " : " << w << " )" << std::endl;
}

float Vec4::length()
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}

void Vec4::normalize()
{
	float get_length = length();
	x /= get_length;
	y /= get_length;
	z /= get_length;
	w /= get_length;
}

// vec3 implementations
Vec3::Vec3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{}

Vec3& Vec3::operator=(const Vec3& _other)
{
	x = _other.x;
	y = _other.y;
	z = _other.z;

	return *this;
}

Vec3 Vec3::operator+(const Vec3 _other) const
{
	return Vec3(x + _other.x, y + _other.y, z + _other.z);
}

Vec3 Vec3::operator-(const Vec3 _other) const
{
	return Vec3(x - _other.x, y - _other.y, z - _other.z);
}

Vec3 Vec3::operator*(float _scalar) const
{
	return Vec3(x * _scalar, y * _scalar, z * _scalar);
}

Vec3 Vec3::operator/(float _scalar) const
{
	return Vec3(x / _scalar, y / _scalar, z / _scalar);
}

float Vec3::dot(const Vec3& _other) const
{
	return x * _other.x + y * _other.y + z * _other.z;
}

Vec3 Vec3::cross(const Vec3& _other) const
{
	float x_component = y * _other.z - z * _other.y;
	float y_component = x * _other.z - z * _other.x;
	float z_component = x * _other.y - y * _other.x;
	return Vec3(x_component, -y_component, z_component);
}

void Vec3::print() const
{
	std::cout << "( " << x << " : " << y << " : " << z << " )" << std::endl;
}

float Vec3::length()
{
	return std::sqrt(x * x + y * y + z * z);
}

void Vec3::normalize()
{
	float get_length = length();
	x /= get_length;
	y /= get_length;
	z /= get_length;
}

// vec2 implementations
Vec2::Vec2(float _x, float _y)
	: x(_x), y(_y)
{}

Vec2 Vec2::operator+(Vec2 _other) const
{
	return Vec2(x + _other.x, y + _other.y);
}

Vec2 Vec2::operator-(Vec2 _other) const
{
	return Vec2(x - _other.x, y - _other.y);
}

Vec2 Vec2::operator*(float _scalar) const
{
	return Vec2(x * _scalar, y * _scalar);
}

Vec2 Vec2::operator/(float _scalar) const
{
	return Vec2(x / _scalar, y / _scalar);
}

void Vec2::print() const
{
	std::cout << "( " << x << " : " << y << " )" << std::endl;
}

float Vec2::length()
{
	return std::sqrt(x * x + y * y);
}

void Vec2::normalize()
{
	float get_length = length();
	x /= get_length;
	y /= get_length;
}

// mat4 implementations
Mat4::Mat4(
	float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p
)
{
	values[0 ] = a;
	values[1 ] = b;
	values[2 ] = c;
	values[3 ] = d;

	values[4 ] = e;
	values[5 ] = f;
	values[6 ] = g;
	values[7 ] = h;

	values[8 ] = i;
	values[9 ] = j;
	values[10] = k;
	values[11] = l;

	values[12] = m;
	values[13] = n;
	values[14] = o;
	values[15] = p;
}

Mat4::Mat4(float _arr[])
{
	memcpy(&values[0], &_arr[0], 4 * 4 * sizeof(float));
}

float Mat4::at(int _row, int _col) const
{
	return values[_row * 4 + _col];
}

void Mat4::set(int _row, int _col, float _val)
{
	values[_row * 4 + _col] = _val;
}

Mat4 Mat4::operator*(const Mat4& _other) const
{
	float result[4 * 4];
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<4;++j)
        {
            float val1 = at(i, 0) * _other.at(0, j);
            float val2 = at(i, 1) * _other.at(1, j);
            float val3 = at(i, 2) * _other.at(2, j);
            float val4 = at(i, 3) * _other.at(3, j);

            result[i * 4 + j] = val1 + val2 + val3 + val4;
        }
    }

    return Mat4(result);
}

Vec4 Mat4::operator*(const Vec4& _other) const
{
	float result[4];
    for(int i=0;i<4;++i)
    {
        float val1 = at(i, 0) * _other.x;
        float val2 = at(i, 1) * _other.y;
        float val3 = at(i, 2) * _other.z;
        float val4 = at(i, 3) * _other.w;
        result[i] = val1 + val2 + val3 + val4;
    }
    return Vec4(result[0], result[1], result[2], result[3]);
}

void Mat4::print() const
{
	std::cout << "[" << std::endl;
	for(int i=0;i<4;++i)
	{
		std::cout << "\t";
		for(int j=0;j<4;++j)
			std::cout << at(i, j) << " ";
		std::cout << std::endl;
	}
	std::cout << "]" << std::endl;
}

// mat2 implementations
Mat2::Mat2(
	float a, float b,
	float c, float d
)
{
	values[0] = a;
	values[1] = b;

	values[2] = c;
	values[3] = d;
}

Mat2::Mat2(float _arr[])
{
	memcpy(&values[0], &_arr[0], 2 * 2 * sizeof(float));
}

float Mat2::at(int _row, int _col) const
{
	return values[_row * 2 + _col];
}

void Mat2::set(int _row, int _col, float _val)
{
	values[_row * 2 + _col] = _val;
}

Mat2 Mat2::operator*(const Mat2& _other) const
{
	float result[2 * 2];
    for(int i=0;i<2;++i)
    {
        for(int j=0;j<2;++j)
        {
            float val1 = at(i, 0) * _other.at(0, j);
            float val2 = at(i, 1) * _other.at(1, j);

            result[i * 2 + j] = val1 + val2;
        }
    }

    return Mat2(result);
}

Vec2 Mat2::operator*(const Vec2& _other) const
{
	float result[2];
    for(int i=0;i<2;++i)
    {
        float val1 = at(i, 0) * _other.x;
        float val2 = at(i, 1) * _other.y;
        result[i] = val1 + val2;
    }
    return Vec2(result[0], result[1]);
}

void Mat2::inverse()
{
	float det = 1.f / (at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0));
	if(abs(det) < LINALG_EPSILON)
		return;

	float a = at(0, 0);
    float b = at(0, 1);
    float c = at(1, 0);
    float d = at(1, 1);
    set(0, 0, d * det);
    set(0, 1, -b * det);
    set(1, 0, -c * det);
    set(1, 1, a * det);
}

void Mat2::print() const
{
	std::cout << "[" << std::endl;
	for(int i=0;i<2;++i)
	{
		std::cout << "\t";
		for(int j=0;j<2;++j)
			std::cout << at(i, j) << " ";
		std::cout << "\t" << std::endl;
	}
	std::cout << "]" << std::endl;
}
