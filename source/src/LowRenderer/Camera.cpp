#include "Camera.hpp"

#include <iostream>

// constructor with vectors
Camera::Camera(Vector3 position, Vector3 up, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;

    Matrix4::Projection(Zoom, 800 / 600, 0.1f, 1000.f, projection);

    updateCameraVectors();
}
// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = Vector3(posX, posY, posZ);
    WorldUp = Vector3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;

    Matrix4::Projection(Zoom, 800 / 600, 0.1f, 1000.f, projection);

    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
Matrix4 Camera::GetViewMatrix()
{
    Matrix4 temp;
    Matrix4::View(Position, Position + Front, Up, temp);
    return temp;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    Vector3 movement;

    if (direction == FORWARD)
        movement = Front;

    if (direction == BACKWARD)
        movement = Front.Opp();

    if (direction == LEFT)
        movement = Right.Opp();

    if (direction == RIGHT)
        movement = Right;

    if (direction == UPWARD)
        movement = Up;

    if (direction == DOWNWARD)
        movement = Up.Opp();

    Position = Position + movement.Normalize() * velocity * deltaTime * 100.f;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset / 15.f;
    if (Zoom < 44.0f)
        Zoom = 44.0f;
    if (Zoom > 47.0f)
        Zoom = 47.0f;
}

void Camera::Update()
{
    view = GetViewMatrix();

    Matrix4::Projection(Zoom, 800 / 600, 0.1f, 1000.f, projection);
    vp = Matrix4::MultiplyBy(projection, view);
}
