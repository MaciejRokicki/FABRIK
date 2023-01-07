#ifndef FABRIK2D_H
#define FABRIK2D_H

#include "fabrik.h"
#include "target2D.h"


class Fabrik2D : public Fabrik {
public:
	Fabrik2D(Tree<Joint2D>* tree);
	Fabrik2D(Tree<Joint2D>* tree, std::vector<Target2D*>& targetsRef);
	void Init();
	void Draw(const Camera& camera) const;
	void Solve();
	Target2D* SelectTargetByMouseButtonPressCallback(Vector3 space_pos);
	void RandomizeTargets(int min, int max);
	void Unload();
	void Forward();
	void Backward();
	void ShowcaseNextStep();
private:
	int forwardCounter = 0;
	int backwardCounter = 0;
	std::vector<Joint2D*>* jointsTmp;
	std::vector<int> forwardOrder;
	std::vector<int> backwardOrder;

	Tree<Joint2D>* tree;
	std::vector<Target2D*>* targets;

	bool IsReachable(Node<Joint2D>* root, Target2D* target);
	float DistanceBetweenJoints(Node<Joint2D>* nodeJoint);
	void ConnectJoints(Node<Joint2D>* nodeJoint);
	void UpdatePosition();

	Joint2D* FindJoint(int id);
};

#endif // !FABRIK2D_H
