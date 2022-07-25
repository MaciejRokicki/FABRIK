#include "headers/object2D.h"
#include "headers/color.h"

Object2D::Object2D() : Object() {
	_vertices_size = 4;
	_indices_size = 6;

	_vertices = new Vertex[_vertices_size] {
		{ { -0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ { -0.5f,  0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f,  0.5f,  0.0f, 1.0f }, color }
	};

	_indices = new GLuint[_indices_size] {
		0,1,2,  2,1,3
	};
}

Object2D::Object2D(Vector2 position, Vector2 scale, Color default_color) : Object(position, { scale.x, scale.y, 1.0f }, default_color) {
	_vertices_size = 4;
	_indices_size = 6;
	
	_vertices = new Vertex[_vertices_size] {
		{ { -0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ { -0.5f,  0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f,  0.5f,  0.0f, 1.0f }, color }
	};

	_indices = new GLuint[_indices_size] {
		0,1,2,  2,1,3
	};
}