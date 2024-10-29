#include "SphereCollider.hpp"

SphereCollider::SphereCollider(Vector3& centerPos, float sphereRadius)
	:currentPosition(centerPos), radius(sphereRadius)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Draw(Matrix4 vp)
{
    ResourceManager::Get<Shader>("lightshader")->Use();

    ResourceManager::Get<Shader>("lightshader")->SetVec3("ourColor", colliding ? Vector3(1.0f, 0.0f, 0.0f) : Vector3(1.0, 1.0, 1.0));
    ResourceManager::Get<Shader>("lightshader")->SetMat4("mvp", Matrix4::MultiplyBy(vp, Matrix4::TRS(currentPosition, Vector3(0.f, 0.f, 0.f), radius)));
    ResourceManager::Get<Shader>("lightshader")->SetMat4("model", Matrix4::TRS(currentPosition, Vector3(0.f, 0.f, 0.f), radius));

    ResourceManager::Get<Texture>("viking_room.jpg")->type = "diffuse";
    ResourceManager::Get<Texture>("viking_room.jpg")->BindTexture("lightshader");
    ResourceManager::Get<Model>("sphere.obj")->Draw(*ResourceManager::Get<Shader>("lightshader"), 1);
}

void SphereCollider::Update(Matrix4 vp)
{
    Draw(vp);
}