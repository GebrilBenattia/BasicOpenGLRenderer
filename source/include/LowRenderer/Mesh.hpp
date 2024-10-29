#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Matrix4.hpp"

#include "Shader.hpp"
#include "Texture.hpp"

struct Vertex;

class Mesh
{
private:

	unsigned int VAO, VBO, EBO;


public:
	void SetupMesh();
	std::string name;

	Mesh(const std::vector<Vertex>& vertices, std::string modelname);
	~Mesh();

	void Draw(Shader& shader, bool wireframe = false);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
};