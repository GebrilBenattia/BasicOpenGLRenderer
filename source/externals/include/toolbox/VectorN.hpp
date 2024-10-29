#pragma once

#include "string"
#include <vector>
#include <ostream>

class Vector
{
public:
	std::vector<float> vectorData;
	int rows;

	Vector();
	Vector(int rows, float value);
	Vector(int rows, std::vector<float> value);
	~Vector();

	Vector Opp() const;
	float Norm() const;
	Vector Normalize() const;
	Vector Add(const Vector& v1, const Vector& v2);
	static float DotProduct(const Vector& v1, const Vector& v2);
	static float Determinant(const Vector& v1, const Vector& v2); // temporaire -> a deplacer dans matrix.hpp
	static Vector CrossProduct(const Vector& v1, const Vector& v2);
	static float Angle(const Vector& v1, const Vector& v2);
	static float Dist(const Vector& v1, const Vector& v2);

	Vector operator+(const Vector& v);
	Vector operator-();
	Vector operator-(const Vector& v);
	Vector operator*(const Vector& v);
	Vector operator/(const Vector& v);

	/*
	Vector Opp();
	float GetNorm();
	float DotProduct(Vector v1, Vector v2);
	float Determinant(Vector v1, Vector v2);
	Vector Translate(Vector p, Vector v);
	Vector* GetTriangle(Vector v1, Vector v2);
	Vector* GetParallelogram(Vector v1, Vector v2);
	float GetAngle(Vector v1, Vector v2);
	Vector Normalize(Vector v);
	Vector GetNormal(Vector v1, Vector v2);
	~Vector();

	//Vector operator+(Vector b) { return Vector(this->x + b.x, this->y + b.y); }
	//Vector operator-(Vector b) { return Vector(this->x - b.x, this->y - b.y); }
	//Vector operator*(Vector b) { return Vector(this->x * b.x, this->y * b.y); }
	//Vector operator/(Vector b) { return Vector(this->x / b.x, this->y / b.y); }
	//std::ostream& operator<<(std::ostream& os) { return os << this->x << this->y; }
	*/
private:
};

//std::ostream& operator<<(std::ostream& os, const Vector& v);
