#ifndef FABRIK3D_H
#define FABRIK3D_H

#include "fabrik.h"
#include "target3D.h"

class Fabrik3D : public Fabrik {
private:
	Tree<Joint3D>* tree;
	std::vector<Target3D*>* targets;

	bool IsReachable(Node<Joint3D>* root, Target3D* target);
	float DistanceBetweenJoints(Node<Joint3D>* nodeJoint);
	void ConnectJoints(Node<Joint3D>* nodeJoint);
	void UpdatePosition();
	void Forward();
	void Backward();
public:
	Fabrik3D(Tree<Joint3D>* tree);
	void Init();
	void Draw(const Camera& camera) const;
	void Solve();
	Target3D* SelectTargetByMouseButtonPressCallback(Vector3 space_pos);
	void RandomizeTargets(int min, int max);
	void Unload();
};

#endif // !FABRIK3D_H
