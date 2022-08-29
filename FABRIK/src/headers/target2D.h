#ifndef TARGET2D_H
#define TARGET2D_H

#include "joint2D.h"

class Target2D : public Object2D {
public:
	Node<Joint2D>* endEffector;

	Target2D(Node<Joint2D>* endEffector, Vector3 position = Vector3::zero, Vector3 scale = { 0.5f, 0.5f, 1.0f }, Color defaultColor = {0.0f, 0.0f, 1.0f, 1.0f});
};

#endif //!TARGET2D_H
