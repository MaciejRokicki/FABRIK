#include "headers/object.h"
#include "headers/color.h"

Object::Object() : Transform() {
    defaultColor = color;
}

Object::Object(Vector3 position, Vector3 scale, Color defaultColor) : Transform(position, scale) {
    color = defaultColor;
    this->defaultColor = defaultColor;
}

void Object::Init() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesSize, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)sizeof(vertices[0].position));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indicesSize, indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object::Draw(const Camera& camera) const {
    glUseProgram(camera);
    glBindVertexArray(vao);

    camera.SetModelMatrix(_matrix);

    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Object::SetDefaultColor() {
    SetColor(defaultColor);
}

void Object::SetColor(Color color, bool isDefaultColor) {
    if (isDefaultColor) {
        defaultColor = color;
    }

    this->color = color;

    for (int i = 0; i < verticesSize; i++) {
        vertices[i] = { {vertices[i].position[0], vertices[i].position[1], vertices[i].position[2], vertices[i].position[3] }, this->color };
    }

    this->~Object();
    Init();
}

Object::~Object() {
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &vertexBuffer);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
}