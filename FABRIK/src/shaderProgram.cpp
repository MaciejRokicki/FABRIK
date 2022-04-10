#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "headers/shaderProgram.h";

using namespace std;

void ShaderProgram::Init(const char* vertex_shader_file, const char* fragment_shader_file) {
	vertex_shader_ = LoadAndCompileShaderOrDie(vertex_shader_file, GL_VERTEX_SHADER);
	fragment_shader_ = LoadAndCompileShaderOrDie(fragment_shader_file, GL_FRAGMENT_SHADER);

	shader_program_ = AttachShadersOrDie(vertex_shader_, fragment_shader_);

	glUseProgram(shader_program_);
	glUseProgram(0);
}

GLuint ShaderProgram::LoadAndCompileShaderOrDie(const char* source_file, GLenum type) {
    int file_size;
    char* shader_code;
    GLuint shader = glCreateShader(type);
    ifstream file(source_file, ios::in | ios::ate | ios::binary);

    if (file.is_open()) {
        file_size = file.tellg();
        shader_code = new char[file_size + 1];
        file.seekg(0, ios::beg);
        file.read(shader_code, file_size);
        shader_code[file_size] = '\0';
        file.close();

        glShaderSource(shader, 1, (const GLchar**)&shader_code, NULL);
        glCompileShader(shader);
        delete[] shader_code;
    }
    else {
        cerr << "Could not open the file " << source_file << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        switch (type) {
            case GL_VERTEX_SHADER:
                std::cerr << "vertex ";
                break;

            case GL_FRAGMENT_SHADER:
                std::cerr << "fragment ";
                break;
        }

        std::cerr << "shader is failed to compile:" << std::endl;
        GLint  log_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char* log_msg = new char[static_cast<GLuint>(log_size)];
        glGetShaderInfoLog(shader, log_size, nullptr, log_msg);
        std::cerr << log_msg << std::endl;
        delete[] log_msg;

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return shader;
}

GLuint ShaderProgram::AttachShadersOrDie(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint new_program = glCreateProgram();

    glAttachShader(new_program, vertex_shader);
    glAttachShader(new_program, fragment_shader);

    glLinkProgram(new_program);

    GLint linked;
    glGetProgramiv(new_program, GL_LINK_STATUS, &linked);

    if (!linked) {
        std::cerr << "Shader program failed to link" << std::endl;

        GLint  log_size;
        glGetProgramiv(new_program, GL_INFO_LOG_LENGTH, &log_size);

        char* log_msg = new char[static_cast<GLuint>(log_size)];
        glGetProgramInfoLog(new_program, log_size, nullptr, log_msg);

        std::cerr << log_msg << std::endl;

        delete[] log_msg;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return new_program;
}

GLint ShaderProgram::GetUniformLocationOrDie(const char* var_name)
{
    GLint location = -1;
    location = glGetUniformLocation(shader_program_, var_name);

    if (location < 0)
    {
        cerr << "ERROR: cannot find uniform location " << var_name << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return location;
}

ShaderProgram::~ShaderProgram() {
    glUseProgram(0);

    glDetachShader(shader_program_, vertex_shader_);
    glDetachShader(shader_program_, fragment_shader_);

    glDeleteShader(vertex_shader_);
    glDeleteShader(fragment_shader_);
}