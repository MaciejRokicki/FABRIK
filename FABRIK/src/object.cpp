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
    //const Vertex kVertices[4] = {
    //    { { -0.1f, 0.0f,  0.0f, 1.0f }, color },
    //    { { -0.1f, 2.0f,  0.0f, 1.0f }, color },
    //    { {  0.1f, 2.0f,  0.0f, 1.0f }, color },
    //    { {  0.1f, 0.0f,  0.0f, 1.0f }, color },
    //};

    const Vertex kVertices[4] = {
        { { -0.5f, -0.5f,  0.0f, 1.0f }, color },
        { { -0.5f,  0.5f,  0.0f, 1.0f }, color },
        { {  0.5f, -0.5f,  0.0f, 1.0f }, color },
        { {  0.5f,  0.5f,  0.0f, 1.0f }, color },
    };

    const GLuint kIndices[6] = {
        0,1,2,  2,1,3
    };

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]), (GLvoid*)sizeof(kVertices[0].postion));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &_index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kIndices), kIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object::Draw(const ModelProgram& program) const {
    glUseProgram(program);
    glBindVertexArray(_vao);

    program.SetModelMatrix(_matrix);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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