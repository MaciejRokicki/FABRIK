#ifndef MODELPROGRAM_H
#define MODELPROGRAM_H

#include "cameraProgram.h"

class ModelProgram : public CameraProgram
{
public:
    void Init(const char* vertex_shader_file, const char* fragment_shader_file);
    void SetModelMatrix(const Mat4&) const;
private:
    GLuint model_matrix_location_;
};

#endif // !MODELPROGRAM_H
