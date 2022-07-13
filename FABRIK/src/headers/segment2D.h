#ifndef SEGMENT2D_H
#define SEGMENT2D_H

#include <GL/glew.h>

#include "object2D.h"
#include "modelProgram.h"
#include "mat4.h"

class Segment2D : public Object2D {
public:
	Segment2D(Vector2 position = Vector2::zero, Vector2 scale = Vector2::one / 2, Color color = { 0.9f, 0.9f, 0.9f, 1.0f });
};

#endif // !SEGMENT2D_H

