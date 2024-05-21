#include <vector>
#include <map>

#include "setup/setup.h"
#include "shaders/shaders.h"
#include "camera/camera.h"
#include "physicsObjects/physicsObjects.h"
#include "collisions/collisionHandler.h"


using namespace std; 

float WINDOW_WIDTH = 800;
float WINDOW_HEIGHT = 600;


// Functions prototypes
void ProcessUserInput(GLFWwindow* window);
void MouseCallback(GLFWwindow * window, double xPosIn, double yPosIn);

// Create a camera object
Camera camera(glm::vec3(0.0f, 5.0f, 10.0f));
bool firstMouse = true;
float lastX = WINDOW_WIDTH / 2.0;
float lastY = WINDOW_HEIGHT / 2.0;
float fov = 45.0f;

// Tracking the time between frames to do changes in a constant rate indepedent from the FPS of each device
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Physics Objects
vector<PhysicsObject> objects;

CollisionHandler collisionHandler;

int main() {

    // Create a window
    GLFWwindow* window = GLFWSetup(3, 3, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Check if the window was created successfully
    if(window == NULL) {
        cout << "ERROR CREATING GLFW WINDOW" << endl;
        glfwTerminate();
        return -1;
    }

    // Load OpenGL function pointers through GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "ERROR LOADING/INITIALIZING GLAD" << endl;
        return -1;
    }

    // Enable taking mouse inputs
    glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Enable Depth Buffer
    glEnable(GL_DEPTH_TEST);

    // Create the shader program
    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");

    //-------------------------------------------------------------------------------------

    objects.push_back(PhysicsObject(make_unique<Sphere>(1.0f, 3), glm::vec3(0.0f, 5.0f, 0.0f), 1.0f, 0.9f));

    objects.push_back(PhysicsObject(make_unique<Sphere>(1.0f, 3), glm::vec3(5.0f, 3.0f, 0.0f), 1.0f, 0.9f));

    objects.push_back(PhysicsObject(make_unique<Sphere>(1.0f, 3), glm::vec3(-5.0f, 3.0f, 0.0f), 1.0f, 0.9f));

    objects.push_back(PhysicsObject(make_unique<Box>(), glm::vec3(0.0f, 10.0f, 0.0f), 1.0f, 0.9f));

    objects.push_back(PhysicsObject(make_unique<Plane>(), glm::vec3(0.0f), 0.0f, 0.0f));

    glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f);
    //-------------------------------------------------------------------------------------


    // Vertex Array Object, Vertex Buffer Object
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

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

        //-----------------------
            glBindVertexArray(VAO);

        for (int i = 0; i < objects.size(); i++){
            glm::vec3 objPos = objects[i].rigidBody.GetPosition();

            //objects[i].rigidBody.AddForce(gravity * objects[i].rigidBody.GetMass());
            objects[i].Update(deltaTime);
            objects[i].rigidBody.AddForce(gravity * objects[i].rigidBody.GetMass());

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, objPos);
            shader.SetMat4("model", model);

            glBufferData(GL_ARRAY_BUFFER, objects[i].shape->shapeSize, objects[i].shape->vertices.data(), GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, objects[i].shape->indices.size() * sizeof(unsigned int), objects[i].shape->indices.data(), GL_STATIC_DRAW);
                // Draw the plane
            glDrawElements(GL_TRIANGLES, objects[i].shape->numVertices, GL_UNSIGNED_INT, 0);
        }

        for (int i = 0; i < objects.size(); i++){
            for (int j = i + 1; j < objects.size(); j++){
                if (objects[i].shape->Intersects(objects[j].shape.get())){
                    collisionHandler.ResolveCollision(objects[i], objects[j]);
                }
            }
        }

        //-----------------------

            // View Uniforms
        
        glm::mat4 view = camera.GetViewMat();
        shader.SetMat4("view", view);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f); 
        shader.SetMat4("projection", projection);

        // Swap the front and back buffers and poll for IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW, clearing any resources allocated by GLFW
    glfwTerminate();
    return 0;
}


void ProcessUserInput(GLFWwindow* window){
    // Close the window when the user presses the ESC key
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    //----------------Adding forces------------------------
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        objects[2].rigidBody.AddForce(glm::vec3(0.0f, -3.0f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        objects[2].rigidBody.AddForce(glm::vec3(0.0f, 3.0f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        objects[2].rigidBody.AddForce(glm::vec3(-3.0f, 0.0f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        objects[2].rigidBody.AddForce(glm::vec3(3.0f, 0.0f, 0.0f));
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