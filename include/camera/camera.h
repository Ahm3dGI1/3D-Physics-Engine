#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Euler angles
    float yaw;
    float pitch;

    // Camera Properties
    float movementSpeed;
    float mouseSensitivity;

    // Constructor w vectors
    Camera(glm::vec3 Pos = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f), float Pitch = PITCH, float Yaw = YAW);

    // Generate a view matrex for the view uniform
    glm::mat4 GetViewMat();

    // Take Inputs
    void KeyboardInputs(CAMERA_MOV_KEYS key, float deltaTime);

    void MouseInputs(float xOffset, float yOffset, GLboolean constrainPitch = true);

private:

    // Quickly updating all of the camera vectors
    void UpdateCameraVectors();
};
#endif // CAMERA_H