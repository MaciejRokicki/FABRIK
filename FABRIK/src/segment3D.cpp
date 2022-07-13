#include <iostream>

#include <GL/glew.h>

#include "headers/segment3D.h"
#include "headers/vertex.h"
#include "headers/mat4.h"

Segment3D::Segment3D(Vector3 position, Vector3 scale, Color default_color) : Object3D(position, scale, default_color) { }