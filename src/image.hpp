#pragma once

#include "linalg.hpp"

struct Pixel
{
	int red;
	int green;
	int blue;
};

struct Image
{
	int width;
	int height;

	char* r;
	char* g;
	char* b;

	float* depth;
};

Image* createImage(int _width, int _height);
Image* deleteImage(Image* _img);
Pixel getPixel(const Image* _img, int _row, int _col);
void setPixel(Image* _img, int _row, int _col, Pixel _px);
void exportImage(const char* _path, const Image* _img);
void renderTriangle(Image* _img, Vec4 _v1, Vec4 _v2, Vec4 _v3, Pixel _color);
