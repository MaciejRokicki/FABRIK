#include <iostream>

#include "headers/hinge3D.h"
#include "headers/mathf.h"
#include "headers/quaternion.h"

Hinge3D::Hinge3D(Axis axis, float minAngle, float maxAngle) : Constraint3D(minAngle, maxAngle) {
	this->axis = axis;
}

void Hinge3D::Apply(Node<Joint3D>* nodeJoint) {
	Vector3 previousJointPosition = nodeJoint->parent->value.PositionTmp;
	Vector3 currentJointPosition = nodeJoint->value.PositionTmp;

	Vector3 previousAngle = Vector3::zero;
	Vector3 angle = GetXYAngleBetweenTwoVectors(previousJointPosition, currentJointPosition);

	if (nodeJoint->parent->parent != NULL) {
		Vector3 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;

		previousAngle = GetXYAngleBetweenTwoVectors(previousPreviousJointPosition, previousJointPosition);
	}

	angle = Mathf::NormalizeAngle360(angle - previousAngle);

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

	angle = Mathf::NormalizeAngle360(angle + previousAngle);

	Quaternion newQuaternion = Quaternion::FromEulersAngles(angle);
	Vector3 direction = newQuaternion * Vector3{ 0.0f, 0.0f, -1.0f };

	float length = Vector3::Distance(previousJointPosition, currentJointPosition);
	Vector3 newTargetVector = previousJointPosition + direction * length;

	nodeJoint->value.PositionTmp = newTargetVector;
}