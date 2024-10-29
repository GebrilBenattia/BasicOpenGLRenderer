#pragma once

#include "Matrix4.hpp"
#include "ResourcesManager.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "PlaneCollider.hpp"

class BoxCollider
{
private:
	Vector3 m_Position;
	Vector3 m_EulerRot;
	Vector3 m_Scaling;
	Camera& m_Camera;

	Object* m_Owner;

public:
	bool colliding = false;

	BoxCollider(Vector3 centerPos, Vector3 eulerRot, Vector3 scaling, Camera& cam);
	BoxCollider(Object* owner, Vector3 centerPos, Vector3 eulerRot, Vector3 scaling, Camera& cam);

	~BoxCollider();

	void Draw(Matrix4 vp);
	bool SolveSphereBox(SphereCollider& sphere, Vector3& hitpoint, Vector3& hitnormal, Vector3& hitdist);
	void Update(Matrix4 vp);
};