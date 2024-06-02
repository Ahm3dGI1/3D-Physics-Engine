#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <math/math.h>

class Rigidbody
{
protected:
    Vec3 position;
    Vec3 previousPosition;
    Vec3 velocity;
    Vec3 acceleration;
    Vec3 forceAccum;

    Vec3 torqueAccum;
    Vec3 angularVelocity;
    Vec3 angularAcceleration;
    Mat3 orientation;
    Mat3 inverseInertiaTensor;

    float mass;
    float inverseMass;

    float damping;
    float restitution;

    bool isFixed;

public:
    Rigidbody(Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), float m = 1.0f, float damp = 0.9f);

    // Setters and Getters
    void SetPosition(Vec3 pos);
    Vec3 GetPosition();

    void SetVelocity(Vec3 vel);
    Vec3 GetVelocity();

    void SetAcceleration(Vec3 acc);
    Vec3 GetAcceleration();

    void SetOrientation(Mat3 orient);
    Mat3 GetOrientation();

    void SetAngularVelocity(Vec3 angVel);
    Vec3 GetAngularVelocity();

    void SetAngularAcceleration(Vec3 angAcc);
    Vec3 GetAngularAcceleration();

    void SetInverseInertiaTensor(Mat3 invInertia);
    Mat3 GetInverseInertiaTensor();


    void SetMass(float m);
    float GetMass();
    float GetInverseMass();

    void SetDamping(float damp);
    float GetDamping();

    void SetRestitution(float rest);
    float GetRestitution();

    void SetFixed(bool fixed);
    bool GetFixed();

    // Add a force to the object
    void AddForce(Vec3 force);
    void AddTorque(Vec3 torque);

    // Clear the forces applied to the object
    void ClearForceAccumulator();
    void ClearTorqueAccumulator();

    // Update the object's position and velocity
    void Update(float deltaTime);

    void UpdateOrientation(float deltaTime);
};


#endif //RIGIDBODY_H