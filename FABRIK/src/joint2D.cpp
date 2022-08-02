#include <iostream>

#include <GL/glew.h>

#include "headers/joint2D.h"
#include "headers/vertex.h"

Joint2D::Joint2D(Vector3 position, Vector3 scale, Color default_color, Constraint2D* constraint) : Object2D(position, scale, default_color) {
	this->PositionTmp = this->GetPosition();
	this->segment = new Segment2D();
	this->constraint = constraint;
}