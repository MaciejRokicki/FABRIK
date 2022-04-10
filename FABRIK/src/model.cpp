#include "headers/model.h"
#include "headers/color.h"

Model::Model() { }

void Model::Init() {
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

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]), (GLvoid*)sizeof(kVertices[0].postion));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kIndices), kIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::Draw(const ModelProgram& program) const {
    glUseProgram(program);
    glBindVertexArray(vao_);

    program.SetModelMatrix(matrix_);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

Model::~Model() {
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &index_buffer_);
    glDeleteBuffers(1, &vertex_buffer_);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao_);
}