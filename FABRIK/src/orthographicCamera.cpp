#include "headers/orthographicCamera.h"

OrthographicCamera::OrthographicCamera(float size, float width, float height, float nearPlane, float farPlane) : Camera(width, height, nearPlane, farPlane) {
	this->size = size;

	this->projectionMatrix = GetOrthographicProjectionMatrix(width, height);

	glUseProgram(*this);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
}

void OrthographicCamera::Resize(float width, float height) {
	this->width = width;
	this->height = height;

	this->projectionMatrix = GetOrthographicProjectionMatrix(width, height);

	glUseProgram(*this);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
}

Vector2 OrthographicCamera::CameraToWorldPosition(double x, double y) {
	x /= size;
	x -= (double)width / size / 2.0;
	x *= 2;
	
	y /= size;
	y -= (double)height / size / 2.0;
	y *= -2;
	
	Vector3 cameraPosition = GetPosition();

	x -= cameraPosition.x;
	y -= cameraPosition.y;
	
	return Vector2{ (float)(round(x * 10.0) / 10.0), (float)(round(y * 10.0) / 10.0) };
}

Mat4 OrthographicCamera::GetOrthographicProjectionMatrix(float width, float height) {
	float left = -width / size;
	float right = width / size;
	float bottom = -height / size;
	float top = height / size;

	float frustum_length = farPlane - nearPlane;

	projectionMatrix = Mat4(0);

	projectionMatrix.matrix[0] = 2 / (right - left);
	projectionMatrix.matrix[5] = 2 / (top - bottom);
	projectionMatrix.matrix[10] = -2 / frustum_length;
	projectionMatrix.matrix[12] = -(right + left) / (right - left);
	projectionMatrix.matrix[13] = -(top + bottom) / (top - bottom);
	projectionMatrix.matrix[14] = -(farPlane + nearPlane) / frustum_length;
	projectionMatrix.matrix[15] = 1;

	return projectionMatrix;
}