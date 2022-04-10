#include <iostream>

#include <GL/glew.h>

#include "headers/transform.h"
#include "headers/vertex.h"
#include "headers/mat4.h"
#include "headers/transform.h"

Transform::Transform(Vector2 position, Vector2 scale) : Model::Model() {
    Scale(scale);
    Translate(position);
}

void Transform::SetColor(Color color) {
    Model::color = color;

    Model::Init();
}

void Transform::Translate(Vector2 position) {
    Vector3 tmp_vector{ matrix_[12], matrix_[13], matrix_[14] };

    Translate(!tmp_vector);
    matrix_.Translate(position.x, position.y, 0.0f);
}

void Transform::Translate(Vector3 position) {
    //Vector3 tmp_vector{ matrix_[12], matrix_[13], matrix_[14] };

    //Translate(!tmp_vector);
    matrix_.Translate(position.x, position.y, position.z);
    //Translate(tmp_vector);
}

void Transform::Scale(Vector2 scale) {
    Vector3 tmp_vector{ matrix_[12], matrix_[13], matrix_[14] };

    Translate(!tmp_vector);
    matrix_.Scale(scale.x, scale.y, 0.0f);
    Translate(tmp_vector);
}

void Transform::Rotate(Vector3 angle) {
    Vector3 tmp_vector{ matrix_[12], matrix_[13], matrix_[14] };

    Translate(!tmp_vector);

    matrix_.RotateX(angle.x);
    matrix_.RotateY(angle.y);
    matrix_.RotateZ(angle.z);

    Translate(tmp_vector);
}

void Transform::LookAt(Transform& transform) {
    float angle = (180 / M_PI) * atan2(transform.matrix_[12] - matrix_[12], transform.matrix_[13] - matrix_[13]);

    Rotate(Vector3{ 0.0f, 0.0f, -angle });
}