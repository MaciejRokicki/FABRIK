#ifndef CAMERAPROGRAM_H
#define CAMERAPROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderProgram.h"
#include "mat4.h"

class CameraProgram : public ShaderProgram {
public:
	void Init(const char* vertex_shader_file, const char* fragment_shader_file);
	void SetViewMatrix(const Mat4&) const;
	void SetProjectionMatrix(const Mat4&) const;
private:
	GLuint projection_matrix_location_;
	GLuint view_matrix_location_;
};

#endif // !CAMERAPROGRAM_H