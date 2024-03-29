#ifndef TARGET3D_H
#define TARGET3D_H

#include "joint3D.h"

class Target3D : public Object3D {
public:
	Node<Joint3D>* endEffector;

	Target3D(Node<Joint3D>* endEffector, Vector3 position = Vector3::zero, Vector3 scale = { 0.5f, 0.5f, 1.0f }, Color defaultColor = { 0.0f, 0.0f, 1.0f, 1.0f });
};

#endif //!TARGET3D_H
