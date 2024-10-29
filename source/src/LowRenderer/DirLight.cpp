#include "DirLight.hpp"

std::vector<DirLight*> DirLight::m_Lights;

DirLight::DirLight()
	:m_SceneShader(*ResourceManager::Get<Shader>("ourshader")), m_Direction(Vector3(0,0,0))
{
	lightAmbient = Vector3(0, 0, 0);
	lightDiffuse = Vector3(0, 0, 0);
	lightSpecular = Vector3(0, 0, 0);
	lightColor = Vector3(1, 1, 1);

	m_Lights.push_back(this);
	
	name = "DirLight" + std::to_string(m_Lights.size());
}

DirLight::DirLight(Vector3 direction, Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 color, Shader& sceneShader)
	:m_SceneShader(sceneShader), m_Direction(direction)
{
	lightAmbient = ambient;
	lightDiffuse = diffuse;
	lightSpecular = specular;
	lightColor = color;

	m_Lights.push_back(this);
	
	name = "DirLight" + std::to_string(m_Lights.size());
}

DirLight::~DirLight()
{
}

void DirLight::Update()
{
	for (size_t i = 0; i < m_Lights.size(); i++) {
		m_Lights[i]->DrawGUI(*m_Lights[i]);

		if (!m_Lights[i]->enable)
			continue;

		std::string name = "dirLights[" + std::to_string(i);

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->Use();
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetInt("NbrDirLights", static_cast<int>(m_Lights.size()));

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->Use();
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3("color", m_Lights[i]->lightColor);

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].direction", m_Lights[i]->m_Direction);

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].ambient", m_Lights[i]->lightAmbient * m_Lights[i]->lightColor);
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].diffuse", m_Lights[i]->lightDiffuse * m_Lights[i]->lightColor);
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].specular", m_Lights[i]->lightSpecular * m_Lights[i]->lightColor);

	}
}

void DirLight::DrawGUI(DirLight& DirLight)
{
	if (ImGui::Begin("DirLights", NULL)) {
		if (ImGui::CollapsingHeader("Sun")) {
			ImGui::PushID(this);
			//ImGui::Text("%s", name.c_str());
			ImGui::Checkbox("Enable Light", &enable);

			//Direction
			ImGui::SliderFloat3("Direction", &DirLight.m_Direction.x, -1.f, 1.f);

			//Ambient
			ImGui::SliderFloat3("Ambient", &DirLight.lightAmbient.x, 0.f, 1.f);

			//Diffuse
			ImGui::SliderFloat3("Diffuse", &DirLight.lightDiffuse.x, 0.f, 1.f);

			//Specular
			ImGui::SliderFloat3("Specular", &DirLight.lightSpecular.x, 0.f, 1.f);

			//Color
			ImGui::SliderFloat3("Color", &DirLight.lightColor.x, 0.f, 1.f);

			ImGui::InputFloat("Max Slider Value", &MaxSliderValue, 0.050000000000f, 0, "%.2f");

			if (ImGui::Button("Reset")) {
				m_Direction = Vector3(0.f, 0.f, 0.f);
				lightAmbient = Vector3(0.f, 0.f, 0.f);
				lightDiffuse = Vector3(0.f, 0.f, 0.f);
				lightSpecular = Vector3(0.f, 0.f, 0.f);
			}

			ImGui::PopID();
		}
	}
	ImGui::End();
}
