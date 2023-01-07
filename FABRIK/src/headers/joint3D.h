#ifndef JOINT3D_H
#define JOINT3D_H

#include <GL/glew.h>

#include "object3D.h"
#include "segment3D.h"
#include "constraint3D.h"

class Constraint3D;

class Joint3D : public Object3D {
public:
	Vector3 PositionTmp;
	bool IsSubBase = false;
	Segment3D* segment = NULL;
	Constraint3D* constraint;

	Joint3D(Vector3 position = Vector3::zero, Vector3 scale = Vector3::one / 2, Color defaultColor = { 1.0f, 0.0f, 0.0f, 1.0f }, Constraint3D* constraint = NULL);

	int id = 0;
};

#endif // !JOINT2D_H

