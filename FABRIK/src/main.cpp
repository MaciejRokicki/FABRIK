#include "headers/main.h"

using namespace std;

const int kMajorGLVersion = 4;
const int kMinorGLVersion = 3;

static Window window("Fabrik - Maciej Kamil Rokicki", 720, 480);

void Resize(GLFWwindow* /*window*/, int new_width, int new_height) {
	window.Resize(new_width, new_height);
}

void KeyPressed(GLFWwindow* /*window*/, int key, int scancode, int action, int mods) {
	window.KeyEvent(key, scancode, action, mods);
}

void MouseButtonPressed(GLFWwindow* /*window*/, int button, int action, int mods) {
    window.MouseButtonEvent(button, action, mods);
}

int main() {
    window.Init(kMajorGLVersion, kMinorGLVersion);
    glfwSetWindowSizeCallback(window, Resize);
    glfwSetKeyCallback(window, KeyPressed);
    glfwSetMouseButtonCallback(window, MouseButtonPressed);
    glfwSwapInterval(1);

    window.Run();

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
