#ifndef FABRIK2D_H
#define FABRIK2D_H

#include <vector>

#include "tree.h"
#include "joint2D.h"
#include "cameraProgram.h"
#include "target2D.h"

class Fabrik2D {
private:
	Tree<Joint2D>* tree;
	std::vector<Target2D*>* targets;
	float tolerance;
	int iterations_limit = 100;
	bool IsReachable(Node<Joint2D>* root, Target2D* target);
	float DistanceBetweenJoints(Node<Joint2D>* nodeJoint);
	void ConnectJoints(Node<Joint2D>* nodeJoint);
	void UpdatePosition();
	void Forward();
	void Backward();
public:
	Fabrik2D(Tree<Joint2D>* tree);
	void Init();
	void Draw(const ModelProgram& program) const;
	void Solve();
	Target2D* SelectTargetByMouseButtonPressCallback(Vector2 space_pos);
};

#endif // !FABRIK2D_H
