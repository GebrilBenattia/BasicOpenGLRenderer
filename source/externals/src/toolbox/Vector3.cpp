#include "Vector3.hpp"
#include <iostream>
#include <cassert>

Vector3::Vector3()
{

}

Vector3::Vector3(float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Vector2& v, float z)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
}

Vector3::~Vector3()
{

}

Vector3 Vector3::Opp() const
{
	Vector3 temp(-this->x, -this->y, -this->z);

	return temp;
}

float Vector3::Norm() const
{
	return std::sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Vector3 Vector3::Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);

	return temp;
}

float Vector3::DotProduct(const Vector3& v1, const Vector3& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vector3 Vector3::CrossProduct(const Vector3& v1, const Vector3& v2)
{
	const float x = v1.y * v2.z - v1.z * v2.y;
	const float y = v1.z * v2.x - v1.x * v2.z;
	const float z = v1.x * v2.y - v1.y * v2.x;

	return Vector3(x, y, z);
}

float Vector3::Dist(const Vector3& v1, const Vector3& v2)
{
	return std::sqrtf((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z));
}

float Vector3::Angle(const Vector3& v1, const Vector3& v2)
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

Vector3 Vector3::Normalize()
{
	float norm = this->Norm();

	return Vector3(this->x / norm, this->y / norm, this->z / norm);
}

void Vector3::Reflect(Vector3& out, const Vector3& incidentVec, const Vector3& normal)
{
	out = normal * (incidentVec - 2.f) * DotProduct(incidentVec, normal);
}

/*
std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
	os << "[ ";
	for (int i = 0; i < v.rows; i++) {
		os << v.vectorData[i];
		if (i != v.rows - 1) {
			os << ", ";
		}
	}
	os << " ]";
	return os;
}
*/