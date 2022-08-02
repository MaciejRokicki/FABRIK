#include "headers/mathf.h"

float Mathf::Rad2Deg(float rad) {
	return rad * 180.0f / M_PI;
}

Vector3 Mathf::Rad2Deg(Vector3 rad) {
	rad.x = Rad2Deg(rad.x);
	rad.y = Rad2Deg(rad.y);
	rad.z = Rad2Deg(rad.z);

	return rad;
}

float Mathf::Deg2Rad(float deg) {
	return deg / 180.0f * M_PI;
}

Vector3 Mathf::Deg2Rad(Vector3 deg) {
	deg.x = Deg2Rad(deg.x);
	deg.y = Deg2Rad(deg.y);
	deg.z = Deg2Rad(deg.z);

	return deg;
}
