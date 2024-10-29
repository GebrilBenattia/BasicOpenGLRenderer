#pragma once

#include "string"
#include <vector>
#include <ostream>

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float value);
	Vector2(float x, float y);
	~Vector2();

	Vector2 Opp() const;
	float Norm() const;
	static Vector2 Add(const Vector2& v1, const Vector2& v2);
	static float DotProduct(const Vector2& v1, const Vector2& v2);
	static float Determinant(const Vector2& v1, const Vector2& v2); // temporaire -> a deplacer dans matrix.hpp
	static Vector2 CrossProduct(const Vector2& v1, const Vector2& v2);
	static float Angle(const Vector2& v1, const Vector2& v2);
	static float Dist(const Vector2& v1, const Vector2& v2);

	Vector2 operator+(const Vector2& v) const
	{
		return Vector2(v.x + x, v.y + y);
	}

	Vector2 operator-(const Vector2& v) const 
	{
		return Vector2(v.x - x, v.y - y);
	}

	Vector2 operator*(const Vector2& v) const
	{
		return Vector2(v.x * x, v.y * y);
	}

	Vector2 operator*(const float f) const
	{
		return Vector2(f * x, f * y);
	}

	Vector2 operator/(const float f) const
	{
		return Vector2(x / f, y / f);
	}
	/*
	Vector2 Opp();
	float GetNorm();
	float DotProduct(Vector2 v1, Vector2 v2);
	float Determinant(Vector2 v1, Vector2 v2);
	Vector2 Translate(Vector2 p, Vector2 v);
	Vector2* GetTriangle(Vector2 v1, Vector2 v2);
	Vector2* GetParallelogram(Vector2 v1, Vector2 v2);
	float GetAngle(Vector2 v1, Vector2 v2);
	Vector2 Normalize(Vector2 v);
	Vector2 GetNormal(Vector2 v1, Vector2 v2);
	~Vector2();

	//Vector2 operator+(Vector2 b) { return Vector2(this->x + b.x, this->y + b.y); }
	//Vector2 operator-(Vector2 b) { return Vector2(this->x - b.x, this->y - b.y); }
	//Vector2 operator*(Vector2 b) { return Vector2(this->x * b.x, this->y * b.y); }
	//Vector2 operator/(Vector2 b) { return Vector2(this->x / b.x, this->y / b.y); }
	//std::ostream& operator<<(std::ostream& os) { return os << this->x << this->y; }
	*/
private:
};

//std::ostream& operator<<(std::ostream& os, const Vector2& v);
