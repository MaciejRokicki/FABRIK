#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>

#include <GL/glew.h>

#include "vector3.h"
#include "color.h"
#include "mat4.h"

class Transform {
private:
	Vector3 rotation = Vector3::zero;
public:
	Mat4 _matrix;
	Transform();
	Transform(Vector3 positon, Vector3 scale);
	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();
	void Translate(Vector3 position);
	void SetScale(Vector3 scale);
	void Rotate(Vector3 angle);
	void LookAt2D(Transform& transform);
	void LookAt3D(Transform& transform);
protected:

};
#endif // !TRANSFORM_H

