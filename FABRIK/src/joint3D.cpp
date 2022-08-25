#include "headers/joint3D.h"

Joint3D::Joint3D(Vector3 position, Vector3 scale, Color defaultColor, Constraint3D* constraint) : Object3D(position, scale, defaultColor) {
	this->PositionTmp = this->GetPosition();
	this->constraint = constraint;
}