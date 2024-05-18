#include "physicsObjects/rigidbody.h"

Rigidbody::Rigidbody(glm::vec3 pos, float m, float damp)
    : position(pos), mass(m), damping(damp){
if (mass == 0.0f) inverseMass = 0.0f;
    else inverseMass = 1.0f / mass;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
}

// Setters and Getters
void Rigidbody::SetPosition(glm::vec3 pos) {
    position = pos;
}

glm::vec3 Rigidbody::GetPosition() {
    return position;
}

void Rigidbody::SetVelocity(glm::vec3 vel) {
    velocity = vel;
}

glm::vec3 Rigidbody::GetVelocity() {
    return velocity;
}

void Rigidbody::SetAcceleration(glm::vec3 acc) {
    acceleration = acc;
}

glm::vec3 Rigidbody::GetAcceleration() {
    return acceleration;
}

void Rigidbody::SetMass(float m) {
    mass = m;
    if (mass == 0.0f) inverseMass = 0.0f;
    else inverseMass = 1.0f / mass;
}

float Rigidbody::GetMass() {
    return mass;
}

void Rigidbody::SetDamping(float damp) {
    damping = damp;
}

float Rigidbody::GetDamping() {
    return damping;
}

// Add a force to the object
void Rigidbody::AddForce(glm::vec3 force) {
    forceAccum += force;
}

// Clear the forces applied to the object
void Rigidbody::ClearAccumulator() {
    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
}

// Update the object's position and velocity
void Rigidbody::Update(float deltaTime) {
    // Update the acceleration
    acceleration = forceAccum * inverseMass;

    // Update the velocity
    velocity += acceleration * deltaTime;

    // Apply damping
    velocity *= pow(damping, deltaTime);

    // Update the position
    position += velocity * deltaTime;

    // Clear the forces applied to the object
    ClearAccumulator();
}
