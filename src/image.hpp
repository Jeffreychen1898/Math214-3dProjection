#pragma once

#include <fstream>
#include <algorithm>

#include "linalg.hpp"

struct Pixel
{
	int red = 0;
	int green = 0;
	int blue = 0;
};

struct Image
{
	int width;
	int height;

	unsigned char* r;
	unsigned char* g;
	unsigned char* b;

	float* depth;
};

struct Triangle
{
	Vec4 vertex1;
	Vec4 vertex2;
	Vec4 vertex3;

	Pixel vertexColor1;
	Pixel vertexColor2;
	Pixel vertexColor3;
};

Image* createImage(int _width, int _height);
void deleteImage(Image* _img);
void clearImage(Image* _img, Pixel _color);
Pixel getPixel(const Image* _img, int _row, int _col);
void setPixel(Image* _img, int _row, int _col, Pixel _px);
void exportImage(const char* _path, const Image* _img);
void renderTriangle(Image* _img, const Triangle& _triangle);


