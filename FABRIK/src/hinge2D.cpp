#include <iostream>

#include "headers/hinge2D.h"
#include "headers/mathf.h"

Hinge2D::Hinge2D(float minAngle, float maxAngle) : Constraint2D(minAngle, maxAngle) { }

void Hinge2D::Apply(Node<Joint2D>* nodeJoint) {
	Vector2 previousJointPosition = nodeJoint->parent->value.PositionTmp;
	Vector2 currentJointPosition = nodeJoint->value.PositionTmp;

	Vector2 direction = (currentJointPosition - previousJointPosition).Normalize();
	float angle = Mathf::Rad2Deg(atan2f(direction.y, direction.x));

	Vector2 newPosition;
	float length = Vector2::Distance(previousJointPosition, currentJointPosition);
	angle = angle < 0 ? angle += 360.0f : angle;

	std::cout
		<< "Position: " << currentJointPosition
		<< " Angle: " << angle
		<< std::endl
		<< std::endl;

	if (minAngle <= maxAngle) {
		if (angle >= minAngle && angle <= maxAngle) {
			return;
		}

		if (angle < minAngle) {
			newPosition.x = length * cos(Mathf::Deg2Rad(minAngle));
			newPosition.y = length * sin(Mathf::Deg2Rad(minAngle));
		}
		else if(angle > maxAngle) {
			newPosition.x = length * cos(Mathf::Deg2Rad(maxAngle));
			newPosition.y = length * sin(Mathf::Deg2Rad(maxAngle));
		}
	} 
	else {
		if (angle >= minAngle || angle <= maxAngle) {
			return;
		}

		if (fabsf(minAngle - angle) > fabsf(maxAngle - angle)) {
			newPosition.x = length * cos(Mathf::Deg2Rad(maxAngle));
			newPosition.y = length * sin(Mathf::Deg2Rad(maxAngle));
		}
		else {
			newPosition.x = length * cos(Mathf::Deg2Rad(minAngle));
			newPosition.y = length * sin(Mathf::Deg2Rad(minAngle));
		}
	}

	//Vector2 relativeTestPosition = newPosition;
	//float testAngle = atan2f(relativeTestPosition.y, relativeTestPosition.x) * 180.0f / M_PI;
	//testAngle = testAngle < 0 ? testAngle += 360.0f : testAngle;

	//std::cout
	//	<< "Test angle: " << testAngle
	//	<< std::endl;

	nodeJoint->value.PositionTmp = newPosition + previousJointPosition;
}