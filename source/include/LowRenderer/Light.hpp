#pragma once

#include "Matrix4.hpp"
#include "ResourcesManager.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include "Object.hpp"
#include "ImGui/imgui.h"

class Light
{
private:

public:
	Vector3 lightAmbient, lightDiffuse, lightSpecular, lightColor;
	float MaxSliderValue = 100.f;
	std::string name;
	bool enable = true;

	~Light() {};
	virtual void Update() {};

	virtual void DrawGUI();
};