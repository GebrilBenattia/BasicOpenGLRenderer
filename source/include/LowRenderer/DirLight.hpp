#pragma once
#include "Light.hpp"

class DirLight : public Light
{
private:
	Vector3 m_Direction;
	static std::vector<DirLight*> m_Lights;
	Shader& m_SceneShader;

public:

	DirLight();
	DirLight(Vector3 direction, Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 color = Vector3(1.f, 1.f, 1.f), Shader& sceneShader = *ResourceManager::Get<Shader>("ourshader"));
	~DirLight();

	static void Update();

	void DrawGUI(DirLight& DirLight);
};