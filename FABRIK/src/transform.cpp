#include <iostream>

#include <GL/glew.h>

#include "headers/transform.h"
#include "headers/vertex.h"
#include "headers/mat4.h"
#include "headers/transform.h"

Transform::Transform() { }

Transform::Transform(Vector3 position, Vector3 scale) {
    SetScale(scale);
    Translate(position);
}

Vector3 Transform::GetPosition() {
    return { _matrix[12], _matrix[13], _matrix[14] };
}

Vector3 Transform::GetRotation() {
    return rotation;
}

Vector3 Transform::GetScale() {
    return Vector3({
        Vector3({_matrix[0], _matrix[4], _matrix[8]}).Magnitude(),
        Vector3({_matrix[1], _matrix[5], _matrix[9]}).Magnitude(),
        Vector3({_matrix[2], _matrix[6], _matrix[10]}).Magnitude(),
    });
}

void Transform::Translate(Vector3 position) {
    position = position - GetPosition();

    _matrix.Translate(position.x, position.y, position.z);
}

void Transform::SetScale(Vector3 scale) {
    Vector3 currentPosition = GetPosition();

    Translate(!currentPosition);
    Rotate(Vector3::zero);
    _matrix.Scale(scale.x, scale.y, scale.z);
    Rotate(rotation);
    Translate(currentPosition);
}

void Transform::Rotate(Vector3 angle) {
    //Vector3 currentPosition = GetPosition();
    //Vector3 currentScale = GetScale();

    //Mat4 rotationMatrix;
    //rotationMatrix.SetUnitMatrix();

    //rotationMatrix.RotateY(angle.y);
    //rotationMatrix.RotateX(angle.x);
    //rotationMatrix.RotateZ(angle.z);

    //rotationMatrix.Scale(currentScale.x, currentScale.y, currentScale.z);
    //rotationMatrix.Translate(currentPosition.x, currentPosition.y, currentPosition.z);

    //_matrix = rotationMatrix;


    //#######################


    //Vector3 tmp_vector{ _matrix[12], _matrix[13], _matrix[14] };

    //Translate(!tmp_vector);

    //_matrix.RotateX(angle.x);
    //_matrix.RotateY(angle.y);
    //_matrix.RotateZ(angle.z);

    //Translate(tmp_vector);


    //#######################


    Vector3 currentPosition = GetPosition();

    Translate(!currentPosition);

    _matrix.RotateX(angle.x - rotation.x);
    _matrix.RotateY(angle.y - rotation.y);
    _matrix.RotateZ(angle.z - rotation.z);

    rotation = angle;

    Translate(currentPosition);
}

void Transform::LookAt2D(Transform& transform) {
    Vector3 position = GetPosition();
    Vector3 target = transform.GetPosition();

    Vector3 vec = target - position;

    Vector3 angles = Vector3{
        0.0f,
        0.0f,
        atan2f(vec.x, vec.y) * 180.0f / M_PI
    };

    Rotate(angles);
}

void Transform::LookAt3D(Transform& transform) {
    Vector3 position = GetPosition();
    Vector3 target = transform.GetPosition();

    Vector3 vec = target - position;
    float xz = sqrtf(vec.x * vec.x + vec.z * vec.z);

    Vector3 angles = Vector3{
        atan2f(vec.y, xz) * 180.0f / M_PI,
        atan2f(-vec.x, vec.z) * 180.0f / M_PI,
        0.0f
    };

    Rotate(angles);
}