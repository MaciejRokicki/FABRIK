#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <GL/glew.h>

#include "object.h"
#include "vertex.h"
#include "vector3.h"

class Object3D : public Object {
public:
	Object3D();
	Object3D(Vector3 position, Vector3 scale, Color default_color);
};

#endif // !OBJECT2D_H
