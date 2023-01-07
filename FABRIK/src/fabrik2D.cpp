#include "headers/fabrik2D.h"
#include "tree.cpp"

Fabrik2D::Fabrik2D(Tree<Joint2D>* tree) : Fabrik() {
	this->jointsTmp = new std::vector<Joint2D*>();
	this->forwardOrder = std::vector<int>();
	this->backwardOrder = std::vector<int>();

	this->tree = tree;
	this->targets = new std::vector<Target2D*>();

	srand((unsigned)time(NULL));

	int i = 0;

	tree->Preorder([&](Node<Joint2D>* nodeJoint) {
		nodeJoint->value.id = i;
		backwardOrder.push_back(nodeJoint->value.id);

		jointsTmp->push_back(new Joint2D(nodeJoint->value.GetPosition(), Vector2{ 0.35f, 0.35f }, Color{ 1.0f, 1.0f, 1.0f, 1.0f }));
		jointsTmp->at(jointsTmp->size()-1)->id = nodeJoint->value.id;

		if (nodeJoint->parent != NULL) {
			nodeJoint->value.segment = new Segment2D();
		}

		if (nodeJoint->child.size() == 0) {
			float r = (rand() % 10 + 1) / 10.0f;
			float g = (rand() % 10 + 1) / 10.0f;
			float b = (rand() % 10 + 1) / 10.0f;

			nodeJoint->value.SetColor({ r, g, b, 1.0f });
			Target2D* target = new Target2D(nodeJoint, Vector3{ 0.0f, 1.0f, 0.0f } + nodeJoint->value.GetPosition(), Vector3::one / 2, { r / 2, g / 2, b / 2, 1.0f });

			this->targets->push_back(target);
		}

		i++;
	});

	tree->Inorder([&](Node<Joint2D>* nodeJoint) {
		forwardOrder.push_back(nodeJoint->value.id);
	});
}

Fabrik2D::Fabrik2D(Tree<Joint2D>* tree, std::vector<Target2D*>& targetsRef) : Fabrik2D(tree) {
	targetsRef = *this->targets;
}

void Fabrik2D::Init() {
	for (int i = 0; i < jointsTmp->size(); i++)
	{
		jointsTmp->at(i)->Init();
	}

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
	for (int i = 0; i < jointsTmp->size(); i++)
	{
		jointsTmp->at(i)->Draw(camera);
	}

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

	float previousTotalDistance = 0.0f;
	float totalDistance = 0.0f;

	do {
		previousTotalDistance = totalDistance;
		totalDistance = 0.0f;

		for (int i = 0; i < targets->size(); i++) {
			totalDistance += Vector2::Distance(targets->at(i)->endEffector->value.GetPosition(), targets->at(i)->GetPosition());
		}

		if (fabsf(totalDistance - previousTotalDistance) < tolerance)
			break;

		Forward();
		Backward();

		UpdatePosition();

		iterations++;
	} while (iterations < iterationsLimit);

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	float executionTime = elapsedTime.count() * 1e-3f;
	float timePerIteration = elapsedTime.count() * 1e-3f / (iterations == 0 ? 1 : iterations);

	executionTimeSum += executionTime;
	tpiSum += timePerIteration;

	std::cout << "[" << runs << "]"
		<< " Iterations: " << iterations
		<< " Execution time: " << executionTime << "ms" << " (AVG: " << executionTimeSum / runs << "ms)"
		<< " TPI: " << timePerIteration << "ms" << " (AVG: " << tpiSum / runs << "ms)" << std::endl;
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
		float x = (float)(rand() % range + min);
		float y = (float)(rand() % range + min);

		Vector2 vector = { x, y };

		targets->at(i)->Translate(vector);
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
		nodeJoint->value.segment->Translate((nodeJoint->value.GetPosition() + nodeJoint->parent->value.GetPosition()) / 2.0f);
		nodeJoint->value.segment->SetScale(Vector3{ 0.2f, Vector2::Distance(nodeJoint->value.GetPosition(), nodeJoint->parent->value.GetPosition()) + 0.25f, 1.0f });

		nodeJoint->value.segment->LookAt(nodeJoint->parent->value);
	}
}

void Fabrik2D::UpdatePosition() {
	tree->Preorder([&](Node<Joint2D>* nodeJoint) {
		nodeJoint->value.Translate(nodeJoint->value.PositionTmp);
		ConnectJoints(nodeJoint);
	});
}

void Fabrik2D::Forward() {
	Node<Joint2D>* subbase = NULL;

	for (int i = 0; i < targets->size(); i++) {
		targets->at(i)->endEffector->value.PositionTmp = targets->at(i)->GetPosition();

		FindJoint(targets->at(i)->endEffector->value.id)->PositionTmp = targets->at(i)->GetPosition();
	}

	tree->Inorder([&](Node<Joint2D>* nodeJoint) {
		if (nodeJoint->parent != tree->root && nodeJoint != tree->root) {
			Vector2 previous_joint_vector = nodeJoint->parent->value.PositionTmp;
			Vector2 current_joint_vector = nodeJoint->value.PositionTmp;
			Vector2 direction = (previous_joint_vector - current_joint_vector).Normalize();

			float joints_distance = DistanceBetweenJoints(nodeJoint);	

			if (nodeJoint->parent->value.IsSubBase) {
				subbase = nodeJoint->parent;
				nodeJoint->parent->value.PositionTmp += (current_joint_vector + direction * joints_distance) / (float)subbase->child.size() / 10;
			}
			else {
				nodeJoint->parent->value.PositionTmp = current_joint_vector + direction * joints_distance;
			}

			FindJoint(nodeJoint->parent->value.id)->PositionTmp = nodeJoint->parent->value.PositionTmp;
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
				nodeJoint->value.constraint->Apply(nodeJoint);
			}

			FindJoint(nodeJoint->value.id)->PositionTmp = nodeJoint->value.PositionTmp;
		});
	}
}

void Fabrik2D::ShowcaseNextStep() {
	if (forwardCounter != forwardOrder.size() - 1)
	{
		if (forwardCounter == 0)
		{
			Forward();
		}

		if (forwardCounter != forwardOrder.size() - 1)
		{
			if (forwardCounter > 0)
			{
				FindJoint(forwardOrder.at(forwardCounter - 1))->SetDefaultColor();
			}

			int currentJointId = forwardOrder.at(forwardCounter);
			Joint2D* currentJoint = FindJoint(currentJointId);

			currentJoint->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

			currentJoint->Translate(currentJoint->PositionTmp);

			forwardCounter++;
		}
	}
	else
	{
		if (backwardCounter != backwardOrder.size())
		{
			if (backwardCounter == 0)
			{
				FindJoint(forwardOrder.at(forwardCounter - 1))->SetDefaultColor();
				Backward();
			}

			if (backwardCounter != backwardOrder.size())
			{
				if (backwardCounter > 0)
				{
					FindJoint(backwardOrder.at(backwardCounter - 1))->SetDefaultColor();
				}

				int currentJointId = backwardOrder.at(backwardCounter);
				Joint2D* currentJoint = FindJoint(currentJointId);

				currentJoint->SetColor({ 0.0f, 1.0f, 1.0f, 1.0f });

				currentJoint->Translate(currentJoint->PositionTmp);

				backwardCounter++;
			}
		}
		else
		{
			UpdatePosition();
			FindJoint(backwardOrder.at(backwardCounter - 1))->SetDefaultColor();
			forwardCounter = 0;
			backwardCounter = 0;
		}
	}
}

Joint2D* Fabrik2D::FindJoint(int id)
{
	for (int i = 0; i < jointsTmp->size(); i++)
	{
		if (id == jointsTmp->at(i)->id)
		{
			return jointsTmp->at(i);
		}
	}
}







//void Fabrik2D::ShowcaseNextStep() {
//	if (forwardCounter != 0)
//	{
//		if (forwardCounter == jointsTmp->size() - 1)
//		{
//			Forward();
//		}
//		else
//		{
//			jointsTmp->at(forwardCounter + 1)->SetDefaultColor();
//		}
//
//		std::cout << "    " << forwardCounter << "F: " << jointsTmp->at(forwardCounter)->GetPosition() << std::endl;
//		jointsTmp->at(forwardCounter)->Translate(vectorsTmp->at(forwardCounter));
//		jointsTmp->at(forwardCounter)->SetColor(Color{ 0.0f, 0.0f, 1.0f, 1.0f });
//
//		forwardCounter--;
//	}
//	else
//	{
//		if (backwardCounter == 0)
//		{
//			Backward();
//		}
//
//		if (backwardCounter != jointsTmp->size() - 1) {
//
//			if (backwardCounter > 0)
//			{
//				jointsTmp->at(backwardCounter)->SetDefaultColor();
//			}
//
//			std::cout << "    " << backwardCounter << "B: " << jointsTmp->at(backwardCounter)->GetPosition() << std::endl;
//			jointsTmp->at(backwardCounter + 1)->Translate(vectorsTmp->at(backwardCounter + 1));
//			jointsTmp->at(backwardCounter + 1)->SetColor(Color{ 1.0f, 0.0f, 1.0f, 1.0f });
//
//			backwardCounter++;
//		}
//		else
//		{
//			UpdatePosition();
//			jointsTmp->at(backwardCounter)->SetDefaultColor();
//			forwardCounter = jointsTmp->size() - 1;
//			backwardCounter = 0;
//		}
//	}
//}
//
//void Fabrik2D::ForwardNextStep() {
//	if (forwardCounter != 0)
//	{
//		if (forwardCounter != jointsTmp->size() - 1)
//		{
//			jointsTmp->at(forwardCounter + 1)->SetDefaultColor();
//		}
//
//		std::cout << "    " << forwardCounter << "F: " << jointsTmp->at(forwardCounter)->GetPosition() << std::endl;
//		jointsTmp->at(forwardCounter)->Translate(vectorsTmp->at(forwardCounter));
//		jointsTmp->at(forwardCounter)->SetColor(Color{ 0.0f, 0.0f, 1.0f, 1.0f });
//
//		forwardCounter--;
//	}
//}
//
//void Fabrik2D::BackwardNextStep() {
//	if (backwardCounter != jointsTmp->size() - 1) {
//
//		if (backwardCounter > 0)
//		{
//			jointsTmp->at(backwardCounter)->SetDefaultColor();
//		}
//
//		std::cout << "    " << backwardCounter << "B: " << jointsTmp->at(backwardCounter)->GetPosition() << std::endl;
//		jointsTmp->at(backwardCounter + 1)->Translate(vectorsTmp->at(backwardCounter + 1));
//		jointsTmp->at(backwardCounter + 1)->SetColor(Color{ 1.0f, 0.0f, 1.0f, 1.0f });
//
//		backwardCounter++;
//	}
//	else
//	{
//		UpdatePosition();
//	}
//}