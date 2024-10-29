#pragma once

#include "Vector3.hpp"

class Matrix3
{
public:
	Vector3 Row0;
	Vector3 Row1;
	Vector3 Row2;

	Matrix3();
	Matrix3(Vector3 row0, Vector3 row1, Vector3 row2);
	//Matrix3(Matrix3& m);
	//Matrix3(const std::initializer_list<const std::initializer_list<float>>& data);
	~Matrix3();

	Vector3 Diag();
	float Trace();
	Matrix3 Opp();
	Matrix3 Transpose();
	static Matrix3 Add(const Matrix3& m, const Matrix3& m2);
	static Matrix3 MultiplyBy(const Matrix3& m, const float f);
	static Matrix3 MultiplyBy(const Matrix3& m, const Matrix3& m2);
	static Vector3 MultiplyBy(const Vector3& v, const Matrix3& m);
	Matrix3 Augment(const Matrix3& m);
	static Matrix3 Identity(int size);
	static Matrix3 Inverse(Matrix3& m);
	static Matrix3 Rotation3D(const float angle, const Vector3& v);
	static Matrix3 Scaling3D(const Vector3& v);
};

//std::ostream& operator<<(std::ostream& os, const Matrix3& v);
