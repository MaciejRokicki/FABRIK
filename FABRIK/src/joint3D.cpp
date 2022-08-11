#include <iostream>

#include <GL/glew.h>

#include "headers/joint3D.h"
#include "headers/vertex.h"

Joint3D::Joint3D(Vector3 position, Vector3 scale, Color default_color, Constraint3D* constraint) : Object3D(position, scale, default_color) {
	this->PositionTmp = this->GetPosition();
	this->constraint = constraint;
}