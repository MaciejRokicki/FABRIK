#include "headers/object2D.h"
#include "headers/color.h"

Object2D::Object2D() : Object() { 
	_vertices = new Vertex[4]{
		{ { -0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ { -0.5f,  0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f,  0.5f,  0.0f, 1.0f }, color }
	};

	_indices = new GLuint[6] {
		0,1,2,  2,1,3
	};
}

Object2D::Object2D(Vector2 position, Vector2 scale, Color default_color) : Object({ position.x, position.y, 0.0f }, { scale.x, scale.y, 0.0f }, default_color) {
	_vertices = new Vertex[4] {
		{ { -0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ { -0.5f,  0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f,  0.5f,  0.0f, 1.0f }, color }
	};

	_indices = new GLuint[6] {
		0,1,2,  2,1,3
	};
}