#ifndef TARGET_H
#define TARGET_H

#include "node.h"
#include "joint.h"

class Target : public Transform {
public:
	Node<Joint>* endEffector;
	Target(Node<Joint>* endEffector, Vector2 position = Vector2::zero, Vector2 scale = { 0.5f, 0.5f }, Color color = { 0.0f, 0.0f, 1.0f, 1.0f });
};

#endif //!TARGET_H
