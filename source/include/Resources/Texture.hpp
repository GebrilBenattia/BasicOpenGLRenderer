#pragma once

#include <filesystem>
#include "ResourcesManager.hpp"
#include "IResource.hpp"
#include "Shader.hpp"
#include "Vector4.hpp"
#include <algorithm>
#include <cmath>
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

class Texture : public IResource
{
private:
	int m_Width, m_Height;
	bool m_NeedRGBA;

public:
	unsigned int TextureID;
	std::string type;

	Texture(std::filesystem::path const& filename, bool RGBA = false);
	~Texture();

	void BindTexture(const char* shaderName) const;
};
