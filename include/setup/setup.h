#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

GLFWwindow* GLFWSetup(int V_MAJOR, int V_MINOR,float WINDOW_WIDTH, float WINDOW_HEIGHT);

#endif // SETUP_H