#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "camera.h"

class OrthographicCamera : public Camera {
public:
	OrthographicCamera(float size, int width, int height, float nearPlane, float farPlane);
	void Resize(int width, int height);
	Vector2 CameraToWorldPosition(double x, double y);
private:
	float size;

	Matrix4 GetProjectionMatrix(int width, int height);
};

#endif // !ORTHOGRAPHICCAMERA_H