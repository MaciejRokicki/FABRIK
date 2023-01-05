#ifndef WINDOW_H
#define WINDOW_H

#include "scene.h"

class Window {
public:
    Window(const char*, int, int);
    void Init(int majorGlVersion, int minorGlVersion);
    void Resize(int newWidth, int newHeight);
    void KeyEvent(int key, int scancode, int action, int mods);
    void MouseButtonEvent(int button, int action, int mods);
    void LoadScene(Scene* scene);
    void Run(void);
    operator GLFWwindow* () { return window; }
private:
    int width;
    int height;
    const char* title;
    GLFWwindow* window = NULL;

    Camera* camera = NULL;

    double time = 0.0;
    double deltaTime = 0.0;

    Scene* scene = NULL;
    int sceneId = 7;

    void InitModels();
    void InitGlfwOrDie(int majorGlVersion, int minorGlVersion);
    void InitGlewOrDie();
};

#endif // !WINDOW_H