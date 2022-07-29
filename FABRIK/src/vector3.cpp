#include "headers/vector2.h"
#include "headers/vector3.h"

Vector3 Vector3::zero { 0.0f, 0.0f, 0.0f };
Vector3 Vector3::one { 1.0f, 1.0f, 1.0f };

float Vector3::Distance(Vector3 vec1, Vector3 vec2) {
	return sqrtf(powf(vec2.x - vec1.x, 2) + powf(vec2.y - vec1.y, 2) + powf(vec2.z - vec1.z, 2));
}

bool Vector3::InRange(const Vector3& vec) {
	return *this >= vec && *this <= vec;
}

float Vector3::Magnitude() {
	return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::Normalize() {
	float length = Magnitude();
	return Vector3({ x / length, y / length, z / length });
}

Vector3 Vector3::operator !() {
	return Vector3{ -this->x, -this->y, -this->z };
}

bool Vector3::operator ==(const Vector3& vec) {
	return this->x == vec.x && this->y == vec.y && this->z == vec.z;
}

bool Vector3::operator !=(const Vector3& vec) {
	return this->x != vec.x || this->y != vec.y || this->z != vec.z;
}

Vector3 Vector3::operator +(const Vector3& vec) {
	return Vector3({ this->x + vec.x, this->y + vec.y, this->z + vec.z });
}

Vector3 Vector3::operator -(const Vector3& vec) {
	return Vector3({ this->x - vec.x, this->y - vec.y, this->z - vec.z });
}

Vector3 Vector3::operator *(const Vector3& vec) {
	return Vector3({ this->x * vec.x, this->y * vec.y, this->z * vec.z });
}

Vector3 Vector3::operator *(const float f) {
	return Vector3({ this->x * f, this->y * f, this->z * f });
}

Vector3 Vector3::operator /(const Vector3& vec) {
	return Vector3({ this->x / vec.x, this->y / vec.y, this->z /vec.z });
}

Vector3 Vector3::operator /(const float f) {
	return Vector3({ this->x / f, this->y / f, this->z / f });
}

bool Vector3::operator >(const Vector3& vec) {
	return this->x > vec.x && this->y > vec.y && this->z > vec.z;
}

bool Vector3::operator <(const Vector3& vec) {
	return this->x < vec.x && this->y < vec.y && this->z < vec.z;
}

bool Vector3::operator >=(const Vector3& vec) {
	return this->x >= vec.x && this->y >= vec.y && this->z >= vec.z;
}

bool Vector3::operator <=(const Vector3& vec) {
	return this->x <= vec.x && this->y <= vec.y && this->z <= vec.z;
}

Vector3::operator Vector2() {
	return { this->x, this->y };
}

std::ostream& operator <<(std::ostream& os, const Vector3& vec) {
	return os << vec.x << " " << vec.y << " " << vec.z;
};