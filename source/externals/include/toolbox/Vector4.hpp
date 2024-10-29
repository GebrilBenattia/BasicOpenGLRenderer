#pragma once

#include "string"
#include <vector>
#include <ostream>

#include "Vector2.hpp"
#include "Vector3.hpp"

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4();
	Vector4(float value);
	Vector4(float x, float y, float z, float w);
	Vector4(Vector2& v, Vector2& v2);
	Vector4(Vector2& v, float z, float w);
	Vector4(Vector3& v, float w);
	//Vector4(Vector4& v);
	~Vector4();

	Vector4 Opp() const;
	float Norm() const;
	static Vector4 Add(const Vector4& v1, const Vector4& v2);
	static float DotProduct(const Vector4& v1, const Vector4& v2);
	static float Determinant(const Vector4& v1, const Vector4& v2); // temporaire -> a deplacer dans matrix.hpp
	static Vector4 CrossProduct(const Vector4& v1, const Vector4& v2);
	static float Angle(const Vector4& v1, const Vector4& v2);
	static float Dist(const Vector4& v1, const Vector4& v2);


	Vector4 operator+(const Vector4& v) const
	{
		return Vector4(v.x + x, v.y + y, v.z + z, v.w + w);
	}

	Vector4 operator-(const Vector4& v) const
	{
		return Vector4(v.x - x, v.y - y, v.z - z, v.w - w);
	}

	Vector4 operator*(const Vector4& v) const
	{
		return Vector4(v.x * x, v.y * y, v.z * z, v.w * w);
	}

	Vector4 operator*(const float f) const
	{
		return Vector4(x * f, y * f, z * f, w * f);
	}

	Vector4 operator/(const float f) const
	{
		return Vector4(x / f, y / f, z / f, w / f);
	}

	/*
	Vector4 Opp();
	float GetNorm();
	float DotProduct(Vector4 v1, Vector4 v2);
	float Determinant(Vector4 v1, Vector4 v2);
	Vector4 Translate(Vector4 p, Vector4 v);
	Vector4* GetTriangle(Vector4 v1, Vector4 v2);
	Vector4* GetParallelogram(Vector4 v1, Vector4 v2);
	float GetAngle(Vector4 v1, Vector4 v2);
	Vector4 Normalize(Vector4 v);
	Vector4 GetNormal(Vector4 v1, Vector4 v2);
	~Vector4();

	//Vector4 operator+(Vector4 b) { return Vector4(this->x + b.x, this->y + b.y); }
	//Vector4 operator-(Vector4 b) { return Vector4(this->x - b.x, this->y - b.y); }
	//Vector4 operator*(Vector4 b) { return Vector4(this->x * b.x, this->y * b.y); }
	//Vector4 operator/(Vector4 b) { return Vector4(this->x / b.x, this->y / b.y); }
	//std::ostream& operator<<(std::ostream& os) { return os << this->x << this->y; }
	*/
private:
};

//std::ostream& operator<<(std::ostream& os, const Vector4& v);
