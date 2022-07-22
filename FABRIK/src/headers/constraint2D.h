#ifndef CONSTRAINT2D_H
#define CONSTRAINT2D_H

#include "vector2.h"
#include "node.h"

class Constraint2D {
protected:
	Vector3 axis;
public:
	Constraint2D(Vector3 axis);
	virtual Vector2 Apply(Vector2 previousJointPosition, Vector2 currentJointPosition) = 0;
};

#endif // !CONSTRAINT2D_H
