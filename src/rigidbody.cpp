#include "physicsObjects/rigidbody.h"

Rigidbody::Rigidbody(Vec3 pos, float m, float damp)
    : position(pos), mass(m), damping(damp){
if (mass == 0.0f) inverseMass = 0.0f;
    else inverseMass = 1.0f / mass;
    previousPosition = position;
    velocity = Vec3(0.0f, 0.0f, 0.0f);
    acceleration = Vec3(0.0f, 0.0f, 0.0f);
    forceAccum = Vec3(0.0f, 0.0f, 0.0f);
    restitution = 0.7f;
    orientation = Mat3(1.0f);
    angularVelocity = Vec3(0.0f, 0.0f, 0.0f);
    angularAcceleration = Vec3(0.0f, 0.0f, 0.0f);
    torqueAccum = Vec3(0.0f, 0.0f, 0.0f);
    inverseInertiaTensor = Mat3(1.0f);
    isFixed = false;
}

// Setters and Getters
void Rigidbody::SetPosition(Vec3 pos) {
    position = pos;
}

Vec3 Rigidbody::GetPosition() {
    return position;
}

void Rigidbody::SetVelocity(Vec3 vel) {
    velocity = vel;
}

Vec3 Rigidbody::GetVelocity() {
    return velocity;
}

void Rigidbody::SetAcceleration(Vec3 acc) {
    acceleration = acc;
}

Vec3 Rigidbody::GetAcceleration() {
    return acceleration;
}

void Rigidbody::SetOrientation(Mat3 orient) {
    orientation = orient;
}

Mat3 Rigidbody::GetOrientation() {
    return orientation;
}

void Rigidbody::SetAngularVelocity(Vec3 angVel) {
    angularVelocity = angVel;
}

Vec3 Rigidbody::GetAngularVelocity() {
    return angularVelocity;
}

void Rigidbody::SetAngularAcceleration(Vec3 angAcc) {
    angularAcceleration = angAcc;
}

Vec3 Rigidbody::GetAngularAcceleration() {
    return angularAcceleration;
}

void Rigidbody::SetInverseInertiaTensor(Mat3 invInertia) {
    inverseInertiaTensor = invInertia;
}

Mat3 Rigidbody::GetInverseInertiaTensor() {
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

void Rigidbody::SetFixed(bool fixed) {
    isFixed = fixed;
}

bool Rigidbody::GetFixed() {
    return isFixed;
}

// Add a force to the object
void Rigidbody::AddForce(Vec3 force) {
    forceAccum += force;
}

void Rigidbody::AddTorque(Vec3 torque) {
    torqueAccum += torque;
}

// Clear the forces applied to the object
void Rigidbody::ClearForceAccumulator() {
    forceAccum = Vec3(0.0f, 0.0f, 0.0f);
}

void Rigidbody::ClearTorqueAccumulator() {
    torqueAccum = Vec3(0.0f, 0.0f, 0.0f);
}

// Update the object's position and velocity
void Rigidbody::Update(float deltaTime) {
    if (!isFixed){
        // Update the acceleration
        acceleration = forceAccum * inverseMass;

        // Update the velocity
        velocity += acceleration * deltaTime;

        // Apply damping
        velocity *= pow(damping, deltaTime);

        // Update the position
        position += velocity * deltaTime;

        // Clear the forces applied to the object
        ClearForceAccumulator();
    }
}

void Rigidbody::UpdateOrientation(float deltaTime) {
    orientation += Mat3(0.0f, -angularVelocity.z, angularVelocity.y,
                             angularVelocity.z, 0.0f, -angularVelocity.x,
                             -angularVelocity.y, angularVelocity.x, 0.0f) * orientation * deltaTime;
}