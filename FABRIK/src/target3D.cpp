#include "headers/target3D.h"

Target3D::Target3D(Node<Joint3D>* endEffector, Vector3 position, Vector3 scale, Color default_color) : Object3D(position, scale, default_color) {
	this->endEffector = endEffector;
}
