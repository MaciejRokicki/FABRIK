#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>

#include <GL/glew.h>

#include "vector3.h"
#include "color.h"
#include "mat4.h"

class Transform {
public:
	Transform();
	Transform(Vector3 positon, Vector3 scale);
	Vector3 GetPosition() const { return { _matrix[12], _matrix[13], _matrix[14] }; };
	Vector3 GetScale() const { return { _matrix[0], _matrix[5], _matrix[10] }; };
	void Translate(Vector3 position);
	void SetScale(Vector3 scale);
	void Rotate(Vector3 angle);
	void LookAt(Transform& transform);
protected:
	Mat4 _matrix;
};
#endif // !TRANSFORM_H

