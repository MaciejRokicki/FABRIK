#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

#include "vertex.h"
#include "modelProgram.h"
#include "mat4.h"
#include "vector3.h"

class Model {
protected:
	Color default_color;
	Color color { 0.9f, 0.9f, 0.9f, 1.0f };
	Mat4 matrix_;
	const Vertex* vertices[4];
	const GLuint* indices[6];
	GLuint vao_;
	GLuint vertex_buffer_;
	GLuint index_buffer_;
public:
	Model();
	void Init();
	void Draw(const ModelProgram& program) const;
	~Model();
};

#endif // !MODEL_H
