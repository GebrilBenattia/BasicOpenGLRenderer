#include "Texture.hpp"

std::filesystem::path const& fpath = "assets/textures/";

Texture::Texture(std::filesystem::path const& filename, bool RGBA)
    :m_NeedRGBA(RGBA)
{
    type = "diffuse";

    std::filesystem::path const& file = fpath.string() + filename.string();

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    int channelCount;
    stbi_set_flip_vertically_on_load(true);
    const unsigned char* data = stbi_load(file.string().c_str(), &m_Width, &m_Height, &channelCount, 0);

    if (data)
    {
        GLenum format{};
        if (channelCount == 1)
            format = GL_RED;
        else if (channelCount == 3)
            format = GL_RGB;
        else if (channelCount == 4)
            format = GL_RGBA;

        //std::cout << channelCount << std::endl;

        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load " << file << " texture" << std::endl;
    }
    stbi_image_free((void*)data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &TextureID);
}

void Texture::BindTexture(const char* shaderName) const
{
    ResourceManager::Get<Shader>(shaderName)->SetInt("material." + type, TextureID); //Set The Active Texture for The Object in The Shader
    ResourceManager::Get<Shader>(shaderName)->SetInt("material.specular", TextureID);
    //ResourceManager::Get<Shader>(shaderName)->SetInt("texture1", TextureID);
    glActiveTexture(GL_TEXTURE0 + TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);
}