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

void Camera::SetModelMatrix(const Matrix4& matrix) const {
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, matrix);
}

void Camera::Translate(Vector3 position) {
	viewMatrix *= Matrix4::Translate(position);

	glUseProgram(*this);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, viewMatrix);
}

void Camera::Rotate(Vector3 angle) {
	Vector3 currentPosition = GetPosition();

	viewMatrix =
		Matrix4::Rotate(angle) *
		Matrix4::Translate(currentPosition);

	glUseProgram(*this);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, viewMatrix);
}

Vector3 Camera::GetPosition() {
	return Vector3{ viewMatrix[12], viewMatrix[13], viewMatrix[14] };
}
