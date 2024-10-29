#pragma once

#include "Matrix4.hpp"
#include "ResourcesManager.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

class SphereCollider
{
public:
	Vector3 prevPos;
	Vector3& currentPosition;
	float radius;

	bool colliding = false;

	SphereCollider(Vector3& centerPos, float sphereRadius);
	~SphereCollider();

	void Draw(Matrix4 vp);
	void Update(Matrix4 vp);
};