#ifndef PARTICLE_H
#define PARTICLE_H

#include <physicsObjects/shape.h>

class Particle {
public:
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;
    Vec3 forceAccum;
    float mass;
    float radius;
    float damping;
    bool isFixed;

    Particle(Vec3 position, float mass, float radius, float damping, bool isFixed);

    Particle();

    void AddForce(Vec3 force);


    void Update(float deltaTime);
};


#endif // PARTICLE_H