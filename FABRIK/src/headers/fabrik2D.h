#ifndef FABRIK2_H
#define FABRIK2_H

#include "joint.h"
#include "tree.h"
#include "segment.h"
#include "cameraProgram.h"

class Fabrik2D {
private:
	float tolerance;
	List<Joint>* joints;
	List<Segment>* segments;
	Joint* target;
	void CreateSegmentsAndConnectJoints();
	bool IsReachable();
	float DistanceBetweenJoints(int i);
public:
	Fabrik2D();
	void Init();
	void Draw(const ModelProgram& program) const;
	void ConnectJoints();
	void SetJoints(List<Joint>& joints);
	void Solve();
	Joint* SelectJointByMouseButtonPressCallback(Vector2 space_pos);
};

#endif
