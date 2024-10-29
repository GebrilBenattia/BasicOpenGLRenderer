#include "Skybox.hpp"

Skybox::Skybox(Camera& cam)
    :MyCamera(cam)
{
    float skyboxVertices[] =
    {
        //   Coordinates
        -1.0f, -1.0f,  1.0f,//        7--------6
         1.0f, -1.0f,  1.0f,//       /|       /|
         1.0f, -1.0f, -1.0f,//      4--------5 |
        -1.0f, -1.0f, -1.0f,//      | |      | |
        -1.0f,  1.0f,  1.0f,//      | 3------|-2
         1.0f,  1.0f,  1.0f,//      |/       |/
         1.0f,  1.0f, -1.0f,//      0--------1
        -1.0f,  1.0f, -1.0f
    };

    unsigned int skyboxIndices[] =
    {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };
    // Create VAO, VBO, and EBO for the skybox
    unsigned int skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // All the faces of the cubemap (make sure they are in this exact order)

    /*faces.push_back("assets/textures/right.jpg");
    faces.push_back("assets/textures/left.jpg");
    faces.push_back("assets/textures/top.jpg");
    faces.push_back("assets/textures/bottom.jpg");
    faces.push_back("assets/textures/front.jpg");
    faces.push_back("assets/textures/back.jpg");*/

    faces.push_back("assets/textures/px1f.jpg");
    faces.push_back("assets/textures/nx1.jpg");
    faces.push_back("assets/textures/py1.jpg");
    faces.push_back("assets/textures/ny1.jpg");
    faces.push_back("assets/textures/pz1.jpg");
    faces.push_back("assets/textures/nz1.jpg");

    CubeMapTexture = LoadCubemap(faces);
}

Skybox::~Skybox()
{
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
}

unsigned int Skybox::LoadCubemap(std::vector<std::string> faces)
{
    // Creates the cubemap texture object
    unsigned int cubemapTexture;
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // This might help with seams on some systems
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    // Cycles through all the textures and attaches them to the cubemap object
    for (unsigned int i = 0; i < faces.size(); i++) {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
            (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else {
            std::cout << "Failed to load texture: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    return cubemapTexture;
}

void Skybox::Update()
{
    glDepthFunc(GL_LEQUAL);

    ResourceManager::Get<Shader>("skyboxshader")->Use();
    Matrix4 view = Matrix4(Vector4(MyCamera.view.Row0.x, MyCamera.view.Row0.y, MyCamera.view.Row0.z, 0), Vector4(MyCamera.view.Row1.x, MyCamera.view.Row1.y, MyCamera.view.Row1.z, 0), Vector4(MyCamera.view.Row2.x, MyCamera.view.Row2.y, MyCamera.view.Row2.z, 0), MyCamera.view.Row3);
    ResourceManager::Get<Shader>("skyboxshader")->SetMat4("vp", Matrix4::MultiplyBy(MyCamera.projection, view));

    // Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
    // where an object is present (a depth of 1.0f will always fail against any object's depth value)
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0 + CubeMapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapTexture);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Switch back to the normal depth function
    glDepthFunc(GL_LESS);
}