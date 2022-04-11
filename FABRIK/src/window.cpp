#include <iostream>
#include <cstdlib>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "headers/window.h"
#include "headers/mat4.h"
#include "headers/joint.h"
#include "headers/transform.h"
#include "headers/list.h"
#include "headers/tree.h"

const char* kVertexShader = "shaders/SimpleShader.vertex.glsl";
const char* kFragmentShader = "shaders/SimpleShader.fragment.glsl";
const int s = 70;

Transform* selectedJoint = NULL;

Tree<Joint>* tree = new Tree<Joint>();
List<Segment>* segments = new List<Segment>();

Window::Window(const char* title, int width, int height) {
    title_ = title;
    width_ = width;
    height_ = height;
    //last_time_ = 0;
}

void Window::Init(int major_gl_version, int minor_gl_version) {
    InitGlfwOrDie(major_gl_version, minor_gl_version);
    InitGlewOrDie();

    std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) << " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    tree->At(0).Push(Joint());
    tree->At(0).Push(Joint({ 0.0f, 4.0f }));
    tree->At(0).Push(Joint({ 3.0f, 3.0f }));
    tree->At(0).Push(Joint({ 5.0f, 1.0f }));
    tree->At(0).Push(Joint({ 7.0f, 6.0f }));
    tree->At(0).Push(Joint({ -3.0f, 5.0f }));
    tree->At(0).Push(Joint({ -5.0f, -3.0f }));

    for (int i = 1; i < tree->At(0).Size(); i++) {
        segments->Push(Segment({ (tree->At(0, i - 1).GetPosition() + tree->At(0, i).GetPosition()) / 2 },
            { 0.2f, Vector2::Distance(tree->At(0, i - 1).GetPosition(), tree->At(0, i).GetPosition()) + 0.25f }));

        segments->At(i - 1).LookAt(tree->At(0, i));
    }

    InitModels();
    InitPrograms();

    //view_matrix_.Translate(0.0f, 0.0f, -10.0f);
    //view_matrix_.RotateY(45.0f);
    SetViewMatrix();

    //projection_matrix_ = Mat4::CreatePerspectiveProjectionMatrix(60, (float)width_ / (float)height_, 0.1f, 1000.0f);
    projection_matrix_ = Mat4::CreateOrthographicProjectionMatrix(-(float)width_ / s, (float)width_ / s, -(float)height_ / s, (float)height_ / s, 0.1f, 100.0f);
    SetProjectionMatrix();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::InitGlfwOrDie(int major_gl_version, int minor_gl_version) {
    if (!glfwInit()) {
        std::cerr << "ERROR: Could not initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_gl_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_gl_version);

    #ifdef DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    #endif

    window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);

    if (!window_) {
        std::cerr << "ERROR: Could not create a new rendering window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);
}

void Window::InitGlewOrDie() {
    GLenum glew_init_result;
    glewExperimental = GL_TRUE;
    glew_init_result = glewInit();

    if (GLEW_OK != glew_init_result) {
        std::cerr << "Glew ERROR: " << glewGetErrorString(glew_init_result) << std::endl;
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

void Window::InitModels() {
    std::cout << "JOINTS" << std::endl;
    for (int i = 0; i < tree->At(0).Size(); i++) {
        tree->At(0, i).Init();
        std::cout << tree->At(0, i).GetPosition() << " | " << tree->At(0, i).GetScale() << std::endl;
    }

    std::cout << "SEGMENTS" << std::endl;

    for (int i = 0; i < tree->At(0).Size() - 1; i++) {
        segments->At(i).Init();
        std::cout << segments->At(i).GetPosition() << " | " << segments->At(i).GetScale() << std::endl;
    }
}

void Window::InitPrograms() {
    model_program_.Init(kVertexShader, kFragmentShader);
}

void Window::SetViewMatrix() const {
    glUseProgram(model_program_);
    model_program_.SetViewMatrix(view_matrix_);
}

void Window::SetProjectionMatrix() const {
    glUseProgram(model_program_);
    model_program_.SetProjectionMatrix(projection_matrix_);
}

void Window::Resize(int new_width, int new_height) {
    width_ = new_width;
    height_ = new_height;
    projection_matrix_ = Mat4::CreateOrthographicProjectionMatrix(-(float)width_ / 70, (float)width_ / 70, -(float)height_ / 70, (float)height_ / 70, 0.1f, 100.0f);
    SetProjectionMatrix();
    glViewport(0, 0, width_, height_);
}

void Window::KeyEvent(int key, int /*scancode*/, int action, int /*mods*/) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window_, GLFW_TRUE);
                break;

            case GLFW_KEY_W:
                view_matrix_.Translate(0.0f, -1.0f, 0.0f);
                SetViewMatrix();
                break;

            case GLFW_KEY_A:
                view_matrix_.Translate(1.0f, 0.0f, 0.0f);
                SetViewMatrix();
                break;

            case GLFW_KEY_S:
                view_matrix_.Translate(0.0f, 1.0f, 0.0f);
                SetViewMatrix();
                break;

            case GLFW_KEY_D:
                view_matrix_.Translate(-1.0f, 0.0f, 0.0f);
                SetViewMatrix();
                break;

            case GLFW_KEY_SPACE:
                segments->At(0).SetColor({ 0.5f, 0.5f, 0.5f });
                break;

            default:
                break;
        } 
    }
    else if (action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                view_matrix_.Translate(0.0f, -1.0f, 0.0f);
                SetViewMatrix();
                break;

            case GLFW_KEY_A:
                view_matrix_.Translate(1.0f, 0.0f, 0.0f);
                SetViewMatrix();
                break;

            case GLFW_KEY_S:
                view_matrix_.Translate(0.0f, 1.0f, 0.0f);
                SetViewMatrix();
                break;

            case GLFW_KEY_D:
                view_matrix_.Translate(-1.0f, 0.0f, 0.0f);
                SetViewMatrix();
                break;

            default:
                break;
        }
    }
}

void Window::MouseButtonEvent(int button, int action, int mods) {
    bool isLeftButtonPressed = false;

    if (action == GLFW_PRESS) {
        switch (button) {
            case GLFW_MOUSE_BUTTON_1:
                isLeftButtonPressed = true;

                double x_pos, y_pos;
                glfwGetCursorPos(window_, &x_pos, &y_pos);

                Vector2 space_pos = MousePositionToSpacePosition(x_pos, y_pos);

                for (int i = 0; i < tree->At(0).Size(); i++) {
                    Vector2 position = tree->At(0, i).GetPosition();
                    Vector2 scale = tree->At(0, i).GetScale();

                    if (space_pos <= position + scale / 2 &&
                        space_pos >= position - scale / 2) {

                        if (selectedJoint != NULL && selectedJoint->GetPosition() != tree->At(0, i).GetPosition()) {
                            selectedJoint->SetColor({ 1.0f, 0.0f, 0.0f });
                        }

                        selectedJoint = &tree->At(0, i);
                        selectedJoint->SetColor({ 0.0f, 1.0f, 0.0f });
                    }
                }

                break;

            default:
                break;
        }
    }
    else if (action == GLFW_RELEASE) {
        switch (button) {
            case GLFW_MOUSE_BUTTON_1:
                double x_pos, y_pos;
                glfwGetCursorPos(window_, &x_pos, &y_pos);

                Vector2 space_pos = MousePositionToSpacePosition(x_pos, y_pos);

                if (selectedJoint != NULL) {
                    selectedJoint->Translate(space_pos);
                    selectedJoint->SetColor({ 1.0f, 0.0f, 0.0f });
                    selectedJoint = NULL;
                    ConnectJoints();
                }

                isLeftButtonPressed = false;
            break;

        default:
            break;
        }
    }
}

Vector2 Window::MousePositionToSpacePosition(double x, double y) {
    x /= s;
    x -= (double)width_ / s / 2;
    x *= 2;

    y /= s;
    y -= (double)height_ / s / 2;
    y *= -2;

    x -= view_matrix_[12];
    y -= view_matrix_[13];

    return { roundf(x * 10.0f) / 10.0f, roundf(y * 10.0f) / 10.0f };
}

void Window::ConnectJoints() {
    //TODO: zamiast aktualizowac wszystkie polaczenia joint'ow to aktualizowac tylko te polaczenia, ktore sa zwiazane ze zmienionym joint'em
    for (int i = 1; i < tree->At(0).Size(); i++) {
        segments->At(i - 1).Translate(Vector2 { (tree->At(0, i - 1).GetPosition() + tree->At(0, i).GetPosition()) / 2 });
        segments->At(i - 1).Scale({ 0.2f, Vector2::Distance(tree->At(0, i - 1).GetPosition(), tree->At(0, i).GetPosition()) + 0.25f });

        segments->At(i - 1).LookAt(tree->At(0, i));
    }
}

void Window::Run(void) {
    while (!glfwWindowShouldClose(window_)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //clock_t now = clock();

        //if (last_time_ == 0) {
        //    last_time_ = now;
        //}

        //last_time_ = now;

        for (int i = 0; i < tree->At(0).Size(); i++) {
            tree->At(0, i).Draw(model_program_);
        }

        for (int i = 0; i < tree->At(0).Size() - 1; i++) {
            segments->At(i).Draw(model_program_);
        }

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}