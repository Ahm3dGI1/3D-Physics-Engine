#include "physicsObjects/rigidbody.h"

Rigidbody::Rigidbody(glm::vec3 pos, float m, float damp)
    : position(pos), mass(m), damping(damp){
if (mass == 0.0f) inverseMass = 0.0f;
    else inverseMass = 1.0f / mass;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
    restitution = 0.7f;
    orientation = glm::mat3(1.0f);
    angularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
    angularAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    torqueAccum = glm::vec3(0.0f, 0.0f, 0.0f);
    inverseInertiaTensor = glm::mat3(1.0f);
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

void Rigidbody::SetOrientation(glm::mat3 orient) {
    orientation = orient;
}

glm::mat3 Rigidbody::GetOrientation() {
    return orientation;
}

void Rigidbody::SetAngularVelocity(glm::vec3 angVel) {
    angularVelocity = angVel;
}

glm::vec3 Rigidbody::GetAngularVelocity() {
    return angularVelocity;
}

void Rigidbody::SetAngularAcceleration(glm::vec3 angAcc) {
    angularAcceleration = angAcc;
}

glm::vec3 Rigidbody::GetAngularAcceleration() {
    return angularAcceleration;
}

void Rigidbody::SetInverseInertiaTensor(glm::mat3 invInertia) {
    inverseInertiaTensor = invInertia;
}

glm::mat3 Rigidbody::GetInverseInertiaTensor() {
    return inverseInertiaTensor;
}

void Rigidbody::SetMass(float m) {
    mass = m;
    if (mass == 0.0f) inverseMass = 0.0f;
    else inverseMass = 1.0f / mass;
}

float Rigidbody::GetMass() {
    return mass;
}

float Rigidbody::GetInverseMass() {
    return inverseMass;
}

void Rigidbody::SetDamping(float damp) {
    damping = damp;
}

float Rigidbody::GetDamping() {
    return damping;
}

void Rigidbody::SetRestitution(float rest) {
    restitution = rest;
}

float Rigidbody::GetRestitution() {
    return restitution;
}

// Add a force to the object
void Rigidbody::AddForce(glm::vec3 force) {
    forceAccum += force;
}

void Rigidbody::AddTorque(glm::vec3 torque) {
    torqueAccum += torque;
}

// Clear the forces applied to the object
void Rigidbody::ClearForceAccumulator() {
    forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Rigidbody::ClearTorqueAccumulator() {
    torqueAccum = glm::vec3(0.0f, 0.0f, 0.0f);
}

// Update the object's position and velocity
void Rigidbody::Update(float deltaTime) {
    // Update the acceleration
    acceleration = forceAccum * inverseMass;

    angularAcceleration = inverseInertiaTensor * torqueAccum;

    // Update the velocity
    velocity += acceleration * deltaTime;

    angularVelocity += angularAcceleration * deltaTime;

    // Apply damping
    velocity *= pow(damping, deltaTime);

    angularVelocity *= pow(damping, deltaTime);

    // Update the position
    position += velocity * deltaTime;

    // Update the orientation
    //UpdateOrientation(deltaTime);

    // Clear the forces applied to the object
    ClearForceAccumulator();
    ClearTorqueAccumulator();
}

void Rigidbody::UpdateOrientation(float deltaTime) {
    orientation += glm::mat3(0.0f, -angularVelocity.z, angularVelocity.y,
                             angularVelocity.z, 0.0f, -angularVelocity.x,
                             -angularVelocity.y, angularVelocity.x, 0.0f) * orientation * deltaTime;
}