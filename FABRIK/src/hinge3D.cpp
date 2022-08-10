#include <iostream>

#include "headers/hinge3D.h"
#include "headers/mathf.h"
#include "headers/segment3D.h"

Hinge3D::Hinge3D(Axis axis, float minAngle, float maxAngle) : Constraint3D(minAngle, maxAngle) {
	this->axis = axis;
}

void Hinge3D::Apply(Node<Joint3D>* nodeJoint) {
	Vector3 previousJointPosition = nodeJoint->parent->value.PositionTmp;
	Vector3 currentJointPosition = nodeJoint->value.PositionTmp;

	Segment3D* currentSegment = nodeJoint->value.segment;
	Segment3D* previousSegment = nodeJoint->parent->value.segment;

	Vector3 direction = currentJointPosition - previousJointPosition;
	float xz = sqrtf(direction.x * direction.x + direction.z * direction.z);

	// Kat XY wzgledem punktu (0, 0) w zakresie przekonwertowanym z [-90, 90] do [0, 360]
	Vector2 angle = Mathf::NormalizeXYAngle90to360({
		Mathf::Rad2Deg(atan2(direction.y, xz)),
		Mathf::Rad2Deg(atan2(-direction.x, direction.z))
	});

	// Kat osi XY z poprzedniego segmentu w zakresie przekonwertowanym z [-90, 90] do [0, 360]
	if (nodeJoint->parent->parent != NULL) {
		Vector3 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;
		Vector3 direction2 = previousJointPosition - previousPreviousJointPosition;
		float xz2 = sqrtf(direction2.x * direction2.x + direction2.z * direction2.z);

		previousSegment->constraintRotationTmp = Mathf::NormalizeXYAngle90to360({
			Mathf::Rad2Deg(atan2f(direction2.y, xz2)),
			Mathf::Rad2Deg(atan2f(-direction2.x, direction2.z)),
		});
	}

	// Zmiana katow XY wzgledem poprzedniego segmentu
	angle -= previousSegment->constraintRotationTmp;

	switch (axis) {
		case Axis::X:
			if (angle.x >= minAngle && angle.x <= maxAngle) {
				return;
			}

			angle.x = Mathf::ClampAngle(angle.x, minAngle, maxAngle);
			break;

		case Axis::Y:
			if (angle.y >= minAngle && angle.y <= maxAngle) {
				return;
			}

			angle.y = Mathf::ClampAngle(angle.y, minAngle, maxAngle);
			break;
	}

	angle += previousSegment->constraintRotationTmp;

	float length = Vector3::Distance(previousJointPosition, currentJointPosition);
	Vector3 newPosition = {
		-length * sinf(Mathf::Deg2Rad(angle.y)) * cosf(Mathf::Deg2Rad(angle.x)),
		 length * sinf(Mathf::Deg2Rad(angle.x)),
		 length * cosf(Mathf::Deg2Rad(angle.y)) * cosf(Mathf::Deg2Rad(angle.x)),
	};

	nodeJoint->value.PositionTmp = newPosition + previousJointPosition;
}