#ifndef WINDOW_H
#define WINDOW_H

#include <cstring>
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "modelProgram.h"
#include "shaderProgram.h"
#include "mat4.h"
#include "segment.h"

class Window {
public:
    Window(const char*, int, int);
    void Init(int major_gl_version, int minor_gl_version);
    void Resize(int new_width, int new_height);
    void KeyEvent(int key, int scancode, int action, int mods);
    void MouseButtonEvent(int button, int action, int mods);
    Vector2 MousePositionToSpacePosition(double x, double y);
    void ConnectJoints();
    void Run(void);
    operator GLFWwindow* () { return window_; }
private:
    int width_;
    int height_;
    const char* title_;
    GLFWwindow* window_;

    ModelProgram model_program_;

    //clock_t last_time_;

    Mat4 view_matrix_;
    Mat4 projection_matrix_;

    void InitModels();
    void InitPrograms();
    void SetViewMatrix() const;
    void SetProjectionMatrix() const;

    void InitGlfwOrDie(int major_gl_version, int minor_gl_version);
    void InitGlewOrDie();
};

#endif // !WINDOW_H