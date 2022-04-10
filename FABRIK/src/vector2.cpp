#include <cmath>

#include "headers/vector2.h";

Vector2 Vector2::zero { 0.0f, 0.0f };
Vector2 Vector2::one { 1.0f, 1.0f };

float Vector2::Distance(Vector2 vec1, Vector2 vec2) {
	return sqrtf(powf(vec2.x - vec1.x, 2) + powf(vec2.y - vec1.y, 2));
}

bool Vector2::InRange(const Vector2& vec) {
	return *this >= vec && *this <= vec;
}

Vector2 Vector2::operator!() {
	return Vector2{ -this->x, -this->y };
}

bool Vector2::operator==(const Vector2& vec) {
	return this->x == vec.x && this->y == vec.y;
}

bool Vector2::operator!=(const Vector2& vec) {
	return this->x != vec.x || this->y != vec.y;
}

Vector2 Vector2::operator+(const Vector2& vec) {
	return Vector2({ this->x + vec.x, this->y + vec.y });
}

Vector2 Vector2::operator-(const Vector2& vec) {
	return Vector2({ this->x - vec.x, this->y - vec.y });
}

Vector2 Vector2::operator*(const Vector2& vec) {
	return Vector2({ this->x * vec.x, this->y * vec.y });
}

Vector2 Vector2::operator*(const float f) {
	return Vector2({ this->x * f, this->y * f });
}

Vector2 Vector2::operator/(const Vector2& vec) {
	return Vector2({ this->x / vec.x, this->y / vec.y });
}

Vector2 Vector2::operator/(const float f) {
	return Vector2({ this->x / f, this->y / f });
}

bool Vector2::operator>(const Vector2& vec) {
	return this->x > vec.x && this->y > vec.y;
}

bool Vector2::operator<(const Vector2& vec) {
	return this->x < vec.x && this->y < vec.y;
}

bool Vector2::operator>=(const Vector2& vec) {
	return this->x >= vec.x && this->y >= vec.y;
}

bool Vector2::operator<=(const Vector2& vec) {
	return this->x <= vec.x && this->y <= vec.y;
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
	return os << vec.x << " " << vec.y;
};