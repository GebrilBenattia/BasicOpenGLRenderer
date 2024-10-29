#pragma once

#include "Object.hpp"
#include "BoxCollider.hpp"

class Cube : public Object
{
private:
	Camera& m_Camera;

public:
	BoxCollider collider;

	Cube(Camera& cam);
	~Cube();

	void Update(Shader& shader, Vector3 color = Vector3(1.f, 1.f, 1.f), Vector3 upScale = Vector3(0.f, 0.f, 0.f));
};