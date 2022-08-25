#include <iostream>

#include <GL/glew.h>

#include "headers/segment3D.h"
#include "headers/vertex.h"

Segment3D::Segment3D(Vector3 position, Vector3 scale, Color defaultColor) : Object3D(position, scale, defaultColor) { }