#include <iostream>

#include "headers/hinge2D.h"

Hinge2D::Hinge2D(Vector3 axis) : Constraint2D(axis) {
}

Vector2 Hinge2D::Apply(Vector2 previousJointPosition, Vector2 currentJointPosition) {
	Vector2 direction = (currentJointPosition - previousJointPosition).Normalize();
	float angle = atan2f(direction.y, direction.x) * 180.0f / M_PI;

	if (angle < 0) {
		angle += 360.0f;
	}

	if (axis.z >= angle) {
		return currentJointPosition;
	} else {
		Vector2 newPosition;
		float length = Vector2::Distance(previousJointPosition, currentJointPosition);

		if (angle <= 270.0f) {
			newPosition.x = length * cos(axis.z / 180.0f * M_PI);
			newPosition.y = length * sin(axis.z / 180.0f * M_PI);
		}
		else {
			newPosition.x = length * cos(0.0f / 180.0f * M_PI);
			newPosition.y = length * sin(0.0f / 180.0f * M_PI);
		}

		//Vector2 relativeTestPosition = newPosition - previousJointPosition;
		//float testAngle = atan2f(relativeTestPosition.y, relativeTestPosition.x) * 180.0f / M_PI;

		//std::cout
		//	<< "Current joint position: (" << currentJointPosition
		//	<< ") Previous joint position (" << previousJointPosition
		//	<< ") Direction: (" << direction
		//	<< ") Angle with parent : " << angle
		//	<< " Test angle: " << testAngle
		//	<< std::endl;

		return newPosition + previousJointPosition;
	}
}