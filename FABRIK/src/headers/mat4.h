#ifndef MAT4_H
#define MAT4_H

#ifndef M_PI
#define M_PI 3.14159265f
#endif

class Mat4 {
public:
	Mat4();
	operator const float* () const { return matrix_; }
	static Mat4 CreatePerspectiveProjectionMatrix(
		float fovy,
		float aspect_ratio,
		float near_plane,
		float far_plane);
	static Mat4 CreateOrthographicProjectionMatrix(
		float left,
		float right,
		float bottom,
		float top,
		float near_plane,
		float far_plane);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Scale(float x_scale, float y_scale, float z_scale);
	void Translate(float delta_x, float delta_y, float delta_z);
	void SetUnitMatrix();
	void Log();
private:
	float matrix_[16];
	void MultiplyBy(const Mat4&);
	explicit Mat4(float);
};

#endif // !MAT4_H