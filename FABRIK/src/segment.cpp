#include <iostream>

#include <GL/glew.h>

#include "headers/segment.h"
#include "headers/vertex.h"
#include "headers/mat4.h"

Segment::Segment(Vector2 position, Vector2 scale, Color color) : Transform(position, scale) {
	Model::color = color;
}