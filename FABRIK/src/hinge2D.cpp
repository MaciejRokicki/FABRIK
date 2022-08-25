#include <iostream>

#include "headers/hinge2D.h"
#include "headers/mathf.h"
#include "headers/segment2D.h"

Hinge2D::Hinge2D(float minAngle, float maxAngle) : Constraint2D(minAngle, maxAngle) { }

void Hinge2D::Apply(Node<Joint2D>* nodeJoint) {
	Vector2 previousJointPosition = nodeJoint->parent->value.PositionTmp;
	Vector2 currentJointPosition = nodeJoint->value.PositionTmp;

	float previousSegmentConstraintRotationTmp = 0.0f;

	Vector2 direction = currentJointPosition - previousJointPosition;

	float angle = Mathf::NormalizeAngle360(
		Mathf::Rad2Deg(atan2f(direction.y, direction.x))
	); 

	if (nodeJoint->parent->parent != NULL) {
		Vector2 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;
		Vector2 direction2 = previousJointPosition - previousPreviousJointPosition;
		previousSegmentConstraintRotationTmp = Mathf::Rad2Deg(atan2f(direction2.y, direction2.x));
	}

	angle -= previousSegmentConstraintRotationTmp;

	if (angle >= minAngle && angle <= maxAngle) {
		return;
	}

	angle = Mathf::ClampAngle(angle, minAngle, maxAngle);
	angle += previousSegmentConstraintRotationTmp;

	float length = Vector2::Distance(previousJointPosition, currentJointPosition);
	Vector2 newPosition = {
		length* cos(Mathf::Deg2Rad(angle)),
		length* sin(Mathf::Deg2Rad(angle))
	};

	nodeJoint->value.PositionTmp = newPosition + previousJointPosition;
}