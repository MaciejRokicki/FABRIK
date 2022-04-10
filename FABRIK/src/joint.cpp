#include <iostream>

#include <GL/glew.h>

#include "headers/joint.h"
#include "headers/vertex.h"
#include "headers/mat4.h"

Joint::Joint(Vector2 position, Vector2 scale, Color color) : Transform(position, scale) {
	Model::color = color;
}