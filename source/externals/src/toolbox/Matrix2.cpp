#include "Matrix2.hpp"
#include <cassert>
#define _USE_MATH_DEFINES
#include "math.h"
#include <iostream>

Matrix2::Matrix2()
{

}

Matrix2::Matrix2(Vector2 row0, Vector2 row1)
{
	this->Row0 = row0;
	this->Row1 = row1;
}

/*
Matrix2::Matrix2(Matrix2& mat)
{
	this->Row0 = mat.Row0;
	this->Row1 = mat.Row1;
}
*/

Vector2 Matrix2::Diag()
{
	return Vector2(this->Row0.x, this->Row1.y);
}

float Matrix2::Trace()
{	
	return (float)(Diag().x + Diag().y);
}
/*
Matrix2 Matrix2::Opp()
{
	Matrix2 opp;
	opp.Row0 = -opp.Row0;
	opp.Row1 = -opp.Row1;
	return opp;
}
*/
/*
Matrix2 Matrix2::Transpose()
{
	Matrix2 transpose(*this);
	for (int i = 0; i < column; i++) {
		for (int j = 0; j < rows; j++) {
			transpose[i][j] = this[j][i];
		}
	}
	return transpose;
}
*/

Matrix2 Matrix2::Add(const Matrix2& m, const Matrix2& m2)
{
	Matrix2 add;
	add.Row0 = add.Row0.Add(m.Row0, m2.Row0);
	add.Row1 = add.Row1.Add(m.Row1, m2.Row1);
	return add;
}

Matrix2 Matrix2::MultiplyBy(const Matrix2& m, const float f)
{
	Matrix2 temp;

	temp.Row0.x = m.Row0.x * f;
	temp.Row0.y = m.Row0.y * f;

	temp.Row1.x = m.Row1.x * f;
	temp.Row1.y = m.Row1.y * f;

	return temp;
}

Matrix2 Matrix2::MultiplyBy(const Matrix2& m, const Matrix2& m2)
{
	Matrix2 temp;

	temp.Row0.x = m.Row0.x * m2.Row0.x + m.Row0.y * m2.Row1.x;
	temp.Row0.y = m.Row0.x * m2.Row0.y + m.Row0.y * m2.Row1.y;

	temp.Row1.x = m.Row1.x * m2.Row0.x + m.Row1.y * m2.Row1.x;
	temp.Row1.y = m.Row1.x * m2.Row0.y + m.Row1.x * m2.Row1.y;

	return temp;
}

float Matrix2::Determinant(const Matrix2& m)
{
	float result = 0;
	result += m.Row0.x * m.Row1.y - m.Row0.y * m.Row1.x;
	return result;
}
/*
Matrix2 Matrix2::Augment(const Matrix2& m)
{
	Matrix2 temp(rows, column + m.column, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < temp.column; j++) {
			if (j < column) {
				temp.matrixData[i][j] = matrixData[i][j];
			}
			else {
				temp.matrixData[i][j] = m.matrixData[i][j - column];
			}
		}
	}
	return temp;
}
*/
Matrix2 Matrix2::Identity()
{
	Matrix2 temp;

	temp.Row0.x = 1;
	temp.Row1.y = 1;

	return temp;
}

Matrix2 Matrix2::Rotation2D(const float angle)
{
	float sinRotation = (angle < 0) ? std::sin(angle) : -std::sin(angle);
	Matrix2 temp;

	temp.Row0 = Vector2(std::cos(angle), -sinRotation);
	temp.Row1 = Vector2(sinRotation, std::cos(angle));
	return temp;
}

Matrix2 Matrix2::Scaling2D(const Vector2& v)
{
	Matrix2 temp;
	temp.Row0.x = v.x;
	temp.Row1.y = v.y;
	return temp;
}

Matrix2::~Matrix2()
{

}
/*
std::ostream& operator<<(std::ostream& os, const Matrix2& matrix)
{
	os << "[ " << matrix.Row0.x << ", " << matrix.Row0.y << ", " << matrix.Row1.x << ", " << matrix.Row1.y << ", " << " ]\n";
	return os;
}
*/