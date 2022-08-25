#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	operator GLuint() const { return shaderProgram; }
protected:
	GLuint shaderProgram;

	GLint GetUniformLocationOrDie(const char* varName);
private:
	const char* kVertexShader = "shaders/SimpleShader.vertex.glsl";
	const char* kFragmentShader = "shaders/SimpleShader.fragment.glsl";
	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint LoadAndCompileShaderOrDie(const char* sourceFile, GLenum type);
	GLuint AttachShadersOrDie(GLuint vertexShader, GLuint fragmentShader);
};

#endif //!SHADERPROGRAM_H