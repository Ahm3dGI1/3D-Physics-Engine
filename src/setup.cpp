#include "setup/setup.h"

GLFWwindow* GLFWSetup(int V_MAJOR, int V_MINOR,float WINDOW_WIDTH, float WINDOW_HEIGHT){
    glfwInit();

    // Set OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, V_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, V_MINOR);

    // Set OpenGL profile to core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Set OpenGL forward compatibility to true if he user has a MacOS
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create a window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "utable", NULL, NULL);

    // Check if the window was created successfully
    if(!window) return NULL;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback); // Update the frame buffer whenever the window is resized
    
    return window;
}

// Whenever the user or the OS changes the window size this function is called to update the viewport size
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Set the viewport size to the new window size
    glViewport(0, 0, width, height);
}