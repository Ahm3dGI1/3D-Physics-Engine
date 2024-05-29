#ifndef SPRING_H
#define SPRING_H

#include <physicsObjects/physicsObjects.h>

class Spring{
public:
    PhysicsObject* node1;
    PhysicsObject* node2;

    float restLength;
    float stiffness;

    Spring(PhysicsObject* node1, PhysicsObject* node2, float restLength, float stiffness);

    void ApplySpringForce();
};



#endif // SPRING_H