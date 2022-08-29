#include "headers/window.h"

Window::Window(const char* title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;
}

void Window::Init(int majorGlVersion, int minorGlVersion) {
    InitGlfwOrDie(majorGlVersion, minorGlVersion);
    InitGlewOrDie();

    std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) << " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    Scene::BuildScenes();
    LoadScene(Scene::scenes->at(sceneId));

    camera = scene->GetCamera();
    camera->Resize(width, height);

    InitModels();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::Resize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;

    camera->Resize(width, height);

    glViewport(0, 0, width, height);
}

void Window::KeyEvent(int key, int /*scancode*/, int action, int /*mods*/) {
    scene->KeyEvent(key, action);

    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;

            case GLFW_KEY_W:
                camera->Translate(Vector3{ 0.0f, -1.0f, 0.0f });
                break;

            case GLFW_KEY_A:
                camera->Translate(Vector3{ 1.0f, 0.0f, 0.0f });
                break;

            case GLFW_KEY_S:
                camera->Translate(Vector3{ 0.0f, 1.0f, 0.0f });
                break;

            case GLFW_KEY_D:
                camera->Translate(Vector3{ -1.0f, 0.0f, 0.0f });
                break;

            case GLFW_KEY_1:
                sceneId--;

                if (sceneId < 0) {
                    sceneId = (int)Scene::scenes->size() - 1;
                }
                LoadScene(Scene::scenes->at(sceneId));
                break;

            case GLFW_KEY_2:
                sceneId++;

                if (sceneId >= Scene::scenes->size()) {
                    sceneId = 0;
                }

                LoadScene(Scene::scenes->at(sceneId));
                break;

            default:
                break;
        } 
    }
    else if (action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                camera->Translate(Vector3{ 0.0f, -1.0f, 0.0f });
                break;

            case GLFW_KEY_A:
                camera->Translate(Vector3{ 1.0f, 0.0f, 0.0f });
                break;

            case GLFW_KEY_S:
                camera->Translate(Vector3{ 0.0f, 1.0f, 0.0f });
                break;

            case GLFW_KEY_D:
                camera->Translate(Vector3{ -1.0f, 0.0f, 0.0f });
                break;

            default:
                break;
        }
    }
}

void Window::MouseButtonEvent(int button, int action, int mods) {
    double xPosition, yPosition;
    glfwGetCursorPos(window, &xPosition, &yPosition);
    Vector2 worldPosition = camera->CameraToWorldPosition(xPosition, yPosition);

    scene->MouseButtonEvent(button, action, worldPosition);
}

void Window::LoadScene(Scene* scene) {
    if (this->scene != NULL) {
        scene->Unload();
    }

    this->scene = scene;

    camera = scene->GetCamera();
    camera->Resize(width, height);

    this->scene->Init();
    this->scene->Start();
}

void Window::Run(void) {
    double previousTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        time = glfwGetTime();

        scene->Update();
        scene->Animate(deltaTime);
        scene->Draw(*camera);

        deltaTime = time - previousTime;
        previousTime = time;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::InitModels() {
    scene->Init();
}

void Window::InitGlfwOrDie(int majorGlVersion, int minorGlVersion) {
    if (!glfwInit()) {
        std::cerr << "ERROR: Could not initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorGlVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorGlVersion);

    #ifdef DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    #endif

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window) {
        std::cerr << "ERROR: Could not create a new rendering window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
}

void Window::InitGlewOrDie() {
    GLenum glewInitResult;
    glewExperimental = GL_TRUE;
    glewInitResult = glewInit();

    if (GLEW_OK != glewInitResult) {
        std::cerr << "Glew ERROR: " << glewGetErrorString(glewInitResult) << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
        if (glDebugMessageCallback) {
            std::cout << "Register OpenGL debug callback " << std::endl;
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback((GLDEBUGPROC)OpenglCallbackFunction, NULL);
            GLuint unused_ids = 0;
            glDebugMessageControl(GL_DONT_CARE,
                GL_DONT_CARE,
                GL_DONT_CARE,
                0,
                &unused_ids,
                GL_FALSE);
        }
        else
            std::cout << "glDebugMessageCallback not available" << std::endl;
    #endif
}