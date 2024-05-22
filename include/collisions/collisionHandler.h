#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <physicsObjects/physicsObjects.h>


class CollisionHandler{
private:


protected:


public:
    
    void ResolveCollision(PhysicsObject& object1, PhysicsObject& object2);

    bool CheckCollision(PhysicsObject& object1, PhysicsObject& object2);
};


#endif //COLLISION_HANDLER_H