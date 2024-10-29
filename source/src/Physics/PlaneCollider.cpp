#include "PlaneCollider.hpp"

/*
PlaneCollider::PlaneCollider(Vector3& centerPos, Vector3& eulerRot, Vector3& scaling, Camera& camera)
    :m_Position(centerPos), m_EulerRot(eulerRot), m_Scaling(scaling), cam(camera)
{
    A = Vector3(m_Position.x - m_Scaling.x, m_Position.y, m_Position.z - m_Scaling.z);
    B = Vector3(m_Position.x + m_Scaling.x, m_Position.y, m_Position.z - m_Scaling.z);
    C = Vector3(m_Position.x + m_Scaling.x, m_Position.y, m_Position.z + m_Scaling.z);
    D = Vector3(m_Position.x - m_Scaling.x, m_Position.y, m_Position.z + m_Scaling.z);

    if (m_EulerRot.x != 0) {
        A = Vector3(A.x, A.y * std::cos(m_EulerRot.x) - A.z * std::sin(m_EulerRot.x), A.y * std::sin(m_EulerRot.x) + A.z * std::cos(m_EulerRot.x));
        B = Vector3(B.x, B.y * std::cos(m_EulerRot.x) - B.z * std::sin(m_EulerRot.x), B.y * std::sin(m_EulerRot.x) + B.z * std::cos(m_EulerRot.x));
        C = Vector3(C.x, C.y * std::cos(m_EulerRot.x) - C.z * std::sin(m_EulerRot.x), C.y * std::sin(m_EulerRot.x) + C.z * std::cos(m_EulerRot.x));
        D = Vector3(D.x, D.y * std::cos(m_EulerRot.x) - D.z * std::sin(m_EulerRot.x), D.y * std::sin(m_EulerRot.x) + D.z * std::cos(m_EulerRot.x));
    }
    else if (m_EulerRot.y != 0) {
        A = Vector3(A.x * std::cos(m_EulerRot.y) + A.z * std::sin(m_EulerRot.y), A.y, -A.x * std::sin(m_EulerRot.y) + A.z * std::cos(m_EulerRot.y));
        B = Vector3(B.x * std::cos(m_EulerRot.y) + B.z * std::sin(m_EulerRot.y), B.y, -B.x * std::sin(m_EulerRot.y) + B.z * std::cos(m_EulerRot.y));
        C = Vector3(C.x * std::cos(m_EulerRot.y) + C.z * std::sin(m_EulerRot.y), C.y, -C.x * std::sin(m_EulerRot.y) + C.z * std::cos(m_EulerRot.y));
        D = Vector3(D.x * std::cos(m_EulerRot.y) + D.z * std::sin(m_EulerRot.y), D.y, -D.x * std::sin(m_EulerRot.y) + D.z * std::cos(m_EulerRot.y));
    }
    else if (m_EulerRot.z != 0) {
        A = Vector3(A.x * std::cos(m_EulerRot.z) - A.y * std::sin(m_EulerRot.z), A.x * std::sin(m_EulerRot.z) + A.y * std::cos(m_EulerRot.z), A.z);
        B = Vector3(B.x * std::cos(m_EulerRot.z) - B.y * std::sin(m_EulerRot.z), B.x * std::sin(m_EulerRot.z) + B.y * std::cos(m_EulerRot.z), B.z);
        C = Vector3(C.x * std::cos(m_EulerRot.z) - C.y * std::sin(m_EulerRot.z), C.x * std::sin(m_EulerRot.z) + C.y * std::cos(m_EulerRot.z), C.z);
        D = Vector3(D.x * std::cos(m_EulerRot.z) - D.y * std::sin(m_EulerRot.z), D.x * std::sin(m_EulerRot.z) + D.y * std::cos(m_EulerRot.z), D.z);
    }
    //std::cout << "A" << " " << A.x << " " << A.y << " " << A.z << std::endl;
    //std::cout << "C" << " " << C.x << " " << C.y << " " << C.z << std::endl;
}
*/
PlaneCollider::PlaneCollider(Vector3 angle, Vector3 centerPos, Vector3 pointA, Vector3 pointB, Vector3 pointC, Vector3 pointD, Object* owner, Camera& camera)
    :rotation(angle), center(centerPos), A(pointA), B(pointB), C(pointC), D(pointD), m_Owner(owner), cam(camera)
{

}

PlaneCollider::PlaneCollider(Vector3 angle, Vector3 centerPos, Vector3 pointA, Vector3 pointB, Vector3 pointC, Vector3 pointD, Camera& camera)
    :rotation(angle), center(centerPos), A(pointA), B(pointB), C(pointC), D(pointD), cam(camera)
{
    m_Owner = nullptr;
}

PlaneCollider::~PlaneCollider()
{

}

void PlaneCollider::Draw()
{
    ResourceManager::Get<Shader>("lightshader")->Use();

    ResourceManager::Get<Shader>("lightshader")->SetVec3("ourColor", colliding ? Vector3(1.0f, 0.0f, 0.0f) : Vector3(1.0, 1.0, 1.0));
    ResourceManager::Get<Shader>("lightshader")->SetMat4("mvp", Matrix4::MultiplyBy(cam.vp, Matrix4::TRS(center, rotation, Vector3(1.f, 1.f,1.f)))); //Set MVP Matrix for Model 1 
    ResourceManager::Get<Shader>("lightshader")->SetMat4("model", Matrix4::TRS(center, rotation, Vector3(1.f, 1.f,1.f)));

    ResourceManager::Get<Texture>("viking_room.jpg")->type = "diffuse";
    ResourceManager::Get<Texture>("viking_room.jpg")->BindTexture("lightshader"); //Bind Texture 0 To Model 1
    ResourceManager::Get<Model>("plane.obj")->Draw(*ResourceManager::Get<Shader>("lightshader"), 1);
}

bool PlaneCollider::SpherePlaneSolver(SphereCollider& sphere, Vector3& hitpoint, Vector3& hitnormal, Vector3& hitdist, int normalDir)
{
    Vector3 pointA, pointB, pointC, pointD;

    if (A.x <= C.x && A.y >= C.y && A.z <= C.z && D.x <= B.x && D.y <= B.y && D.z <= B.z)
    {
        pointA = D;
        pointB = A;
        pointD = B;
        pointC = C;
    }
    else
    {
        pointA = A;
        pointB = B;
        pointD = D;
        pointC = C;
    }

    const Vector3 u = sphere.currentPosition - sphere.prevPos;

    const Vector3 normal = Vector3::CrossProduct((pointB - pointA), (pointD - pointA)) * static_cast<float>(normalDir);
    if (Vector3::DotProduct(normal, u) == 0) {
        return false;
    }

    //std::cout << normal.x << " " << normal.y << " " << normal.z << " " << std::endl;
    
    // ax + by + cz + d = 0 ==> ax + by + cz = -d
    const float d = -(Vector3::DotProduct(normal, pointA));

    // t0 = OpointA . n + d / u . n
    const float t0 = -((Vector3::DotProduct(sphere.prevPos, normal) + d) / (Vector3::DotProduct(u, normal)));

    if (t0 < 0 || t0 > 1) {
        return false;
    }

    //P(t0) = pointA + t0 * u
    const Vector3 hitPoint = sphere.prevPos + (u * t0);

    if (hitPoint.x >= pointA.x - 0.01f && hitPoint.y >= pointA.y - 0.01f && hitPoint.z >= pointA.z - 0.01f && hitPoint.x <= pointC.x + 0.01f && hitPoint.y <= pointC.y + 0.01f && hitPoint.z <= pointC.z + 0.01f) {
        hitnormal = normal;
        hitpoint = hitPoint;
        hitdist = Vector3::Dist(sphere.currentPosition, hitPoint);

        return true;
    }
        //std::cout << hitPoint.x << " " << hitPoint.y << " " << hitPoint.z << " " << std::endl;

    return false;
}

void PlaneCollider::Update()
{
    Draw();
}
