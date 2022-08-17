#include "headers/quaternion.h"
#include "headers/mathf.h"

Quaternion::Quaternion() { 
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion Quaternion::FromEulersAngles(Vector3 angles) {
    angles = Mathf::Deg2Rad(angles);

    float cosX = cosf(angles.x * 0.5);
    float sinX = sinf(angles.x * 0.5);
    float cosY = cosf(angles.y * 0.5);
    float sinY = sinf(angles.y * 0.5);
    float cosZ = cosf(angles.z * 0.5);
    float sinZ = sinf(angles.z * 0.5);

    float x = sinX * cosY * cosZ - cosX * sinY * sinZ;
    float y = cosX * sinY * cosZ + sinX * cosY * sinZ;
    float z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    float w = cosX * cosY * cosZ + sinX * sinY * sinZ;

    Quaternion quaternion = Quaternion(x, y, z, w);

    return quaternion;
}

Vector3 Quaternion::ToEulerAngles() {
    Vector3 eulerAngles = Vector3::zero;

    float yX = 2 * (w * x + y * z);
    float xX = 1 - 2 * (x * x + y * y);
    eulerAngles.x = atan2f(yX, xX);

    double sinp = 2 * (w * y - z * x);
    if (fabsf(sinp) >= 1)
        eulerAngles.y = copysign(M_PI / 2, sinp);
    else
        eulerAngles.y = asinf(sinp);

    float zY = 2 * (w * z + x * y);
    float zX = 1 - 2 * (y * y + z * z);
    eulerAngles.z = atan2f(zY, zX);

    eulerAngles = Mathf::Rad2Deg(eulerAngles);
    eulerAngles = Mathf::NormalizeAngle360(eulerAngles);

    return eulerAngles;
}

std::ostream& operator <<(std::ostream& os, const Quaternion& quaternion)
{
    return os << "(" << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << ", " << quaternion.w << ")";
};