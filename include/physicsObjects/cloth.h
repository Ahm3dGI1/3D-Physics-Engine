#ifndef CLOTH_H
#define CLOTH_H

#include <vector>
#include "physicsObjects/spring.h"

class Cloth {
public:
    Vec3 position;

    int width;
    int height;

    float spacing;
    float flexibility;
    float mass;

    std::vector<PhysicsObject> particles;
    std::vector<Spring> springs;

    Cloth(int w, int h, float s, float f, float m, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f));

    void Update(float deltaTime);
};


#endif // CLOTH_H