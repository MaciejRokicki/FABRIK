#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>

#include "transform.h"
#include "vertex.h"
#include "mat4.h"
#include "vector3.h"
#include "camera.h"

class Object : public Transform {
public:
	Object();
	Object(Vector3 position, Vector3 scale, Color default_color);
	void Init();
	void Draw(const Camera& camera) const;
	void SetDefaultColor();
	void SetColor(Color color, bool isDefaultColor = false);
	virtual ~Object();
protected:
	Color default_color;
	Color color = Color({ 0.9f, 0.9f, 0.9f, 1.0f });
	int _vertices_size = 0;
	int _indices_size = 0;
	Vertex* _vertices;
	GLuint* _indices;
private:
	GLuint _vao = NULL;
	GLuint _vertex_buffer = NULL;
	GLuint _index_buffer = NULL;
};

#endif // !OBJECT2D_H
