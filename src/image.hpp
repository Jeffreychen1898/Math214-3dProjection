#pragma once

#include <fstream>
#include <algorithm>

#include "linalg.hpp"

struct Pixel
{
	int red;
	int green;
	int blue;
	float depth;
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

Image* createImage(int _width, int _height);
void deleteImage(Image* _img);
void clearImage(Image* _img, Pixel _color);
Pixel getPixel(const Image* _img, int _row, int _col);
void setPixel(Image* _img, int _row, int _col, Pixel _px);
void exportImage(const char* _path, const Image* _img);
void renderTriangle(Image* _img, Vec4 _v1, Vec4 _v2, Vec4 _v3, Pixel _color);
