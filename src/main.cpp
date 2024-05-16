#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders/shaders.h"
#include "camera/camera.h"


using namespace std; 

float WINDOW_WIDTH = 800;
float WINDOW_HEIGHT = 600;


// Functions prototypes
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessUserInput(GLFWwindow* window);
void MouseCallback(GLFWwindow * window, double xPosIn, double yPosIn);

// Create a camera object
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = WINDOW_WIDTH / 2.0;
float lastY = WINDOW_HEIGHT / 2.0;
float fov = 45.0f;

// Tracking the time between frames to do changes in a constant rate indepedent from the FPS of each device
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback); // Update the frame buffer whenever the window is resized

    // Enable taking mouse inputs
    glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Load OpenGL function pointers through GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "ERROR LOADING/INITIALIZING GLAD" << endl;
        return -1;
    }

    // Enable Depth Buffer
    glEnable(GL_DEPTH_TEST);

    // Create the shader program
    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");


    // 6 plane vertices
    float planeVerts[] = {
        // Positions              // Colors
         1.5f,  1.5f, 0.0f,    1.0f, 0.0f, 0.0f,
         1.5f, -1.5f, 0.0f,    0.0f, 1.0f, 0.0f,
        -1.5f, -1.5f, 0.0f,    0.0f, 0.0f, 1.0f,
        -1.5f,  1.5f, 0.0f,    0.0f, 0.0f, 1.0f,
         1.5f,  1.5f, 0.0f,    1.0f, 0.0f, 0.0f,
        -1.5f, -1.5f, 0.0f,    0.0f, 1.0f, 0.0f
    };

    // Vertex Array Object, Vertex Buffer Object
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVerts), planeVerts, GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader.Use();


    // Render loop
    while (!glfwWindowShouldClose(window)){
        // Taking Input
        ProcessUserInput(window);

        // Processing Time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Rendering commands here
        glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // View Uniforms
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-89.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shader.SetMat4("model", model);
        
        glm::mat4 view = camera.GetViewMat();
        shader.SetMat4("view", view);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f); 
        shader.SetMat4("projection", projection);



            // Draw the plane
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

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

    // Camera movements
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.KeyboardInputs(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.KeyboardInputs(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.KeyboardInputs(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.KeyboardInputs(RIGHT, deltaTime);
}

void MouseCallback(GLFWwindow* window, double xPosIn, double yPosIn){
    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
        return; // Skip the first input to prevent jumps.
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; // reversed since y-coordinates go from bottom to top

    lastX = xPos;
    lastY = yPos;

    camera.MouseInputs(xOffset, yOffset);
}