#include "Cube.hpp"

Cube::Cube(Camera& cam)
	:m_Camera(cam), collider(BoxCollider(this, transform.pos, transform.eulerRot, transform.scale / 2.f, cam))
{
    name = ResourceManager::Get<Model>("cube.obj")->name;
}

Cube::~Cube()
{
}

void Cube::Update(Shader& shader, Vector3 color, Vector3 upScale)
{
    ResourceManager::Get<Shader>(shader.name)->Use();

    transform.isDirty = true;
    transform.computeModelMatrix();
    ResourceManager::Get<Shader>(shader.name)->SetVec3("color", color);
    ResourceManager::Get<Shader>(shader.name)->SetMat4("mvp", Matrix4::MultiplyBy(m_Camera.vp, Matrix4::TRS(transform.pos, transform.eulerRot, transform.scale + upScale))); //Set MVP Matrix for Model 1 
    ResourceManager::Get<Shader>(shader.name)->SetMat4("model", Matrix4::TRS(transform.pos, transform.eulerRot, transform.scale + upScale));

    ResourceManager::Get<Texture>("viking_room.jpg")->type = "diffuse";
    ResourceManager::Get<Texture>("viking_room.jpg")->BindTexture(shader.name.c_str()); //Bind Texture 0 To Model 1

    Draw(*ResourceManager::Get<Shader>(shader.name));

    //std::cout << transform.scale.x << " " << transform.scale.y << " " << transform.scale.z << std::endl;

    //collider.Update(m_Camera.vp);
}
