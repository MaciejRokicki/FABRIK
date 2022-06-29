#include "headers/target.h"

Target::Target(Node<Joint>* endEffector, Vector2 position, Vector2 scale, Color color) : Transform(position, scale) {
	Model::color = color;
	Model::default_color = color;
	this->endEffector = endEffector;
}
