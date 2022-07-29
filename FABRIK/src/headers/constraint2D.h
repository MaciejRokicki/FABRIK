#ifndef CONSTRAINT2D_H
#define CONSTRAINT2D_H

#include "vector2.h"
#include "transform.h"

class Constraint2D {
protected:
	float minAngle;
	float maxAngle;
public:
	Constraint2D(float minAngle, float maxAngle);
	virtual Vector2 Apply(Transform previousJointPosition, Transform currentJointPosition) = 0;
};

#endif // !CONSTRAINT2D_H