#include <iostream>

#include <GL/glew.h>

#include "headers/joint2D.h"
#include "headers/vertex.h"
#include "headers/mat4.h"

Joint2D::Joint2D(Vector2 position, Vector2 scale, Color default_color) : Object2D(position, scale, default_color) {
	this->PositionTmp = this->GetPosition();
	this->segment = new Segment2D();
}