#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

class Rigidbody
{
protected:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 forceAccum;

    float mass;
    float inverseMass;

    float damping;

public:
    Rigidbody(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), float m = 1.0f, float damp = 0.9f);

    // Setters and Getters
    void SetPosition(glm::vec3 pos);
    glm::vec3 GetPosition();

    void SetVelocity(glm::vec3 vel);
    glm::vec3 GetVelocity();

    void SetAcceleration(glm::vec3 acc);
    glm::vec3 GetAcceleration();

    void SetMass(float m);
    float GetMass();

    void SetDamping(float damp);
    float GetDamping();

    // Add a force to the object
    void AddForce(glm::vec3 force);

    // Clear the forces applied to the object
    void ClearAccumulator();

    // Update the object's position and velocity
    void Update(float deltaTime);
};


#endif //RIGIDBODY_H