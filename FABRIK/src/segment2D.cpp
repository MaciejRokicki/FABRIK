#include <iostream>

#include <GL/glew.h>

#include "headers/segment2D.h"
#include "headers/vertex.h"

Segment2D::Segment2D(Vector3 position, Vector3 scale, Color default_color) : Object2D(position, scale, default_color) { }