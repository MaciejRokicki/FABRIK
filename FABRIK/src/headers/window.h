#ifndef WINDOW_H
#define WINDOW_H

#include <cstring>
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "mat4.h"
#include "vector2.h"
#include "scene.h"
#include "camera.h"

class Window {
private:
    int width;
    int height;
    const char* title;
    GLFWwindow* window = NULL;

    //clock_t last_time_;

    Camera* camera = NULL;

    Scene* scene;
    int sceneId = 3;

    void InitModels();
    void InitGlfwOrDie(int majorGlVersion, int minorGlVersion);
    void InitGlewOrDie();
public:
    Window(const char*, int, int);
    void Init(int majorGlVersion, int minorGlVersion);
    void Resize(int newWidth, int newHeight);
    void KeyEvent(int key, int scancode, int action, int mods);
    void MouseButtonEvent(int button, int action, int mods);
    void LoadScene(Scene* scene);
    void Run(void);
    operator GLFWwindow* () { return window; }
};

#endif // !WINDOW_H