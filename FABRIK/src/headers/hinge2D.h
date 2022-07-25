#ifndef HINGE2D_H
#define HINGE2D_H

#include "constraint2D.h"
#include "joint2D.h"

class Hinge2D : public Constraint2D {
public:
	Hinge2D(float minAngle, float maxAngle);
	Vector2 Apply(Vector3 rotation, Vector2 previousJointPosition, Vector2 currentJointPosition);
};

#endif // !HINGE2D_H
