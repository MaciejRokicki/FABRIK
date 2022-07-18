#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "headers/shaderProgram.h"

using namespace std;

ShaderProgram::ShaderProgram() {
	vertexShader = LoadAndCompileShaderOrDie(kVertexShader, GL_VERTEX_SHADER);
	fragmentShader = LoadAndCompileShaderOrDie(kFragmentShader, GL_FRAGMENT_SHADER);

	shaderProgram = AttachShadersOrDie(vertexShader, fragmentShader);

	glUseProgram(shaderProgram);
	glUseProgram(0);
}

GLuint ShaderProgram::LoadAndCompileShaderOrDie(const char* sourceFile, GLenum type) {
    int fileSize;
    char* shaderCode;
    GLuint shader = glCreateShader(type);
    ifstream file(sourceFile, ios::in | ios::ate | ios::binary);

    if (file.is_open()) {
        fileSize = (int)file.tellg();
        shaderCode = new char[fileSize + 1];
        file.seekg(0, ios::beg);
        file.read(shaderCode, fileSize);
        shaderCode[fileSize] = '\0';
        file.close();

        glShaderSource(shader, 1, (const GLchar**)&shaderCode, NULL);
        glCompileShader(shader);
        delete[] shaderCode;
    }
    else {
        cerr << "Could not open the file " << sourceFile << endl;
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
        GLint logSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[static_cast<GLuint>(logSize)];
        glGetShaderInfoLog(shader, logSize, nullptr, logMsg);
        std::cerr << logMsg << std::endl;
        delete[] logMsg;

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return shader;
}

GLuint ShaderProgram::AttachShadersOrDie(GLuint vertexShader, GLuint fragmentShader) {
    GLuint newProgram = glCreateProgram();

    glAttachShader(newProgram, vertexShader);
    glAttachShader(newProgram, fragmentShader);

    glLinkProgram(newProgram);

    GLint linked;
    glGetProgramiv(newProgram, GL_LINK_STATUS, &linked);

    if (!linked) {
        std::cerr << "Shader program failed to link" << std::endl;

        GLint  logSize;
        glGetProgramiv(newProgram, GL_INFO_LOG_LENGTH, &logSize);

        char* logMsg = new char[static_cast<GLuint>(logSize)];
        glGetProgramInfoLog(newProgram, logSize, nullptr, logMsg);

        std::cerr << logMsg << std::endl;

        delete[] logMsg;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return newProgram;
}

GLint ShaderProgram::GetUniformLocationOrDie(const char* varName)
{
    GLint location = -1;
    location = glGetUniformLocation(shaderProgram, varName);

    if (location < 0)
    {
        cerr << "ERROR: cannot find uniform location " << varName << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return location;
}

ShaderProgram::~ShaderProgram() {
    glUseProgram(0);

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}