#include "headers/object3D.h"
#include "headers/color.h"

Object3D::Object3D() : Object() {
	verticesSize = 8;
	indicesSize = 36;

	vertices = new Vertex[verticesSize]{
		{ { -.5f, -.5f,  .5f, 1.0f }, color },
		{ { -.5f,  .5f,  .5f, 1.0f }, color },
		{ {  .5f,  .5f,  .5f, 1.0f }, color },
		{ {  .5f, -.5f,  .5f, 1.0f }, color },
		{ { -.5f, -.5f, -.5f, 1.0f }, color },
		{ { -.5f,  .5f, -.5f, 1.0f }, color },
		{ {  .5f,  .5f, -.5f, 1.0f }, color },
		{ {  .5f, -.5f, -.5f, 1.0f }, color }
	};

	indices = new GLuint[indicesSize]{
		0,1,2,  0,2,3,
		4,0,3,  4,3,7,
		4,5,1,  4,1,0,
		3,2,6,  3,6,7,
		1,5,6,  1,6,2,
		7,6,5,  7,5,4
	};
}

Object3D::Object3D(Vector3 position, Vector3 scale, Color defaultColor) : Object(position, scale, defaultColor) {
	verticesSize = 8;
	indicesSize = 36;
	
	vertices = new Vertex[verticesSize]{
		{ { -.5f, -.5f,  .5f, 1.0f }, color },
		{ { -.5f,  .5f,  .5f, 1.0f }, color },
		{ {  .5f,  .5f,  .5f, 1.0f }, color },
		{ {  .5f, -.5f,  .5f, 1.0f }, color },
		{ { -.5f, -.5f, -.5f, 1.0f }, color },
		{ { -.5f,  .5f, -.5f, 1.0f }, color },
		{ {  .5f,  .5f, -.5f, 1.0f }, color },
		{ {  .5f, -.5f, -.5f, 1.0f }, color }
	};

	indices = new GLuint[indicesSize]{
		0,1,2,  0,2,3,
		4,0,3,  4,3,7,
		4,5,1,  4,1,0,
		3,2,6,  3,6,7,
		1,5,6,  1,6,2,
		7,6,5,  7,5,4
	};
}