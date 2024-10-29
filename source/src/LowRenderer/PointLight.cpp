#include "PointLight.hpp"

std::vector<PointLight*> PointLight::m_Lights;

PointLight::PointLight()
	:m_SceneShader(*ResourceManager::Get<Shader>("ourshader")), m_LightShader(*ResourceManager::Get<Shader>("lightshader")), m_Position(Vector3(0,0,0)), m_Constant(1.0), m_Linear(0), m_Quadratic(0)
{
	lightAmbient = Vector3(0, 0, 0);
	lightDiffuse = Vector3(0, 0, 0);
	lightSpecular = Vector3(0, 0, 0);
	lightColor = Vector3(1, 1, 1);

	m_Lights.push_back(this);

	name = "PointLight" + std::to_string(m_Lights.size());
}

PointLight::PointLight(Vector3 position, float constant, float linear, float quadratic, Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 color, Shader& sceneShader, Shader& lightShader)
	:m_SceneShader(sceneShader), m_LightShader(lightShader), m_Position(position), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic)
{
	lightAmbient = ambient;
	lightDiffuse = diffuse;
	lightSpecular = specular;
	lightColor = color;

	m_Lights.push_back(this);

	name = "PointLight" + std::to_string(m_Lights.size());
}

PointLight::~PointLight()
{
}

void PointLight::Update(Camera& cam)
{
	if (m_Lights.size() <= 0)
		return;

	for (size_t i = 0; i < m_Lights.size(); i++) {
		m_Lights[i]->DrawGUI(*m_Lights[i]);

		if (!m_Lights[i]->enable)
			continue;

		std::string name = "pointLights[" + std::to_string(i);

		Shader* sceneShader = ResourceManager::Get<Shader>(m_Lights[i]->m_SceneShader.name);
		Shader* lightShader = ResourceManager::Get<Shader>(m_Lights[i]->m_LightShader.name);

		sceneShader->Use();
		sceneShader->SetInt("NbrPointLights", static_cast<int>(m_Lights.size()));

		sceneShader->Use();

		sceneShader->SetVec3("color", m_Lights[i]->lightColor);
		sceneShader->SetVec3(name + "].position", m_Lights[i]->m_Position);

		sceneShader->SetFloat(name + "].constant", m_Lights[i]->m_Constant);
		sceneShader->SetFloat(name + "].linear", m_Lights[i]->m_Linear);
		sceneShader->SetFloat(name + "].quadratic", m_Lights[i]->m_Quadratic);

		sceneShader->SetVec3(name + "].ambient", m_Lights[i]->lightAmbient * m_Lights[i]->lightColor);
		sceneShader->SetVec3(name + "].diffuse", m_Lights[i]->lightDiffuse * m_Lights[i]->lightColor);
		sceneShader->SetVec3(name + "].specular", m_Lights[i]->lightSpecular * m_Lights[i]->lightColor);

		lightShader->Use();
		lightShader->SetMat4("mvp", Matrix4::MultiplyBy(cam.vp, Matrix4::TRS(m_Lights[i]->m_Position, Vector3(0.f, 0.f, 0.f), Vector3(0.8f, 0.8f, 0.8f))));

		lightShader->SetVec3("ourColor", m_Lights[i]->lightColor);

		ResourceManager::Get<Model>("cube.obj")->Draw(*lightShader);

	}
}

void PointLight::DrawGUI(PointLight& PointLight)
{
	if (ImGui::Begin("PointLights", NULL)) {
		if (ImGui::CollapsingHeader(name.c_str())) {
			ImGui::PushID(this);
			//ImGui::Text("%s", name.c_str());
			ImGui::Checkbox("Enable Light", &enable);

			//Position
			ImGui::SliderFloat3("Position", &PointLight.m_Position.x, -MaxSliderValue, MaxSliderValue);

			//Ambient
			ImGui::SliderFloat3("Ambient", &PointLight.lightAmbient.x, 0.f, 1.f);

			//Diffuse
			ImGui::SliderFloat3("Diffuse", &PointLight.lightDiffuse.x, 0.f, 1.f);

			//Specular
			ImGui::SliderFloat3("Specular", &PointLight.lightSpecular.x, 0.f, 1.f);

			//Color
			ImGui::SliderFloat3("Color", &PointLight.lightColor.x, 0.f, 1.f);

			ImGui::InputFloat("Max Slider Value", &MaxSliderValue, 0.050000000000f, 0, "%.2f");

			if (ImGui::Button("Reset")) {
				m_Position = Vector3(0.f, 0.f, 0.f);
				lightAmbient = Vector3(0.f, 0.f, 0.f);
				lightDiffuse = Vector3(0.f, 0.f, 0.f);
				lightSpecular = Vector3(0.f, 0.f, 0.f);
			}

			ImGui::PopID();
		}
	}
	ImGui::End();
}
