#include "headers/mathf.h"

float Mathf::Rad2Deg(float rad) {
	return rad * 180.0f / M_PI;
}

float Mathf::Deg2Rad(float deg) {
	return deg / 180.0f * M_PI;
}
