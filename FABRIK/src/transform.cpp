#include <iostream>

#include <GL/glew.h>

#include "headers/transform.h"
#include "headers/mathf.h"

Transform::Transform() { }

Transform::Transform(Vector3 position, Vector3 scale) {
    Translate(position);
    SetScale(scale);
}

Vector3 Transform::GetPosition() {
    return { _matrix[12], _matrix[13], _matrix[14] };
}

Vector3 Transform::GetRotation() {
    //ZYX - odwrotnie do kolejnosci rotacji obiektow
    Vector3 scale = GetScale();

    float m00 = _matrix[0] / scale.x;
    float m01 = _matrix[1] / scale.x;
    float m02 = _matrix[2] / scale.x;
    float m10 = _matrix[4] / scale.y;
    float m11 = _matrix[5] / scale.y;
    float m12 = _matrix[6] / scale.y;
    float m20 = _matrix[8] / scale.z;
    float m21 = _matrix[9] / scale.z;
    float m22 = _matrix[10] / scale.z;
     
    float T1 = atan2f(m01, m00);
    float C2 = sqrtf(m12 * m12 + m22 * m22);
    float T2 = atan2f(-m02, C2);
    float S1 = sinf(T1);
    float C1 = cosf(T1);
    float T3 = atan2f(S1 * m20 - C1 * m21, C1 * m11 - S1 * m10);

    return Mathf::Rad2Deg({ T3, T2, T1 });
}

Vector3 Transform::GetScale() {
    return Vector3({
        Vector3({_matrix[0], _matrix[1], _matrix[2]}).Magnitude(),
        Vector3({_matrix[4], _matrix[5], _matrix[6]}).Magnitude(),
        Vector3({_matrix[8], _matrix[9], _matrix[10]}).Magnitude(),
    });
}

void Transform::Translate(Vector3 position) {
    position = position - GetPosition();

    this->_matrix *= Matrix4::Translate(position);
}

void Transform::SetScale(Vector3 scale) {
    Vector3 currentPosition = GetPosition();
    Vector3 currentRotation = GetRotation();
    Vector3 currentScale = GetScale();

    this->_matrix = 
        Matrix4::Scale(scale) * 
        Matrix4::Rotate(currentRotation) *
        Matrix4::Translate(currentPosition);
}

void Transform::Rotate(Vector3 angle) {
    Vector3 currentPosition = GetPosition();
    Vector3 currentRotation = GetRotation();
    Vector3 currentScale = GetScale();

    this->_matrix =
        Matrix4::Scale(currentScale) *
        Matrix4::Rotate(angle) *
        Matrix4::Translate(currentPosition);
}

void Transform::LookAt(Transform& transform) {
    Vector3 currentPosition = GetPosition();
    Vector3 currentScale = GetScale();
    Vector3 targetPosition = transform.GetPosition();

    Vector3 vec = targetPosition - currentPosition;
    float xz = sqrtf(vec.x * vec.x + vec.z * vec.z);

    Vector3 angles = Mathf::Rad2Deg(Vector3 {
        atan2f(vec.y, xz),
        atan2f(-vec.x, vec.z)
    });

    this->_matrix =
        Matrix4::Scale(currentScale) *
        Matrix4::Rotate(angles) *
        Matrix4::Translate(currentPosition);
}