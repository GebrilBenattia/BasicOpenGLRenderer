#include "Vector4.hpp"
#include <iostream>
#include <cassert>

Vector4::Vector4()
{

}

Vector4::Vector4(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
	this->w = value;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(Vector2& v, Vector2& v2)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v2.x;
	this->w = v2.y;
}

Vector4::Vector4(Vector2& v, float z, float w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(Vector3& v, float w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}

Vector4::~Vector4()
{

}


Vector4 Vector4::Opp() const
{
	Vector4 temp(-this->x, -this->y, -this->z, -this->w);

	return temp;
}

float Vector4::Norm() const
{
	return std::sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
}

Vector4 Vector4::Add(const Vector4& v1, const Vector4& v2)
{
	Vector4 temp(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);

	return temp;
}

float Vector4::DotProduct(const Vector4& v1, const Vector4& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
/*
Vector4 Vector4::CrossProduct(const Vector4& v1, const Vector4& v2)
{

}
*/

float Vector4::Angle(const Vector4& v1, const Vector4& v2)
{
	float angle = DotProduct(v1, v2) / (v1.Norm() * v2.Norm());

	angle = acosf(angle);

	/*
	if (Determinant(v1, v2) < 0) {
		angle = -angle;
	}
	*/

	return angle;
}