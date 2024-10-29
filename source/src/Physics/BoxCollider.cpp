#include "BoxCollider.hpp"

BoxCollider::BoxCollider(Vector3 centerPos, Vector3 eulerRot, Vector3 scaling, Camera& cam)
    :m_Position(centerPos), m_EulerRot(eulerRot), m_Scaling(scaling), m_Camera(cam)
{
    m_Owner = nullptr;
}

BoxCollider::BoxCollider(Object* owner,Vector3 centerPos, Vector3 eulerRot, Vector3 scaling, Camera& cam)
    :m_Owner(owner), m_Position(centerPos), m_EulerRot(eulerRot), m_Scaling(scaling), m_Camera(cam)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Draw(Matrix4 vp)
{
    ResourceManager::Get<Shader>("lightshader")->Use();

    ResourceManager::Get<Shader>("lightshader")->SetVec3("ourColor", colliding ? Vector3(1.0f, 0.0f, 0.0f) : Vector3(1.0, 1.0, 1.0));
    ResourceManager::Get<Shader>("lightshader")->SetMat4("mvp", Matrix4::MultiplyBy(vp, Matrix4::TRS(m_Position, Vector3(0.f, 0.f, 0.f), m_Scaling))); //Set MVP Matrix for Model 1 
    ResourceManager::Get<Shader>("lightshader")->SetMat4("model", Matrix4::TRS(m_Position, Vector3(0.f, 0.f, 0.f), m_Scaling));

    ResourceManager::Get<Texture>("viking_room.jpg")->type = "diffuse";
    ResourceManager::Get<Texture>("viking_room.jpg")->BindTexture("lightshader"); //Bind Texture 0 To Model 1
    ResourceManager::Get<Model>("cube.obj")->Draw(*ResourceManager::Get<Shader>("lightshader"), 1);
}

bool BoxCollider::SolveSphereBox(SphereCollider& sphere, Vector3& hitpoint, Vector3& hitnormal, Vector3& hitdist)
{
    //DOWN
    /*
    PlaneCollider down(Vector3(0.f, 0.f, 0.f), Vector3(m_Position.x, (m_Position.y - m_Scaling.y) - sphere.radius, m_Position.z), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y) - sphere.radius, (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y) - sphere.radius, (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y) - sphere.radius, (m_Position.z + m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y) - sphere.radius, (m_Position.z + m_Scaling.z)), m_Camera);
    PlaneCollider up(Vector3(0.f, 0.f, 0.f), Vector3(m_Position.x, (m_Position.y + m_Scaling.y) + sphere.radius, m_Position.z), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y) + sphere.radius, (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y) + sphere.radius, (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y) + sphere.radius, (m_Position.z + m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y) + sphere.radius, (m_Position.z + m_Scaling.z)), m_Camera);
    
    PlaneCollider left(Vector3(0.f, 0.f, static_cast<float>(M_PI / 2.f)), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, m_Position.y, m_Position.z), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z)), m_Camera);
    PlaneCollider right(Vector3(0.f, 0.f, static_cast<float>(M_PI / 2.f)), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, m_Position.y, m_Position.z), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z)), m_Camera);
    
    PlaneCollider back(Vector3(static_cast<float>(M_PI / 2.f), 0.f, 0.f), Vector3(m_Position.x, m_Position.y, (m_Position.z - m_Scaling.z) - sphere.radius), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z) - sphere.radius), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z) - sphere.radius), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z) - sphere.radius), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z) - sphere.radius), m_Camera);
    PlaneCollider front(Vector3(static_cast<float>(M_PI / 2.f), 0.f, 0.f), Vector3(m_Position.x, m_Position.y, (m_Position.z + m_Scaling.z) + sphere.radius), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z) + sphere.radius), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z) + sphere.radius), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z) + sphere.radius), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z) + sphere.radius), m_Camera);
    */

    /*
    PlaneCollider down(Vector3(0.f, 0.f, 0.f), Vector3(m_Position.x, (m_Position.y - m_Scaling.y) - sphere.radius, m_Position.z), Vector3((m_Position.x - m_Scaling.x * 2), (m_Position.y - m_Scaling.y) - sphere.radius, (m_Position.z - m_Scaling.z * 2)), Vector3((m_Position.x + m_Scaling.x * 2), (m_Position.y - m_Scaling.y) - sphere.radius, (m_Position.z - m_Scaling.z * 2)), Vector3((m_Position.x + m_Scaling.x * 2), (m_Position.y - m_Scaling.y) - sphere.radius, (m_Position.z + m_Scaling.z * 2)), Vector3((m_Position.x - m_Scaling.x * 2), (m_Position.y - m_Scaling.y) - sphere.radius, (m_Position.z + m_Scaling.z * 2)), m_Camera);
    PlaneCollider up(Vector3(0.f, 0.f, 0.f), Vector3(m_Position.x, (m_Position.y + m_Scaling.y) + sphere.radius, m_Position.z), Vector3((m_Position.x - m_Scaling.x * 2), (m_Position.y + m_Scaling.y) + sphere.radius, (m_Position.z - m_Scaling.z * 2)), Vector3((m_Position.x + m_Scaling.x * 2), (m_Position.y + m_Scaling.y) + sphere.radius, (m_Position.z - m_Scaling.z * 2)), Vector3((m_Position.x + m_Scaling.x * 2), (m_Position.y + m_Scaling.y) + sphere.radius, (m_Position.z + m_Scaling.z * 2)), Vector3((m_Position.x - m_Scaling.x * 2), (m_Position.y + m_Scaling.y) + sphere.radius, (m_Position.z + m_Scaling.z * 2)), m_Camera);

    PlaneCollider left(Vector3(0.f, 0.f, static_cast<float>(M_PI / 2.f)), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, m_Position.y, m_Position.z), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, (m_Position.y - m_Scaling.y * 2), (m_Position.z - m_Scaling.z * 2)), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, (m_Position.y + m_Scaling.y * 2), (m_Position.z - m_Scaling.z * 2)), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, (m_Position.y + m_Scaling.y * 2), (m_Position.z + m_Scaling.z * 2)), Vector3((m_Position.x - m_Scaling.x) - sphere.radius, (m_Position.y - m_Scaling.y * 2), (m_Position.z + m_Scaling.z * 2)), m_Camera);
    PlaneCollider right(Vector3(0.f, 0.f, static_cast<float>(M_PI / 2.f)), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, m_Position.y, m_Position.z), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, (m_Position.y - m_Scaling.y * 2), (m_Position.z - m_Scaling.z * 2)), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, (m_Position.y + m_Scaling.y * 2), (m_Position.z - m_Scaling.z * 2)), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, (m_Position.y + m_Scaling.y * 2), (m_Position.z + m_Scaling.z * 2)), Vector3((m_Position.x + m_Scaling.x) + sphere.radius, (m_Position.y - m_Scaling.y * 2), (m_Position.z + m_Scaling.z * 2)), m_Camera);

    PlaneCollider back(Vector3(static_cast<float>(M_PI / 2.f), 0.f, 0.f), Vector3(m_Position.x, m_Position.y, (m_Position.z - m_Scaling.z) - sphere.radius), Vector3((m_Position.x - m_Scaling.x * 2), (m_Position.y - m_Scaling.y * 2), (m_Position.z - m_Scaling.z) - sphere.radius), Vector3((m_Position.x + m_Scaling.x * 2), (m_Position.y - m_Scaling.y * 2), (m_Position.z - m_Scaling.z) - sphere.radius), Vector3((m_Position.x + m_Scaling.x * 2), (m_Position.y + m_Scaling.y * 2), (m_Position.z - m_Scaling.z) - sphere.radius), Vector3((m_Position.x - m_Scaling.x * 2), (m_Position.y + m_Scaling.y * 2), (m_Position.z - m_Scaling.z) - sphere.radius), m_Camera);
    PlaneCollider front(Vector3(static_cast<float>(M_PI / 2.f), 0.f, 0.f), Vector3(m_Position.x, m_Position.y, (m_Position.z + m_Scaling.z) + sphere.radius), Vector3((m_Position.x - m_Scaling.x * 2), (m_Position.y - m_Scaling.y * 2), (m_Position.z + m_Scaling.z) + sphere.radius), Vector3((m_Position.x + m_Scaling.x * 2), (m_Position.y - m_Scaling.y * 2), (m_Position.z + m_Scaling.z) + sphere.radius), Vector3((m_Position.x + m_Scaling.x * 2), (m_Position.y + m_Scaling.y * 2), (m_Position.z + m_Scaling.z) + sphere.radius), Vector3((m_Position.x - m_Scaling.x * 2), (m_Position.y + m_Scaling.y * 2), (m_Position.z + m_Scaling.z) + sphere.radius), m_Camera);
    */

    PlaneCollider down(Vector3(0.f, 0.f, 0.f), Vector3(m_Position.x, (m_Position.y - m_Scaling.y), m_Position.z), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z)), m_Camera);
    PlaneCollider up(Vector3(0.f, 0.f, 0.f), Vector3(m_Position.x, (m_Position.y + m_Scaling.y), m_Position.z), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z)), m_Camera);

    PlaneCollider left(Vector3(0.f, 0.f, static_cast<float>(M_PI / 2.f)), Vector3((m_Position.x - m_Scaling.x), m_Position.y, m_Position.z), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z)), m_Camera);
    PlaneCollider right(Vector3(0.f, 0.f, static_cast<float>(M_PI / 2.f)), Vector3((m_Position.x + m_Scaling.x), m_Position.y, m_Position.z), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z)), m_Camera);

    PlaneCollider back(Vector3(static_cast<float>(M_PI / 2.f), 0.f, 0.f), Vector3(m_Position.x, m_Position.y, (m_Position.z - m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z - m_Scaling.z)), m_Camera);
    PlaneCollider front(Vector3(static_cast<float>(M_PI / 2.f), 0.f, 0.f), Vector3(m_Position.x, m_Position.y, (m_Position.z + m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y - m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x + m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z)), Vector3((m_Position.x - m_Scaling.x), (m_Position.y + m_Scaling.y), (m_Position.z + m_Scaling.z)), m_Camera);

    /*
    down.Update();
    up.Update();

    left.Update();
    right.Update();

    front.Update();
    back.Update();

    std::cout << "A " << front.A.x << " " << front.A.y << " " << front.A.z << std::endl;
    std::cout << "B " << front.B.x << " " << front.B.y << " " << front.B.z << std::endl;
    std::cout << "C " << front.C.x << " " << front.C.y << " " << front.C.z << std::endl;
    std::cout << "D " << front.D.x << " " << front.D.y << " " << front.D.z << std::endl;
    */

    //UP
    if (up.SpherePlaneSolver(sphere, hitpoint, hitnormal, hitdist, -1)) {
        return true;
    }
    
    //DOWN
    if (down.SpherePlaneSolver(sphere, hitpoint, hitnormal, hitdist)) {
        return true;
    }
    
    //LEFT
    if (left.SpherePlaneSolver(sphere, hitpoint, hitnormal, hitdist, -1)) {
        return true;
    }

    //RIGHT
    if (right.SpherePlaneSolver(sphere, hitpoint, hitnormal, hitdist)) {
        return true;
    }

    //FRONT
    if (front.SpherePlaneSolver(sphere, hitpoint, hitnormal, hitdist)) {
        return true;
    }
    
    //BACK
    if (back.SpherePlaneSolver(sphere, hitpoint, hitnormal, hitdist, -1)) {
        return true;
    }

    return false;
}

void BoxCollider::Update(Matrix4 vp)
{
    Draw(vp);

    m_Scaling = m_Owner->transform.scale;
}
