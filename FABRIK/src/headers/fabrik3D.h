#ifndef FABRIK3D_H
#define FABRIK3D_H

#include "fabrik.h"
#include "target3D.h"

class Fabrik3D : public Fabrik {
public:
	Fabrik3D(Tree<Joint3D>* tree);
	Fabrik3D(Tree<Joint3D>* tree, std::vector<Target3D*>& targetsRef);
	void Init();
	void Draw(const Camera& camera) const;
	void Solve();
	Target3D* SelectTargetByMouseButtonPressCallback(Vector3 space_pos);
	void RandomizeTargets(int min, int max);
	void Unload();
private:
	Tree<Joint3D>* tree;
	std::vector<Target3D*>* targets;

	bool IsReachable(Node<Joint3D>* root, Target3D* target);
	float DistanceBetweenJoints(Node<Joint3D>* nodeJoint);
	void ConnectJoints(Node<Joint3D>* nodeJoint);
	void UpdatePosition();
	void Forward();
	void Backward();
};

#endif // !FABRIK3D_H
