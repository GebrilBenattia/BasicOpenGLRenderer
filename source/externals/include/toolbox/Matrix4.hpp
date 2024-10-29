#pragma once

#include "Vector4.hpp"

class Matrix4
{
public:
	Vector4 Row0;
	Vector4 Row1;
	Vector4 Row2;
	Vector4 Row3;

	Matrix4();
	Matrix4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3);
	//Matrix4(Matrix4& m);

	~Matrix4();

	Vector4 Diag();
	float Trace();
	Matrix4 Opp();
	Matrix4 Transpose();
	static Matrix4 Add(const Matrix4& m, const Matrix4& m2);
	static Matrix4 MultiplyBy(const Matrix4& m, const float f);
	static Matrix4 MultiplyBy(const Matrix4& m, const Matrix4& m2);
	static Vector4 MultiplyBy(const Matrix4& m, const Vector4& v);
	static float Determinant(const Matrix4& m);
	static Matrix4 PivotGaussJordan(const Matrix4& m);
	Matrix4 Augment(const Matrix4& m);
	static Matrix4 Identity();
	static Matrix4 Inverse(Matrix4& m);
	static Matrix4 TRS(Vector3 translate, Vector3 angle, Vector3 scale);
	static void Projection(float fov, float aspectRatio, float zNear, float zFar, Matrix4& m);
	static void View(Vector3 eye, Vector3 center, Vector3 up, Matrix4& m);
	void Log() const;
	static void Rotation(const float angle, const Vector3& axis, Matrix4& dst);
};

//std::ostream& operator<<(std::ostream& os, const Matrix4& v);
