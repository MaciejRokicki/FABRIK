#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderProgram.h"
#include "matrix4.h"
#include "vector2.h"
#include "vector3.h"

class Camera : public ShaderProgram {
protected:
	GLuint projectionMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint modelMatrixLocation;

	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;

	float nearPlane;
	float farPlane;
	int width;
	int height;
public:
	Camera(int width, int height, float nearPlane, float farPlane);
	void SetModelMatrix(const Matrix4& matrix) const;
	void Translate(Vector3 position);
	void Rotate(Vector3 angle);
	Vector3 GetPosition();
	virtual void Resize(int width, int height) = 0;
	virtual Vector2 CameraToWorldPosition(double x, double y) = 0;
};

#endif // !CAMERA_H