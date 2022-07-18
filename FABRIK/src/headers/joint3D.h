#ifndef JOINT3D_H
#define JOINT3D_H

#include <GL/glew.h>

#include "vector2.h"
#include "object3D.h"
#include "mat4.h"
#include "segment3D.h"

class Joint3D : public Object3D {
public:
	Vector3 PositionTmp;
	bool IsSubBase = false;
	Segment3D* segment;
	Joint3D(Vector3 position = Vector3::zero, Vector3 scale = Vector3::one / 2, Color default_color = { 1.0f, 0.0f, 0.0f, 1.0f });
};

#endif // !JOINT2D_H

