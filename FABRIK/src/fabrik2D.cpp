#include <iostream>
#include <functional>

#include "headers/fabrik2D.h"
#include "headers/node.h"
#include "headers/tree.h"
#include "tree.cpp"

Fabrik2D::Fabrik2D() {
	this->tolerance = 0.4f;
	//this->joints = new std::vector<Joint*>();
	this->segments = new std::vector<Segment*>();
	//this->target = new Joint(Vector2::one * 5.0f, { 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f });
}

void Fabrik2D::Init() {
	//joints->at(0)->Init();

	//for (int i = 1; i < joints->size(); i++) {
	//	joints->at(i)->Init();

	//	segments->at(i - 1)->Init();
	//}

	//target->Init();

	tree->Preorder([](Joint* joint) {
		joint->Init();
	});
}

void Fabrik2D::Draw(const ModelProgram& program) const {
	//joints->at(0)->Draw(program);

	//for (int i = 1; i < joints->size(); i++) {
	//	joints->at(i)->Draw(program);

	//	segments->at(i - 1)->Draw(program);
	//}

	//target->Draw(program);

	tree->Preorder([program](Joint* joint) {
		joint->Draw(program);
	});
}

//void Fabrik2D::SetJoints(std::vector<Joint*>* joints) {
//	//this->joints = joints;
//	//this->joints->at(this->joints->size() - 1)->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f }, true);
//	//	
//	//CreateSegmentsAndConnectJoints();
//}

//bool Fabrik2D::IsReachable() {
//	//float root_target_distance = Vector2::Distance(joints->at(0)->GetPosition(), target->GetPosition());
//	//float total_joints_distance = 0.0f;
//
//	//for (int i = 0; i < joints->size() - 1; i++) {
//	//	total_joints_distance += DistanceBetweenJoints(i);
//	//}
//
//	//return root_target_distance <= total_joints_distance;
//}

void Fabrik2D::Solve() {
	//std::vector<Vector2> new_vectors = std::vector<Vector2>();
	//Vector2 target_vector = target->GetPosition();

	//if (!IsReachable()) {
	//	new_vectors.push_back(joints->at(0)->GetPosition());
	//	Vector2 direction = (target_vector - new_vectors.at(0)).Normalize();

	//	for (int i = 1; i < joints->size(); i++) {
	//		Vector2 previous_joint_vector = new_vectors.at(i - 1);
	//		float joints_distance = DistanceBetweenJoints(i - 1);

	//		Vector2 new_vector = previous_joint_vector + direction * joints_distance;

	//		new_vectors.push_back(new_vector);
	//	}
	//}
	//else {
	//	for (int i = 0; i < joints->size(); i++) {
	//		new_vectors.push_back(joints->at(i)->GetPosition());
	//	}

	//	float diff = Vector2::Distance(new_vectors.at(new_vectors.size() - 1), target_vector);

	//	while (diff > tolerance) {
	//		new_vectors.at(joints->size() - 1) = target_vector;

	//		for (int i = joints->size() - 2; i > 0; i--) {
	//			Vector2 current_joint_vector = new_vectors.at(i);
	//			Vector2 next_joint_vector = new_vectors.at(i + 1);
	//			
	//			float joints_distance = DistanceBetweenJoints(i);

	//			new_vectors.at(i) = next_joint_vector + (current_joint_vector - next_joint_vector).Normalize() * joints_distance;
	//		}

	//		for (int i = 1; i < joints->size(); i++) {
	//			Vector2 current_joint_vector = new_vectors.at(i);
	//			Vector2 previous_joint_vector = new_vectors.at(i - 1);
	//			
	//			float joints_distance = DistanceBetweenJoints(i - 1);

	//			new_vectors.at(i) = previous_joint_vector + (current_joint_vector - previous_joint_vector).Normalize() * joints_distance;
	//		}

	//		diff = Vector2::Distance(new_vectors.at(new_vectors.size() - 1), target_vector);
	//	}
	//}

	//for (int i = 0; i < new_vectors.size(); i++) {
	//	joints->at(i)->Translate(new_vectors.at(i));
	//}

	//ConnectJoints();
}

//Joint* Fabrik2D::SelectJointByMouseButtonPressCallback(Vector2 space_pos) {
//	//for (int i = 0; i < joints->size(); i++) {
//	//	Vector2 position = joints->at(i)->GetPosition();
//	//	Vector2 scale = joints->at(i)->GetScale();
//
//	//	if (space_pos <= position + scale / 2 &&
//	//		space_pos >= position - scale / 2) {
//
//	//		return joints->at(i);
//	//	}
//	//}
//
//	//if (space_pos <= target->GetPosition() + target->GetScale() / 2 &&
//	//	space_pos >= target->GetPosition() - target->GetScale() / 2) {
//
//	//	return target;
//	//}
//
//	//return NULL;
//}

void Fabrik2D::CreateSegmentsAndConnectJoints() {
	//for (int i = 1; i < joints->size(); i++) {
	//	segments->push_back(new Segment({ (joints->at(i - 1)->GetPosition() + joints->at(i)->GetPosition()) / 2 },
	//		{ 0.2f, Vector2::Distance(joints->at(i - 1)->GetPosition(), joints->at(i)->GetPosition()) + 0.25f }));

	//	segments->at(i - 1)->LookAt(*joints->at(i));
	//}
}

//float Fabrik2D::DistanceBetweenJoints(int i) {
//	//float distance = 0.0f;
//
//	//distance += Vector2::Distance(joints->at(i)->GetPosition(), joints->at(i + 1)->GetPosition());
//
//	//return distance;
//}

void Fabrik2D::ConnectJoints() {	
	//for (int i = 1; i < joints->size(); i++) {
	//	segments->at(i - 1)->Translate(Vector2{ (joints->at(i - 1)->GetPosition() + joints->at(i)->GetPosition()) / 2 });
	//	segments->at(i - 1)->Scale({ 0.2f, Vector2::Distance(joints->at(i - 1)->GetPosition(), joints->at(i)->GetPosition()) + 0.25f });

	//	segments->at(i - 1)->LookAt(*joints->at(i));
	//}
}