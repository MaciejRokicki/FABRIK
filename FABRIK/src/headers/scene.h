#ifndef SCENE_H
#define SCENE_H

#include "fabrik.h"

class Scene {
public:
	static std::vector<Scene*>* scenes;

	std::function<void(int, int)> KeyEvent = [](int, int) { return; };
	std::function<void(int, int, Vector2)> MouseButtonEvent = [](int, int, Vector2) { return; };
	std::function<void()> Start = [] { return; };
	std::function<void()> Update = [] { return; };
	std::function<void(double)> Animate = [](double) { return; };

	static void BuildScenes();

	Scene(Camera* camera, Fabrik* fabrik);
	Scene(Camera* camera, Fabrik* fabrik, std::vector<Object*>* objects);
	Camera* GetCamera();
	void Init();
	void Draw(const Camera& camera);
	void Unload();
private:
	Camera* camera;
	Fabrik* fabrik;
	std::vector<Object*>* objects;
	Object* selectedObject = NULL;

	static Scene* BuildScene1();
	static Scene* BuildScene2();
	static Scene* BuildScene3();
	static Scene* BuildScene4();
	static Scene* BuildScene5();
	static Scene* BuildScene6();
};

#endif // SCENE_H
