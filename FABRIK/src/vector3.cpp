#include "headers/vector3.h";

Vector3 Vector3::zero { 0.0f, 0.0f, 0.0f };
Vector3 Vector3::one { 1.0f, 1.0f, 1.0f };

float Vector3::Distance(Vector3 vec1, Vector3 vec2) {
	return sqrtf(powf(vec2.x - vec1.x, 2) + powf(vec2.y - vec1.y, 2) + powf(vec2.z - vec1.z, 2));
}

Vector3 Vector3::operator!() {
	return Vector3{ -this->x, -this->y, -this->z };
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
	return os << vec.x << " " << vec.y << " " << vec.y;
};