#ifndef SEGMENT_H
#define SEGMENT_H

#include <GL/glew.h>

#include "transform.h"
#include "modelProgram.h"
#include "mat4.h"

class Segment : public Transform {
public:
	Segment(Vector2 position = Vector2::zero, Vector2 scale = { 0.5f, 0.5f }, Color color = { 0.9f, 0.9f, 0.9f, 1.0f });
};

#endif // !SEGMENT_H

