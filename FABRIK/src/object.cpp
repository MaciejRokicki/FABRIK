#include "headers/object.h"
#include "headers/color.h"

Object::Object() : Transform() {
    default_color = color;
}

Object::Object(Vector3 position, Vector3 scale, Color default_color) : Transform(position, scale) {
    color = default_color;
    this->default_color = default_color;
}

void Object::Init() {
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0]) * _vertices_size, _vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(_vertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(_vertices[0]), (GLvoid*)sizeof(_vertices[0].position));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &_index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _indices_size, _indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object::Draw(const Camera& camera) const {
    glUseProgram(camera);
    glBindVertexArray(_vao);

    camera.SetModelMatrix(_matrix);

    glDrawElements(GL_TRIANGLES, _indices_size, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Object::SetDefaultColor() {
    SetColor(default_color);
}

void Object::SetColor(Color color, bool isDefaultColor) {
    if (isDefaultColor) {
        default_color = color;
    }

    this->color = color;

    for (int i = 0; i < _vertices_size; i++) {
        _vertices[i] = { {_vertices[i].position[0], _vertices[i].position[1], _vertices[i].position[2], _vertices[i].position[3] }, this->color };
    }

    this->~Object();
    Init();
}

Object::~Object() {
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &_index_buffer);
    glDeleteBuffers(1, &_vertex_buffer);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &_vao);
}