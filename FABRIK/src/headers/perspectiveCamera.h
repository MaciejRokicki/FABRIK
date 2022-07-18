#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "camera.h"
#include "vector2.h"

class PerspectiveCamera : public Camera {
private:
	float fov;

	Mat4 GetPerspectiveProjectionMatrix(float width, float height);
public:
	PerspectiveCamera(float fov, float width, float height, float nearPlane, float farPlane);
	void Resize(float width, float height);
	Vector2 CameraToWorldPosition(double x, double y);
};

#endif // !PERSPECTIVECAMERA_H