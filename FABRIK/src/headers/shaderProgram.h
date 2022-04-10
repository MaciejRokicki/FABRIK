#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>

class ShaderProgram {
public:
	void Init(const char* vertex_shader_file, const char* fragment_shader_file);
	operator GLuint() const { return shader_program_; }
	~ShaderProgram();
protected:
	GLuint shader_program_;
	GLint GetUniformLocationOrDie(const char*);
private:
	GLuint vertex_shader_;
	GLuint fragment_shader_;
	GLuint LoadAndCompileShaderOrDie(const char* source_file, GLenum type);
	GLuint AttachShadersOrDie(GLuint vertex_shader, GLuint fragment_shader);
};

#endif //!SHADERPROGRAM_H