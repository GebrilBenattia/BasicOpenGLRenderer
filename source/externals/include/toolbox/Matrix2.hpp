#pragma once

#include "Vector2.hpp"

class Matrix2
{
public:
	Vector2 Row0;
	Vector2 Row1;

	Matrix2();
	Matrix2(Vector2 row0, Vector2 row1);
	Matrix2(Matrix2& mat);
	//Matrix2(const std::initializer_list<const std::initializer_list<float>>& data);
	~Matrix2();

	Vector2 Diag();
	float Trace();
	Matrix2 Opp();
	Matrix2 Transpose();
	static Matrix2 Add(const Matrix2& m, const Matrix2& m2);
	static Matrix2 MultiplyBy(const Matrix2& m, const Matrix2& m2);
	static Matrix2 MultiplyBy(const Matrix2& m, const float f);
	static float Determinant(const Matrix2& m);
	static Matrix2 PivotGaussJordan(const Matrix2& m);
	Matrix2 Augment(const Matrix2& m);
	static Matrix2 Identity();
	static Matrix2 Rotation2D(const float angle);
	static Matrix2 Scaling2D(const Vector2& v);
};

//std::ostream& operator<<(std::ostream& os, const Matrix2& v);
