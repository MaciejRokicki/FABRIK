#include <iostream>
#include <cmath>

#include "headers/mat4.h"

using namespace std;

Mat4::Mat4() {
	for (int i = 0; i < 16; i++) {
		matrix[i] = 0;
	}

	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1;
}

Mat4::Mat4(float val)
{
	for (int i = 0; i < 16; i++)
	{
		matrix[i] = val;
	}
}

void Mat4::RotateX(float degrees)
{
	Mat4 rotation;
	float radians = degrees * M_PI / 180.0f;
	float sine = (float)sin(radians);
	float cosine = (float)cos(radians);

	rotation.matrix[5] = cosine;
	rotation.matrix[6] = -sine;
	rotation.matrix[9] = sine;
	rotation.matrix[10] = cosine;

	MultiplyBy(rotation);
}

void Mat4::RotateY(float degrees)
{
	Mat4 rotation;
	float radians = degrees * M_PI / 180.0f;
	float sine = (float)sin(radians);
	float cosine = (float)cos(radians);

	rotation.matrix[0] = cosine;
	rotation.matrix[2] = sine;
	rotation.matrix[8] = -sine;
	rotation.matrix[10] = cosine;

	MultiplyBy(rotation);
}

void Mat4::RotateZ(float degrees)
{
	Mat4 rotation;
	float radians = degrees * M_PI / 180.0f;
	float sine = (float)sin(radians);
	float cosine = (float)cos(radians);

	rotation.matrix[0] = cosine;
	rotation.matrix[1] = -sine;
	rotation.matrix[4] = sine;
	rotation.matrix[5] = cosine;

	MultiplyBy(rotation);
}

void Mat4::Scale(float x, float y, float z) {
	Mat4 scale;

	scale.matrix[0] = x;
	scale.matrix[5] = y;
	scale.matrix[10] = z;

	for (int i = 0; i < 16; i++) {
		matrix[i] = scale[i];
	}
}

void Mat4::Translate(float x, float y, float z)
{
	Mat4 translate;

	translate.matrix[12] = x;
	translate.matrix[13] = y;
	translate.matrix[14] = z;

	MultiplyBy(translate);
}

void Mat4::MultiplyBy(const Mat4& matrix) {
	float new_matrix[16];
	unsigned int row, column, row_offset;

	for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4) {
		for (column = 0; column < 4; ++column) {
			new_matrix[row_offset + column] =
				(this->matrix[row_offset + 0] * matrix.matrix[column + 0]) +
				(this->matrix[row_offset + 1] * matrix.matrix[column + 4]) +
				(this->matrix[row_offset + 2] * matrix.matrix[column + 8]) +
				(this->matrix[row_offset + 3] * matrix.matrix[column + 12]);
		}
	}

	for (int i = 0; i < 16; i++) {
		this->matrix[i] = new_matrix[i];
	}
}

void Mat4::SetUnitMatrix() {
	for (int i = 0; i < 16; i++) {
		matrix[i] = 0;
	}

	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1;
}

void Mat4::Log() {
	for (int i = 0; i < 16; i++) {
		cout << matrix[i] << ' ';
		if (i % 4 == 3) {
			cout << endl;
		}
	}
}