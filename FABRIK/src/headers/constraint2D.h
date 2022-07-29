#ifndef CONSTRAINT2D_H
#define CONSTRAINT2D_H

#include "vector2.h"

class Joint2D;

class Constraint2D {
protected:
	float minAngle;
	float maxAngle;
public:
	Constraint2D(float minAngle, float maxAngle);
	virtual Vector2 Apply(Joint2D previousJoint, Joint2D currentJoint) = 0;
};

#endif // !CONSTRAINT2D_H