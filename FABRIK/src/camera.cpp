#include <cmath>

#include "headers/camera.h"

Camera::Camera(int width, int height, float nearPlane, float farPlane) : ShaderProgram() {
	this->width = width;
	this->height = height;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;

	projectionMatrixLocation = GetUniformLocationOrDie("projection_matrix");
	viewMatrixLocation = GetUniformLocationOrDie("view_matrix");
	modelMatrixLocation = GetUniformLocationOrDie("model_matrix");

	glUseProgram(*this);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, viewMatrix);
}

void Camera::SetModelMatrix(const Mat4& matrix) const {
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, matrix);
}

void Camera::Translate(Vector3 vector) {
	viewMatrix.Translate(vector.x, vector.y, vector.z);

	glUseProgram(*this);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, viewMatrix);
}

void Camera::Rotate(Vector3 vector) {
	Vector3 tmp_vector = GetPosition();

	Translate(!tmp_vector);

	viewMatrix.RotateX(vector.x);
	viewMatrix.RotateY(vector.y);
	viewMatrix.RotateZ(vector.z);

	Translate(tmp_vector);
}

Vector3 Camera::GetPosition() {
	return Vector3{ viewMatrix[12], viewMatrix[13], viewMatrix[14] };
}
