#ifndef SEGMENT3D_H
#define SEGMENT3D_H

#include "object3D.h"

class Segment3D : public Object3D {
public:
	Segment3D(Vector3 position = Vector3::zero, Vector3 scale = Vector3::one / 2, Color color = { 0.9f, 0.9f, 0.9f, 1.0f });
};

#endif // !SEGMENT2D_H

