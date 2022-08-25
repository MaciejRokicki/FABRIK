#ifndef CONSTRAINT3D_H
#define CONSTRAINT3D_H

#include "vector3.h"
#include "node.h"

class Joint3D;

class Constraint3D {
public:
	Constraint3D(float minAngle, float maxAngle);
	virtual void Apply(Node<Joint3D>* nodeJoint) = 0;
	Vector3 GetXYAngleBetweenTwoVectors(Vector3 from, Vector3 to);
protected:
	float minAngle;
	float maxAngle;
};

#endif // !CONSTRAINT3D_H