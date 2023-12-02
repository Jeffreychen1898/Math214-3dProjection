#pragma once

#define HALF_PI 1.57079632679
#define PI      3.14159265359

#define SHAPE_PATH "in/triangle.txt"
#define IMAGE_OUT_PATH "out/testing.ppm"

#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT 600

// horizonal fov (vertical will be calculated with aspect ratio)
#define CAMERA_FOV HALF_PI

// only points with z in [-NEAR, FAR] will be rendered
// should be positive
#define NEAR_PLANE 20.f
#define FAR_PLANE -100.f

#define CAMERA_POSITION_X 50.f
#define CAMERA_POSITION_Y 100.f
#define CAMERA_POSITION_Z -100.f

#define CAMERA_LOOKAT_X 0.f
#define CAMERA_LOOKAT_Y 0.f
#define CAMERA_LOOKAT_Z 0.f

// general up direction
#define CAMERA_UP_X 0.f
#define CAMERA_UP_Y 1.f
#define CAMERA_UP_Z 0.f
