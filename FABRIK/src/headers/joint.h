#ifndef JOINT_H
#define JOINT_H

#include <GL/glew.h>

#include "vector2.h"
#include "transform.h"
#include "modelProgram.h"
#include "mat4.h"
#include "segment.h"

class Joint : public Transform {
public:
	Vector2 Position;
	bool IsSubBase;
	Segment* segment;
	Joint(Vector2 position = Vector2::zero, Vector2 scale = { 0.5f, 0.5f }, Color color = { 1.0f, 0.0f, 0.0f, 1.0f });
};

#endif // !JOINT_H

