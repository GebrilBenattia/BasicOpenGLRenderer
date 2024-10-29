#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "IResource.hpp"
#include "Texture.hpp"
#include "Vector4.hpp"

#include "Mesh.hpp"

struct Vertex
{
    Vector3 position;
    Vector3 normal;
    Vector2 textureUv;
};

class Model : public IResource
{
private:
    static std::vector<Vertex> m_Vertices;
    static std::vector<Mesh> m_Meshes;
    static std::vector<unsigned int> IndexBuffer;

public:
    Model();
    Model(std::string modelName)
    {
        name = modelName;
    }
    ~Model();

    void Load3DModel(std::string filename);

    void Draw(Shader& shader, bool wireframe = false) const;
};