#ifndef FABRIK2_H
#define FABRIK2_H

#include <vector>

#include "tree.h"
#include "joint.h"
#include "segment.h"
#include "cameraProgram.h"
#include "target.h"

class Fabrik2D {
private:
	Tree<Joint>* tree;
	std::vector<Target*>* targets;
	float tolerance;
	void CreateSegmentsAndConnectJoints();
	bool IsReachable(Node<Joint>* root, Target* target);
	float DistanceBetweenJoints(Node<Joint>* nodeJoint);
public:
	Fabrik2D(Tree<Joint>* tree);
	void Init();
	void Draw(const ModelProgram& program) const;
	void ConnectJoints(Node<Joint>* nodeJoint);
	void Solve();
	Target* SelectTargetByMouseButtonPressCallback(Vector2 space_pos);
};

#endif
