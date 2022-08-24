#ifndef FABRIKANIMATION_H
#define FABRIKANIMATION_H

#include <vector>
#include <functional>

#include "vector3.h"
#include "target3D.h"

class FabrikAnimation {
private:
	std::vector<Vector3*> frames;
	int currentFrame = 0;
	bool stopped = false;
	bool loop = false;
	double time = 0.0;
	double timePerFrame = 0.1;

	std::vector<Object*>* targets;
	std::function<void()> frameUpdate;

	void generateFrames(int targetsCount, Vector3* startPosition, Vector3* endPosition, int frames);
	void mirrorFrames();
public:
	FabrikAnimation(
		std::vector<Object*>* targets,
		std::vector<Vector3*> frames, 
		bool playOnStart = false, 
		double timePerFrame = 0.1, 
		std::function<void()> frameUpdate = [] { return; }, 
		bool loop = false, 
		bool mirror = false);
	FabrikAnimation(
		std::vector<Object*>* targets,
		Vector3** positions,
		int positionCount, 
		int framesPerPosition,
		bool playOnStart = false,
		double timePerFrame = 0.1,
		std::function<void()> frameUpdate = [] { return; },
		bool loop = false,
		bool mirror = false);
	void Play(double deltaTime);
	void PauseResume();
	void Reset();
	void NextFrame();
	void PreviousFrame();
};

#endif // !FABRIKANIMATION_H
