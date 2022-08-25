#ifndef CONSTRAINT2D_H
#define CONSTRAINT2D_H

#include "node.h"

class Joint2D;

class Constraint2D {
public:
	Constraint2D(float minAngle, float maxAngle);
	virtual void Apply(Node<Joint2D>* nodeJoint) = 0;
protected:
	float minAngle;
	float maxAngle;
};

#endif // !CONSTRAINT2D_H