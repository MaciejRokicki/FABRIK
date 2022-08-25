#ifndef FABRIK_H
#define FABRIK_H

#include <iostream>
#include <functional>
#include <chrono>

#include "object.h"
#include "tree.h"

class Fabrik {
public:
	Fabrik();
	virtual void Init() = 0;
	virtual void Draw(const Camera& camera) const = 0;
	virtual void Solve() = 0;
	virtual Object* SelectTargetByMouseButtonPressCallback(Vector3 space_pos) = 0;
	virtual void RandomizeTargets(int min, int max) = 0;
	virtual void Unload() = 0;
protected:
	float tolerance;
	int iterations_limit = 10;

	int runs = 0;
	double executionTimeSum = 0.0;
	double tpiSum = 0.0;
};

#endif // !FABRIK3D_H
