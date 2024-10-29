#pragma once
#include "Light.hpp"
#include <Camera.hpp>

class PointLight : public Light
{
private:
	Vector3 m_Position;
	float m_Constant, m_Linear, m_Quadratic;
	static std::vector<PointLight*> m_Lights;
	Shader& m_SceneShader;
	Shader& m_LightShader;

public:

	PointLight();
	PointLight(Vector3 position, float constant, float linear, float quadratic, Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 color = Vector3(1.f, 1.f, 1.f), Shader& sceneShader = *ResourceManager::Get<Shader>("ourshader"), Shader& lightShader = *ResourceManager::Get<Shader>("lightshader"));
	~PointLight();

	static void Update(Camera& cam);

	void DrawGUI(PointLight& PointLight);
};