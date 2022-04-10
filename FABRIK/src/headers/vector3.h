#ifndef VECTOR3_H
#define VECTOR3_H

#include <ostream>

struct Vector3 {
	float x;
	float y;
	float z;

	static Vector3 zero;
	static Vector3 one;
	static float Distance(Vector3 vec1, Vector3 vec2);

	Vector3 operator !();
	friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};

#endif // !VECTOR3_H