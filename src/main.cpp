#include <iostream>
#include <cmath>

#include "config.hpp"
#include "parser.hpp"
#include "linalg.hpp"
#include "image.hpp"

static Mat4 calculatePerspectiveMatrix(float _fov, float _aspect_ratio, float _near, float _far);
static Mat4 calculateViewMatrix(Vec3 _position, Vec3 _lookat, Vec3 _up);

int main()
{
	int image_width = IMAGE_WIDTH;
	int image_height = IMAGE_HEIGHT;

	Image* out_image = createImage(image_width, image_height);
	clearImage(out_image, {0, 0, 0});

	// load the shape
	Shapes* new_shapes = loadShapes(SHAPE_PATH);
	int triangle_count = getShapeTriangleCount(new_shapes);
	Triangle shape_triangles[triangle_count];
	getShapeTriangles(new_shapes, shape_triangles);

	// create the perspective matrix
	float fov = CAMERA_FOV;
	float aspect_ratio = static_cast<float>(image_width) / image_height;
	float near_plane = NEAR_PLANE;
	float far_plane = FAR_PLANE;
	Mat4 perspective_mat = calculatePerspectiveMatrix(fov, aspect_ratio, near_plane, far_plane);

	// create the view matrix
	Vec3 lookat_vector(CAMERA_LOOKAT_X, CAMERA_LOOKAT_Y, CAMERA_LOOKAT_Z); // have the camera look at the origin
	Vec3 up_vector(CAMERA_UP_X, CAMERA_UP_Y, CAMERA_UP_Z); // general up direction is +y
	Vec3 camera_position(CAMERA_POSITION_X, CAMERA_POSITION_Y, CAMERA_POSITION_Z);
	Mat4 view_mat = calculateViewMatrix(camera_position, lookat_vector, up_vector);

	Mat4 mvp_mat = perspective_mat * view_mat;

	for(int i=0;i<triangle_count;++i)
	{
		shape_triangles[i].vertex1 = mvp_mat * shape_triangles[i].vertex1;
		shape_triangles[i].vertex2 = mvp_mat * shape_triangles[i].vertex2;
		shape_triangles[i].vertex3 = mvp_mat * shape_triangles[i].vertex3;

		renderTriangle(out_image, shape_triangles[i]);
	}

	exportImage(IMAGE_OUT_PATH, out_image);
	deleteImage(out_image);
	deleteShapes(new_shapes);
	return 0;
}

Mat4 calculatePerspectiveMatrix(float _fov, float _aspect_ratio, float _near, float _far)
{
	float thfov = tan(_fov / 2.f);
	float a = _aspect_ratio;
	float f = _far;
	float n = _near;
	Mat4 perspective_matrix(
			1.f / (a * thfov), 0.f        , 0.f         , 0.f,
			0.f              , 1.f / thfov, 0.f			, 0.f,
			0.f				 , 0.f		  , -(f+n)/(f-n), -2.f*f*n/(f-n),
			0.f				 , 0.f		  , -1.f		, 0.f
	);
	return perspective_matrix;
}

Mat4 calculateViewMatrix(Vec3 _position, Vec3 _lookat, Vec3 _up)
{
	// using gram schmidt also works.
	// however, u1 MUST be the forward vector because you
	// do not want to change the forward vector.

	Vec3 forward_vector = _lookat - _position;
	// this program mimics OpenGL's API and opengl have +z pointing
	// out of the screen not into the screen, so the left is actually
	// the right
	Vec3 right_vector = forward_vector.cross(_up);
	Vec3 up_vector = right_vector.cross(forward_vector);
	
	forward_vector.normalize();
	right_vector.normalize();
	up_vector.normalize();

	Mat4 change_in_basis(
			right_vector.x  , right_vector.y  , right_vector.z  , -right_vector.dot(_position),
			up_vector.x     , up_vector.y     , up_vector.z     , -up_vector.dot(_position),
			-forward_vector.x, -forward_vector.y, -forward_vector.z, forward_vector.dot(_position),
			0.f             , 0.f             , 0.f             , 1.f
	);
	
	return change_in_basis;
}
