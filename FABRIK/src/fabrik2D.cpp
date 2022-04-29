#include <iostream>

#include "headers/fabrik2D.h"

Fabrik2D::Fabrik2D() {
	this->tolerance = 0.4f;
	this->joints = new List<Joint>();
	this->segments = new List<Segment>();
	this->target = new Joint(Vector2::one * 5.0f, { 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f });
}

void Fabrik2D::Init() {
	joints->At(0).Init();

	for (int i = 1; i < joints->Size(); i++) {
		joints->At(i).Init();

		segments->At(i - 1).Init();
	}

	target->Init();
}

void Fabrik2D::Draw(const ModelProgram& program) const {
	joints->At(0).Draw(program);

	for (int i = 1; i < joints->Size(); i++) {
		joints->At(i).Draw(program);

		segments->At(i - 1).Draw(program);
	}

	target->Draw(program);
}

void Fabrik2D::SetJoints(List<Joint>& joints) {
	this->joints = &joints;
	this->joints->At(this->joints->Size() - 1).SetColor({ 1.0f, 1.0f, 0.0f, 1.0f }, true);
		
	CreateSegmentsAndConnectJoints();
}

bool Fabrik2D::IsReachable() {
	float root_target_distance = Vector2::Distance(joints->At(0).GetPosition(), target->GetPosition());
	float total_joints_distance = 0.0f;

	for (int i = 0; i < joints->Size() - 1; i++) {
		total_joints_distance += DistanceBetweenJoints(i);
	}

	return root_target_distance <= total_joints_distance;
}

//void Fabrik2D::Iterate() {
//	float tol = 0.5f;
//	List<Vector2> new_vectors = List<Vector2>();
//	Vector2 target_vector = target->GetPosition();
//
//	if (!IsReachable()) {
//		new_vectors.Push(joints->At(0).GetPosition());
//
//		for (int i = 1; i < joints->Size(); i++) {
//			Vector2 previous_joint_vector = joints->At(i - 1).GetPosition();
//
//			float r = Vector2::Distance(target_vector, previous_joint_vector);
//			float lambda = DistanceBetweenJoints(i-1) / r;
//
//			Vector2 new_vector = previous_joint_vector * (1 - lambda) + target_vector * lambda;
//
//			new_vectors.Push(new_vector);
//		}
//	}
//	else {
//		Vector2 base = joints->At(0).GetPosition();
//
//		for (int i = 0; i < joints->Size(); i++) {
//			new_vectors.Push(joints->At(i).GetPosition());
//		}
//
//		float diff = Vector2::Distance(joints->At(joints->Size() - 1).GetPosition(), target_vector);
//
//		while (diff > tol) {
//			new_vectors.At(joints->Size() - 1) = target_vector;
//
//			for (int i = joints->Size() - 2; i >= 0; i--) {
//				Vector2 current_joint_vector = joints->At(i).GetPosition();	
//				Vector2 next_joint_vector = joints->At(i + 1).GetPosition();
//				
//				float r = Vector2::Distance(next_joint_vector, current_joint_vector);
//				float lambda = DistanceBetweenJoints(i) / r;
//
//				Vector2 new_vector = { next_joint_vector * (1 - lambda) + current_joint_vector * lambda };
//
//				new_vectors.At(i) = new_vector;
//			}
//
//			new_vectors.At(0) = base;
//
//			for (int i = 1; i < joints->Size() - 1; i++) {
//				Vector2 current_joint_vector = joints->At(i).GetPosition();
//				Vector2 next_joint_vector = joints->At(i + 1).GetPosition();
//				
//				float r = Vector2::Distance(next_joint_vector, current_joint_vector);
//				float lambda = DistanceBetweenJoints(i) / r;
//
//				Vector2 new_vector = { current_joint_vector * (1 - lambda) + next_joint_vector * lambda };
//
//				new_vectors.At(i + 1) = new_vector;
//			}
//
//			diff = Vector2::Distance(new_vectors.At(new_vectors.Size() - 1), target_vector);
//		}
//	}
//
//	for (int i = 0; i < new_vectors.Size(); i++) {
//		joints->At(i).Translate(new_vectors.At(i));
//	}
//
//	ConnectJoints();
//}

void Fabrik2D::Solve() {
	List<Vector2> new_vectors = List<Vector2>();
	Vector2 target_vector = target->GetPosition();

	if (!IsReachable()) {
		new_vectors.Push(joints->At(0).GetPosition());
		Vector2 direction = (target_vector - new_vectors.At(0)).Normalize();

		for (int i = 1; i < joints->Size(); i++) {
			Vector2 previous_joint_vector = new_vectors.At(i - 1);
			float joints_distance = DistanceBetweenJoints(i - 1);

			Vector2 new_vector = previous_joint_vector + direction * joints_distance;

			new_vectors.Push(new_vector);
		}
	}
	else {
		for (int i = 0; i < joints->Size(); i++) {
			new_vectors.Push(joints->At(i).GetPosition());
		}

		float diff = Vector2::Distance(new_vectors.At(new_vectors.Size() - 1), target_vector);

		while (diff > tolerance) {
			new_vectors.At(joints->Size() - 1) = target_vector;

			for (int i = joints->Size() - 2; i > 0; i--) {
				Vector2 current_joint_vector = new_vectors.At(i);
				Vector2 next_joint_vector = new_vectors.At(i + 1);
				
				float joints_distance = DistanceBetweenJoints(i);

				new_vectors.At(i) = next_joint_vector + (current_joint_vector - next_joint_vector).Normalize() * joints_distance;
			}

			for (int i = 1; i < joints->Size(); i++) {
				Vector2 current_joint_vector = new_vectors.At(i);
				Vector2 previous_joint_vector = new_vectors.At(i - 1);
				
				float joints_distance = DistanceBetweenJoints(i - 1);

				new_vectors.At(i) = previous_joint_vector + (current_joint_vector - previous_joint_vector).Normalize() * joints_distance;
			}

			diff = Vector2::Distance(new_vectors.At(new_vectors.Size() - 1), target_vector);
		}
	}

	for (int i = 0; i < new_vectors.Size(); i++) {
		joints->At(i).Translate(new_vectors.At(i));
	}

	ConnectJoints();
}

Joint* Fabrik2D::SelectJointByMouseButtonPressCallback(Vector2 space_pos) {
	for (int i = 0; i < joints->Size(); i++) {
		Vector2 position = joints->At(i).GetPosition();
		Vector2 scale = joints->At(i).GetScale();

		if (space_pos <= position + scale / 2 &&
			space_pos >= position - scale / 2) {

			return &joints->At(i);
		}
	}

	if (space_pos <= target->GetPosition() + target->GetScale() / 2 &&
		space_pos >= target->GetPosition() - target->GetScale() / 2) {

		return target;
	}

	return NULL;
}

void Fabrik2D::CreateSegmentsAndConnectJoints() {
	for (int i = 1; i < joints->Size(); i++) {
		segments->Push(Segment({ (joints->At(i - 1).GetPosition() + joints->At(i).GetPosition()) / 2 },
			{ 0.2f, Vector2::Distance(joints->At(i - 1).GetPosition(), joints->At(i).GetPosition()) + 0.25f }));

		segments->At(i - 1).LookAt(joints->At(i));
	}
}

float Fabrik2D::DistanceBetweenJoints(int i) {
	float distance = 0.0f;

	distance += Vector2::Distance(joints->At(i).GetPosition(), joints->At(i + 1).GetPosition());

	return distance;
}

void Fabrik2D::ConnectJoints() {	
	for (int i = 1; i < joints->Size(); i++) {
		segments->At(i - 1).Translate(Vector2{ (joints->At(i - 1).GetPosition() + joints->At(i).GetPosition()) / 2 });
		segments->At(i - 1).Scale({ 0.2f, Vector2::Distance(joints->At(i - 1).GetPosition(), joints->At(i).GetPosition()) + 0.25f });

		segments->At(i - 1).LookAt(joints->At(i));
	}
}