#include <iostream>

#include "headers/hinge3D.h"
#include "headers/mathf.h"
#include "headers/segment3D.h"
#include <iomanip>


//void Hinge3D::Apply(Node<Joint3D>* nodeJoint) {
//	Vector3 previousJointPosition = nodeJoint->parent->value.PositionTmp;
//	Vector3 currentJointPosition = nodeJoint->value.PositionTmp;
//
//	Vector3 previousSegmentConstraintRotationTmp = Vector3::zero;
//
//	Vector3 direction = currentJointPosition - previousJointPosition;
//	float xz = sqrtf(direction.x * direction.x + direction.z * direction.z);
//
//	// Kat XY wzgledem punktu (0, 0) w zakresie [-90, 90]
//	Vector2 angle = {
//		Mathf::Rad2Deg(atan2(direction.y, xz)),
//		Mathf::Rad2Deg(atan2(-direction.x, direction.z))
//	};
//
//	// Kat osi XY z poprzedniego segmentu w zakresie [-90, 90]
//	if (nodeJoint->parent->parent != NULL) {
//		Vector3 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;
//		Vector3 direction2 = previousJointPosition - previousPreviousJointPosition;
//		float xz2 = sqrtf(direction2.x * direction2.x + direction2.z * direction2.z);
//
//		previousSegmentConstraintRotationTmp = {
//			Mathf::Rad2Deg(atan2f(direction2.y, xz2)),
//			Mathf::Rad2Deg(atan2f(-direction2.x, direction2.z)),
//		};
//
//		// Zmiana katow XY wzgledem poprzedniego segmentu
//		angle -= previousSegmentConstraintRotationTmp;
//	}
//
//	angle = Mathf::NormalizeXYAngle90to360(angle);
//
//	switch (axis) {
//	case Axis::X:
//		if (angle.x >= minAngle && angle.x <= maxAngle) {
//			return;
//		}
//		angle.x = Mathf::ClampAngle(angle.x, minAngle, maxAngle);
//		break;
//
//	case Axis::Y:
//		if (angle.y >= minAngle && angle.y <= maxAngle) {
//			return;
//		}
//
//		angle.y = Mathf::ClampAngle(angle.y, minAngle, maxAngle);
//		break;
//	}
//
//	angle += Mathf::NormalizeAngle360(Mathf::NormalizeXYAngle90to360(previousSegmentConstraintRotationTmp));
//
//	float length = Vector3::Distance(previousJointPosition, currentJointPosition);
//	Vector3 newPosition = {
//		-length * sinf(Mathf::Deg2Rad(angle.y)) * cosf(Mathf::Deg2Rad(angle.x)),
//		 length * sinf(Mathf::Deg2Rad(angle.x)),
//		 length * cosf(Mathf::Deg2Rad(angle.y)) * cosf(Mathf::Deg2Rad(angle.x)),
//	};
//
//	nodeJoint->value.PositionTmp = newPosition + previousJointPosition;
//}

//void Hinge3D::Apply(Node<Joint3D>* nodeJoint) {
//	Vector3 previousJointPosition = nodeJoint->parent->value.PositionTmp;
//	Vector3 currentJointPosition = nodeJoint->value.PositionTmp;
//
//	Vector3 previousSegmentConstraintRotationTmp = Vector3::zero;
//
//	Vector3 direction = currentJointPosition - previousJointPosition;
//	float xz = sqrtf(direction.x * direction.x + direction.z * direction.z);
//
//	// Kat XY wzgledem punktu (0, 0)
//	Vector2 angle = Mathf::NormalizeXYAngle90to360({
//		Mathf::Rad2Deg(atan2(direction.y, xz)),
//		Mathf::Rad2Deg(atan2(-direction.x, -direction.z))
//		});
//
//	angle = Mathf::NormalizeAngle360(angle);
//
//	std::cout
//		<< "Angle:                 " << angle
//		<< std::endl;
//
//	// Kat osi XY z poprzedniego segmentu w zakresie [-90, 90]
//	if (nodeJoint->parent->parent != NULL) {
//		Vector3 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;
//		Vector3 direction2 = previousJointPosition - previousPreviousJointPosition;
//		float xz2 = sqrtf(direction2.x * direction2.x + direction2.z * direction2.z);
//
//		previousSegmentConstraintRotationTmp = Mathf::NormalizeXYAngle90to360({
//			Mathf::Rad2Deg(atan2f(direction2.y, xz2)),
//			Mathf::Rad2Deg(atan2f(-direction2.x, -direction2.z)),
//			});
//
//		previousSegmentConstraintRotationTmp = Mathf::NormalizeAngle360(previousSegmentConstraintRotationTmp);
//
//		// Zmiana katow XY wzgledem poprzedniego segmentu
//		angle = Mathf::NormalizeAngle360(angle - previousSegmentConstraintRotationTmp);
//	}
//
//	std::cout
//		<< "PreviousConstraintTmp: " << previousSegmentConstraintRotationTmp
//		<< std::endl
//		<< "LocalAngle:            " << angle
//		<< std::endl;
//
//	switch (axis) {
//	case Axis::X:
//		if (angle.x >= minAngle && angle.x <= maxAngle) {
//			return;
//		}
//		angle.x = Mathf::ClampAngle(angle.x, minAngle, maxAngle);
//		break;
//
//	case Axis::Y:
//		if (angle.y >= minAngle && angle.y <= maxAngle) {
//			return;
//		}
//
//		angle.y = Mathf::ClampAngle(angle.y, minAngle, maxAngle);
//		break;
//	}
//
//	std::cout
//		<< "ClampedAngle:          " << angle
//		<< std::endl;
//	angle += previousSegmentConstraintRotationTmp;
//	std::cout
//		<< "FinalAngle:            " << angle
//		<< std::endl;
//
//	angle = Mathf::Deg2Rad(angle);
//
//	float length = Vector3::Distance(previousJointPosition, currentJointPosition);
//	Vector3 newPosition = {
//		//-length * sinf(angle.y) * cosf(angle.x),
//		// length * sinf(angle.x),
//		// length * cosf(angle.y) * cosf(angle.x),
//		 length * cosf(angle.y) * sinf(angle.x),
//		 length * cosf(angle.y) * cosf(angle.x),
//		 length * sinf(angle.y),
//	};
//
//	//nodeJoint->value.PositionTmp = newPosition;
//
//	Vector3 testDirection = nodeJoint->value.PositionTmp - previousJointPosition;
//	float testXz = sqrtf(testDirection.x * testDirection.x + testDirection.z * testDirection.z);
//
//	// Kat XY wzgledem punktu (0, 0)
//	Vector2 testAngle = Mathf::NormalizeXYAngle90to360({
//		Mathf::Rad2Deg(atan2(testDirection.y, testXz)),
//		Mathf::Rad2Deg(atan2(-testDirection.x, -testDirection.z))
//		});
//
//	testAngle = Mathf::NormalizeAngle360(testAngle);
//
//	std::cout
//		<< "NewPosition:           " << newPosition
//		<< std::endl
//		<< "Length:                " << length
//		<< std::endl
//		<< "TestAngle:             " << testAngle
//		<< std::endl;
//}


Hinge3D::Hinge3D(Axis axis, float minAngle, float maxAngle) : Constraint3D(minAngle, maxAngle) {
	this->axis = axis;
}

void Hinge3D::Apply(Node<Joint3D>* nodeJoint) {
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

	Vector2 angle = getAngles(currentJointPosition, previousJointPosition);

	std::cout << "Angle: " << angle;

	// Kat osi XY z poprzedniego segmentu w zakresie [-90, 90]
	if (nodeJoint->parent->parent != NULL) {
		Vector3 previousPreviousJointPosition = nodeJoint->parent->parent->value.PositionTmp;

		previousSegmentConstraintRotationTmp = getAngles(previousJointPosition, previousPreviousJointPosition);

		std::cout << " PreviousSegmentConstraintRotationTmp: " << previousSegmentConstraintRotationTmp;
		// Zmiana katow XY wzgledem poprzedniego segmentu
		angle = Mathf::NormalizeAngle360(angle - previousSegmentConstraintRotationTmp);

		std::cout << " LocalAngle: " << angle;
	}

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

	angle = Mathf::NormalizeAngle360(angle + previousSegmentConstraintRotationTmp);

	angle = Mathf::Deg2Rad(angle);

	float length = Vector3::Distance(previousJointPosition, currentJointPosition);
	Vector3 newPosition = {
		cosf(angle.y) * cosf(angle.x),
		sinf(angle.x),
		sinf(angle.y) * cosf(angle.x),
	};

	newPosition *= length;

	//std::cout << " NewPostion: " << newPosition;

	//nodeJoint->value.PositionTmp = newPosition + previousJointPosition;

	//Vector3 testDirection = nodeJoint->value.PositionTmp - previousJointPosition;
	//float testXz = sqrtf(testDirection.x * testDirection.x + testDirection.z * testDirection.z);

	//// Kat XY wzgledem punktu (0, 0)
	//Vector2 testAngle = Mathf::NormalizeXYAngle90to360({
	//	Mathf::Rad2Deg(atan2(testDirection.y, testXz)),
	//	Mathf::Rad2Deg(atan2(-testDirection.x, -testDirection.z))
	//});

	//testAngle = Mathf::NormalizeAngle360(testAngle);

	//std::cout << " Length: " << length << " TestAngle: " << testAngle << std::endl;
}