#include "headers/perspectiveCamera.h"
#include "headers/mathf.h"

PerspectiveCamera::PerspectiveCamera(float fov, int width, int height, float nearPlane, float farPlane) : Camera(width, height, nearPlane, farPlane) {
	this->fov = fov;
	
	this->projectionMatrix = GetPerspectiveProjectionMatrix(width, height);

	glUseProgram(*this);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
}

void PerspectiveCamera::Resize(int width, int height) {
	this->width = width;
	this->height = height;

	this->projectionMatrix = GetPerspectiveProjectionMatrix(width, height);

	glUseProgram(*this);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
}
Vector2 PerspectiveCamera::CameraToWorldPosition(double x, double y) {
	return Vector2::zero;
}

Matrix4 PerspectiveCamera::GetPerspectiveProjectionMatrix(int width, int height) {
	float aspectRatio = (float)width / (float)height;

	float yScale = 1.0f / tan(fov * M_PI / 360.0f);
	float xScale = yScale / aspectRatio;
	float frustumLength = farPlane - nearPlane;

	float matrix[16]= {0};

	matrix[0] = xScale;
	matrix[5] = yScale;
	matrix[10] = -((farPlane + nearPlane) / frustumLength);
	matrix[11] = -1;
	matrix[14] = -((2 * nearPlane * farPlane) / frustumLength);

	return Matrix4(matrix);
}