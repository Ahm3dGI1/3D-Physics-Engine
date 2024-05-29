#include "physicsObjects/spring.h"

Spring::Spring(PhysicsObject* node1, PhysicsObject* node2, float restLength, float stiffness) {
    this->node1 = node1;
    this->node2 = node2;
    this->restLength = restLength;
    this->stiffness = stiffness;
}

void Spring::ApplySpringForce() {
    glm::vec3 springVector = node2->rigidBody.GetPosition() - node1->rigidBody.GetPosition();
    float currentLength = glm::length(springVector);
    glm::vec3 force = glm::normalize(springVector) * stiffness * (currentLength - restLength);
    node1->rigidBody.AddForce(force);
    node2->rigidBody.AddForce(-force);
}