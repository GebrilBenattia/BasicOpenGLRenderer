#pragma once
#include "Light.hpp"
#include <Camera.hpp>


class SpotLight : public Light
{
private:
	float m_CutOff, m_OuterCutOff, m_Constant, m_Linear, m_Quadratic;
	static std::vector<SpotLight*> m_Lights;
	Shader& m_SceneShader;
	Shader& m_LightShader;

public:
	Vector3 m_Position, m_Direction;

	SpotLight();
	SpotLight(Vector3 position, Vector3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic, Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 color = Vector3(1.f, 1.f, 1.f), Shader& sceneShader = *ResourceManager::Get<Shader>("ourshader"), Shader& lightShader = *ResourceManager::Get<Shader>("lightshader"));
	~SpotLight();

	static void Update(Camera& cam);
	void UpdateSelf(Camera& cam);

	void DrawGUI(SpotLight& SpotLight, Camera& cam);
};