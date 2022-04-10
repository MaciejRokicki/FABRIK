#include "headers/modelProgram.h"

void ModelProgram::Init(const char* vertex_shader_file, const char* fragment_shader_file)
{
    CameraProgram::Init(vertex_shader_file, fragment_shader_file);
    model_matrix_location_ = GetUniformLocationOrDie("model_matrix");
}


void ModelProgram::SetModelMatrix(const Mat4& matrix) const
{
    glUniformMatrix4fv(model_matrix_location_, 1, GL_FALSE, matrix);
}
