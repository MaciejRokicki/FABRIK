#include <iostream>

#include "headers/hinge3D.h"
#include "headers/mathf.h"
#include "headers/segment3D.h"
#include "headers/quaternion.h"

Hinge3D::Hinge3D(Axis axis, float minAngle, float maxAngle) : Constraint3D(minAngle, maxAngle) {
	this->axis = axis;
}

void Hinge3D::Apply(Node<Joint3D>* nodeJoint) {
	auto getAngles = [](Vector3 to, Vector3 from) {
		Vector3 direction = to - from;
		float xz = sqrtf(direction.x * direction.x + direction.z * direction.z);

		// Kat XY wzgledem punktu (0, 0)
		Vector3 angle = {
			Mathf::Rad2Deg(atan2(direction.y, xz)),
			Mathf::Rad2Deg(atan2(-direction.x, -direction.z))
		};

		return angle;
	};

	Vector3 previousJointPosition = nodeJoint->parent->value.PositionTmp;
	Vector3 currentJointPosition = nodeJoint->value.PositionTmp;

	Quaternion previousSegmentConstraintRotationTmp = Quaternion();
	Vector3 previousAngle = Vector3::zero;

	Vector3 angle = Mathf::NormalizeAngle360(getAngles(currentJointPosition, previousJointPosition));

	if (nodeJoint->parent->parent != NULL) {
		Vector3 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;

		previousAngle = Mathf::NormalizeAngle360(getAngles(previousJointPosition, previousPreviousJointPosition));
		previousSegmentConstraintRotationTmp = Quaternion::FromEulersAngles(previousAngle);
	}

	angle -= previousAngle;
	angle = Mathf::NormalizeAngle360(angle);

	switch (axis) {
		case Axis::X:
			if (angle.x >= minAngle && angle.x <= maxAngle) {
				return;
			}

			angle.x = Mathf::ClampAngle(angle.x, minAngle, maxAngle);
			angle.y = 0.0f;
			break;

		case Axis::Y:
			if (angle.y >= minAngle && angle.y <= maxAngle) {
				return;
			}

			angle.x = 0.0f;
			angle.y = Mathf::ClampAngle(angle.y, minAngle, maxAngle);
			break;
	}

	angle += previousAngle;
	angle = Mathf::NormalizeAngle360(angle);

	Quaternion newQuaternion = Quaternion::FromEulersAngles(angle);
	Vector3 direction = newQuaternion * Vector3{ 0.0f, 0.0f, -1.0f };

	float length = Vector3::Distance(previousJointPosition, currentJointPosition);
	Vector3 newTargetVector = previousJointPosition + direction * length;

	nodeJoint->value.PositionTmp = newTargetVector;
}