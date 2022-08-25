#include <iostream>

#include "headers/matrix4.h"
#include "headers/mathf.h"

Matrix4::Matrix4() {
	for (int i = 0; i < 16; i++) {
		matrix[i] = 0;
	}

	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1;
}

Matrix4::Matrix4(float val) {
	for (int i = 0; i < 16; i++) {
		matrix[i] = val;
	}
}

Matrix4::Matrix4(float matrix[16]) {
	for (int i = 0; i < 16; i++) {
		this->matrix[i] = matrix[i];
	}
}

Matrix4 Matrix4::Translate(Vector3 position) {
	Matrix4 translateMatrix;

	translateMatrix.matrix[12] = position.x;
	translateMatrix.matrix[13] = position.y;
	translateMatrix.matrix[14] = position.z;

	return translateMatrix;
}

Matrix4 Matrix4::Rotate(Vector3 angle) {
	Vector3 radians = Mathf::Deg2Rad(angle);

	float xSin = sinf(radians.x);
	float xCos = cosf(radians.x);
	float ySin = sinf(radians.y);
	float yCos = cosf(radians.y);
	float zSin = sinf(radians.z);
	float zCos = cosf(radians.z);

	Matrix4 xRotation;
	Matrix4 yRotation;
	Matrix4 zRotation;

	xRotation.matrix[5] = xCos;
	xRotation.matrix[6] = -xSin;
	xRotation.matrix[9] = xSin;
	xRotation.matrix[10] = xCos;

	yRotation.matrix[0] = yCos;
	yRotation.matrix[2] = ySin;
	yRotation.matrix[8] = -ySin;
	yRotation.matrix[10] = yCos;

	zRotation.matrix[0] = zCos;
	zRotation.matrix[1] = -zSin;
	zRotation.matrix[4] = zSin;
	zRotation.matrix[5] = zCos;

	return xRotation * yRotation * zRotation;
}

Matrix4 Matrix4::Scale(Vector3 scale) {
	Matrix4 scaleMatrix;

	scaleMatrix.matrix[0] = scale.x;
	scaleMatrix.matrix[5] = scale.y;
	scaleMatrix.matrix[10] = scale.z;

	return scaleMatrix;
}

void Matrix4::Log() {
	for (int i = 0; i < 16; i++) {
		std::cout << matrix[i] << ' ';

		if (i % 4 == 3) {
			std::cout << std::endl;
		}
	}
}

Matrix4::operator const float* () const {
	return matrix;
}

void Matrix4::MultiplyBy(const Matrix4& m1, const Matrix4& m2, Matrix4& resultMatrix) {
	unsigned int row, column, row_offset;

	for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4) {
		for (column = 0; column < 4; ++column) {
			resultMatrix.matrix[row_offset + column] =
				(m1.matrix[row_offset + 0] * m2.matrix[column + 0]) +
				(m1.matrix[row_offset + 1] * m2.matrix[column + 4]) +
				(m1.matrix[row_offset + 2] * m2.matrix[column + 8]) +
				(m1.matrix[row_offset + 3] * m2.matrix[column + 12]);
		}
	}
}

Matrix4 Matrix4::operator*(const Matrix4& mat) {
	Matrix4 resultMatrix;
	Matrix4::MultiplyBy(*this, mat, resultMatrix);

	return resultMatrix;
}

Matrix4& Matrix4::operator*=(const Matrix4& mat) {
	Matrix4::MultiplyBy(*this, mat, *this);

	return *this;
}
