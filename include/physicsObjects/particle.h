#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>
#include <physicsObjects/shape.h>

class Particle {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 forceAccum;
    float mass;
    float radius;
    float damping;
    bool isFixed;

    Particle(glm::vec3 position, float mass, float radius, float damping, bool isFixed);

    Particle();

    void AddForce(glm::vec3 force);


    void Update(float deltaTime);
};


#endif // PARTICLE_H