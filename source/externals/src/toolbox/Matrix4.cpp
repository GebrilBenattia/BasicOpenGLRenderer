#include "Matrix4.hpp"
#include "Matrix3.hpp"
#include <cassert>
#define _USE_MATH_DEFINES
#include "math.h"
#include <iostream>

Matrix4::Matrix4()
{

}

Matrix4::Matrix4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3)
{
	this->Row0 = row0;
	this->Row1 = row1;
	this->Row2 = row2;
	this->Row3 = row3;
}

Matrix4::~Matrix4()
{

}
/*
Vector4 Matrix4::Diag()
{

}

float Matrix4::Trace()
{

}
Matrix4 Matrix4::Opp()
{
	Matrix4 opp;
	opp.Row0 = -opp.Row0;
	opp.Row1 = -opp.Row1;
	opp.Row2 = -opp.Row2;
	opp.Row3 = -opp.Row3;
	return opp;
}
*/
/*
Matrix4 Matrix4::Transpose()
{

}
*/

Matrix4 Matrix4::Add(const Matrix4& m, const Matrix4& m2)
{
	Matrix4 temp;

	temp.Row0.x = m.Row0.x + m2.Row0.x;
	temp.Row0.y = m.Row0.y + m2.Row0.y;
	temp.Row0.z = m.Row0.z + m2.Row0.z;
	temp.Row0.w = m.Row0.w + m2.Row0.w;

	temp.Row1.x = m.Row1.x + m2.Row1.x;
	temp.Row1.y = m.Row1.y + m2.Row1.y;
	temp.Row1.z = m.Row1.z + m2.Row1.z;
	temp.Row1.w = m.Row1.w + m2.Row1.w;

	temp.Row2.x = m.Row2.x + m2.Row2.x;
	temp.Row2.y = m.Row2.y + m2.Row2.y;
	temp.Row2.z = m.Row2.z + m2.Row2.z;
	temp.Row2.w = m.Row2.w + m2.Row2.w;

	temp.Row3.x = m.Row3.x + m2.Row3.x;
	temp.Row3.y = m.Row3.y + m2.Row3.y;
	temp.Row3.z = m.Row3.z + m2.Row3.z;
	temp.Row3.w = m.Row3.w + m2.Row3.w;

	return temp;
}

Matrix4 Matrix4::MultiplyBy(const Matrix4& m, const float f)
{
	Matrix4 temp;

	temp.Row0.x = m.Row0.x * f;
	temp.Row0.y = m.Row0.y * f;
	temp.Row0.z = m.Row0.z * f;
	temp.Row0.w = m.Row0.w * f;

	temp.Row1.x = m.Row1.x * f;
	temp.Row1.y = m.Row1.y * f;
	temp.Row1.z = m.Row1.z * f;
	temp.Row1.w = m.Row1.w * f;

	temp.Row2.x = m.Row2.x * f;
	temp.Row2.y = m.Row2.y * f;
	temp.Row2.z = m.Row2.z * f;
	temp.Row2.w = m.Row2.w * f;

	temp.Row3.x = m.Row3.x * f;
	temp.Row3.y = m.Row3.y * f;
	temp.Row3.z = m.Row3.z * f;
	temp.Row3.w = m.Row3.w * f;

	return temp;
}

Matrix4 Matrix4::MultiplyBy(const Matrix4& m, const Matrix4& m2)
{
	Matrix4 temp;

	temp.Row0.x = m.Row0.x * m2.Row0.x + m.Row0.y * m2.Row1.x + m.Row0.z * m2.Row2.x + m.Row0.w * m2.Row3.x;
	temp.Row0.y = m.Row0.x * m2.Row0.y + m.Row0.y * m2.Row1.y + m.Row0.z * m2.Row2.y + m.Row0.w * m2.Row3.y;
	temp.Row0.z = m.Row0.x * m2.Row0.z + m.Row0.y * m2.Row1.z + m.Row0.z * m2.Row2.z + m.Row0.w * m2.Row3.z;
	temp.Row0.w = m.Row0.x * m2.Row0.w + m.Row0.y * m2.Row1.w + m.Row0.z * m2.Row2.w + m.Row0.w * m2.Row3.w;

	temp.Row1.x = m.Row1.x * m2.Row0.x + m.Row1.y * m2.Row1.x + m.Row1.z * m2.Row2.x + m.Row1.w * m2.Row3.x;
	temp.Row1.y = m.Row1.x * m2.Row0.y + m.Row1.y * m2.Row1.y + m.Row1.z * m2.Row2.y + m.Row1.w * m2.Row3.y;
	temp.Row1.z = m.Row1.x * m2.Row0.z + m.Row1.y * m2.Row1.z + m.Row1.z * m2.Row2.z + m.Row1.w * m2.Row3.z;
	temp.Row1.w = m.Row1.x * m2.Row0.w + m.Row1.y * m2.Row1.w + m.Row1.z * m2.Row2.w + m.Row1.w * m2.Row3.w;

	temp.Row2.x = m.Row2.x * m2.Row0.x + m.Row2.y * m2.Row1.x + m.Row2.z * m2.Row2.x + m.Row2.w * m2.Row3.x;
	temp.Row2.y = m.Row2.x * m2.Row0.y + m.Row2.y * m2.Row1.y + m.Row2.z * m2.Row2.y + m.Row2.w * m2.Row3.y;
	temp.Row2.z = m.Row2.x * m2.Row0.z + m.Row2.y * m2.Row1.z + m.Row2.z * m2.Row2.z + m.Row2.w * m2.Row3.z;
	temp.Row2.w = m.Row2.x * m2.Row0.w + m.Row2.y * m2.Row1.w + m.Row2.z * m2.Row2.w + m.Row2.w * m2.Row3.w;

	temp.Row3.x = m.Row3.x * m2.Row0.x + m.Row3.y * m2.Row1.x + m.Row3.z * m2.Row2.x + m.Row3.w * m2.Row3.x;
	temp.Row3.y = m.Row3.x * m2.Row0.y + m.Row3.y * m2.Row1.y + m.Row3.z * m2.Row2.y + m.Row3.w * m2.Row3.y;
	temp.Row3.z = m.Row3.x * m2.Row0.z + m.Row3.y * m2.Row1.z + m.Row3.z * m2.Row2.z + m.Row3.w * m2.Row3.z;
	temp.Row3.w = m.Row3.x * m2.Row0.w + m.Row3.y * m2.Row1.w + m.Row3.z * m2.Row2.w + m.Row3.w * m2.Row3.w;

	return temp;
}

Vector4 Matrix4::MultiplyBy(const Matrix4& m, const Vector4& v)
{
	const float x = v.x * m.Row0.x + v.y * m.Row0.y + v.z * m.Row0.z + v.w * m.Row0.w;
	const float y = v.x * m.Row1.x + v.y * m.Row1.y + v.z * m.Row1.z + v.w * m.Row1.w;
	const float z = v.x * m.Row2.x + v.y * m.Row2.y + v.z * m.Row2.z + v.w * m.Row2.w;
	const float w = v.x * m.Row3.x + v.y * m.Row3.y + v.z * m.Row3.z + v.w * m.Row3.w;

	return Vector4(x, y, z, w);
}

/*
Matrix4 Matrix4::Augment(const Matrix4& m)
{

}
*/

Matrix4 Matrix4::Identity()
{
	Matrix4 temp;

	temp.Row0 = 0;
	temp.Row1 = 0;
	temp.Row2 = 0;
	temp.Row3 = 0;

	temp.Row0.x = 1;
	temp.Row1.y = 1;
	temp.Row2.z = 1;
	temp.Row3.w = 1;

	return temp;
}
/*
Matrix4 Matrix4::Inverse(Matrix4& m)
{

}
*/

Matrix4 Matrix4::TRS(Vector3 translate, Vector3 angle, Vector3 scale)
{
	Matrix4 Rx;
	Matrix4 Ry;
	Matrix4 Rz;

	Matrix4::Rotation(angle.x, Vector3(1, 0, 0), Rx);
	Matrix4::Rotation(angle.y, Vector3(0, 1, 0), Ry);
	Matrix4::Rotation(angle.z, Vector3(0, 0, 1), Rz);

	Matrix4 Rzy = Matrix4::MultiplyBy(Rz, Ry);

	Matrix4 Rxyz = Matrix4::MultiplyBy(Rzy, Rx);

	Matrix4 S = Matrix4(
		{ scale.x, 0.f, 0.f, 0.f },
		{ 0.f, scale.y, 0.f, 0.f },
		{ 0.f, 0.f, scale.z, 0.f },
		{ 0.f, 0.f, 0.f, 1.f }
		);

	Matrix4 temp = Matrix4::MultiplyBy(Rxyz, S);

	temp.Row0.w = translate.x;
	temp.Row1.w = translate.y;
	temp.Row2.w = translate.z;

	return temp;
}

void Matrix4::Rotation(const float angle, const Vector3& axis, Matrix4& dst)
{
	// Based on https://en.wikipedia.org/wiki/Transformation_matrix#Rotation_2

	const float c = std::cos(angle);
	const float s = std::sin(angle);
	const float c2 = 1 - c;

	const float r00 = axis.x * axis.x * c2 + c;
	const float r01 = axis.y * axis.x * c2 - axis.z * s;
	const float r02 = axis.z * axis.x * c2 + axis.y * s;

	const float r10 = axis.x * axis.y * c2 + axis.z * s;
	const float r11 = axis.y * axis.y * c2 + c;
	const float r12 = axis.z * axis.y * c2 - axis.x * s;

	const float r20 = axis.x * axis.z * c2 - axis.y * s;
	const float r21 = axis.y * axis.z * c2 + axis.x * s;
	const float r22 = axis.z * axis.z * c2 + c;

	dst = Matrix4(
		{ r00, r01, r02, 0 },
		{ r10, r11, r12, 0 },
		{ r20, r21, r22, 0 },
		{ 0, 0, 0, 1 }
	);
}

void Matrix4::Projection(float fov, float aspectRatio, float zNear, float zFar, Matrix4& m)
{
	assert(zFar > zNear && "Skill Issue");

	const float f = 1.0f / std::tan(fov / 2.0f);
	const float zDiff = zFar - zNear;

	const float r00 = f / aspectRatio;
	const float r22 = -(zFar + zNear) / zDiff;
	const float r23 = -(2 * zFar * zNear) / zDiff;

	m.Row0 = Vector4(r00, 0.f, 0.f, 0.f);
	m.Row1 = Vector4(0.f, f, 0.f, 0.f);
	m.Row2 = Vector4(0.f, 0.f, r22, r23);
	m.Row3 = Vector4(0.f, 0.f, -1.0f, 0.f);

}

void Matrix4::View(Vector3 eye, Vector3 center, Vector3 up, Matrix4& m)
{
	const Vector3 yup = up.Normalize();

	const Vector3 z = Vector3(eye.x - center.x, eye.y - center.y, eye.z - center.z).Normalize();
	const Vector3 x = Vector3::CrossProduct(yup, z).Normalize();
	const Vector3 y = Vector3::CrossProduct(z, x).Normalize();

	const float r03 = -Vector3::DotProduct(x, eye);
	const float r13 = -Vector3::DotProduct(y, eye);
	const float r23 = -Vector3::DotProduct(z, eye);

	m.Row0 = Vector4(x.x, x.y, x.z, r03);
	m.Row1 = Vector4(y.x, y.y, y.z, r13);
	m.Row2 = Vector4(z.x, z.y, z.z, r23);
	m.Row3 = Vector4(0.f, 0.f, 0.f, 1.f);
}

void Matrix4::Log() const
{
	std::cout << "[ " << Row0.x << ", " << Row0.y << ", " << Row0.z << ", " << Row0.w << " ]" << std::endl;
	std::cout << "[ " << Row1.x << ", " << Row1.y << ", " << Row1.z << ", " << Row1.w << " ]" << std::endl;
	std::cout << "[ " << Row2.x << ", " << Row2.y << ", " << Row2.z << ", " << Row2.w << " ]" << std::endl;
	std::cout << "[ " << Row3.x << ", " << Row3.y << ", " << Row3.z << ", " << Row3.w << " ]" << std::endl;
}

/*
std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
{
		os << "[ " << matrix.Row0 << ",\n" << matrix.Row1 << ",\n" << matrix.Row2 << ",\n" << matrix.Row3 << " ]\n";

	return os;
}
*/
