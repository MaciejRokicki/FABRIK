#include <functional>

#include "headers/fabrik2D.h"
#include "headers/target.h"
#include "headers/node.h"
#include "headers/tree.h"
#include "target.cpp"
#include "tree.cpp"
#include <iostream>

Fabrik2D::Fabrik2D(Tree<Joint>* tree) {
	this->tree = tree;
	this->targets = new std::vector<Target*>();
	this->bases = new std::vector<Node<Joint>*>();
	this->tolerance = 0.4f;

	tree->Preorder([&](Node<Joint>* nodeJoint) {
		if (nodeJoint->child.size() == 0) {
			Target* target = new Target(nodeJoint, nodeJoint->value.GetPosition() + Vector2{ 0.0f, 1.0f });

			this->targets->push_back(target);
		}
	});
}

void Fabrik2D::Init() {
	bases->push_back(tree->root);

	tree->Preorder([&](Node<Joint>* nodeJoint) {
		if (nodeJoint->child.size() > 1) {
			nodeJoint->value.IsSubBase = true;
			bases->push_back(nodeJoint);
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

bool Fabrik2D::IsReachable(Node<Joint>* root, Target* target) {
	float root_target_distance = Vector2::Distance(root->value.GetPosition(), target->GetPosition());
	float total_joints_distance = 0.0f;

	for (Node<Joint>* nodeJoint = target->endEffector; nodeJoint != root; nodeJoint = nodeJoint->parent) {
		total_joints_distance += DistanceBetweenJoints(nodeJoint);
	}

	std::cout << total_joints_distance << std::endl;

	return root_target_distance <= total_joints_distance;
}

void Fabrik2D::Solve() {
	std::vector<Vector2> new_vectors = std::vector<Vector2>();
	
	for (Target* target : *targets) {
		if (!IsReachable(tree->root, target)) {
			new_vectors.push_back(tree->root->value.GetPosition());
			Vector2 direction = (target->GetPosition() - new_vectors.at(0)).Normalize();
			Vector2 tmp_previous_joint_new_vector = new_vectors.at(0);

			tree->Preorder(tree->root->child[0], [&](Node<Joint>* nodeJoint) {
				float joints_distance = DistanceBetweenJoints(nodeJoint);

				Vector2 new_vector = tmp_previous_joint_new_vector + direction * joints_distance;

				new_vectors.push_back(new_vector);
				tmp_previous_joint_new_vector = new_vector;
			});
		}
		else {
			tree->Preorder(tree->root, [&](Node<Joint>* nodeJoint) {
				new_vectors.push_back(nodeJoint->value.GetPosition());
			});

			float diff = Vector2::Distance(new_vectors.at(new_vectors.size() - 1), target->GetPosition());

			while (diff > tolerance) {
				new_vectors.at(new_vectors.size() - 1) = target->GetPosition();

				int i = new_vectors.size() - 2;

				for (Node<Joint>* nodeJoint = target->endEffector->parent; nodeJoint->parent != NULL; nodeJoint = nodeJoint->parent) {
					Vector2 current_joint_vector = new_vectors.at(i);
					Vector2 next_joint_vector = new_vectors.at(i + 1);

					float joints_distance = DistanceBetweenJoints(nodeJoint->child.at(0));

					new_vectors.at(i) = next_joint_vector + (current_joint_vector - next_joint_vector).Normalize() * joints_distance;

					i--;
				}

				i = 1;

				tree->Preorder(tree->root->child.at(0), [&](Node<Joint>* nodeJoint) {
					Vector2 current_joint_vector = new_vectors.at(i);
					Vector2 previous_joint_vector = new_vectors.at(i - 1);

					float joints_distance = DistanceBetweenJoints(nodeJoint);

					new_vectors.at(i) = previous_joint_vector + (current_joint_vector - previous_joint_vector).Normalize() * joints_distance;
					i++;
				});

				diff = Vector2::Distance(new_vectors.at(new_vectors.size() - 1), target->GetPosition());
			}
		}
	}

	int i = 0;
 	tree->Preorder([&](Node<Joint>* nodeJoint) {
		nodeJoint->value.Translate(new_vectors.at(i));
		ConnectJoints(nodeJoint);

		i++;
	});
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