#ifndef FABRIK2D_H
#define FABRIK2D_H

#include "fabrik.h"
#include "target2D.h"

class Fabrik2D : public Fabrik {
private:
	Tree<Joint2D>* tree;
	std::vector<Target2D*>* targets;

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
	Target2D* SelectTargetByMouseButtonPressCallback(Vector3 space_pos);
};

#endif // !FABRIK2D_H
