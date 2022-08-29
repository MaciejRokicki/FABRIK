#ifndef HINGE2D_H
#define HINGE2D_H

#include <cmath>

#include "constraint2D.h"
#include "joint2D.h"

class Hinge2D : public Constraint2D {
public:
	Hinge2D(float minAngle, float maxAngle);
	void Apply(Node<Joint2D>* nodeJoint);
};

#endif // !HINGE2D_H
