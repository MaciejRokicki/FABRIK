#ifndef CONSTRAINT2D_H
#define CONSTRAINT2D_H

#include "vector2.h"
#include "node.h"

class Joint2D;

class Constraint2D {
protected:
	float minAngle;
	float maxAngle;
public:
	Constraint2D(float minAngle, float maxAngle);
	virtual void Apply(Node<Joint2D>* nodeJoint) = 0;
};

#endif // !CONSTRAINT2D_H