#include <iostream>

#include <GL/glew.h>

#include "headers/segment2D.h"
#include "headers/vertex.h"

Segment2D::Segment2D(Vector3 position, Vector3 scale, Color defaultColor) : Object2D(position, scale, defaultColor) { }