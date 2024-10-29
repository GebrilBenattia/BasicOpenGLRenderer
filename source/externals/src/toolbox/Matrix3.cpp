#include "Matrix3.hpp"
#include <cassert>
#define _USE_MATH_DEFINES
#include "math.h"
#include <iostream>

Matrix3::Matrix3()
{

}

Matrix3::Matrix3(Vector3 row0, Vector3 row1, Vector3 row2)
{
	this->Row0 = row0;
	this->Row1 = row1;
	this->Row2 = row2;
}

Matrix3::~Matrix3()
{

}

Vector3 Matrix3::Diag()
{
	Vector3 temp;

	temp.x = Row0.x;
	temp.y = Row1.y;
	temp.z = Row2.z;

	return temp;
}
/*
float Matrix3::Trace()
{

}
Matrix3 Matrix3::Opp()
{
	Matrix3 opp;
	opp.Row0 = -opp.Row0;
	opp.Row1 = -opp.Row1;
	opp.Row2 = -opp.Row2;
	return opp;
}
*/
/*
Matrix3 Matrix3::Transpose()
{

}
*/
Matrix3 Matrix3::Add(const Matrix3& m, const Matrix3& m2)
{
	Matrix3 temp;

	temp.Row0.x = m.Row0.x + m2.Row0.x;
	temp.Row0.y = m.Row0.y + m2.Row0.y;
	temp.Row0.z = m.Row0.z + m2.Row0.z;

	temp.Row1.x = m.Row1.x + m2.Row1.x;
	temp.Row1.y = m.Row1.y + m2.Row1.y;
	temp.Row1.z = m.Row1.z + m2.Row1.z;

	temp.Row2.x = m.Row2.x + m2.Row2.x;
	temp.Row2.y = m.Row2.y + m2.Row2.y;
	temp.Row2.z = m.Row2.z + m2.Row2.z;

	return temp;
}

Matrix3 Matrix3::MultiplyBy(const Matrix3& m, const float f)
{
	Matrix3 temp;

	temp.Row0.x = m.Row0.x * f;
	temp.Row0.y = m.Row0.y * f;
	temp.Row0.z = m.Row0.z * f;

	temp.Row1.x = m.Row1.x * f;
	temp.Row1.y = m.Row1.y * f;
	temp.Row1.z = m.Row1.z * f;

	temp.Row2.x = m.Row2.x * f;
	temp.Row2.y = m.Row2.y * f;
	temp.Row2.z = m.Row2.z * f;

	return temp;
}

Matrix3 Matrix3::MultiplyBy(const Matrix3& m, const Matrix3& m2)
{
	Matrix3 temp;

	temp.Row0.x = m.Row0.x * m2.Row0.x + m.Row0.y * m2.Row1.x + m.Row0.z * m2.Row2.x;
	temp.Row0.y = m.Row0.x * m2.Row0.y + m.Row0.y * m2.Row1.y + m.Row0.z * m2.Row2.y;
	temp.Row0.z = m.Row0.x * m2.Row0.z + m.Row0.y * m2.Row1.z + m.Row0.z * m2.Row2.z;

	temp.Row1.x = m.Row1.x * m2.Row0.x + m.Row1.y * m2.Row1.x + m.Row1.z * m2.Row2.x;
	temp.Row1.y = m.Row1.x * m2.Row0.y + m.Row1.y * m2.Row1.y + m.Row1.z * m2.Row2.y;
	temp.Row1.z = m.Row1.x * m2.Row0.z + m.Row1.y * m2.Row1.z + m.Row1.z * m2.Row2.z;

	temp.Row2.x = m.Row2.x * m2.Row0.x + m.Row2.y * m2.Row1.x + m.Row2.z * m2.Row2.x;
	temp.Row2.y = m.Row2.x * m2.Row0.y + m.Row2.y * m2.Row1.y + m.Row2.z * m2.Row2.y;
	temp.Row2.z = m.Row2.x * m2.Row0.z + m.Row2.y * m2.Row1.z + m.Row2.z * m2.Row2.z;

	return temp;
}

Vector3 Matrix3::MultiplyBy(const Vector3& v, const Matrix3& m)
{
	Vector3 temp;

	temp.x = v.x * m.Row0.x + v.y * m.Row0.x + v.z * m.Row0.x;
	temp.y = v.x * m.Row0.y + v.y * m.Row0.y + v.z * m.Row0.y;
	temp.z = v.x * m.Row0.z + v.y * m.Row0.z + v.z * m.Row0.z;

	temp.x = v.x * m.Row1.x + v.y * m.Row1.x + v.z * m.Row1.x;
	temp.y = v.x * m.Row1.y + v.y * m.Row1.y + v.z * m.Row1.y;
	temp.z = v.x * m.Row1.z + v.y * m.Row1.z + v.z * m.Row1.z;

	temp.x = v.x * m.Row2.x + v.y * m.Row2.x + v.z * m.Row2.x;
	temp.y = v.x * m.Row2.y + v.y * m.Row2.y + v.z * m.Row2.y;
	temp.z = v.x * m.Row2.z + v.y * m.Row2.z + v.z * m.Row2.z;

	return temp;
}


/*
Matrix3 Matrix3::Augment(const Matrix3& m)
{

}
*/
Matrix3 Matrix3::Identity(int size)
{
	Matrix3 temp;

	temp.Row0.x = 1;
	temp.Row1.y = 1;
	temp.Row2.z = 1;

	return temp;
}
/*
Matrix3 Matrix3::Inverse(Matrix3& m)
{

}
*/
Matrix3 Matrix3::Scaling3D(const Vector3& v)
{
	Matrix3 temp;

	temp.Row0.x = v.x;
	temp.Row1.y = v.y;
	temp.Row2.z = v.z;

	return temp;
}

Matrix3 Matrix3::Rotation3D(const float angle, const Vector3& v)
{
	Vector3 row0;
	Vector3 row1;
	Vector3 row2;

	const float cos = std::cos(angle);
	const float sin = std::sin(angle);
	const float c = 1 - cos;

	const float r00 = v.x * v.x * c + cos;
	const float r01 = v.y * v.y * c + v.z * sin;
	const float r02 = v.z * v.z * c - v.y * sin;

	row0.x = r00;
	row0.y = r01;
	row0.z = r02;

	const float r10 = v.x * v.x * c - v.z * sin;
	const float r11 = v.y * v.y * c + cos;
	const float r12 = v.z * v.z * c + v.x * sin;

	row1.x = r10;
	row1.y = r11;
	row1.z = r12;

	const float r20 = v.x * v.x * c + v.y * sin;
	const float r21 = v.y * v.y * c - v.x * sin;
	const float r22 = v.z * v.z * c + cos;

	row2.x = r20;
	row2.y = r21;
	row2.z = r22;

	Matrix3 temp(row0, row1, row2);

	return temp;
}

/*
std::ostream& operator<<(std::ostream& os, const Matrix3& matrix)
{
	for (int i = 0; i < matrix.rows; i++) {
		os << "[ ";
		for (int j = 0; j < matrix.column; j++) {
			os << matrix.matrixData[i][j];
			if (j != matrix.column - 1) {
				os << ", ";
			}
		}
		os << " ]\n";
	}
	return os;
}
*/