#ifndef HINGE3D_H
#define HINGE3D_H

#include "constraint3D.h"
#include "joint3D.h"

enum Axis {
	X,
	Y
};

class Hinge3D : public Constraint3D {
public:
	Hinge3D(Axis axis, float minAngle, float maxAngle);
	void Apply(Node<Joint3D>* nodeJoint);
private:
	Axis axis;
};

#endif // !HINGE3D_H
