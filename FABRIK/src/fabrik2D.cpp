#include <iostream>
#include <functional>
#include <time.h>
#include <chrono>
#include <iomanip>

#include "headers/fabrik2D.h"
#include "headers/target.h"
#include "headers/node.h"
#include "headers/tree.h"
#include "target.cpp"
#include "tree.cpp"

Fabrik2D::Fabrik2D(Tree<Joint>* tree) {
	this->tree = tree;
	this->targets = new std::vector<Target*>();
	this->tolerance = 0.04f;

	srand((unsigned)time(NULL));

	tree->Preorder([&](Node<Joint>* nodeJoint) {
		if (nodeJoint->child.size() == 0) {
			float r = (rand() % 10 + 1) / 10.0f;
			float g = (rand() % 10 + 1) / 10.0f;
			float b = (rand() % 10 + 1) / 10.0f;

			nodeJoint->value.SetColor({ r, g, b, 1.0f });
			Target* target = new Target(nodeJoint, nodeJoint->value.GetPosition() + Vector2{ 0.0f, 1.0f }, Vector2::one / 2, { r/2, g/2, b/2, 1.0f });

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

void Fabrik2D::Solve() {
	auto begin = std::chrono::high_resolution_clock::now();
	int iterations = 0;


	float diff = 0.0f;

	do {
		iterations++;
		diff = 0.0f;
		int counter = 0;

		for (int i = 0; i < targets->size(); i++) {
			Node<Joint>* subbase = targets->at(i)->endEffector->parent;

			for (subbase; !subbase->value.IsSubBase && subbase->parent != NULL; subbase = subbase->parent) { }

			if (IsReachable(subbase, targets->at(i))) {
				diff += Vector2::Distance(targets->at(i)->endEffector->value.GetPosition(), targets->at(i)->GetPosition());
				counter++;
			}
		}

		diff /= counter;

		Forward();
		Backward();

		UpdatePosition();
	} while (diff > tolerance);

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	std::cout << "Iterations: " << iterations << " Execution time: " << elapsedTime.count() * 1e-3 << "ms" << std::endl;
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

bool Fabrik2D::IsReachable(Node<Joint>* root, Target* target) {
	float root_target_distance = Vector2::Distance(root->value.GetPosition(), target->GetPosition());
	float total_joints_distance = 0.0f;

	for (Node<Joint>* nodeJoint = target->endEffector; nodeJoint != root; nodeJoint = nodeJoint->parent) {
		total_joints_distance += DistanceBetweenJoints(nodeJoint);
	}

	return root_target_distance <= total_joints_distance;
}

float Fabrik2D::DistanceBetweenJoints(Node<Joint>* nodeJoint) {
	float distance = Vector2::Distance(nodeJoint->parent->value.GetPosition(), nodeJoint->value.GetPosition());

	return distance;
}

void Fabrik2D::ConnectJoints(Node<Joint>* nodeJoint) {
	if (nodeJoint->parent) {
		nodeJoint->value.segment->Translate(Vector2{ (nodeJoint->value.GetPosition() + nodeJoint->parent->value.GetPosition()) / 2 });
		nodeJoint->value.segment->Scale({ 0.2f, Vector2::Distance(nodeJoint->value.GetPosition(), nodeJoint->parent->value.GetPosition()) + 0.25f });

		nodeJoint->value.segment->LookAt(nodeJoint->parent->value);
	}
}

void Fabrik2D::UpdatePosition() {
	tree->Preorder([&](Node<Joint>* nodeJoint) {
		nodeJoint->value.Translate(nodeJoint->value.Position);
		ConnectJoints(nodeJoint);
	});
}

void Fabrik2D::Forward() {
	int i = 0;
	Node<Joint>* subbase = NULL;

	tree->Inorder([&](Node<Joint>* nodeJoint) {
		if (nodeJoint->child.size() == 0) {
			nodeJoint->value.Position = targets->at(i)->GetPosition();
			i++;
		}

		//Krok niepotrzebny, suma wekorow nowych pozycji subbase'a z kazdego lanucucha wystarczy do wyznaczenia kierunku, a dlugosc miedzy stawami i tak jest zachowana
		if (nodeJoint == subbase) {
			subbase->value.Position = subbase->value.Position / subbase->child.size();
		}

		if (nodeJoint->parent != tree->root && nodeJoint != tree->root) {
			Vector2 previous_joint_vector = nodeJoint->parent->value.Position;
			Vector2 current_joint_vector = nodeJoint->value.Position;
			Vector2 direction = (previous_joint_vector - current_joint_vector).Normalize();

			float joints_distance = DistanceBetweenJoints(nodeJoint);	

			if (nodeJoint->parent->value.IsSubBase) {
				subbase = nodeJoint->parent;
				nodeJoint->parent->value.Position = nodeJoint->parent->value.Position + current_joint_vector + direction * joints_distance;
			}
			else {
				nodeJoint->parent->value.Position = current_joint_vector + direction * joints_distance;
			}
		}
	});
}

void Fabrik2D::Backward() {
	for (int i = 0; i < tree->root->child.size(); i++) {
		tree->Preorder(tree->root->child.at(i), [&](Node<Joint>* nodeJoint) {
			Vector2 current_joint_vector = nodeJoint->value.Position;
			Vector2 previous_joint_vector = nodeJoint->parent->value.Position;
			Vector2 direction = (current_joint_vector - previous_joint_vector).Normalize();

			float joints_distance = DistanceBetweenJoints(nodeJoint);

			nodeJoint->value.Position = previous_joint_vector + direction * joints_distance;
		});
	}
}