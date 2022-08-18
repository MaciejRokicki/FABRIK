#include "headers/twist3D.h"
#include "headers/mathf.h"
#include "headers/quaternion.h"

Twist3D::Twist3D(float minAngle, float maxAngle) : Constraint3D(minAngle, maxAngle) {
	minAngleY = minAngle;
	maxAngleY = maxAngle;
}

//minAngle i maxAngle z Constraint3D dotyczy osi X
Twist3D::Twist3D(float minAngleX, float maxAngleX, float minAngleY, float maxAngleY) : Constraint3D(minAngleX, maxAngleX) {
	this->minAngleY = minAngleY;
	this->maxAngleY = maxAngleY;
}

void Twist3D::Apply(Node<Joint3D>* nodeJoint) {
	auto getAngles = [](Vector3 to, Vector3 from) {
		Vector3 direction = to - from;
		float xz = sqrtf(direction.x * direction.x + direction.z * direction.z);

		Vector2 angle = {
			Mathf::Rad2Deg(atan2(direction.y, xz)),
			Mathf::Rad2Deg(atan2(-direction.x, -direction.z))
		};

		return angle;
	};

	Vector3 previousJointPosition = nodeJoint->parent->value.PositionTmp;
	Vector3 currentJointPosition = nodeJoint->value.PositionTmp;

	Quaternion previousSegmentConstraintRotationTmp = Quaternion();
	Vector3 previousAngle = Vector3::zero;

	Vector2 angle = Mathf::NormalizeAngle360(getAngles(currentJointPosition, previousJointPosition));

	if (nodeJoint->parent->parent != NULL) {
		Vector3 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;

		previousAngle = Mathf::NormalizeAngle360(getAngles(previousJointPosition, previousPreviousJointPosition));
		previousSegmentConstraintRotationTmp = Quaternion::FromEulersAngles(previousAngle);
	}

	angle -= previousAngle;
	angle = Mathf::NormalizeAngle360(angle);

	bool inRangeX = angle.x >= minAngle && angle.x <= maxAngle;
	bool inRangeY = angle.y >= minAngleY && angle.y <= maxAngleY;

	if (inRangeX && inRangeY) {
		return;
	}
	else if (!inRangeX && inRangeY) {
		angle.x = Mathf::ClampAngle(angle.x, minAngle, maxAngle);
	}
	else if (inRangeX && !inRangeY) {
		angle.y = Mathf::ClampAngle(angle.y, minAngleY, maxAngleY);
	}
	else if(!inRangeX && !inRangeY) {
		angle.x = Mathf::ClampAngle(angle.x, minAngle, maxAngle);
		angle.y = Mathf::ClampAngle(angle.y, minAngleY, maxAngleY);
	}

	angle += previousAngle;
	angle = Mathf::NormalizeAngle360(angle);

	Quaternion newQuaternion = Quaternion::FromEulersAngles(angle);
	Vector3 direction = newQuaternion * Vector3{ 0.0f, 0.0f, -1.0f };

	float length = Vector3::Distance(previousJointPosition, currentJointPosition);
	Vector3 newTargetVector = previousJointPosition + direction * length;

	nodeJoint->value.PositionTmp = newTargetVector;
}
