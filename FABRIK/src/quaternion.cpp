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

    Quaternion quaternion;
    quaternion.x = sinX * cosY * cosZ - cosX * sinY * sinZ;
    quaternion.y = cosX * sinY * cosZ + sinX * cosY * sinZ;
    quaternion.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    quaternion.w = cosX * cosY * cosZ + sinX * sinY * sinZ;

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

    return eulerAngles;
}

Vector3 Quaternion::operator *(const Vector3& vec)
{
    float num = x * 2.0f;
    float num2 = y * 2.0f;
    float num3 = z * 2.0f;
    float num4 = x * num;
    float num5 = y * num2;
    float num6 = z * num3;
    float num7 = x * num2;
    float num8 = x * num3;
    float num9 = y * num3;
    float num10 = w * num;
    float num11 = w * num2;
    float num12 = w * num3;

    Vector3 result;
    result.x = (1.0f - (num5 + num6)) * vec.x + (num7 - num12) * vec.y + (num8 + num11) * vec.z;
    result.y = (num7 + num12) * vec.x + (1.0f - (num4 + num6)) * vec.y + (num9 - num10) * vec.z;
    result.z = (num8 - num11) * vec.x + (num9 + num10) * vec.y + (1.0f - (num4 + num5)) * vec.z;

    return result;
}

std::ostream& operator <<(std::ostream& os, const Quaternion& quaternion)
{
    return os << "(" << quaternion.x << ", " << quaternion.y << ", " << quaternion.z << ", " << quaternion.w << ")";
};