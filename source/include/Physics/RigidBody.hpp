#pragma once
#include "Model.hpp"
#include "Transform.hpp"

enum ForceMode
{
    FORCE,
    IMPULSE,
    ACCELERATION,
    VELOCITY_CHANGE
};

class RigidBody
{
public:
    Vector3 position;
    Vector3 velocity;
    float mass = 1.f;

    bool useGravity = true;

    void AddForce(Vector3 force, ForceMode mode, float dt = 0.016f);
    void Update(Vector3& pos, float dt = 0.016f);
};