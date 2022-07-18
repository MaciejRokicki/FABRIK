#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"

void Resize(GLFWwindow* /*window*/, int new_width, int new_height);
void KeyPressed(GLFWwindow* /*window*/, int key, int scancode, int action, int mods);
void MouseButtonPressed(GLFWwindow* window, int button, int action, int mods);

#endif // !MAIN_H