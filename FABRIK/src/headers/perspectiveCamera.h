#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "camera.h"

class PerspectiveCamera : public Camera {
public:
	PerspectiveCamera(float fov, int width, int height, float nearPlane, float farPlane);
	void Resize(int width, int height);
	Vector2 CameraToWorldPosition(double x, double y);
private:
	float fov;

	Matrix4 GetProjectionMatrix(int width, int height);
};

#endif // !PERSPECTIVECAMERA_H