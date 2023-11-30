#include "linalg.hpp"

// vec4 implementations
Vec4::Vec4(float _x, float _y, float _z, float _w)
{
}

Vec4 Vec4::operator+(Vec4& _other) const
{
}

Vec4 Vec4::operator-(Vec4& _other) const
{
}

Vec4 Vec4::operator*(float _scalar) const
{
}

Vec4 Vec4::operator/(float _scalar) const
{
}

// vec3 implementations
Vec3::Vec3(float _x, float _y, float _z)
{
}

Vec3 Vec3::operator+(const Vec3& _other) const
{
}

Vec3 Vec3::operator-(const Vec3& _other) const
{
}

Vec4 Vec3::operator*(float _scalar) const
{
}

Vec4 Vec3::operator/(float _scalar) const
{
}

Vec3 Vec3::dot(const Vec3& _other) const
{
}

Vec3 Vec3::cross(const Vec3& _other) const
{
}

// vec2 implementations
Vec2(float _x, float _y)
{
}

Vec2 operator+(Vec2& _other) const
{
}

Vec2 operator-(Vec2& _other) const
{
}

Vec2 operator*(float _scalar) const
{
}

Vec2 operator/(float _scalar) const
{
}

// mat4 implementations
Mat4::Mat4(
	float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p
)
{
}

float Mat4::at(int _row, int _col)
{
}

void Mat4::set(int _row, int _col, float _val)
{
}

Mat4 Mat4::operator*(const Mat4& _other) const
{
}

Vec4 Mat4::operator*(const Vec4& _other) const
{
}

// mat2 implementations
Mat2::Mat2(
	float a, float b,
	float c, float d
)
{
}

float Mat2::at(int _row, int _col)
{
}

void Mat2::set(int _row, int _col, float _val)
{
}

Mat2 Mat2::operator*(const Mat2& _other) const
{
}

Vec2 Mat2::operator*(const Vec2& _other) const
{
}

void Mat2::inverse()
{
}
