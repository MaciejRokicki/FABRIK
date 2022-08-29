#ifndef VECTOR3_H
#define VECTOR3_H

#include <ostream>
#include <cmath>

struct Vector2;

struct Vector3 {
	float x;
	float y;
	float z;

	static Vector3 zero;
	static Vector3 one;

	static float Distance(Vector3 vec1, Vector3 vec2);

	bool InRange(const Vector3& vec);
	float Magnitude();
	Vector3 Normalize();

	Vector3 operator !();

	bool operator ==(const Vector3& vec);
	bool operator !=(const Vector3& vec);
	bool operator >(const Vector3& vec);
	bool operator <(const Vector3& vec);
	bool operator >=(const Vector3& vec);
	bool operator <=(const Vector3& vec);

	Vector3 operator +(const Vector3& vec);
	Vector3& operator +=(const Vector3& vec);
	Vector3 operator -(const Vector3& vec);
	Vector3& operator -=(const Vector3& vec);
	Vector3 operator *(const Vector3& vec);
	Vector3 operator *(const float f);
	Vector3& operator *=(const Vector3& vec);
	Vector3& operator *=(const float f);
	Vector3 operator /(const Vector3& vec);
	Vector3 operator /(const float f);
	Vector3& operator /=(const Vector3& vec);
	Vector3& operator /=(const float f);

	operator Vector2();

	friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};

#endif // !VECTOR3_H