#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Rigidbody
{
protected:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 forceAccum;

    glm::vec3 torqueAccum;
    glm::vec3 angularVelocity;
    glm::vec3 angularAcceleration;
    glm::mat3 orientation;
    glm::mat3 inverseInertiaTensor;

    float mass;
    float inverseMass;

    float damping;
    float restitution;

public:
    Rigidbody(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), float m = 1.0f, float damp = 0.9f);

    // Setters and Getters
    void SetPosition(glm::vec3 pos);
    glm::vec3 GetPosition();

    void SetVelocity(glm::vec3 vel);
    glm::vec3 GetVelocity();

    void SetAcceleration(glm::vec3 acc);
    glm::vec3 GetAcceleration();

    void SetOrientation(glm::mat3 orient);
    glm::mat3 GetOrientation();

    void SetAngularVelocity(glm::vec3 angVel);
    glm::vec3 GetAngularVelocity();

    void SetAngularAcceleration(glm::vec3 angAcc);
    glm::vec3 GetAngularAcceleration();

    void SetInverseInertiaTensor(glm::mat3 invInertia);
    glm::mat3 GetInverseInertiaTensor();


    void SetMass(float m);
    float GetMass();
    float GetInverseMass();

    void SetDamping(float damp);
    float GetDamping();

    void SetRestitution(float rest);
    float GetRestitution();

    // Add a force to the object
    void AddForce(glm::vec3 force);
    void AddTorque(glm::vec3 torque);

    // Clear the forces applied to the object
    void ClearForceAccumulator();
    void ClearTorqueAccumulator();

    // Update the object's position and velocity
    void Update(float deltaTime);

    void UpdateOrientation(float deltaTime);
};


#endif //RIGIDBODY_H