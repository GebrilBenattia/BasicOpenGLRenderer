#include "VectorN.hpp"
#include <iostream>
#include <cassert>

Vector::Vector()
{

}

Vector::Vector(int rows, float value)
{
	for (int i = 0; i < rows; i++) {
		vectorData.push_back(value);
	}
	this->rows = rows;
}

Vector::Vector(int rows, std::vector<float> value)
{
	for (int i = 0; i < rows; i++) {
		vectorData.push_back(value[i]);
	}
	this->rows = rows;
}

Vector Vector::Opp() const
{
	Vector v((int)vectorData.size(), 0);
	for (int i = 0; i < rows; i++) {
		v.vectorData[i] = -vectorData[i];
	}
	return v;
}

float Vector::Norm() const
{
	float norm = 0;
	for (int i = 0; i < vectorData.size(); i++) {
		norm += (vectorData[i] * vectorData[i]);
	}
	return sqrt(norm);
}

Vector Vector::Normalize() const
{
	Vector temp(vectorData.size(), vectorData);
	float norm = temp.Norm();

	Vector Norm(vectorData.size(), 0);
	for (int i = 0; i < vectorData.size(); i++) {
		temp.vectorData[i] = Norm.vectorData[i] / norm;
	}
	return Norm;
}

Vector Vector::Add(const Vector& v1, const Vector& v2)
{
	Vector temp(vectorData.size(), 0);
	for (int i = 0; i < vectorData.size(); i++) {
		temp.vectorData[i] = v1.vectorData[i] + v2.vectorData[i];
	}
	return v1;
}

float Vector::DotProduct(const Vector& v1, const Vector& v2)
{
	float result = 0;
	for (int i = 0; i < v1.vectorData.size(); i++) {
		result += v1.vectorData[i] * v2.vectorData[i];
	}
	return result;
}

float Vector::Determinant(const Vector& v1, const Vector& v2)
{
	assert(v1.vectorData.size() == 2 && v2.vectorData.size() == 2);

	float result = 0;
	result += v1.vectorData[0] * v2.vectorData[1] - v1.vectorData[1] * v2.vectorData[0];
	return result;
}

Vector Vector::CrossProduct(const Vector& v1, const Vector& v2)
{
	assert(v1.vectorData.size() == 3 && v2.vectorData.size() == 3);

	Vector v(3, 0);
	for (int i = 0; i < v1.vectorData.size(); i++) {
		v.vectorData[0] = v1.vectorData[1] * v2.vectorData[2] - v1.vectorData[2] * v2.vectorData[1];
		v.vectorData[1] = v1.vectorData[2] * v2.vectorData[0] - v1.vectorData[0] * v2.vectorData[2];
		v.vectorData[2] = v1.vectorData[0] * v2.vectorData[1] - v1.vectorData[1] * v2.vectorData[0];
	}
	return v;
}

float Vector::Angle(const Vector& v1, const Vector& v2)
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

float Vector::Dist(const Vector& v1, const Vector& v2)
{
	float result = 0;
	for (int i = 0; i < v1.vectorData.size(); i++) {
		result += (v2.vectorData[i] - v1.vectorData[i]) * (v2.vectorData[i] - v1.vectorData[i]);
	}
	return sqrt(result);
}

Vector::~Vector()
{

}
/*
Vector Vector::operator+(const Vector& v)
{
	for (int i = 0; i < vectorData.size(); i++) {
		vectorData[i] += v.vectorData[i];
	}
	return v;
}

Vector Vector::operator-(const Vector& v)
{
	for (int i = 0; i < vectorData.size(); i++) {
		vectorData[i] -= v.vectorData[i];
	}
	return v;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
	os << "[ ";
	for (int i = 0; i < v.rows; i++) {
		os << v.vectorData[i];
		if(i != v.rows - 1){
			os << ", ";
		}
	}
	os << " ]";
	return os;
}

Vector Vector::operator-()
{
	Vector temp(vectorData.size(), 0);
	for (int i = 0; i < vectorData.size(); i++) {
		temp.vectorData[i] = -vectorData[i];
	}
	return temp;
}
*/