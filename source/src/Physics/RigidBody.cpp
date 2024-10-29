#include "RigidBody.hpp"

void RigidBody::AddForce(Vector3 force, ForceMode mode, float dt)
{
    if (mode == FORCE) {
        this->velocity.x += (force.x * dt) / mass;
        this->velocity.y += (force.y * dt) / mass;
        this->velocity.z += (force.z * dt) / mass;
    }
    else if (mode == IMPULSE) {
        this->velocity.x += force.x / mass;
        this->velocity.y += force.y / mass;
        this->velocity.z += force.z / mass;
    }
    else if (mode == ACCELERATION) {
        this->velocity.x += force.x * dt;
        this->velocity.y += force.y * dt;
        this->velocity.z += force.z * dt;
    }
    else if (mode == VELOCITY_CHANGE) {
        this->velocity.x += force.x;
        this->velocity.y += force.y;
        this->velocity.z += force.z;
    }
}

void RigidBody::Update(Vector3& pos, float dt)
{
    pos.x += velocity.x * dt;
    pos.y += velocity.y * dt;
    pos.z += velocity.z * dt;
}