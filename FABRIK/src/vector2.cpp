#include "headers/vector2.h"
#include "headers/vector3.h"

Vector2 Vector2::zero { 0.0f, 0.0f };
Vector2 Vector2::one { 1.0f, 1.0f };

float Vector2::Distance(Vector2 vec1, Vector2 vec2) {
	return sqrtf(powf(vec2.x - vec1.x, 2) + powf(vec2.y - vec1.y, 2));
}

bool Vector2::InRange(const Vector2& vec) {
	return *this >= vec && *this <= vec;
}

float Vector2::Magnitude() {
	return sqrtf(x * x + y * y);
}

Vector2 Vector2::Normalize() {
	float length = Magnitude();
	return Vector2({ x / length, y / length});
}

Vector2 Vector2::operator !() {
	return Vector2({ -this->x, -this->y });
}

bool Vector2::operator ==(const Vector2& vec) {
	return this->x == vec.x && this->y == vec.y;
}

bool Vector2::operator !=(const Vector2& vec){
	return this->x != vec.x || this->y != vec.y;
}

Vector2 Vector2::operator +(const Vector2& vec) {
	return Vector2({ this->x + vec.x, this->y + vec.y });
}

Vector2& Vector2::operator +=(const Vector2& vec){
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2 Vector2::operator -(const Vector2& vec) {
	return Vector2({ this->x - vec.x, this->y - vec.y });
}

Vector2& Vector2::operator -=(const Vector2& vec){
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2 Vector2::operator *(const Vector2& vec) {
	return Vector2({ this->x * vec.x, this->y * vec.y });
}

Vector2 Vector2::operator *(const float f){
	return Vector2({ this->x * f, this->y * f });
}

Vector2& Vector2::operator *=(const Vector2& vec){
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2& Vector2::operator *=(const float f){
	this->x *= f;
	this->y *= f;

	return *this;
}

Vector2 Vector2::operator /(const Vector2& vec) {
	return Vector2({ this->x / vec.x, this->y / vec.y });
}

Vector2 Vector2::operator /(const float f) {
	return Vector2({ this->x / f, this->y / f });
}

Vector2& Vector2::operator /=(const Vector2& vec){
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2& Vector2::operator /=(const float f){
	this->x /= f;
	this->y /= f;

	return *this;
}

bool Vector2::operator >(const Vector2& vec) {
	return this->x > vec.x && this->y > vec.y;
}

bool Vector2::operator <(const Vector2& vec) {
	return this->x < vec.x && this->y < vec.y;
}

bool Vector2::operator >=(const Vector2& vec) {
	return this->x >= vec.x && this->y >= vec.y;
}

bool Vector2::operator <=(const Vector2& vec) {
	return this->x <= vec.x && this->y <= vec.y;
}

Vector2::operator Vector3() {
	return { this->x, this->y, 0.0f };
}

std::ostream& operator <<(std::ostream& os, const Vector2& vec){
	return os << "(" << vec.x << ", " << vec.y << ")";
};