#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>

#include <GL/glew.h>

#include "model.h"
#include "vector2.h"
#include "vector3.h"
#include "color.h"
#include "mat4.h"

class Transform : public Model {
public:
	Vector2 GetPosition() const { return { matrix_[12], matrix_[13] }; };
	Vector2 GetScale() const { return { matrix_[0], matrix_[5] }; };
	Transform(Vector2 positon, Vector2 scale);
	void SetColor(Color color);
	void Translate(Vector2 position);
	void Translate(Vector3 position);
	void Scale(Vector2 scale);
	void Rotate(Vector3 angle);
	void LookAt(Transform& transform);
};
#endif // !TRANSFORM_H

