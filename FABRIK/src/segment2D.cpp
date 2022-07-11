#include <iostream>

#include <GL/glew.h>

#include "headers/segment2D.h"
#include "headers/vertex.h"
#include "headers/mat4.h"

Segment2D::Segment2D(Vector2 position, Vector2 scale, Color default_color) : Object2D(position, scale, default_color) { }