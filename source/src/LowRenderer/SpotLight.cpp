#include "SpotLight.hpp"

std::vector<SpotLight*> SpotLight::m_Lights;

SpotLight::SpotLight()
	:m_SceneShader(*ResourceManager::Get<Shader>("ourshader")), m_LightShader(*ResourceManager::Get<Shader>("lightshader")), m_Position(Vector3(0,0,0)), m_Direction(Vector3(0, 0, 0)), m_CutOff(0), m_OuterCutOff(0), m_Constant(1.0), m_Linear(0), m_Quadratic(0)
{
	lightAmbient = Vector3(0, 0, 0);
	lightDiffuse = Vector3(0, 0, 0);
	lightSpecular = Vector3(0, 0, 0);
	lightColor = Vector3(1, 1, 1);

	m_Lights.push_back(this);

	name = "SpotLight" + std::to_string(m_Lights.size());
}

SpotLight::SpotLight(Vector3 position, Vector3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic, Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 color, Shader& sceneShader, Shader& lightShader)
	:m_SceneShader(sceneShader), m_LightShader(lightShader), m_Position(position), m_Direction(direction), m_CutOff(cutOff), m_OuterCutOff(outerCutOff), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic)
{
	lightAmbient = ambient;
	lightDiffuse = diffuse;
	lightSpecular = specular;
	lightColor = color;

	m_Lights.push_back(this);

	name = "SpotLight" + std::to_string(m_Lights.size());
}

SpotLight::~SpotLight()
{
}

void SpotLight::Update(Camera& cam)
{
	if (m_Lights.size() <= 0)
		return;

	for (size_t i = 0; i < m_Lights.size(); i++) {
		m_Lights[i]->DrawGUI(*m_Lights[i], cam);

		if (!m_Lights[i]->enable)
			continue;

		std::string name = "spotLights[" + std::to_string(i);	

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->Use();
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetInt("NbrSpotLights", static_cast<int>(m_Lights.size()));

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->Use();
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3("color", m_Lights[i]->lightColor);

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].position", m_Lights[i]->m_Position);
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].direction", m_Lights[i]->m_Direction);

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetFloat(name + "].cutOff", m_Lights[i]->m_CutOff);
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetFloat(name + "].outerCutOff", m_Lights[i]->m_OuterCutOff);

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetFloat(name + "].constant", m_Lights[i]->m_Constant);
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetFloat(name + "].linear", m_Lights[i]->m_Linear);
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetFloat(name + "].quadratic", m_Lights[i]->m_Quadratic);

		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].ambient", m_Lights[i]->lightAmbient * m_Lights[i]->lightColor);
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].diffuse", m_Lights[i]->lightDiffuse * m_Lights[i]->lightColor);
		ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name)->SetVec3(name + "].specular", m_Lights[i]->lightSpecular * m_Lights[i]->lightColor);

		if (m_Lights[i]->m_Position.x != cam.Position.x && m_Lights[i]->m_Position.y != cam.Position.y && m_Lights[i]->m_Position.z != cam.Position.z) {
			ResourceManager::Get<Shader>(m_Lights[i]->m_LightShader.name)->Use();
			ResourceManager::Get<Shader>(m_Lights[i]->m_LightShader.name)->SetMat4("mvp", Matrix4::MultiplyBy(cam.vp, Matrix4::TRS(m_Lights[i]->m_Position, Vector3(0.f, 0.f, 0.f), Vector3(0.8f, 0.8f, 0.8f))));

			ResourceManager::Get<Shader>(m_Lights[i]->m_LightShader.name)->SetVec3("ourColor", m_Lights[i]->lightColor);

			ResourceManager::Get<Model>("cube.obj")->Draw(*ResourceManager::Get<Shader>(m_Lights[i]->m_LightShader.name));
		}
	}
}

void SpotLight::UpdateSelf(Camera& cam)
{
	this->DrawGUI(*this, cam);
	if (!enable)
		return;

	std::string name = "spotLights[" + std::to_string(0);

	ResourceManager::Get<Shader>(m_SceneShader.name)->Use();
	ResourceManager::Get<Shader>(m_SceneShader.name)->SetInt("NbrSpotLights", static_cast<int>(m_Lights.size()));

	ResourceManager::Get<Shader>(m_SceneShader.name)->Use();
	ResourceManager::Get<Shader>(m_SceneShader.name)->SetVec3("color", lightColor);

	ResourceManager::Get<Shader>(m_SceneShader.name)->SetVec3(name + "].position", m_Position);
	ResourceManager::Get<Shader>(m_SceneShader.name)->SetVec3(name + "].direction", m_Direction);

	ResourceManager::Get<Shader>(m_SceneShader.name)->SetFloat(name + "].cutOff", m_CutOff);
	ResourceManager::Get<Shader>(m_SceneShader.name)->SetFloat(name + "].outerCutOff", m_OuterCutOff);

	ResourceManager::Get<Shader>(m_SceneShader.name)->SetFloat(name + "].constant", m_Constant);
	ResourceManager::Get<Shader>(m_SceneShader.name)->SetFloat(name + "].linear", m_Linear);
	ResourceManager::Get<Shader>(m_SceneShader.name)->SetFloat(name + "].quadratic", m_Quadratic);

	ResourceManager::Get<Shader>(m_SceneShader.name)->SetVec3(name + "].ambient", lightAmbient * lightColor);
	ResourceManager::Get<Shader>(m_SceneShader.name)->SetVec3(name + "].diffuse", lightDiffuse * lightColor);
	ResourceManager::Get<Shader>(m_SceneShader.name)->SetVec3(name + "].specular", lightSpecular * lightColor);

	if (m_Position.x != cam.Position.x && m_Position.y != cam.Position.y && m_Position.z != cam.Position.z) {
		ResourceManager::Get<Shader>(m_LightShader.name)->Use();
		ResourceManager::Get<Shader>(m_LightShader.name)->SetMat4("mvp", Matrix4::MultiplyBy(cam.vp, Matrix4::TRS(m_Position, Vector3(0.f, 0.f, 0.f), Vector3(0.2f, 0.2f, 0.2f))));

		ResourceManager::Get<Shader>(m_LightShader.name)->SetVec3("ourColor", lightColor);

		ResourceManager::Get<Model>("cube.obj")->Draw(*ResourceManager::Get<Shader>(m_LightShader.name));
	}
}


void SpotLight::DrawGUI(SpotLight& SpotLight, Camera& cam)
{
	if (ImGui::Begin("SpotLights", NULL)) {
		if (ImGui::CollapsingHeader(name.c_str())) {
			ImGui::PushID(this);
			//ImGui::Text("%s", name.c_str());
			
			ImGui::Checkbox("Enable Light", &enable);
			
			if (m_Position.x != cam.Position.x && m_Position.y != cam.Position.y && m_Position.z != cam.Position.z) {
				ImGui::SliderFloat3("Position", &SpotLight.m_Position.x, -MaxSliderValue, MaxSliderValue);

				ImGui::SliderFloat3("Direction", &SpotLight.m_Direction.x, -1.f, 1.f);
			}

			//Ambient
			ImGui::SliderFloat3("Ambient", &SpotLight.lightAmbient.x, 0.f, 1.f);

			//Diffuse
			ImGui::SliderFloat3("Diffuse", &SpotLight.lightDiffuse.x, 0.f, 1.f);

			//Specular
			ImGui::SliderFloat3("Specular", &SpotLight.lightSpecular.x, 0.f, 1.f);

			//Color
			ImGui::SliderFloat3("Color", &SpotLight.lightColor.x, 0.f, 1.f);

			ImGui::InputFloat("Max Slider Value", &MaxSliderValue, 0.050000000000f, 0, "%.2f");

			if (ImGui::Button("Reset")) {
				if (m_Position.x != cam.Position.x && m_Position.y != cam.Position.y && m_Position.z != cam.Position.z) {
					m_Position = Vector3(0.f, 0.f, 0.f);
					m_Direction = Vector3(0.f, 0.f, 0.f);
				}
				lightAmbient = Vector3(0.f, 0.f, 0.f);
				lightDiffuse = Vector3(0.f, 0.f, 0.f);
				lightSpecular = Vector3(0.f, 0.f, 0.f);
			}

			ImGui::PopID();
		}
	}
	ImGui::End();
}
