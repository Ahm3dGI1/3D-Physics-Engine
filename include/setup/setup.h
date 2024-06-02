#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <setup/frameCounter.h>
#include <math/math.h>
#include <shaders/shaders.h>
#include <camera/camera.h>
#include <physicsObjects/physicsObjects.h>
#include <physicsObjects/spring.h>
#include <physicsObjects/cloth.h>
#include <collisions/collisionHandler.h>

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

GLFWwindow* GLFWSetup(int V_MAJOR, int V_MINOR,float WINDOW_WIDTH, float WINDOW_HEIGHT);

#endif // SETUP_H