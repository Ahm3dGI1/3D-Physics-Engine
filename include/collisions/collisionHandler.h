#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <physicsObjects/physicsObjects.h>


class CollisionHandler{
private:


protected:


public:
    
    void ResolveCollision(PhysicsObject& object1, PhysicsObject& object2);


};







// Another approach backup
/*
class CollisionResolver;


class CollisionHandler{

    friend class CollisionResolver;

private:

    void ResolveVelocity(float deltaTime);

protected:

    void Resolve(float deltaTime);

    float CalculateSeparatingVelocity() const;

public:
    PhysicsObject *object1, *object2;

    float restitution;

    glm::vec3 collisionNormal;

    float penetrationDepth; // negative value means no intersection and zero means touching

    CollisionHandler(PhysicsObject *o1, PhysicsObject *o2, float rest);

    void ResolveInterpenetration(float deltaTime);
};

class CollisionResolver{
private:

protected:
    unsigned iterations;

    unsigned iterationsUsed; // performance metric

public:
    CollisionResolver(unsigned iterations);

    void SetIterations(unsigned iterations);

    void ResolveCollision(CollisionHandler *collisionArray, unsigned numCollisions, float deltaTime);

};
*/

#endif //COLLISION_HANDLER_H