#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <GL/glew.h>

#include "object.h"
#include "vertex.h"
#include "vector2.h"

class Object2D : public Object {
public:
	Object2D();
	Object2D(Vector3 position, Vector3 scale, Color defaultColor);
	void LookAt(Transform& transform);
};

#endif // !OBJECT2D_H
