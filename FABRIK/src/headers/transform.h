#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>

#include <GL/glew.h>

#include "vector3.h"
#include "color.h"
#include "matrix4.h"

class Transform {
public:
	Transform();
	Transform(Vector3 positon, Vector3 scale);
	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();
	void Translate(Vector3 position);
	void SetScale(Vector3 scale);
	void Rotate(Vector3 angle);
	void LookAt(Transform& transform);
protected:
	Matrix4 _matrix;
};
#endif // !TRANSFORM_H

