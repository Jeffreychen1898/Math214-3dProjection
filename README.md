# Math 214 Final Project Demo
## Shape File
To render a specific shape, a ```txt``` file must be created and referenced in the ```config.hpp``` file. This file provides the vertices of the shape to render.

**making comments**

Any lines beginning with a ```#``` will be ignored.

**specifying the vertex**

The line should look something like this:

```v1: 50 30 20 255 0 200```

The ```v1``` is the name of the vertex. The name and the numbers are separated by a ```:```. The next 3 numbers specify the position of the vertex. The 3 numbers after that is color in rgb format.


**specifying the triangle**

The line should look something like this:

```t: v1 v2 v3```

The ```t``` indicates that this line specifices the triangle to render. After the ```:```, the following 3 are the vertices that make up the triangle.

**sample**
```
# here is a sample that create 2 triangles sharing 2 vertices with each other.

v1:  0  0 -50 		255 0 0
v2:  20 0  0		255 0 255
v3: -20 0  0		0 255 0
v4:  0  0  50		255 255 255

t: v1 v2 v3
t: v2 v3 v4
```

## Config.hpp
All of the program's settings are placed into the ```src/config.hpp``` file for easy access. The following are a list of the variables inside the file:

```SHAPE_PATH``` - The path to the file containing all the vertices of the shape to render.

```IMAGE_OUT_PATH``` - The path for the output image. This path should end in .ppm as that is the only file format supported.

```IMAGE_WIDTH``` - The width of the image.

```IMAGE_HEIGHT``` - The height of the image.

```CAMERA_FOV``` - The horizontal field of the view angle of the camera (in radians).

```NEAR_PLANE``` - The near plane which is usually positive. Only points whose z is in between [-NEAR_PLANE, FAR_PLANE] is rendered.

```FAR_PLANE``` - The far plane which is usually negative.

```CAMERA_POSITION_X``` - The x coordinate of the camera.

```CAMERA_POSITION_Y``` - The y coordinate of the camera.

```CAMERA_POSITION_Z``` - The z coordinate of the camera.

```CAMERA_LOOKAT_X``` - The x coordinate of the lookat vector, the point in space that the camera is pointing at.

```CAMERA_LOOKAT_Y``` - The y coordinate of the lookat vector.

```CAMERA_LOOKAT_Z``` - The z coordinate of the lookat vector.

```CAMERA_UP_X``` - The x coordinate of the up vector. The general up direction of the camera.

```CAMERA_UP_Y``` - The y coordinate of the up vector.

```CAMERA_UP_Z``` - The z coordinate of the up vector.

## Compiling the Code

Run the following commands to execute the following actions:

```make all``` - build the program in the project's root directory. The name of the the program is "projection". To run the program, simply execute the command ```./projection```

```make run``` - build and run the program.

```make clean``` - clean up the project directory. Deletes all the output files as well as the builds.
