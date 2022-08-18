#include "headers/constraint3D.h"
#include "headers/mathf.h"

Constraint3D::Constraint3D(float minAngle, float maxAngle) {
	this->minAngle = minAngle;
	this->maxAngle = maxAngle;
}

Vector3 Constraint3D::GetXYAngleBetweenTwoVectors(Vector3 from, Vector3 to) {
	Vector3 direction = to - from;
	float xz = sqrtf(direction.x * direction.x + direction.z * direction.z);

	Vector3 angle = {
		Mathf::Rad2Deg(atan2(direction.y, xz)),
		Mathf::Rad2Deg(atan2(-direction.x, -direction.z))
	};

	angle = Mathf::NormalizeAngle360(angle);

	return angle;
}
