#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>

#include "transform.h"
#include "vertex.h"
#include "vector3.h"
#include "camera.h"

class Object : public Transform {
public:
	Object();
	Object(Vector3 position, Vector3 scale, Color defaultColor);
	void Init();
	void Draw(const Camera& camera) const;
	void SetDefaultColor();
	void SetColor(Color color, bool isDefaultColor = false);
	virtual ~Object();
protected:
	Color defaultColor;
	Color color = Color({ 0.9f, 0.9f, 0.9f, 1.0f });
	int verticesSize = 0;
	int indicesSize = 0;
	Vertex* vertices = 0;
	GLuint* indices = 0;
private:
	GLuint vao = 0;
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
};

#endif // !OBJECT2D_H
