#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "camera.h"
#include "vector2.h"

class PerspectiveCamera : public Camera {
private:
	float fov;

	Matrix4 GetPerspectiveProjectionMatrix(int width, int height);
public:
	PerspectiveCamera(float fov, int width, int height, float nearPlane, float farPlane);
	void Resize(int width, int height);
	Vector2 CameraToWorldPosition(double x, double y);
};

#endif // !PERSPECTIVECAMERA_H