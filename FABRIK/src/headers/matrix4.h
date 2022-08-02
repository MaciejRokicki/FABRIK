#ifndef MATRIX4_H
#define MATRIX4_H

#include "vector3.h"

class Matrix4 {
private:
	float matrix[16];
	static void MultiplyBy(const Matrix4& a, const Matrix4& b, Matrix4& resultMatrix);
public:
	Matrix4();
	Matrix4(float);
	Matrix4(float matrix[16]);
	static Matrix4 Translate(Vector3 position);
	static Matrix4 Rotate(Vector3 angle);
	static Matrix4 Scale(Vector3 scale);
	void Log();

	operator const float* () const;
	Matrix4 operator *(const Matrix4& mat);
	Matrix4& operator *=(const Matrix4& mat);
};

#endif // !MATRIX4_H