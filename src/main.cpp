#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 

float WINDOW_WIDTH = 800;
float WINDOW_HEIGHT = 600;


// Functions prototypes
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessUserInput(GLFWwindow* window);

int main() {
    glfwInit();

    // Set OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set OpenGL profile to core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Set OpenGL forward compatibility to true if he user has a MacOS
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create a window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "utable", NULL, NULL);

    // Check if the window was created successfully
    if(window == NULL) {
        cout << "ERROR CREATING GLFW WINDOW" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    // Load OpenGL function pointers through GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "ERROR LOADING/INITIALIZING GLAD" << endl;
        return -1;
    }

    // Render loop
    while (!glfwWindowShouldClose(window)){
        // Taking Input
        ProcessUserInput(window);

        // Rendering commands here
        glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the front and back buffers and poll for IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW, clearing any resources allocated by GLFW
    glfwTerminate();
    return 0;
}

// Whenever the user or the OS changes the window size this function is called to update the viewport size
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Set the viewport size to the new window size
    glViewport(0, 0, width, height);
}

void ProcessUserInput(GLFWwindow* window){
    // Close the window when the user presses the ESC key
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}