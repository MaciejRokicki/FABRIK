#include <iostream>

#include "headers/hinge2D.h"
#include "headers/mathf.h"
#include "headers/segment2D.h"

Hinge2D::Hinge2D(float minAngle, float maxAngle) : Constraint2D(minAngle, maxAngle) { }

void Hinge2D::Apply(Node<Joint2D>* nodeJoint) {
	Vector2 previousJointPosition = nodeJoint->parent->value.PositionTmp;
	Vector2 currentJointPosition = nodeJoint->value.PositionTmp;

	Segment2D* currentSegment = nodeJoint->value.segment;
	Segment2D* previousSegment = nodeJoint->parent->value.segment;

	Vector2 direction = currentJointPosition - previousJointPosition;
	float angle = Mathf::Rad2Deg(atan2f(direction.y, direction.x)); // Kat wzgledem punktu (0, 0)

	// Kat osi z poprzedniego segmentu
	if (nodeJoint->parent->parent != NULL) {
		Vector2 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;
		Vector2 direction2 = previousJointPosition - previousPreviousJointPosition;
		previousSegment->constraintRotationTmp.z = Mathf::Rad2Deg(atan2f(direction2.y, direction2.x));
	}

	// Kat wzgledem poprzedniego segmentu
	angle -= previousSegment->constraintRotationTmp.z;			

	// Normalizacja wartosci katow do przedzialu 0-360
	angle = Mathf::NormalizeAngle360(angle);

	if (angle >= minAngle && angle <= maxAngle) {
		return;
	}

	angle = Mathf::ClampAngle(angle, minAngle, maxAngle);

	float length = Vector2::Distance(previousJointPosition, currentJointPosition);
	Vector2 newPosition = {
		length* cos(Mathf::Deg2Rad(angle + previousSegment->constraintRotationTmp.z)),
		length* sin(Mathf::Deg2Rad(angle + previousSegment->constraintRotationTmp.z))
	};

	currentSegment->constraintRotationTmp.z = angle;

	nodeJoint->value.PositionTmp = newPosition + previousJointPosition;
}