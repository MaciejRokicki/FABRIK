#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector3.h"

class Quaternion {
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);

	static Quaternion FromEulersAngles(Vector3 angles);
	Vector3 ToEulerAngles();

	Vector3 operator *(const Vector3& vec);
	Quaternion operator *(const Quaternion& quaternion);

	friend std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion);
};

#endif // !QUATERNION_H