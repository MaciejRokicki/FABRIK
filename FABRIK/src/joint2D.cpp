#include <iostream>

#include <GL/glew.h>

#include "headers/joint2D.h"
#include "headers/vertex.h"

Joint2D::Joint2D(Vector3 position, Vector3 scale, Color defaultColor, Constraint2D* constraint) : Object2D(position, scale, defaultColor) {
	this->PositionTmp = this->GetPosition();
	this->segment = new Segment2D();
	this->constraint = constraint;
}