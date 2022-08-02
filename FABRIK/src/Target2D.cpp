#include "headers/target2D.h"

Target2D::Target2D(Node<Joint2D>* endEffector, Vector3 position, Vector3 scale, Color default_color) : Object2D(position, scale, default_color) {
	this->endEffector = endEffector;
}
