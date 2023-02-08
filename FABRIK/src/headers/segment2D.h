#ifndef SEGMENT2D_H
#define SEGMENT2D_H

#include "object2D.h"

class Segment2D : public Object2D {
public:
	Segment2D(Vector3 position = Vector3::zero, Vector3 scale = { 0.5f, 0.5f, 1.0f }, Color color = {0.0f, 0.0f, 0.0f, 1.0f});
};

#endif // !SEGMENT2D_H

