#include <iostream>
#include <functional>
#include <time.h>
#include <chrono>
#include <iomanip>

#include "headers/fabrik.h"
#include "headers/fabrik2D.h"
#include "headers/target2D.h"
#include "headers/node.h"
#include "headers/tree.h"
#include "target2D.cpp"
#include "tree.cpp"

Fabrik2D::Fabrik2D(Tree<Joint2D>* tree) : Fabrik() {
	this->tree = tree;
	this->targets = new std::vector<Target2D*>();

	srand((unsigned)time(NULL));

	tree->Preorder([&](Node<Joint2D>* nodeJoint) {
		if (nodeJoint->child.size() == 0) {
			float r = (rand() % 10 + 1) / 10.0f;
			float g = (rand() % 10 + 1) / 10.0f;
			float b = (rand() % 10 + 1) / 10.0f;

			nodeJoint->value.SetColor({ r, g, b, 1.0f });
			Target2D* target = new Target2D(nodeJoint, Vector2{ 0.0f, 1.0f } + nodeJoint->value.GetPosition(), Vector2::one / 2, {r / 2, g / 2, b / 2, 1.0f});

			this->targets->push_back(target);
		}
	});
}

void Fabrik2D::Init() {
	tree->Preorder([&](Node<Joint2D>* nodeJoint) {
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

void Fabrik2D::Draw(const Camera& camera) const {
	tree->Preorder([&camera](Node<Joint2D>* nodeJoint) {
		nodeJoint->value.Draw(camera);

		if (nodeJoint->value.segment) {
			nodeJoint->value.segment->Draw(camera);
		}
	});

	for (int i = 0; i < this->targets->size(); i++) {
		this->targets->at(i)->Draw(camera);
	}
}

void Fabrik2D::Solve() {
	runs++;

	auto begin = std::chrono::high_resolution_clock::now();
	int iterations = 0;

	float accuracy;
	int reachableTargetsCounter;

	do {
		iterations++;

		accuracy = 0.0f;
		reachableTargetsCounter = 0;

		for (int i = 0; i < targets->size(); i++) {
			Node<Joint2D>* subbase = targets->at(i)->endEffector->parent;

			for (subbase; !subbase->value.IsSubBase && subbase->parent != NULL; subbase = subbase->parent) { }

			if (IsReachable(subbase, targets->at(i))) {
				accuracy += Vector2::Distance(targets->at(i)->endEffector->value.GetPosition(), targets->at(i)->GetPosition());
				reachableTargetsCounter++;
			}
		}

		accuracy /= reachableTargetsCounter;

		Forward();
		Backward();

		UpdatePosition();
	} while (accuracy > tolerance && iterations < iterations_limit);

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	double executionTime = elapsedTime.count() * 1e-3;
	double timePerIteration = elapsedTime.count() * 1e-3 / iterations;

	executionTimeSum += executionTime;
	tpiSum += timePerIteration;

	//std::cout <<"[" << runs << "]"
	//	<< " Iterations: " << iterations
	//	<< " Execution time: " << executionTime  << "ms" << " (AVG: " << executionTimeSum / runs << "ms)"
	//	<< " TPI: " << timePerIteration << "ms" << " (AVG: " << tpiSum / runs << "ms)"
	//	<< " Reachable targets: " << reachableTargetsCounter
	//	<< " Accuracy: " << (1 - accuracy) * 1e2 << std::endl;
}

Target2D* Fabrik2D::SelectTargetByMouseButtonPressCallback(Vector3 space_pos) {
	for (int i = 0; i < targets->size(); i++) {
		Target2D* target = targets->at(i);

		if (space_pos <= target->GetPosition() + target->GetScale() / 2 &&
			space_pos >= target->GetPosition() - target->GetScale() / 2) {

			return target;
		}
	}

	return NULL;
}

void Fabrik2D::RandomizeTargets(int min, int max) {
	int range = max - min + 1;

	for (int i = 0; i < targets->size(); i++) {
		float x = static_cast<float>(rand() % range + min);
		float y = static_cast<float>(rand() % range + min);

		Vector2 vector = { x, y };

		targets->at(i)->Translate(vector);
	}
}

bool Fabrik2D::IsReachable(Node<Joint2D>* root, Target2D* target) {
	float root_target_distance = Vector2::Distance(root->value.GetPosition(), target->GetPosition());
	float total_joints_distance = 0.0f;

	for (Node<Joint2D>* nodeJoint = target->endEffector; nodeJoint != root; nodeJoint = nodeJoint->parent) {
		total_joints_distance += DistanceBetweenJoints(nodeJoint);
	}

	return root_target_distance <= total_joints_distance;
}

float Fabrik2D::DistanceBetweenJoints(Node<Joint2D>* nodeJoint) {
	float distance = Vector2::Distance(nodeJoint->parent->value.GetPosition(), nodeJoint->value.GetPosition());

	return distance;
}

void Fabrik2D::ConnectJoints(Node<Joint2D>* nodeJoint) {
	if (nodeJoint->parent) {
		nodeJoint->value.segment->Translate(Vector2{ (nodeJoint->value.GetPosition() + nodeJoint->parent->value.GetPosition()) / 2.0f });
		nodeJoint->value.segment->SetScale({ 0.2f, Vector2::Distance(nodeJoint->value.GetPosition(), nodeJoint->parent->value.GetPosition()) + 0.25f });

		nodeJoint->value.segment->LookAt2D(nodeJoint->parent->value);
	}
}

void Fabrik2D::UpdatePosition() {
	tree->Preorder([&](Node<Joint2D>* nodeJoint) {
		nodeJoint->value.Translate(nodeJoint->value.PositionTmp);
		ConnectJoints(nodeJoint);
	});
}

void Fabrik2D::Forward() {
	int i = 0;
	Node<Joint2D>* subbase = NULL;

	tree->Inorder([&](Node<Joint2D>* nodeJoint) {
		if (nodeJoint->child.size() == 0) {
			nodeJoint->value.PositionTmp = targets->at(i)->GetPosition();
			i++;
		}

		//Krok niepotrzebny, suma wekorow nowych pozycji subbase'a z kazdego lanucucha wystarczy do wyznaczenia kierunku, a dlugosc miedzy stawami i tak jest zachowana
		if (nodeJoint == subbase) {
			subbase->value.PositionTmp = subbase->value.PositionTmp / (float)subbase->child.size();
		}

		if (nodeJoint->parent != tree->root && nodeJoint != tree->root) {
			Vector2 previous_joint_vector = nodeJoint->parent->value.PositionTmp;
			Vector2 current_joint_vector = nodeJoint->value.PositionTmp;
			Vector2 direction = (previous_joint_vector - current_joint_vector).Normalize();

			float joints_distance = DistanceBetweenJoints(nodeJoint);	

			if (nodeJoint->parent->value.IsSubBase) {
				subbase = nodeJoint->parent;
				nodeJoint->parent->value.PositionTmp = nodeJoint->parent->value.PositionTmp + current_joint_vector + direction * joints_distance;
			}
			else {
				nodeJoint->parent->value.PositionTmp = current_joint_vector + direction * joints_distance;
			}
		}
	});
}

void Fabrik2D::Backward() {
	for (int i = 0; i < tree->root->child.size(); i++) {
		tree->Preorder(tree->root->child.at(i), [&](Node<Joint2D>* nodeJoint) {
			Vector2 current_joint_vector = nodeJoint->value.PositionTmp;
			Vector2 previous_joint_vector = nodeJoint->parent->value.PositionTmp;
			Vector2 direction = (current_joint_vector - previous_joint_vector).Normalize();

			float joints_distance = DistanceBetweenJoints(nodeJoint);

			nodeJoint->value.PositionTmp = previous_joint_vector + direction * joints_distance;

			if (nodeJoint->value.constraint) {
				nodeJoint->value.PositionTmp = nodeJoint->value.constraint->Apply(&nodeJoint->parent->value, &nodeJoint->value);
			}
		});
	}
}

void Fabrik2D::Unload() {
	for (int i = 0; i < targets->size(); i++) {
		targets->at(i)->~Target2D();
	}

	tree->Preorder([](Node<Joint2D>* nodeJoint) {
		nodeJoint->value.segment->~Segment2D();
		nodeJoint->value.~Joint2D();
	});
}