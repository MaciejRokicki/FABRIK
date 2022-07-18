#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderProgram.h"
#include "mat4.h"
#include "vector2.h"
#include "vector3.h"

class Camera : public ShaderProgram {
protected:
	GLuint projectionMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint modelMatrixLocation;

	Mat4 viewMatrix;
	Mat4 projectionMatrix;

	float nearPlane;
	float farPlane;
	float width;
	float height;
public:
	Camera(float width, float height, float nearPlane, float farPlane);
	void SetModelMatrix(const Mat4& matrix) const;
	void Translate(Vector3 vector);
	void Rotate(Vector3 vector);
	Vector3 GetPosition();
	virtual void Resize(float width, float height) = 0;
	virtual Vector2 CameraToWorldPosition(double x, double y) = 0;
};

#endif // !CAMERA_H