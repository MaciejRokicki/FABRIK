#ifndef JOINT2D_H
#define JOINT2D_H

#include <GL/glew.h>

#include "vector2.h"
#include "object2D.h"
#include "mat4.h"
#include "segment2D.h"
#include "constraint2D.h"

class Constraint2D;

class Joint2D : public Object2D {
public:
	Vector2 PositionTmp;
	bool IsSubBase = false;
	Segment2D* segment;
	Constraint2D* constraint;
	Joint2D(Vector2 position = Vector2::zero, Vector2 scale = Vector2::one / 2, Color default_color = { 1.0f, 0.0f, 0.0f, 1.0f }, Constraint2D* constraint = NULL);
};

#endif // !JOINT2D_H

