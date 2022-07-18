#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <functional>

#include "fabrik.h"
#include "object.h"
#include "modelProgram.h"
#include "vector2.h"

class Scene {
private:
	Fabrik* fabrik;
	std::vector<Object*>* objects;
	Object* selectedObject = NULL;

	static Scene* BuildScene1();
	static Scene* BuildScene2();
public:
	static std::vector<Scene*>* scenes;

	std::function<void(int, int)> KeyEvent;
	std::function<void(int, int, Vector2)> MouseButtonEvent;
	std::function<void()> Update;

	static void BuildScenes();

	Scene(Fabrik* fabrik);
	Scene(Fabrik* fabrik, std::vector<Object*>* objects);
	void Init();
	void Draw(const ModelProgram& program);
};

#endif // SCENE_H
