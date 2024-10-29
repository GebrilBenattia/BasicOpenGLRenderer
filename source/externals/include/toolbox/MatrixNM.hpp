#pragma once

#include "VectorN.hpp"

class Matrix
{
public:
	std::vector<std::vector<float>> matrixData;

	int rows, column = 0;

	Matrix();
	Matrix(const int row, const int column, float value);
	Matrix(const int row, const int column, std::vector<std::vector<float>> values);
	//Matrix(const std::initializer_list<const std::initializer_list<float>>& data);
	~Matrix();

	Vector Diag();
	float Trace();
	Matrix Opp();
	Matrix Transpose();
	bool IsSquare();
	bool IsDiagonal();
	static Matrix Add(const Matrix& m, const Matrix& m2);
	static Matrix MultiplyBy(const Matrix& m, const float f);
	static Matrix MultiplyBy(const Matrix& m, const Matrix& m2);
	static float Determinant(const Matrix& m);
	static Matrix PivotGaussJordan(const Matrix& m);
	Matrix Augment(const Matrix& m);
	static Matrix Identity(int size);
	static Matrix Inverse(Matrix& m);
	static Matrix Rotation2D(const float angle);
	static Matrix Rotation3D(const float angle, const Vector& v);
	static Matrix Scaling2D(const Vector& v);
	static Matrix Scaling3D(const Vector& v);
	static Matrix TRS(Vector translate, Vector angle, Vector scale);
};

std::ostream& operator<<(std::ostream& os, const Matrix& v);
