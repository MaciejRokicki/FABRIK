#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <functional>

#include "fabrik.h"
#include "object.h"
#include "vector2.h"

class Scene {
public:
	static std::vector<Scene*>* scenes;

	std::function<void(int, int)> KeyEvent;
	std::function<void(int, int, Vector2)> MouseButtonEvent;
	std::function<void()> Update;
	std::function<void(double)> Animate;

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
