#include "physicsObjects/spring.h"

Spring::Spring(PhysicsObject* node1, PhysicsObject* node2, float restLength, float stiffness) {
    this->node1 = node1;
    this->node2 = node2;
    this->restLength = restLength;
    this->stiffness = stiffness;
}

void Spring::ApplySpringForce() {
    Vec3 springVector = node2->rigidBody.GetPosition() - node1->rigidBody.GetPosition();
    float currentLength = Math::Magnitude(springVector);
    Vec3 force = Math::Normalize(springVector) * stiffness * (currentLength - restLength);
    node1->rigidBody.AddForce(force);
    node2->rigidBody.AddForce(-force);
}