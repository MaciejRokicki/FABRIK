#include "headers/target2D.h"

Target2D::Target2D(Node<Joint2D>* endEffector, Vector3 position, Vector3 scale, Color defaultColor) : Object2D(position, scale, defaultColor) {
	this->endEffector = endEffector;
}
