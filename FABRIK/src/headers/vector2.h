#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>

struct Vector3;

struct Vector2 {
	float x;
	float y;
	static Vector2 zero;
	static Vector2 one;
	static float Distance(Vector2 vec1, Vector2 vec2);

	bool InRange(const Vector2& vec);
	float Magnitude();
	Vector2 Normalize();

	Vector2 operator !();

	bool operator ==(const Vector2& vec);
	bool operator !=(const Vector2& vec);
	bool operator >(const Vector2& vec);
	bool operator <(const Vector2& vec);
	bool operator >=(const Vector2& vec);
	bool operator <=(const Vector2& vec);

	Vector2 operator +(const Vector2& vec);
	Vector2 operator -(const Vector2& vec);
	Vector2 operator *(const Vector2& vec);
	Vector2 operator *(const float f);
	Vector2 operator /(const Vector2& vec);
	Vector2 operator /(const float f);

	operator Vector3();

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};

#endif // !VECTOR2_H
