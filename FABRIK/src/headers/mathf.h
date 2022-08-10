#ifndef MATHF_H
#define MATHF_H

#ifndef M_PI
#define M_PI 3.14159265f
#endif

#include "vector2.h"
#include "vector3.h"

class Mathf {
public:
	static float Rad2Deg(float rad);
	static Vector3 Rad2Deg(Vector3 rad);
	static float Deg2Rad(float deg);
	static Vector3 Deg2Rad(Vector3 deg);
	static float NormalizeAngle180(float angle);
	static Vector3 NormalizeAngle180(Vector3 angle);
	static float NormalizeAngle360(float angle);
	static Vector3 NormalizeAngle360(Vector3 angle);
	static Vector2 NormalizeXYAngle90to360(Vector2 angle);
	static float ClampAngle(float angle, float minAngle, float maxAngle);
};

#endif // !MATHF_H
