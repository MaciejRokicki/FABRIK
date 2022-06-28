#ifndef FABRIK2_H
#define FABRIK2_H

#include <vector>

#include "tree.h"
#include "joint.h"
#include "segment.h"
#include "cameraProgram.h"

class Fabrik2D {
private:
	float tolerance;
	//std::vector<Joint*>* joints;
	std::vector<Segment*>* segments;
	Joint* target;
	void CreateSegmentsAndConnectJoints();
	//bool IsReachable();
	//float DistanceBetweenJoints(int i);
public:
	Tree<Joint>* tree;
	Fabrik2D();
	void Init();
	void Draw(const ModelProgram& program) const;
	void ConnectJoints();
	//void SetJoints(std::vector<Joint*>* joints);
	void Solve();
	//Joint* SelectJointByMouseButtonPressCallback(Vector2 space_pos);
};

#endif
