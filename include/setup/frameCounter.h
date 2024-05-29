#ifndef FRAMECOUNTER_H
#define FRAMECOUNTER_H

#include <iostream>
#include <GLFW/glfw3.h>

class FrameCounter {
public:
    FrameCounter() : frameCount(0), lastTime(0.0f) {}

    void Update() {
        double currentTime = glfwGetTime();
        frameCount++;
        
        if (currentTime - lastTime >= 1.0) {
            std::cout << "FPS: " << frameCount << std::endl;
            frameCount = 0;
            lastTime = currentTime;
        }
    }

private:
    int frameCount;
    double lastTime;
};

#endif // FRAMECOUNTER_H