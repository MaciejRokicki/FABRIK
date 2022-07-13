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

void Transform::Translate(Vector3 position) {
    Vector3 tmp_vector{ _matrix[12], _matrix[13], _matrix[14] };

    _matrix.Translate(-tmp_vector.x, -tmp_vector.y, -tmp_vector.z);
    _matrix.Translate(position.x, position.y, position.z);
}

void Transform::SetScale(Vector3 scale) {
    Vector3 tmp_vector{ _matrix[12], _matrix[13], _matrix[14] };

    Translate(!tmp_vector);
    _matrix.Scale(scale.x, scale.y, scale.z);
    Translate(tmp_vector);
}

void Transform::Rotate(Vector3 angle) {
    Vector3 tmp_vector{ _matrix[12], _matrix[13], _matrix[14] };

    Translate(!tmp_vector);

    _matrix.RotateX(angle.x);
    _matrix.RotateY(angle.y);
    _matrix.RotateZ(angle.z);

    Translate(tmp_vector);
}

void Transform::LookAt(Transform& transform) {
    float angle = (180 / M_PI) * atan2(transform._matrix[12] - _matrix[12], transform._matrix[13] - _matrix[13]);

    Rotate(Vector3{ 0.0f, 0.0f, angle });
}