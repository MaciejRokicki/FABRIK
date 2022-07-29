#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "camera.h"
#include "vector2.h"

class OrthographicCamera : public Camera {
private:
	float size;

	Mat4 GetOrthographicProjectionMatrix(int width, int height);
public:
	OrthographicCamera(float size, int width, int height, float nearPlane, float farPlane);
	void Resize(int width, int height);
	Vector2 CameraToWorldPosition(double x, double y);
};

#endif // !ORTHOGRAPHICCAMERA_H