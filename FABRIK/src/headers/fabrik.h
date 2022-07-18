#pragma once
#ifndef FABRIK_H
#define FABRIK_H

#include <vector>

#include "tree.h"
#include "object.h"
#include "cameraProgram.h"

class Fabrik {
protected:
	float tolerance;
	int iterations_limit = 100;
public:
	Fabrik();
	virtual void Init() = 0;
	virtual void Draw(const ModelProgram& program) const = 0;
	virtual void Solve() = 0;
	virtual Object* SelectTargetByMouseButtonPressCallback(Vector3 space_pos) = 0;
};

#endif // !FABRIK3D_H
