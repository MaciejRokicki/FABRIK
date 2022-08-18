#include "headers/mathf.h"
#include <iostream>

float Mathf::Rad2Deg(float rad) {
	rad = rad * 180.0f / M_PI;

	return rad;
}

Vector3 Mathf::Rad2Deg(Vector3 rad) {
	rad.x = Rad2Deg(rad.x);
	rad.y = Rad2Deg(rad.y);
	rad.z = Rad2Deg(rad.z);

	return rad;
}

float Mathf::Deg2Rad(float deg) {
	deg = deg / 180.0f * M_PI;

	return deg;
}

Vector3 Mathf::Deg2Rad(Vector3 deg) {
	deg.x = Deg2Rad(deg.x);
	deg.y = Deg2Rad(deg.y);
	deg.z = Deg2Rad(deg.z);

	return deg;
}

float Mathf::NormalizeAngle180(float angle) {
	if (angle >= 180.0f)
		return angle - 360.0f;

	if (angle < -180.0f)
		return angle + 360.0f;

	return angle;
}

Vector3 Mathf::NormalizeAngle180(Vector3 angle) {
	angle.x = NormalizeAngle180(angle.x);
	angle.y = NormalizeAngle180(angle.y);
	angle.z = NormalizeAngle180(angle.z);

	return angle;
}

float Mathf::NormalizeAngle360(float angle) {
	if (angle >= 360.0f)
		return angle - 360.0f;

	if (angle < 0)
		return angle + 360.0f;

	return angle;
}

Vector3 Mathf::NormalizeAngle360(Vector3 angle) {
	angle.x = NormalizeAngle360(angle.x);
	angle.y = NormalizeAngle360(angle.y);
	angle.z = NormalizeAngle360(angle.z);

	return angle;
}

float Mathf::ClampAngle(float angle, float minAngle, float maxAngle) {
	float min = NormalizeAngle180(minAngle - angle);
	float max = NormalizeAngle180(maxAngle - angle);

	if (min <= 0 && max>= 0)
		return angle;

	if (fabsf(min) < fabsf(max))
		return minAngle;

	return maxAngle;
}