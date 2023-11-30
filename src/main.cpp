#include <iostream>

#include "linalg.hpp"

void test_vec2();
void test_vec3();
void test_vec4();
void test_mat2();
void test_mat4();

int main()
{
	test_vec2();
	std::cout << std::endl;

	test_vec3();
	std::cout << std::endl;

	test_vec4();
	std::cout << std::endl;

	test_mat2();
	std::cout << std::endl;

	test_mat4();
	return 0;
}

void test_vec2()
{
	Vec2 vector1(1.f, 2.f);
	Vec2 vector2(2.f, 4.f);

	vector1.print();
	vector2.print();

	Vec2 vec_sum = vector1 + vector2;
	vec_sum.print();

	Vec2 vec_diff = vector1 - vector2;
	vec_diff.print();

	Vec2 vec_mult = vector1 * 0.02f;
	vec_mult.print();

	Vec2 vec_div = vector1 / 2.f;
	vec_div.print();
}

void test_vec3()
{
	Vec3 vector1(1.f, 2.f, 3.f);
	Vec3 vector2(2.f, 4.f, 8.f);

	vector1.print();
	vector2.print();

	Vec3 vec_sum = vector1 + vector2;
	vec_sum.print();

	Vec3 vec_diff = vector1 - vector2;
	vec_diff.print();

	Vec3 vec_mult = vector1 * 0.02f;
	vec_mult.print();

	Vec3 vec_div = vector1 / 2.f;
	vec_div.print();

	float vec_dot = vector1.dot(vector2);
	Vec3 vec_cross = vector1.cross(vector2);
	std::cout << vec_dot << std::endl;
	vec_cross.print();
}

void test_vec4()
{
	Vec4 vector1(1.f, 2.f, 3.f, 4.f);
	Vec4 vector2(2.f, 4.f, 6.f, 8.f);

	vector1.print();
	vector2.print();

	Vec4 vec_sum = vector1 + vector2;
	vec_sum.print();

	Vec4 vec_diff = vector1 - vector2;
	vec_diff.print();

	Vec4 vec_mult = vector1 * 0.02f;
	vec_mult.print();

	Vec4 vec_div = vector1 / 2.f;
	vec_div.print();
}

void test_mat4()
{
	Mat4 mat1(
			1.f, 2.f, 4.f, 6.f,
			2.f, 4.f, 2.f, 1.f,
			3.f, 6.f, 2.f, 3.f,
			8.f, 2.f, 1.f, 2.f
		);
	Mat4 mat2(
			3.f, 5.f, 2.f, 9.f,
			2.f, 4.f, 1.f, 1.f,
			7.f, 3.f, 9.f, 2.f,
			8.f, 2.f, 4.f, 4.f
		);
	Vec4 vec(1.f, 2.f, 5.f, 2.f);
	
	mat1.print();
	mat2.print();
	vec.print();

	(mat1 * mat2).print();
	(mat1 * vec).print();
}

void test_mat2()
{
	Mat2 mat1(
			1.f, 2.f,
			5.f, 3.f
		);
	Mat2 mat2(
			2.f, 3.f,
			1.f, 5.f
		);
	Vec2 vec(1.f, 3.f);

	mat1.print();
	mat2.print();
	vec.print();

	(mat1 * mat2).print();
	(mat1 * vec).print();

	mat1.inverse();
	mat1.print();
}
