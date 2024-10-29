#include "Model.hpp"

std::vector<Vertex> Model::m_Vertices;
std::vector<Mesh> Model::m_Meshes;
std::vector<unsigned int> Model::IndexBuffer;

std::string folderpath = "assets/models/";

Model::Model()
{
}

Model::~Model()
{
}

void Model::Load3DModel(std::string filename)
{
    //std::cout << name << std::endl;

    std::ifstream file(folderpath + filename);

    std::vector<Vector3> positions;
    std::vector<Vector2> textures;
    std::vector<Vector3> normals;

    int i = 0;

    m_Vertices.clear();
    IndexBuffer.clear();

    if (!file.is_open())
    {
        std::cout << "file can't be opened" << std::endl;
        return;
    }

    std::string line;

    while (getline(file, line))
    {
        size_t commentPos = line.find("#");

        if (commentPos != -1)
        {
            line = line.substr(0, commentPos);
        }

        if (line.empty())
        {
            continue;
        }

        if (line[0] == 'v')
        {

            if (line[1] == 't')
            {
                Vector2 uv;
                sscanf_s(line.c_str(), "vt %f %f", &uv.x, &uv.y);
                textures.push_back(uv);
            }

            else if (line[1] == 'n')
            {
                Vector3 normal;
                sscanf_s(line.c_str(), "vn %f %f %f", &normal.x, &normal.y, &normal.z);
                normals.push_back(normal);
            }

            else
            {
                Vector3 position;
                sscanf_s(line.c_str(), "v %f %f %f", &position.x, &position.y, &position.z);
                positions.push_back(position);
            }
        }

        else if (line[0] == 'f')
        {
            int index[9];
            sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &index[0], &index[1], &index[2], &index[3], &index[4], &index[5], &index[6], &index[7], &index[8]);
            Vertex vertex;

            vertex.position = positions[index[0] - 1];
            vertex.textureUv = textures[index[1] - 1];
            vertex.normal = normals[index[2] - 1];
            m_Vertices.push_back(vertex);

            vertex.position = positions[index[3] - 1];
            vertex.textureUv = textures[index[4] - 1];
            vertex.normal = normals[index[5] - 1];
            m_Vertices.push_back(vertex);

            vertex.position = positions[index[6] - 1];
            vertex.textureUv = textures[index[7] - 1];
            vertex.normal = normals[index[8] - 1];
            m_Vertices.push_back(vertex);
        }
    }
    m_Meshes.push_back(Mesh(m_Vertices, filename));
}

void Model::Draw(Shader& shader, bool wireframe) const
{
    for (size_t i = 0; i < m_Meshes.size(); i++) {
        if (m_Meshes[i].name == name)
            m_Meshes[i].Draw(shader, wireframe);
    }
}