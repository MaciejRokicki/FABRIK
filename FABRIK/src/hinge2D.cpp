#include <iostream>

#include "headers/hinge2D.h"
#include "headers/joint2D.h"

Hinge2D::Hinge2D(float minAngle, float maxAngle) : Constraint2D(minAngle, maxAngle) {
}

//Vector2 newPosition;
//float length = Vector2::Distance(previousJointPosition, currentJointPosition);
//
//if (angle < minAngle) {
//	newPosition.x = length * cos(minAngle / 180.0f * M_PI);
//	newPosition.y = length * sin(minAngle / 180.0f * M_PI);
//}
//else if (angle > maxAngle) {
//	newPosition.x = length * cos(maxAngle / 180.0f * M_PI);
//	newPosition.y = length * sin(maxAngle / 180.0f * M_PI);
//}
//
//Vector2 relativeTestPosition = newPosition - previousJointPosition;
//float testAngle = atan2f(relativeTestPosition.y, relativeTestPosition.x) * 180.0f / M_PI;
//
//std::cout
//<< "Angle with parent : " << angle
//<< " Test angle: " << testAngle
//<< std::endl;
//
//return newPosition + previousJointPosition;

Vector2 Hinge2D::Apply(Transform previousJoint, Transform currentJoint) {
	Vector2 previousJointPosition = previousJoint.GetPosition();
	Vector2 currentJointPosition = currentJoint.GetPosition();
	Vector2 direction = (currentJointPosition - previousJointPosition).Normalize();
	float angle = atan2f(direction.y, direction.x) * 180.0f / M_PI;

	Vector2 newPosition;
	float length = Vector2::Distance(previousJointPosition, currentJointPosition);
	angle = angle < 0 ? angle += 360.0f : angle;

	std::cout
		<< "Angle: " << angle
		<< " dir: " << direction
		<< std::endl
		<< std::endl;

	//if (minAngle <= maxAngle) {
	//	if (angle >= minAngle && angle <= maxAngle) {
	//		return currentJointPosition;
	//	}

	//	if (angle < minAngle) {
	//		newPosition.x = length * cos(minAngle / 180.0f * M_PI);
	//		newPosition.y = length * sin(minAngle / 180.0f * M_PI);
	//	}
	//	else if(angle > maxAngle) {
	//		newPosition.x = length * cos(maxAngle / 180.0f * M_PI);
	//		newPosition.y = length * sin(maxAngle / 180.0f * M_PI);
	//	}
	//} 
	//else {
	//	if (angle >= minAngle || angle <= maxAngle) {
	//		return currentJointPosition;
	//	}

	//	if (fabsf(minAngle - angle) > fabsf(maxAngle - angle)) {
	//		newPosition.x = length * cos(minAngle / 180.0f * M_PI);
	//		newPosition.y = length * sin(minAngle / 180.0f * M_PI);
	//	}
	//	else {
	//		newPosition.x = length * cos(maxAngle / 180.0f * M_PI);
	//		newPosition.y = length * sin(maxAngle / 180.0f * M_PI);
	//	}
	//}

	//Vector2 relativeTestPosition = newPosition;
	//float testAngle = atan2f(relativeTestPosition.y, relativeTestPosition.x) * 180.0f / M_PI;

	//std::cout
	//	<< "Test angle: " << testAngle
	//	<< std::endl;

	//return newPosition + previousJointPosition;

	return currentJointPosition;
}