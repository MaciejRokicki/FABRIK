#ifndef TWIST3D_H
#define TWIST3D_H

#include "constraint3D.h"
#include "joint3D.h"

class Twist3D : public Constraint3D {
public:
	Twist3D(float minAngle, float maxAngle);
	Twist3D(float minAngleX, float maxAngleX, float minAngleY, float maxAngleY);
	void Apply(Node<Joint3D>* nodeJoint);
private:
	float minAngleY;
	float maxAngleY;
};

#endif // !TWIST3D_H
