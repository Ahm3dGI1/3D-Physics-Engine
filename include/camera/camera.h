#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <math/math.h>

enum CAMERA_MOV_KEYS {
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT
};

// Default camera properties
    // Movement
extern float SPEED;
extern float SENSITIVITY;

    // Euler angles
extern float YAW;
extern float PITCH;

class Camera {
public:
    // Camera
    Vec3 pos;
    Vec3 front;
    Vec3 up;
    Vec3 right;
    Vec3 worldUp;

    // Euler angles
    float yaw;
    float pitch;

    // Camera Properties
    float movementSpeed;
    float mouseSensitivity;

    // Constructor w vectors
    Camera(Vec3 Pos = Vec3(0.0f, 0.0f, 3.0f), Vec3 WorldUp = Vec3(0.0f, 1.0f, 0.0f), float Pitch = PITCH, float Yaw = YAW);

    // Generate a view matrex for the view uniform
    Mat4 GetViewMat();

    // Take Inputs
    void KeyboardInputs(CAMERA_MOV_KEYS key, float deltaTime);

    void MouseInputs(float xOffset, float yOffset, GLboolean constrainPitch = true);

private:

    // Quickly updating all of the camera vectors
    void UpdateCameraVectors();
};
#endif // CAMERA_H