#include <iostream>

#include "linalg.hpp"
#include "image.hpp"

int main()
{
	Image* test_image = createImage(100, 100);
	clearImage(test_image, {255, 255, 0});

	Vec4 v1(0.f, 0.5f, -1.f, 1.f);
	Vec4 v2(0.5f, -0.5f, -0.5f, 1.f);
	Vec4 v3(-0.5f, -0.5f, -0.5f, 1.f);

	Triangle triangle = {
		v1, v2, v3, {255, 0, 0}, {255, 0, 255}, {0, 255, 0}
	};

	renderTriangle(test_image, triangle);

	exportImage("out/testimg.ppm", test_image);
	return 0;
}
