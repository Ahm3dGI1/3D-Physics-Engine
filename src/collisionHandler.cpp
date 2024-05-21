#include "collisions/collisionHandler.h"

#include <iostream>

void CollisionHandler::ResolveCollision(PhysicsObject& object1, PhysicsObject& object2){
    Shape* shape1 = object1.GetShape();
    Shape* shape2 = object2.GetShape();

    if (Sphere* sphere1 = dynamic_cast<Sphere*>(shape1)){
        if (Sphere* sphere2 = dynamic_cast<Sphere*>(shape2)){
            // Sphere-Sphere collision
            glm::vec3 collisionNormal = sphere1->center - sphere2->center;
            float distance = glm::length(collisionNormal);
            collisionNormal = glm::normalize(collisionNormal);

            float penetration = sphere1->radius + sphere2->radius - distance;

            float totalInvMass = object1.rigidBody.GetInverseMass() + object2.rigidBody.GetInverseMass();
            float movePerMass = penetration / totalInvMass;

            // Separating the two spheres by moving them in the opposite direction of the collision normal by an amount relative to their mass
            object1.rigidBody.SetPosition(object1.rigidBody.GetPosition() + collisionNormal * movePerMass * object1.rigidBody.GetInverseMass());
            object2.rigidBody.SetPosition(object2.rigidBody.GetPosition() - collisionNormal * movePerMass * object2.rigidBody.GetInverseMass());

            // Calculate the new velocity of the spheres after the collision using impulses
            glm::vec3 relativeVelocity = object1.rigidBody.GetVelocity() - object2.rigidBody.GetVelocity();
            float separatingVelocity = glm::dot(relativeVelocity, collisionNormal);

            float e = std::min(object1.rigidBody.GetRestitution(), object2.rigidBody.GetRestitution());

            float deltaSepVelocity = -(1 + e) * separatingVelocity;

            float impulse = deltaSepVelocity / totalInvMass;

            glm::vec3 impulsePerMass = collisionNormal * impulse;

            object1.rigidBody.SetVelocity(object1.rigidBody.GetVelocity() + impulsePerMass * object1.rigidBody.GetInverseMass());
            object2.rigidBody.SetVelocity(object2.rigidBody.GetVelocity() - impulsePerMass * object2.rigidBody.GetInverseMass());
        }

        else if (Box* box2 = dynamic_cast<Box*>(shape2)){
            // Sphere-Box collision
            glm::vec3 closestPoint = glm::clamp(object1.rigidBody.GetPosition(), box2->minCorner, box2->maxCorner);
            glm::vec3 collisionNormal = object1.rigidBody.GetPosition() - closestPoint;
            float distance = glm::length(collisionNormal);
            collisionNormal = glm::normalize(collisionNormal);

            float penetration = sphere1->radius - distance;

            float totalInvMass = object1.rigidBody.GetInverseMass() + object2.rigidBody.GetInverseMass();
            float movePerMass = penetration / totalInvMass;

            // Separating the sphere and the box by moving them in the opposite direction of the collision normal by an amount relative to their mass
            object1.rigidBody.SetPosition(object1.rigidBody.GetPosition() + collisionNormal * movePerMass * object1.rigidBody.GetInverseMass());
            object2.rigidBody.SetPosition(object2.rigidBody.GetPosition() - collisionNormal * movePerMass * object2.rigidBody.GetInverseMass());

            // Calculate the new velocity of the sphere and the box after the collision using impulses
            glm::vec3 relativeVelocity = object1.rigidBody.GetVelocity() - object2.rigidBody.GetVelocity();
            float separatingVelocity = glm::dot(relativeVelocity, collisionNormal);

            float e = std::min(object1.rigidBody.GetRestitution(), object2.rigidBody.GetRestitution());

            float deltaSepVelocity = -(1 + e) * separatingVelocity;

            float impulse = deltaSepVelocity / totalInvMass;

            glm::vec3 impulsePerMass = collisionNormal * impulse;

            object1.rigidBody.SetVelocity(object1.rigidBody.GetVelocity() + impulsePerMass * object1.rigidBody.GetInverseMass());
            object2.rigidBody.SetVelocity(object2.rigidBody.GetVelocity() - impulsePerMass * object2.rigidBody.GetInverseMass());
        }

        else if (Plane* plane2 = dynamic_cast<Plane*>(shape2)){
            // Sphere-Plane collision
            glm::vec3 collisionNormal = plane2->normal;
            float distance = glm::dot(object1.rigidBody.GetPosition() - plane2->center, collisionNormal);
            float penetration = sphere1->radius - distance;

            float totalInvMass = object1.rigidBody.GetInverseMass();
            float movePerMass = penetration / totalInvMass;

            // Separating the sphere and the plane by moving them in the opposite direction of the collision normal by an amount relative to their mass
            object1.rigidBody.SetPosition(object1.rigidBody.GetPosition() + collisionNormal * movePerMass * object1.rigidBody.GetInverseMass());

            // Calculate the new velocity of the sphere after the collision using impulses
            float separatingVelocity = glm::dot(object1.rigidBody.GetVelocity(), collisionNormal);

            float e = object1.rigidBody.GetRestitution();

            float deltaSepVelocity = -(1 + e) * separatingVelocity;

            float impulse = deltaSepVelocity / totalInvMass;

            glm::vec3 impulsePerMass = collisionNormal * impulse;

            object1.rigidBody.SetVelocity(object1.rigidBody.GetVelocity() + impulsePerMass * object1.rigidBody.GetInverseMass());
        } 
    }
}







// ANOTHER APPROACH BACKUP

/*
// Note For me: The Calculations are done from the prespective of the first object
CollisionHandler::CollisionHandler(PhysicsObject *o1, PhysicsObject *o2, float rest)
    : object1(o1), object2(o2), restitution(rest){
    // Calculate the collision normal
    collisionNormal = glm::normalize(object1->rigidBody.GetPosition() - object2->rigidBody.GetPosition());
}

void CollisionHandler::Resolve(float deltaTime) {
    ResolveVelocity(deltaTime);
    ResolveInterpenetration(deltaTime);
}

float CollisionHandler::CalculateSeparatingVelocity() const {
    glm::vec3 relativeVelocity = object1->rigidBody.GetVelocity();
    if (object2) 
        relativeVelocity -= object2->rigidBody.GetVelocity();
    return glm::dot(relativeVelocity, collisionNormal);
}

void CollisionHandler::ResolveVelocity(float deltaTime){
    // Calculate the separating velocity in the direction of the collision normal
    float separatingVelocity = CalculateSeparatingVelocity();

    // Check if the collision needs to be resolved
    if (separatingVelocity > 0) return; // The contact is separating (moving away from each other) or stationary

    // Calculate the new separating velocity according to the coefficient of restitution
    float newSepVelocity = -separatingVelocity * restitution;

    // Check the velocity buildup due to acceleration only
    glm::vec3 accCausedVelocity = object1->rigidBody.GetAcceleration();
    if (object2) accCausedVelocity -= object2->rigidBody.GetAcceleration();

    float accCausedSepVelocity = glm::dot(accCausedVelocity, collisionNormal) * deltaTime;

    if (accCausedSepVelocity < 0) {
        newSepVelocity += restitution * accCausedSepVelocity;

        if (newSepVelocity < 0) newSepVelocity = 0;
    }

    // Check the change in the velocity to apply it to each object according to its mass (more mass = less change in velocity)
    float deltaSepVelocity = newSepVelocity - separatingVelocity;

    float totalInvMass = object1->rigidBody.GetInverseMass();
    if (object2) totalInvMass += object2->rigidBody.GetInverseMass();

    // Check if the objects have infinite mass
    if (totalInvMass <= 0) return;

    // Calculate the impulse to apply to each object
    float impulse = deltaSepVelocity / totalInvMass;

    // Calculate the impulse to apply to each object according to its mass
    glm::vec3 impulsePerMass = collisionNormal * impulse;

    // Apply the impulse to the objects
    object1->rigidBody.SetVelocity(object1->rigidBody.GetVelocity() + impulsePerMass * object1->rigidBody.GetInverseMass());

    if (object2) {
        // The second object goes in the opposite direction
        object2->rigidBody.SetVelocity(object2->rigidBody.GetVelocity() - impulsePerMass * object2->rigidBody.GetInverseMass());
    }
}

void CollisionHandler::ResolveInterpenetration(float deltaTime){
    if (penetrationDepth <= 0) return; // No penetration

    // The calculations are relatice to the inverse mass since bigger mass means less movement
    float totalInvMass = object1->rigidBody.GetInverseMass();
    if (object2) totalInvMass += object2->rigidBody.GetInverseMass();

    if (totalInvMass <= 0) return; // Infinite mass means we have nothing to do

    glm::vec3 movePerMass = collisionNormal * (penetrationDepth / totalInvMass);

    // Move the objects
    object1->rigidBody.SetPosition(object1->rigidBody.GetPosition() + movePerMass * object1->rigidBody.GetInverseMass());

    if (object2) {
        object2->rigidBody.SetPosition(object2->rigidBody.GetPosition() + movePerMass * object2->rigidBody.GetInverseMass());
    }
}


// ********************** CollisionResolver **********************

CollisionResolver::CollisionResolver(unsigned iters) : iterations(iters), iterationsUsed(0) {}

void CollisionResolver::SetIterations(unsigned iters) {
    iterations = iters;
}

void CollisionResolver::ResolveCollision(CollisionHandler *collisionArray, unsigned numCollisions, float deltaTime){
    iterationsUsed = 0;

    while (iterationsUsed < iterations) {
        float maxSepVelocity = 0;
        unsigned maxIndex = numCollisions;

        for (unsigned i = 0; i < numCollisions; i++) {
            float sepVelocity = collisionArray[i].CalculateSeparatingVelocity();

            if (sepVelocity < maxSepVelocity) {
                maxSepVelocity = sepVelocity;
                maxIndex = i;
            }
        }

        if (maxIndex == numCollisions) break;

        collisionArray[maxIndex].Resolve(deltaTime);
        iterationsUsed++;
    }
}
*/