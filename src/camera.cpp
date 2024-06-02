#include "camera/camera.h"

// Default camera properties
    // Movement
float SPEED = 15.0f;
float SENSITIVITY = 0.2f;

    // Euler angles
float YAW = -90.0f;
float PITCH = 0.0f;

// Constructor with vectors
Camera::Camera(Vec3 Pos, Vec3 WorldUp, float Pitch, float Yaw)
: pos(Pos), worldUp(WorldUp), front(Vec3(0.0f, 0.0f, -1.0f)), pitch(Pitch), yaw(Yaw), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
    UpdateCameraVectors();
}

// Generate a view matrex for the view uniform
Mat4 Camera::GetViewMat(){
    return Math::LookAt(pos, pos + front, up);
}

// Take Inputs
void Camera::KeyboardInputs(CAMERA_MOV_KEYS key, float deltaTime){
    if (key == FORWARD)
        pos += front * movementSpeed * deltaTime;
    
    if (key == BACKWARD)
        pos -= front * movementSpeed * deltaTime;

    if (key == RIGHT)
        pos += right * movementSpeed * deltaTime;

    if (key == LEFT)
        pos -= right * movementSpeed * deltaTime;
}

void Camera::MouseInputs(float xOffset, float yOffset, GLboolean constrainPitch){
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw   += xOffset;
    pitch += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch){
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

// Quickly updating all of the camera vectors
void Camera::UpdateCameraVectors(){
    // Creating new front vector and use it to update the main one
    Vec3 Front;
    Front.x = cos(Math::ToRadians(yaw)) * cos(Math::ToRadians(pitch));
    Front.y = sin(Math::ToRadians(pitch));
    Front.z = sin(Math::ToRadians(yaw)) * cos(Math::ToRadians(pitch));
    front = Math::Normalize(Front);

    // Calculate the right vector of the camera and use it to calculate the up
    right = Math::Normalize(Math::Cross(front, worldUp));
    up = Math::Normalize(Math::Cross(right, front));
}