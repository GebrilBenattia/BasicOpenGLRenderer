#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vector4.hpp"
#include "Matrix4.hpp"

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD,
    DOWNWARD
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 30.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        Vector3 front;
        front.x = cosf(static_cast<float>(Yaw * (M_PI / 180.f))) * cosf(static_cast<float>(Pitch * (M_PI / 180.f)));
        front.y = sinf(static_cast<float>(Pitch * (M_PI / 180.f)));
        front.z = sinf(static_cast<float>(Yaw * (M_PI / 180.f))) * cosf(static_cast<float>(Pitch * (M_PI / 180.f)));
        Front = front.Normalize();
        // also re-calculate the Right and Up vector
        Right = Vector3(Vector3::CrossProduct(Front, WorldUp)).Normalize();  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = WorldUp;
        //Up = Vector3(Vector3::CrossProduct(Right, Front)).Normalize();
    }

public:
    // camera Attributes
    Vector3 Position;
    Vector3 Front;
    Vector3 Up;
    Vector3 Right;
    Vector3 WorldUp;

    Matrix4 projection;
    Matrix4 view;
    Matrix4 vp;

    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    float lastX = 800 / 2.0f;
    float lastY = 600 / 2.0f;

    bool firstMouse = true;

    // constructor with vectors
    Camera(Vector3 position = Vector3(0.0f, 0.0f, -1.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    Matrix4 GetViewMatrix();

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

    void Update();
};