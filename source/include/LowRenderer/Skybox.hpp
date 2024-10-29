#pragma once
#include "Cube.hpp"
#include "Texture.hpp"
#include <Matrix3.hpp>

class Skybox
{
private:
    
public:
	std::vector<std::string> faces;
	unsigned int CubeMapTexture;

	unsigned int skyboxVAO, skyboxVBO;

	Camera& MyCamera;

	Skybox(Camera& cam);
	~Skybox();

	unsigned int LoadCubemap(std::vector<std::string> faces);

	void Update();
};