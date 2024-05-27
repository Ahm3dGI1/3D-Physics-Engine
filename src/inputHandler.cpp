#include "input/inputHandler.h"

InputHandler::InputHandler(GLFWwindow* window, Camera camera) : window(window), camera(camera) {
 
}

void InputHandler::ProcessUserInput(GLFWwindow* window, float deltaTime) {
    // Process Input
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.pos += camera.front * camera.movementSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.pos -= camera.front * camera.movementSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.pos += camera.right * camera.movementSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.pos -= camera.right * camera.movementSpeed * deltaTime;
    }
}