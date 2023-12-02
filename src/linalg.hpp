#pragma once

#include <iostream>
#include <cmath>

class Vec4
{
	public:
		float x;
		float y;
		float z;
		float w;

		Vec4();
		Vec4(float _x, float _y, float _z, float _w);

		Vec4& operator=(const Vec4& _other);
		Vec4 operator+(Vec4 _other) const;
		Vec4 operator-(Vec4 _other) const;
		Vec4 operator*(float _scalar) const;
		Vec4 operator/(float _scalar) const;

		void print() const;
		void normalize();
		float length();
};

class Vec3
{
	public:
		float x;
		float y;
		float z;

		Vec3(float _x, float _y, float _z);

		Vec3& operator=(const Vec3& _other);
		Vec3 operator+(const Vec3 _other) const;
		Vec3 operator-(const Vec3 _other) const;
		Vec3 operator*(float _scalar) const;
		Vec3 operator/(float _scalar) const;
		
		float dot(const Vec3& _other) const;
		Vec3 cross(const Vec3& _other) const;
		
		void print() const;
		void normalize();
		float length();
};

class Vec2
{
	public:
		float x;
		float y;

		Vec2(float _x, float _y);

		Vec2 operator+(Vec2 _other) const;
		Vec2 operator-(Vec2 _other) const;
		Vec2 operator*(float _scalar) const;
		Vec2 operator/(float _scalar) const;

		void print() const;
		void normalize();
		float length();
};

class Mat4
{
	private:
		float values[4 * 4];
	public:
		Mat4(
			float a, float b, float c, float d,
			float e, float f, float g, float h,
			float i, float j, float k, float l,
			float m, float n, float o, float p
		);
		Mat4(float _arr[]);
		
		float at(int _row, int _col) const;
		void set(int _row, int _col, float _val);

		Mat4 operator*(const Mat4& _other) const;
		Vec4 operator*(const Vec4& _other) const;

		void print() const;
};

class Mat2
{
	private:
		float values[2 * 2];
	public:
		Mat2(
			float a, float b,
			float c, float d
		);
		Mat2(float _arr[]);

		float at(int _row, int _col) const;
		void set(int _row, int _col, float _val);

		Mat2 operator*(const Mat2& _other) const;
		Vec2 operator*(const Vec2& _other) const;

		void inverse();

		void print() const;
};
