#pragma once

#include "Matrix4.hpp"
#include "ResourcesManager.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Object.hpp"

#include "SphereCollider.hpp"

class PlaneCollider
{
private:
	Vector3 center;
	Vector3 rotation;
	Camera& cam;

	Object* m_Owner;

public:
	Vector3 A, B, C, D;
	bool colliding = false;

	//PlaneCollider(Vector3& centerPos, Vector3& eulerRot, Vector3& scaling, Camera& camera);
	PlaneCollider(Vector3 angle, Vector3 centerPos, Vector3 A, Vector3 B, Vector3 C, Vector3 D, Object* owner,Camera& camera);
	PlaneCollider(Vector3 angle, Vector3 centerPos, Vector3 A, Vector3 B, Vector3 C, Vector3 D, Camera& camera);

	~PlaneCollider();

	void Draw();
	bool SpherePlaneSolver(SphereCollider& sphere, Vector3& hitpoint, Vector3& hitnormal, Vector3& hitdist, int normalDir = 1);
	void Update();
};