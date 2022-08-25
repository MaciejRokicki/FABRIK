#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "object.h"

class Object3D : public Object {
public:
	Object3D();
	Object3D(Vector3 position, Vector3 scale, Color defaultColor);
};

#endif // !OBJECT2D_H
