#include "headers/orthographicCamera.h"

OrthographicCamera::OrthographicCamera(float size, int width, int height, float nearPlane, float farPlane) : Camera(width, height, nearPlane, farPlane) {
	this->size = size;

	this->projectionMatrix = GetProjectionMatrix(width, height);

	glUseProgram(*this);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
}

void OrthographicCamera::Resize(int width, int height) {
	this->width = width;
	this->height = height;

	this->projectionMatrix = GetProjectionMatrix(width, height);

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

Matrix4 OrthographicCamera::GetProjectionMatrix(int width, int height) {
	float left = -width / size;
	float right = width / size;
	float bottom = -height / size;
	float top = height / size;

	float matrix[16] = {0};
	
	matrix[0] = 2 / (right - left);
	matrix[3] = -(right + left) / (right - left);
	matrix[5] = 2 / (top - bottom);
	matrix[7] = -(top + bottom) / (top - bottom);
	matrix[10] = -2 / (farPlane - nearPlane);
	matrix[11] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	matrix[15] = 1;

	Matrix4 projectionMatrix = Matrix4(matrix);

	return projectionMatrix;
}