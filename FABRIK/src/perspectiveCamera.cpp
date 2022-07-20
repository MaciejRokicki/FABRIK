#include "headers/perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float nearPlane, float farPlane) : Camera(width, height, nearPlane, farPlane) {
	this->fov = fov;
	
	this->projectionMatrix = GetPerspectiveProjectionMatrix(width, height);

	glUseProgram(*this);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
}

void PerspectiveCamera::Resize(float width, float height) {
	this->width = width;
	this->height = height;

	this->projectionMatrix = GetPerspectiveProjectionMatrix(width, height);

	glUseProgram(*this);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
}

Vector2 PerspectiveCamera::CameraToWorldPosition(double x, double y) {
	return Vector2::zero;
}

Mat4 PerspectiveCamera::GetPerspectiveProjectionMatrix(float width, float height) {
	float aspectRatio = width / height;

	projectionMatrix = Mat4(0);

	float y_scale = 1.0f / tan(fov * M_PI / 360.0f);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = farPlane - nearPlane;

	projectionMatrix.matrix[0] = x_scale;
	projectionMatrix.matrix[5] = y_scale;
	projectionMatrix.matrix[10] = -((farPlane + nearPlane) / frustum_length);
	projectionMatrix.matrix[11] = -1;
	projectionMatrix.matrix[14] = -((2 * nearPlane * farPlane) / frustum_length);

	return projectionMatrix;
}