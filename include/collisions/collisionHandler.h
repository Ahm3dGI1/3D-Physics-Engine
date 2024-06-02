#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <physicsObjects/physicsObjects.h>
#include <math/math.h>

#include <iostream>


class CollisionHandler{
private:


protected:


public:
    
    void HandleCollision(PhysicsObject& object1, PhysicsObject& object2);
    void HandleSphereSphereCollision(PhysicsObject& sphereObject, PhysicsObject& object2, Sphere* sphere1, Sphere* sphere2);
    void HandleSphereBoxCollision(PhysicsObject& sphereObject, PhysicsObject& boxObject, Sphere* sphere, Box* box);
    void HandleSpherePlaneCollision(PhysicsObject& object1, Plane* plane, Sphere* sphere);
    //void HandleBoxBoxCollision(PhysicsObject& object1, PhysicsObject& object2, Box* box1, Box* box2);
    void HandleBoxPlaneCollision(PhysicsObject& boxObject, Plane* plane, Box* box);

    bool CheckCollision(PhysicsObject& object1, PhysicsObject& object2);
};


#endif //COLLISION_HANDLER_H