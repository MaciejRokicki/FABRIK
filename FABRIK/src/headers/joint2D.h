#ifndef JOINT2D_H
#define JOINT2D_H

#include <GL/glew.h>

#include "vector2.h"
#include "object2D.h"
#include "segment2D.h"
#include "constraint2D.h"

class Constraint2D;

class Joint2D : public Object2D {
public:
	Vector3 PositionTmp;
	bool IsSubBase = false;
	Segment2D* segment;
	Constraint2D* constraint;
	Joint2D(Vector3 position = Vector3::zero, Vector3 scale = { 0.5f, 0.5f, 1.0f }, Color default_color = {1.0f, 0.0f, 0.0f, 1.0f}, Constraint2D* constraint = NULL);

};

#endif // !JOINT2D_H

