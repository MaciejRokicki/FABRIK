#ifndef TARGET3D_H
#define TARGET3D_H

#include "node.h"
#include "joint3D.h"

class Target3D : public Object3D {
public:
	Node<Joint3D>* endEffector;
	Target3D(Node<Joint3D>* endEffector, Vector3 position = Vector3::zero, Vector3 scale = Vector3::one / 2, Color default_color = { 0.0f, 0.0f, 1.0f, 1.0f });
};

#endif //!TARGET3D_H
