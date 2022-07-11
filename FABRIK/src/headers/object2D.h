#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <GL/glew.h>

#include "object.h"
#include "vertex.h"
#include "vector2.h"

class Object2D : public Object {
public:
	Object2D();
	Object2D(Vector2 position, Vector2 scale, Color default_color);
	Vector2 GetPosition() const { return { _matrix[12], _matrix[13] }; };
	Vector2 GetScale() const { return { _matrix[0], _matrix[5] }; };
};

#endif // !OBJECT2D_H
