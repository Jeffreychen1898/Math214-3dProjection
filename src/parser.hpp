#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>

#include "linalg.hpp"
#include "image.hpp"

struct Shapes
{
	std::vector<Vec4>* vertices;
	std::vector<Vec3>* verticesColor;
	std::vector<unsigned int>* indices;
};

Shapes* loadShapes(const char* _path);
void deleteShapes(Shapes* _shape);

int getShapeTriangleCount(const Shapes* _shape);
void getShapeTriangles(const Shapes* _shape, Triangle* _triangles);
