#include "headers/scene.h"
#include "node.cpp"
#include "headers/joint2D.h"
#include "tree.cpp"
#include "headers/fabrik2D.h"
#include "headers/joint3D.h"
#include "headers/fabrik3D.h"
#include "headers/orthographicCamera.h"
#include "headers/perspectiveCamera.h"
#include "headers/main.h"
#include "headers/hinge2D.h"
#include "headers/hinge3D.h"
#include "headers/twist3D.h"
#include "headers/quaternion.h"

std::vector<Scene*>* Scene::scenes = new std::vector<Scene*>();

Scene::Scene(Camera* camera, Fabrik* fabrik) {
    this->camera = camera;
	this->fabrik = fabrik;
	this->objects = new std::vector<Object*>();

    this->KeyEvent = [](int, int) { return; };
    this->MouseButtonEvent = [](int, int, Vector2) { return; };
    this->Update = [] { return; };
}

Scene::Scene(Camera* camera, Fabrik* fabrik, std::vector<Object*>* objects) {
    this->camera = camera;
	this->fabrik = fabrik;
	this->objects = objects;

    this->KeyEvent = [](int, int) { return; };
    this->MouseButtonEvent = [](int, int, Vector2) { return; };
    this->Update = [] { return; };
}

Camera* Scene::GetCamera() {
    return camera;
}

void Scene::Init() {
	fabrik->Init();

	for (int i = 0; i < objects->size(); i++) {
		objects->at(i)->Init();
	}
}

void Scene::Draw(const Camera& camera) {
	fabrik->Draw(camera);

	for (int i = 0; i < objects->size(); i++) {
		objects->at(i)->Draw(camera);
	}
}

void Scene::Unload() {
    for (int i = 0; i < objects->size(); i++) {
        objects->at(i)->~Object();
    }

    fabrik->Unload();
}

Scene* Scene::BuildScene1() {
    Camera* camera = new OrthographicCamera(70, 0, 0, 0.1f, 100.0f);
    camera->Translate(Vector3{ 0.0f, -3.0f, 0.0f });

    Node<Joint2D>* root = new Node<Joint2D>(Joint2D(Vector2::zero, { 0.5f, 0.5f }, { 0.5f, 0.0f, 1.0f, 1.0f }));

    root->next(Joint2D({ 0.0f, 0.75f }, { 0.35f, 0.35f }));
    root->child[0]->next(Joint2D({ 0.0f, 1.5f }, { 0.35f, 0.35f }));
    root->child[0]->child[0]->next(Joint2D({0.0f, 2.25f}, {0.35f, 0.35f}));
    root->child[0]->child[0]->child[0]->next(Joint2D({0.0f, 3.0f}, {0.35f, 0.35f}));
    root->child[0]->child[0]->child[0]->child[0]->next(Joint2D({0.0f, 3.75f}, {0.35f, 0.35f}));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint2D({0.0f, 4.5f}, {0.35f, 0.35f}));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint2D({0.0f, 5.25f}, {0.35f, 0.35f}));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint2D({0.0f, 6.0f}, {0.35f, 0.35f}));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint2D({0.0f, 6.75f}, {0.35f, 0.35f}));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint2D({0.0f, 7.5f}, {0.35f, 0.35f}));

    Tree<Joint2D>* tree = new Tree<Joint2D>(root);
    Fabrik* fabrik = new Fabrik2D(tree);

    Scene* scene = new Scene(camera, fabrik);

    std::function<void(int, int)> keyEvent = [fabrik](int key, int action) {
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_SPACE:
                fabrik->Solve();
                break;
            
            case GLFW_KEY_R:
                fabrik->RandomizeTargets(-7, 7);
                break;
            }
        }
    };

    std::function<void(int, int, Vector2)> mouseEvent = [fabrik, scene](
        int button,
        int action,
        Vector2 space_pos) {
            if (action == GLFW_PRESS) {
                switch (button) {
                case GLFW_MOUSE_BUTTON_1:
                    scene->selectedObject = fabrik->SelectTargetByMouseButtonPressCallback(space_pos);

                    if (scene->selectedObject != NULL) {
                        scene->selectedObject->SetColor({ 0.0f, 1.0f, 0.0f });
                    }

                    break;
                }
            }
            else if (action == GLFW_RELEASE) {
                switch (button) {
                case GLFW_MOUSE_BUTTON_1:
                    if (scene->selectedObject != NULL) {
                        scene->selectedObject->Translate({ space_pos.x, space_pos.y, 0.0f });
                        scene->selectedObject->SetDefaultColor();
                        scene->selectedObject = NULL;
                    }
                    break;
                }
            }
    };

    scene->KeyEvent = keyEvent;
    scene->MouseButtonEvent = mouseEvent;

    return scene;
}

Scene* Scene::BuildScene2() {
    Camera* camera = new OrthographicCamera(70, 0, 0, 0.1f, 100.0f);

    Node<Joint2D>* root = new Node<Joint2D>(Joint2D(Vector2::zero, { 0.5f, 0.5f }, { 0.5f, 0.0f, 1.0f, 1.0f }));

    root->next(                     Joint2D({  0.0f,  3.0f }, { 0.35f, 0.35f }));   //tulow - 0
    root->child[0]->next(           Joint2D({  0.0f,  4.0f }, { 0.35f, 0.35f }));   //szyja - 0
    root->child[0]->next(           Joint2D({ -1.0f,  2.5f }, { 0.35f, 0.35f }));   //lewe ramie - 1
    root->child[0]->child[1]->next( Joint2D({ -1.0f,  1.0f }, { 0.35f, 0.35f }));   //lewe przedramie
    root->child[0]->next(           Joint2D({  1.0f,  2.5f }, { 0.35f, 0.35f }));   //prawe ramie - 2
    root->child[0]->child[2]->next( Joint2D({  1.0f,  1.0f }, { 0.35f, 0.35f }));   //prawe przedramie

    root->next(                     Joint2D({ -1.0f, -1.0f }, { 0.35f, 0.35f }));   //lewe udo - 1
    root->child[1]->next(           Joint2D({ -1.0f, -3.0f }, { 0.35f, 0.35f }));   //lewy piszczel
    root->next(                     Joint2D({  1.0f, -1.0f }, { 0.35f, 0.35f }));   //prawe udo - 2
    root->child[2]->next(           Joint2D({  1.0f, -3.0f }, { 0.35f, 0.35f }));   //prawy piszczel

    Tree<Joint2D>* tree = new Tree<Joint2D>(root);
    Fabrik* fabrik = new Fabrik2D(tree);

    Scene* scene = new Scene(camera, fabrik);

    std::function<void(int, int)> keyEvent = [fabrik](int key, int action) {
        if (action == GLFW_PRESS) {
            switch (key) {
                case GLFW_KEY_SPACE:
                    fabrik->Solve();
                    break;
            }
        }
    };

    std::function<void(int, int, Vector2)> mouseEvent = [fabrik, scene](
        int button,
        int action,
        Vector2 space_pos) {
            if (action == GLFW_PRESS) {
                switch (button) {
                    case GLFW_MOUSE_BUTTON_1:
                        scene->selectedObject = fabrik->SelectTargetByMouseButtonPressCallback(space_pos);

                        if (scene->selectedObject != NULL) {
                            scene->selectedObject->SetColor({ 0.0f, 1.0f, 0.0f });
                        }

                        break;
                }
            }
            else if (action == GLFW_RELEASE) {
                switch (button) {
                    case GLFW_MOUSE_BUTTON_1:
                        if (scene->selectedObject != NULL) {
                            scene->selectedObject->Translate({ space_pos.x, space_pos.y, 0.0f });
                            scene->selectedObject->SetDefaultColor();
                            scene->selectedObject = NULL;
                        }
                        break;
                }
            }
    };

    scene->KeyEvent = keyEvent;
    scene->MouseButtonEvent = mouseEvent;

    return scene;
}

Scene* Scene::BuildScene3() {
    Camera* camera = new OrthographicCamera(70, 0, 0, 0.1f, 100.0f);

    Node<Joint2D>* root = new Node<Joint2D>(Joint2D(Vector2::zero, { 0.5f, 0.5f }, { 0.5f, 0.0f, 1.0f, 1.0f }));

    root->next(                     Joint2D({  0.0f,  3.00f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(  0.0f, 180.0f)));     //tulow - 0
    root->child[0]->next(           Joint2D({  0.0f,  4.00f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(290.0f,  70.0f)));     //szyja - 0
    root->child[0]->next(           Joint2D({ -1.0f,  2.50f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D( 90.0f, 190.0f)));     //lewe ramie - 1
    root->child[0]->child[1]->next( Joint2D({ -1.0f,  1.00f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(  0.0f, 170.0f)));     //lewe przedramie
    root->child[0]->next(           Joint2D({  1.0f,  2.50f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(170.0f, 270.0f)));     //prawe ramie - 2
    root->child[0]->child[2]->next( Joint2D({  1.0f,  1.00f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(  0.0f, 170.0f)));     //prawe przedramie

    root->next(                     Joint2D({ -1.0f, -1.00f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(190.0f, 350.0f)));     //lewe udo - 1
    root->child[1]->next(           Joint2D({ -1.0f, -3.00f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(250.0f,   0.0f)));     //lewy piszczel
    root->next(                     Joint2D({  1.0f, -1.00f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(190.0f, 350.0f)));     //prawe udo - 2
    root->child[2]->next(           Joint2D({  1.0f, -3.00f }, { 0.35f, 0.35f }, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge2D(250.0f,   0.0f)));     //prawy piszczel

    Tree<Joint2D>* tree = new Tree<Joint2D>(root);
    Fabrik* fabrik = new Fabrik2D(tree);

    Scene* scene = new Scene(camera, fabrik);

    std::function<void(int, int)> keyEvent = [root, fabrik](int key, int action) {
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_SPACE:
                fabrik->Solve();
                break;
            }
        }
    };

    std::function<void(int, int, Vector2)> mouseEvent = [fabrik, scene](
        int button,
        int action,
        Vector2 space_pos) {
            if (action == GLFW_PRESS) {
                switch (button) {
                case GLFW_MOUSE_BUTTON_1:
                    scene->selectedObject = fabrik->SelectTargetByMouseButtonPressCallback(space_pos);

                    if (scene->selectedObject != NULL) {
                        scene->selectedObject->SetColor({ 0.0f, 1.0f, 0.0f });
                    }

                    break;
                }
            }
            else if (action == GLFW_RELEASE) {
                switch (button) {
                case GLFW_MOUSE_BUTTON_1:
                    if (scene->selectedObject != NULL) {
                        scene->selectedObject->Translate({ space_pos.x, space_pos.y, 0.0f });
                        scene->selectedObject->SetDefaultColor();
                        scene->selectedObject = NULL;
                    }
                    break;
                }
            }
    };

    scene->KeyEvent = keyEvent;
    scene->MouseButtonEvent = mouseEvent;

    return scene;
}

Scene* Scene::BuildScene4() {
    Camera* camera = new PerspectiveCamera(60, 0, 0, 0.1f, 1000.0f);
    camera->Translate(Vector3{ -2.0f, 0.0f, -19.0f });
    camera->Rotate(Vector3{ 0.0f, 45.0f, 0.0f });

    std::vector<Object*>* objects = new std::vector<Object*>{
        new Object3D(Vector3{ 0.0f,  0.0f, -15.0f }, Vector3{ 100.0f, 100.0f, 1.0f }, Color{ 0.3f, 0.3f, 0.3f }),
        new Object3D(Vector3{ 0.0f,  0.0f, -15.0f }, Vector3{ 100.0f, 100.0f, 1.0f }, Color{ 0.4f, 0.4f, 0.4f }),
        new Object3D(Vector3{ 0.0f, -12.0f, -15.0f }, Vector3{ 100.0f, 1.0f, 100.0f }, Color{ 0.5f, 0.5f, 0.5f }),
    };

    objects->at(0)->Rotate(Vector3{ 0.0f, 45.0f, 0.0f });
    objects->at(1)->Rotate(Vector3{ 0.0f, -45.0f, 0.0f });

    Node<Joint3D>* root = new Node<Joint3D>(Joint3D(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3::one / 2, { 0.5f, 0.0f, 1.0f, 1.0f }));

    //gora
    root->next(Joint3D(Vector3{ 0.0f, 0.75f, 0.0f }, Vector3::one / 3));
    root->child[0]->next(Joint3D(Vector3{ 0.0f, 1.5f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, 2.25f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, 3.0f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -0.75f, 3.75f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -0.75f, 4.5f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -0.75f, 5.25f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -0.75f, 6.0f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -0.75f, 6.75f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -0.75f, 7.5f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -0.75f, 8.25f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -0.75f, 9.0f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.75f, 3.75f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[1]->next(Joint3D(Vector3{ 0.75f, 4.5f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[1]->child[0]->next(Joint3D(Vector3{ 0.75f, 5.25f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[1]->child[0]->child[0]->next(Joint3D(Vector3{ 0.75f, 6.0f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[1]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.75f, 6.75f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[1]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.75f, 7.5f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.75f, 8.25f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[0]->child[0]->child[0]->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.75f, 9.0f, 0.0f }, Vector3::one / 3));

    //lewo
    root->next(Joint3D(Vector3{ -0.75f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->next(Joint3D(Vector3{ -1.5f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->next(Joint3D(Vector3{ -2.25f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->next(Joint3D(Vector3{ -3.0f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -3.75f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -4.5f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -5.25f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -6.0f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -6.75f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -7.5f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -8.25f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[1]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ -9.0f, 0.0f, 0.0f }, Vector3::one / 3));

    //dol
    root->next(Joint3D(Vector3{ 0.0f, -0.75f, 0.0f }, Vector3::one / 3));
    root->child[2]->next(Joint3D(Vector3{ 0.0f, -1.5f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->next(Joint3D(Vector3{ 0.0f, -2.25f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -3.0f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -3.75f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -4.5f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -5.25f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -6.0f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -6.75f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -7.5f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -8.25f, 0.0f }, Vector3::one / 3));
    root->child[2]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 0.0f, -9.0f, 0.0f }, Vector3::one / 3));

    //prawo
    root->next(Joint3D(Vector3{ 0.75f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->next(Joint3D(Vector3{ 1.5f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->next(Joint3D(Vector3{ 2.25f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->next(Joint3D(Vector3{ 3.0f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 3.75f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 4.5f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 5.25f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 6.0f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 6.75f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 7.5f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 8.25f, 0.0f, 0.0f }, Vector3::one / 3));
    root->child[3]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->child[0]->next(Joint3D(Vector3{ 9.0f, 0.0f, 0.0f }, Vector3::one / 3));

    Tree<Joint3D>* tree = new Tree<Joint3D>(root);
    Fabrik* fabrik = new Fabrik3D(tree);

    Scene* scene = new Scene(camera, fabrik, objects);

    std::function<void(int, int)> keyEvent = [fabrik](int key, int action) {
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_SPACE:
                fabrik->Solve();
                break;

            case GLFW_KEY_R:
                fabrik->RandomizeTargets(-10, 10);
                break;
            }
        }
    };

    scene->KeyEvent = keyEvent;

    return scene;
}

Scene* Scene::BuildScene5() {
    Camera* camera = new PerspectiveCamera(45, 0, 0, 0.1f, 1000.0f);
    camera->Translate(Vector3{ 0.0f, 0.0f, -10.0f });

    std::vector<Object*>* objects = new std::vector<Object*>{
        new Object3D(Vector3{ 0.0f,  0.0f, -10.0f }, Vector3{ 100.0f, 100.0f, 1.0f }, Color{ 0.3f, 0.3f, 0.3f }),
        new Object3D(Vector3{ 0.0f,  0.0f, -10.0f }, Vector3{ 100.0f, 100.0f, 1.0f }, Color{ 0.4f, 0.4f, 0.4f }),
        new Object3D(Vector3{ 0.0f, -5.0f, -10.0f }, Vector3{ 100.0f, 1.0f, 100.0f }, Color{ 0.5f, 0.5f, 0.5f }),
    };

    objects->at(0)->Rotate(Vector3{ 0.0f, 45.0f, 0.0f });
    objects->at(1)->Rotate(Vector3{ 0.0f, -45.0f, 0.0f });

    Node<Joint3D>* root = new Node<Joint3D>(Joint3D(Vector3::zero, Vector3::one / 2, { 0.5f, 0.0f, 1.0f, 1.0f }));

    root->next(                               Joint3D(Vector3{ 0.50f, 1.50f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }, new Twist3D(10.0f, 170.0f, 0.0f, 360.0f)));
    root->child[0]->next(                     Joint3D(Vector3{ 1.50f, 1.75f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge3D(Axis::X, 190.0f, 0.0f)));
    root->child[0]->child[0]->next(           Joint3D(Vector3{ 2.00f, 1.50f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge3D(Axis::Y, 190.0f, 0.0f)));
    root->child[0]->child[0]->child[0]->next( Joint3D(Vector3{ 2.25f, 2.00f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }));

    Tree<Joint3D>* tree = new Tree<Joint3D>(root);
    Fabrik* fabrik = new Fabrik3D(tree);

    Scene* scene = new Scene(camera, fabrik, objects);

    std::function<void(int, int)> keyEvent = [camera, fabrik](int key, int action) {
        if (action == GLFW_PRESS) {
            switch (key) {

            case GLFW_KEY_SPACE:
                fabrik->Solve();
                break;

            case GLFW_KEY_R:
                fabrik->RandomizeTargets(-3, 3);
                break;

            case GLFW_KEY_T:
                camera->Rotate(Vector3{ -90.0f, 0.0f, 0.0f });

                break;

            case GLFW_KEY_Y:
                camera->Rotate(Vector3{ 0.0f, 0.0f, 0.0f });

                break;
            }
        }
    };

    scene->KeyEvent = keyEvent;

    return scene;
}

Scene* Scene::BuildScene6() {
    Camera* camera = new PerspectiveCamera(55, 0, 0, 0.1f, 1000.0f);
    camera->Translate(Vector3{ 0.0f, -1.0f, -10.0f });
    camera->Rotate(Vector3{ 0.0f, 45.0f, 0.0f });

    std::vector<Object*>* objects = new std::vector<Object*>{
        new Object3D(Vector3{ 0.0f,  0.0f, -15.0f }, Vector3{ 100.0f, 100.0f, 1.0f }, Color{ 0.3f, 0.3f, 0.3f }),
        new Object3D(Vector3{ 0.0f,  0.0f, -15.0f }, Vector3{ 100.0f, 100.0f, 1.0f }, Color{ 0.4f, 0.4f, 0.4f }),
        new Object3D(Vector3{ 0.0f, -12.0f, -15.0f }, Vector3{ 100.0f, 1.0f, 100.0f }, Color{ 0.5f, 0.5f, 0.5f }),
    };

    objects->at(0)->Rotate(Vector3{ 0.0f, 45.0f, 0.0f });
    objects->at(1)->Rotate(Vector3{ 0.0f, -45.0f, 0.0f });

    Node<Joint3D>* root = new Node<Joint3D>(Joint3D(Vector3{ 0.0f, -3.0f, 0.0f }, Vector3::one / 2, { 0.5f, 0.0f, 1.0f, 1.0f }));

    root->next(                                         Joint3D(Vector3{  0.000f, -2.00f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }, new Twist3D(80.0f, 270.0f, 0.0f, 0.0f)));

    root->child[0]->next(                               Joint3D(Vector3{ -1.000f,  0.00f, 0.0f }, Vector3::one / 3));
    root->child[0]->next(                               Joint3D(Vector3{ -0.500f,  0.25f, 0.0f }, Vector3::one / 3));
    root->child[0]->next(                               Joint3D(Vector3{  0.000f,  0.30f, 0.0f }, Vector3::one / 3));
    root->child[0]->next(                               Joint3D(Vector3{  0.500f,  0.00f, 0.0f }, Vector3::one / 3));
    root->child[0]->next(                               Joint3D(Vector3{  1.000f, -1.00f, 0.0f }, Vector3::one / 3));

    root->child[0]->child[0]->next(                     Joint3D(Vector3{ -1.350f,  0.75f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[1]->next(                     Joint3D(Vector3{ -0.750f,  1.20f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[2]->next(                     Joint3D(Vector3{  0.000f,  1.40f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[3]->next(                     Joint3D(Vector3{  0.775f,  1.10f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[4]->next(                     Joint3D(Vector3{  1.600f, -0.40f, 0.0f }, Vector3::one / 3));

    root->child[0]->child[0]->child[0]->next(           Joint3D(Vector3{ -1.750f,  1.60f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[1]->child[0]->next(           Joint3D(Vector3{ -1.050f,  2.40f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[2]->child[0]->next(           Joint3D(Vector3{  0.000f,  2.80f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[3]->child[0]->next(           Joint3D(Vector3{  1.050f,  2.20f, 0.0f }, Vector3::one / 3));
    root->child[0]->child[4]->child[0]->next(           Joint3D(Vector3{  2.050f,  0.10f, 0.0f }, Vector3::one / 3));

    root->child[0]->child[0]->child[0]->child[0]->next( Joint3D(Vector3{ -2.000f,  2.10f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge3D(Axis::X, 270.0f, 0.0f)));
    root->child[0]->child[1]->child[0]->child[0]->next( Joint3D(Vector3{ -1.200f,  3.00f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge3D(Axis::X, 270.0f, 0.0f)));
    root->child[0]->child[2]->child[0]->child[0]->next( Joint3D(Vector3{  0.000f,  3.30f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge3D(Axis::X, 270.0f, 0.0f)));
    root->child[0]->child[3]->child[0]->child[0]->next( Joint3D(Vector3{  1.175f,  2.80f, 0.0f }, Vector3::one / 3, { 1.0f, 0.0f, 0.0f, 1.0f }, new Hinge3D(Axis::X, 270.0f, 0.0f)));

    Tree<Joint3D>* tree = new Tree<Joint3D>(root);
    std::vector<Target3D*>* targets = new std::vector<Target3D*>();
    Fabrik* fabrik = new Fabrik3D(tree, *targets);

    Scene* scene = new Scene(camera, fabrik, objects);

    std::vector<Vector3*> targetPositions = std::vector<Vector3*>();

    int frames = 20;
    Vector3 currentVec1 = { -2.000f,  3.10f,  0.0f };
    Vector3 currentVec2 = { -1.200f,  4.00f,  0.0f };
    Vector3 currentVec3 = {  0.000f,  4.30f,  0.0f };
    Vector3 currentVec4 = {  1.175f,  3.80f,  0.0f };
    Vector3 currentVec5 = {  2.050f,  1.10f,  -1.0f };

    Vector3 targetVec1 =  { -1.500f,  1.00f, -3.5f };
    Vector3 targetVec2 =  { -0.700f,  1.15f, -3.5f };
    Vector3 targetVec3 =  {  0.000f,  1.30f, -3.5f };
    Vector3 targetVec4 =  {  0.675f,  1.20f, -3.5f };
    Vector3 targetVec5 =  {  1.000f, -1.00f, -2.5f };

    Vector3 diffVec1 = targetVec1 - currentVec1;
    Vector3 diffVec2 = targetVec2 - currentVec2;
    Vector3 diffVec3 = targetVec3 - currentVec3;
    Vector3 diffVec4 = targetVec4 - currentVec4;
    Vector3 diffVec5 = targetVec5 - currentVec5;

    targetPositions.push_back(new Vector3[targets->size()]{
        currentVec1,
        currentVec2,
        currentVec3,
        currentVec4,
        currentVec5,
    });

    for (int i = frames; i > 0; i--) {
        Vector3 vec1 = currentVec1 + diffVec1 / frames * (frames - i);
        Vector3 vec2 = currentVec2 + diffVec2 / frames * (frames - i);
        Vector3 vec3 = currentVec3 + diffVec3 / frames * (frames - i);
        Vector3 vec4 = currentVec4 + diffVec4 / frames * (frames - i);
        Vector3 vec5 = currentVec5 + diffVec5 / frames * (frames - i);

        targetPositions.push_back(new Vector3[targets->size()]{
            vec1,
            vec2,
            vec3,
            vec4,
            vec5
        });
    }

    targetPositions.push_back(new Vector3[targets->size()]{
        targetVec1,
        targetVec2,
        targetVec3,
        targetVec4,
        targetVec5
    });

    for (int i = frames; i > 1; i--) {
        targetPositions.push_back(new Vector3[targets->size()]{
            targetPositions[i][0],
            targetPositions[i][1],
            targetPositions[i][2],
            targetPositions[i][3],
            targetPositions[i][4]
        });
    }

    int& currentFrame = *(new int(0));

    for (int i = 0; i < targets->size(); i++) {
        targets->at(i)->Translate(targetPositions[currentFrame][i]);
    }

    fabrik->Solve();

    std::function<void(int, int)> keyEvent = [camera, fabrik, targets, targetPositions, &currentFrame](int key, int action) {
        if (action == GLFW_PRESS) {
            switch (key) {
            case GLFW_KEY_T:
                camera->Rotate(Vector3::zero);
                break;

            case GLFW_KEY_Y:
                camera->Rotate({ 0.0f, 45.0f, 0.0f });
                break;

            case GLFW_KEY_SPACE:
                currentFrame++;

                if (currentFrame > targetPositions.size() - 1) {
                    currentFrame = 0;
                }

                for (int i = 0; i < targets->size(); i++) {
                    targets->at(i)->Translate(targetPositions[currentFrame][i]);
                }

                fabrik->Solve();
                break;
            }
        }
    };

    scene->KeyEvent = keyEvent;

    return scene;
}

void Scene::BuildScenes() {
    Scene::scenes->push_back(BuildScene1());
    Scene::scenes->push_back(BuildScene2());
    Scene::scenes->push_back(BuildScene3());
    Scene::scenes->push_back(BuildScene4());
    Scene::scenes->push_back(BuildScene5());
    Scene::scenes->push_back(BuildScene6());
}