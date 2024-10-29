#pragma once

#include "string"
#include <vector>
#include <ostream>

#include "Vector2.hpp"

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float value);
	Vector3(float x, float y, float z);
	Vector3(Vector2& v, float z);
	//Vector3(Vector3& v);
	~Vector3();

	Vector3 Opp() const;
	float Norm() const;
	Vector3 Add(const Vector3& v1, const Vector3& v2);
	static float DotProduct(const Vector3& v1, const Vector3& v2);
	static float Determinant(const Vector3& v1, const Vector3& v2); // temporaire -> a deplacer dans matrix.hpp
	static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);
	static float Angle(const Vector3& v1, const Vector3& v2);
	static float Dist(const Vector3& v1, const Vector3& v2);
	Vector3 Normalize();

	static void Reflect(Vector3& out, const Vector3& incidentVec, const Vector3& normal);

	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(v.x + x, v.y + y, v.z + z);
	}

	Vector3 operator+=(const Vector3& v) const
	{
		return Vector3(v.x + x, v.y + y, v.z + z);
	}

	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator-=(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(const Vector3& v) const
	{
		return Vector3(v.x * x, v.y * y, v.z * z);
	}

	Vector3 operator*(const float f) const
	{
		return Vector3(x * f, y * f, z * f);
	}

	Vector3 operator/(const float f) const
	{
		return Vector3(x / f, y / f, z / f);
	}

	/*
	Vector3 operator+(const Vector3& v);
	Vector3 operator-();
	Vector3 operator-(const Vector3& v);
	Vector3 operator*(const Vector3& v);
	Vector3 operator/(const Vector3& v);
	*/

	/*
	Vector3 Opp();
	float GetNorm();
	float DotProduct(Vector3 v1, Vector3 v2);
	float Determinant(Vector3 v1, Vector3 v2);
	Vector3 Translate(Vector3 p, Vector3 v);
	Vector3* GetTriangle(Vector3 v1, Vector3 v2);
	Vector3* GetParallelogram(Vector3 v1, Vector3 v2);
	float GetAngle(Vector3 v1, Vector3 v2);
	Vector3 Normalize(Vector3 v);
	Vector3 GetNormal(Vector3 v1, Vector3 v2);
	~Vector3();

	//Vector3 operator+(Vector3 b) { return Vector3(this->x + b.x, this->y + b.y); }
	//Vector3 operator-(Vector3 b) { return Vector3(this->x - b.x, this->y - b.y); }
	//Vector3 operator*(Vector3 b) { return Vector3(this->x * b.x, this->y * b.y); }
	//Vector3 operator/(Vector3 b) { return Vector3(this->x / b.x, this->y / b.y); }
	//std::ostream& operator<<(std::ostream& os) { return os << this->x << this->y; }
	*/
private:
};

//std::ostream& operator<<(std::ostream& os, const Vector3& v);
