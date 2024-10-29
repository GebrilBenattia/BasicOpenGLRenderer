#include "Light.hpp"
Vector3 lightAmbient, lightDiffuse, lightSpecular, lightColor;
std::string name;

//Create sliders to modify lights values
void Light::DrawGUI()
{
	if (ImGui::Begin(name.c_str(), NULL)) {
		ImGui::Text("%s", name.c_str());
		//Ambient
		ImGui::SliderFloat3("Ambient", &lightAmbient.x, 0.f, 1.f);

		//Diffuse
		ImGui::SliderFloat3("Diffuse", &lightDiffuse.x, 0.f, 1.f);

		//Specular
		ImGui::SliderFloat3("Specular", &lightSpecular.x, 0.f, 1.f);
	}
	ImGui::End();
}
