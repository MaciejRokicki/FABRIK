#include <iostream>

#include <GL/glew.h>

#include "headers/joint3D.h"
#include "headers/vertex.h"

Joint3D::Joint3D(Vector3 position, Vector3 scale, Color defaultColor, Constraint3D* constraint) : Object3D(position, scale, defaultColor) {
	this->PositionTmp = this->GetPosition();
	this->constraint = constraint;
}