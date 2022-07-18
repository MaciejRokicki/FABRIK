#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "camera.h"
#include "vector2.h"

class OrthographicCamera : public Camera {
private:
	float size;

	Mat4 GetOrthographicProjectionMatrix(float width, float height);
public:
	OrthographicCamera(float size, float width, float height, float nearPlane, float farPlane);
	void Resize(float width, float height);
	Vector2 CameraToWorldPosition(double x, double y);
};

#endif // !ORTHOGRAPHICCAMERA_H