#include "Vector2.hpp"
#include <iostream>
#include <cassert>

Vector2::Vector2()
{

}

Vector2::Vector2(float value)
{
	this->x = value;
	this->y = value;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::Opp() const
{
	return Vector2(-this->x, -this->y);
}

float Vector2::Norm() const
{
	return std::sqrtf((this->x * this->x) + (this->y * this->y));
}

Vector2 Vector2::Add(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x + v2.x, v2.y + v2.y);
}

float Vector2::DotProduct(const Vector2& v1, const Vector2& v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float Vector2::Angle(const Vector2& v1, const Vector2& v2)
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

float Vector2::Dist(const Vector2& v1, const Vector2& v2)
{
	return std::sqrtf((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
}

Vector2::~Vector2()
{

}
/*
Vector2 Vector2::operator+(const Vector2& v)
{
	for (int i = 0; i < vectorData.size(); i++) {
		vectorData[i] += v.vectorData[i];
	}
	return v;
}

Vector2 Vector2::operator-(const Vector2& v)
{
	for (int i = 0; i < vectorData.size(); i++) {
		vectorData[i] -= v.vectorData[i];
	}
	return v;
}

std::ostream& operator<<(std::ostream& os, const Vector2& v)
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

Vector2 Vector2::operator-()
{
	Vector2 temp(vectorData.size(), 0);
	for (int i = 0; i < vectorData.size(); i++) {
		temp.vectorData[i] = -vectorData[i];
	}
	return temp;
}
*/