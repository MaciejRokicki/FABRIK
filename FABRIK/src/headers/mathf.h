#ifndef MATHF_H
#define MATHF_H

#ifndef M_PI
#define M_PI 3.14159265f
#endif

#include "vector3.h"

class Mathf {
public:
	static float Rad2Deg(float rad);
	static Vector3 Rad2Deg(Vector3 rad);
	static float Deg2Rad(float deg);
	static Vector3 Deg2Rad(Vector3 deg);
};

#endif // !MATHF_H
