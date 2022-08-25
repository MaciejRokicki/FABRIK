#include "headers/object2D.h"
#include "headers/color.h"
#include "headers/mathf.h"

Object2D::Object2D() : Object() {
	verticesSize = 4;
	indicesSize = 6;

	vertices = new Vertex[verticesSize] {
		{ { -0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ { -0.5f,  0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f,  0.5f,  0.0f, 1.0f }, color }
	};

	indices = new GLuint[indicesSize] {
		0,1,2,  2,1,3
	};
}

Object2D::Object2D(Vector3 position, Vector3 scale, Color defaultColor) : Object(position, scale, defaultColor) {
	verticesSize = 4;
	indicesSize = 6;
	
	vertices = new Vertex[verticesSize] {
		{ { -0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ { -0.5f,  0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f, -0.5f,  0.0f, 1.0f }, color },
		{ {  0.5f,  0.5f,  0.0f, 1.0f }, color }
	};

	indices = new GLuint[indicesSize] {
		0,1,2,  2,1,3
	};
}

void Object2D::LookAt(Transform& transform) {
	Vector3 currentPosition = GetPosition();
	Vector3 currentScale = GetScale();
	Vector3 targetPosition = transform.GetPosition();

	Vector3 vec = targetPosition - currentPosition;

	Vector3 angles = Mathf::Rad2Deg(Vector3{
		0.0f,
		0.0f,
		atan2f(vec.x, vec.y)
	});

	this->_matrix =
		Matrix4::Scale(currentScale) *
		Matrix4::Rotate(angles) *
		Matrix4::Translate(currentPosition);
}