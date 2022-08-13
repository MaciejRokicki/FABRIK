#include "headers/twist3D.h"
#include "headers/mathf.h"

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

		// Kat XY wzgledem punktu (0, 0)
		Vector2 angle = Mathf::NormalizeXYAngle90to360({
			Mathf::Rad2Deg(atan2(direction.y, xz)),
			Mathf::Rad2Deg(atan2(-direction.x, -direction.z))
		});

		return angle;
	};

	Vector3 previousJointPosition = nodeJoint->parent->value.PositionTmp;
	Vector3 currentJointPosition = nodeJoint->value.PositionTmp;

	Vector3 previousSegmentConstraintRotationTmp = Vector3::zero;

	// Kat XY wzgledem punktu (0, 0) w zakresie przekonwertowanym z [-90, 90] do [0, 360]
	Vector2 angle = getAngles(currentJointPosition, previousJointPosition);

	// Kat osi XY z poprzedniego segmentu w zakresie przekonwertowanym z [-90, 90] do [0, 360]
	if (nodeJoint->parent->parent != NULL) {
		Vector3 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;

		previousSegmentConstraintRotationTmp = getAngles(previousJointPosition, previousPreviousJointPosition);
	}

	// Zmiana katow XY wzgledem poprzedniego segmentu
	angle = Mathf::NormalizeAngle360(angle - previousSegmentConstraintRotationTmp);

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

	angle = Mathf::NormalizeAngle360(angle + previousSegmentConstraintRotationTmp);

	float length = Vector3::Distance(previousJointPosition, currentJointPosition);
	Vector3 newPosition = {
		-length * sinf(Mathf::Deg2Rad(angle.y)) * cosf(Mathf::Deg2Rad(angle.x)),
		 length * sinf(Mathf::Deg2Rad(angle.x)),
		 length * cosf(Mathf::Deg2Rad(angle.y)) * cosf(Mathf::Deg2Rad(angle.x)),
	};

	nodeJoint->value.PositionTmp = newPosition + previousJointPosition;
}
