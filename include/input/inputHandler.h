#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GLFW/glfw3.h>
#include <camera/camera.h>



class InputHandler
{
private:
    GLFWwindow* window;
    Camera camera;
public:
    InputHandler(GLFWwindow* window, Camera camera);

    void ProcessUserInput(GLFWwindow* window, float deltaTime);

    void MouseCallback(GLFWwindow * window, double xPosIn, double yPosIn);

    // Camera Inputs
    void KeyboardInputs(CAMERA_MOV_KEYS key, float deltaTime);

    void MouseInputs(float xOffset, float yOffset, GLboolean constrainPitch = true);
};


#endif //INPUT_HANDLER_H