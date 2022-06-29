#include <functional>

#include "headers/fabrik2D.h"
#include "headers/target.h"
#include "headers/node.h"
#include "headers/tree.h"
#include "target.cpp"
#include "tree.cpp"

Fabrik2D::Fabrik2D(Tree<Joint>* tree) {
	this->tree = tree;
	this->targets = new std::vector<Target*>();
	this->tolerance = 0.4f;

	tree->Preorder([&](Node<Joint>* nodeJoint) {
		if (nodeJoint->child.size() == 0) {
			Target* target = new Target(nodeJoint, nodeJoint->value.GetPosition() + Vector2{ 0.0f, 1.0f });

			this->targets->push_back(target);
		}
	});
}

void Fabrik2D::Init() {
	tree->Preorder([&](Node<Joint>* nodeJoint) {
		if (nodeJoint->child.size() > 1) {
			nodeJoint->value.IsSubBase = true;
		}

		nodeJoint->value.Init();

		ConnectJoints(nodeJoint);

		if (nodeJoint->value.segment) {
			nodeJoint->value.segment->Init();
		}
	});

	for (int i = 0; i < this->targets->size(); i++) {
		this->targets->at(i)->Init();
	}

	bool c = IsReachable(tree->root, this->targets->at(0));
}

void Fabrik2D::Draw(const ModelProgram& program) const {
	tree->Preorder([program](Node<Joint>* nodeJoint) {
		nodeJoint->value.Draw(program);

		if (nodeJoint->value.segment) {
			nodeJoint->value.segment->Draw(program);
		}
	});

	for (int i = 0; i < this->targets->size(); i++) {
		this->targets->at(i)->Draw(program);
	}
}

bool Fabrik2D::IsReachable(Node<Joint>* root, Target* target) {
	float root_target_distance = Vector2::Distance(root->value.GetPosition(), target->GetPosition());
	float total_joints_distance = 0.0f;

	Node<Joint>* nodeJoint = target->endEffector;

	while (nodeJoint != root) {
		total_joints_distance += DistanceBetweenJoints(nodeJoint);
		nodeJoint = nodeJoint->parent;
	}

	return root_target_distance <= total_joints_distance;
}

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

Target* Fabrik2D::SelectTargetByMouseButtonPressCallback(Vector2 space_pos) {
	for (int i = 0; i < targets->size(); i++) {
		Target* target = targets->at(i);

		if (space_pos <= target->GetPosition() + target->GetScale() / 2 &&
			space_pos >= target->GetPosition() - target->GetScale() / 2) {

			return target;
		}
	}

	return NULL;
}

float Fabrik2D::DistanceBetweenJoints(Node<Joint>* nodeJoint) {
	float distance = 0.0f;

	distance += Vector2::Distance(nodeJoint->parent->value.GetPosition(), nodeJoint->value.GetPosition());

	return distance;
}

void Fabrik2D::ConnectJoints(Node<Joint>* nodeJoint) {
	if (nodeJoint->parent) {
		nodeJoint->value.segment->Translate(Vector2{ (nodeJoint->value.GetPosition() + nodeJoint->parent->value.GetPosition()) / 2 });
		nodeJoint->value.segment->Scale({ 0.2f, Vector2::Distance(nodeJoint->value.GetPosition(), nodeJoint->parent->value.GetPosition()) + 0.25f });

		nodeJoint->value.segment->LookAt(nodeJoint->parent->value);
	}
}