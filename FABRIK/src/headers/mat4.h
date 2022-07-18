#ifndef MAT4_H
#define MAT4_H

#ifndef M_PI
#define M_PI 3.14159265f
#endif

class Mat4 {
public:
	float matrix[16];

	Mat4();
	explicit Mat4(float);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Scale(float x_scale, float y_scale, float z_scale);
	void Translate(float delta_x, float delta_y, float delta_z);
	void MultiplyBy(const Mat4&);
	void SetUnitMatrix();
	void Log();

	operator const float* () const { return matrix; }
};

#endif // !MAT4_H