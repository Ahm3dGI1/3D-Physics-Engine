#include "collisions/collisionHandler.h"


void CollisionHandler::HandleCollision(PhysicsObject& object1, PhysicsObject& object2) {
    Shape* shape1 = object1.GetShape();
    Shape* shape2 = object2.GetShape();

    if (Sphere* sphere1 = dynamic_cast<Sphere*>(shape1)) {
        if (Sphere* sphere2 = dynamic_cast<Sphere*>(shape2)) {
            HandleSphereSphereCollision(object1, object2, sphere1, sphere2);
        } 
        
        else if (Box* box2 = dynamic_cast<Box*>(shape2)) {
            HandleSphereBoxCollision(object1, object2, sphere1, box2);
        } 
        
        else if (Plane* plane2 = dynamic_cast<Plane*>(shape2)) {
            HandleSpherePlaneCollision(object1, plane2, sphere1);
        }
    } 
    
    else if (Box* box1 = dynamic_cast<Box*>(shape1)) {
        if (Sphere* sphere2 = dynamic_cast<Sphere*>(shape2)) {
            HandleSphereBoxCollision(object2, object1, sphere2, box1);
        } 
        
        /*else if (Box* box2 = dynamic_cast<Box*>(shape2)){
            HandleBoxBoxCollision(object1, object2, box1, box2);
        }*/

        else if (Plane* plane2 = dynamic_cast<Plane*>(shape2)) {
            HandleBoxPlaneCollision(object1, plane2, box1);
        }
    }

    else if (Plane* plane1 = dynamic_cast<Plane*>(shape1)) {
        if (Sphere* sphere2 = dynamic_cast<Sphere*>(shape2)) {
            HandleSpherePlaneCollision(object2, plane1, sphere2);
        } 
        
        else if (Box* box2 = dynamic_cast<Box*>(shape2)) {
            HandleBoxPlaneCollision(object2, plane1, box2);
        }
    }
}

void CollisionHandler::HandleSphereSphereCollision(PhysicsObject& object1, PhysicsObject& object2, Sphere* sphere1, Sphere* sphere2) {
    Vec3 collisionNormal = sphere1->center - sphere2->center;
    float distance = Math::Magnitude(collisionNormal);
    collisionNormal = Math::Normalize(collisionNormal);

    float penetration = sphere1->radius + sphere2->radius - distance;

    float totalInvMass = object1.rigidBody.GetInverseMass() + object2.rigidBody.GetInverseMass();
    float movePerMass = penetration / totalInvMass;

    // Separating the two spheres
    object1.rigidBody.SetPosition(object1.rigidBody.GetPosition() + collisionNormal * movePerMass * object1.rigidBody.GetInverseMass());
    object2.rigidBody.SetPosition(object2.rigidBody.GetPosition() - collisionNormal * movePerMass * object2.rigidBody.GetInverseMass());

    // Calculate the new velocity of the spheres after the collision using impulses
    Vec3 relativeVelocity = object1.rigidBody.GetVelocity() - object2.rigidBody.GetVelocity();
    float separatingVelocity = Math::Dot(relativeVelocity, collisionNormal);

    float e = std::min(object1.rigidBody.GetRestitution(), object2.rigidBody.GetRestitution());

    float deltaSepVelocity = -(1 + e) * separatingVelocity;

    float impulse = deltaSepVelocity / totalInvMass;

    Vec3 impulsePerMass = collisionNormal * impulse;

    object1.rigidBody.SetVelocity(object1.rigidBody.GetVelocity() + impulsePerMass * object1.rigidBody.GetInverseMass());
    object2.rigidBody.SetVelocity(object2.rigidBody.GetVelocity() - impulsePerMass * object2.rigidBody.GetInverseMass());
}

void CollisionHandler::HandleSphereBoxCollision(PhysicsObject& sphereObject, PhysicsObject& boxObject, Sphere* sphere, Box* box) {
    Vec3 closestPoint = Math::Clamp(sphereObject.rigidBody.GetPosition(), box->minCorner, box->maxCorner);
    Vec3 collisionNormal = sphereObject.rigidBody.GetPosition() - closestPoint;
    float distance = Math::Magnitude(collisionNormal);
    collisionNormal = Math::Normalize(collisionNormal);

    float penetration = sphere->radius - distance;

    float totalInvMass = sphereObject.rigidBody.GetInverseMass() + boxObject.rigidBody.GetInverseMass();
    float movePerMass = penetration / totalInvMass;

    // Separating the sphere and the box
    sphereObject.rigidBody.SetPosition(sphereObject.rigidBody.GetPosition() + collisionNormal * penetration);

    // Calculate the new velocity of the sphere and the box after the collision using impulses
    Vec3 contactPoint = closestPoint;
    Vec3 contactVectorBox = contactPoint - box->center;

    Vec3 relativeVelocity = sphereObject.rigidBody.GetVelocity()
                               - boxObject.rigidBody.GetVelocity() - Math::Cross(boxObject.rigidBody.GetAngularVelocity(), contactVectorBox);

    float velocityAlongNormal = Math::Dot(relativeVelocity, collisionNormal);

    float e = std::min(sphereObject.rigidBody.GetRestitution(), boxObject.rigidBody.GetRestitution());

    float deltaSepVelocity = -(1 + e) * velocityAlongNormal;

    float impulse = deltaSepVelocity / (totalInvMass + Math::Dot(collisionNormal, Math::Cross(boxObject.rigidBody.GetInverseInertiaTensor() * Math::Cross(contactVectorBox, collisionNormal), contactVectorBox)));

    Vec3 impulsePerMass = collisionNormal * impulse;

    sphereObject.rigidBody.SetVelocity(sphereObject.rigidBody.GetVelocity() + impulsePerMass * sphereObject.rigidBody.GetInverseMass());

    boxObject.rigidBody.SetVelocity(boxObject.rigidBody.GetVelocity() - impulsePerMass * boxObject.rigidBody.GetInverseMass());
    boxObject.rigidBody.SetAngularVelocity(boxObject.rigidBody.GetAngularVelocity() + boxObject.rigidBody.GetInverseInertiaTensor() * Math::Cross(contactVectorBox ,impulsePerMass));
}

void CollisionHandler::HandleSpherePlaneCollision(PhysicsObject& sphereObject, Plane* plane, Sphere* sphere) {
    Vec3 collisionNormal = plane->normal;
    float distance = Math::Dot(sphereObject.rigidBody.GetPosition() - plane->center, collisionNormal);
    float penetration = sphere->radius - distance;

    float totalInvMass = sphereObject.rigidBody.GetInverseMass();
    float movePerMass = penetration / totalInvMass;

    // Separating the sphere and the plane
    sphereObject.rigidBody.SetPosition(sphereObject.rigidBody.GetPosition() + collisionNormal * movePerMass * sphereObject.rigidBody.GetInverseMass());

    // Calculate the new velocity of the sphere after the collision using impulses
    float separatingVelocity = Math::Dot(sphereObject.rigidBody.GetVelocity(), collisionNormal);

    float e = sphereObject.rigidBody.GetRestitution();

    float deltaSepVelocity = -(1 + e) * separatingVelocity;

    float impulse = deltaSepVelocity / totalInvMass;

    Vec3 impulsePerMass = collisionNormal * impulse;

    sphereObject.rigidBody.SetVelocity(sphereObject.rigidBody.GetVelocity() + impulsePerMass * sphereObject.rigidBody.GetInverseMass());
}

void CollisionHandler::HandleBoxPlaneCollision(PhysicsObject& boxObject, Plane* plane, Box* box) {
    Vec3 collisionNormal = -plane->normal;
    Vec3 vertices[8] = {
        Vec3(box->minCorner.x, box->minCorner.y, box->minCorner.z),
        Vec3(box->maxCorner.x, box->minCorner.y, box->minCorner.z),
        Vec3(box->maxCorner.x, box->maxCorner.y, box->minCorner.z),
        Vec3(box->minCorner.x, box->maxCorner.y, box->minCorner.z),
        Vec3(box->minCorner.x, box->minCorner.y, box->maxCorner.z),
        Vec3(box->maxCorner.x, box->minCorner.y, box->maxCorner.z),
        Vec3(box->maxCorner.x, box->maxCorner.y, box->maxCorner.z),
        Vec3(box->minCorner.x, box->maxCorner.y, box->maxCorner.z)
    };

    float maxPenetration = -MAX_FLT;
    Vec3 contactPoint;
    for (int i = 0; i < 8; ++i) {
        float distance = Math::Dot(vertices[i] - plane->center, collisionNormal);
        if (distance > maxPenetration) {
            maxPenetration = distance;
            contactPoint = vertices[i];
        }
    }

    if (maxPenetration <= 0) return; // No collision

    float penetration = -maxPenetration;

    float totalInvMass = boxObject.rigidBody.GetInverseMass();
    float movePerMass = penetration / totalInvMass;

    // Separating the box and the plane
    boxObject.rigidBody.SetPosition(boxObject.rigidBody.GetPosition() + collisionNormal * movePerMass * boxObject.rigidBody.GetInverseMass());

    // Calculate the new velocity of the box after the collision using impulses
    float separatingVelocity = Math::Dot(boxObject.rigidBody.GetVelocity(), collisionNormal);

    float e = boxObject.rigidBody.GetRestitution();

    float deltaSepVelocity = -(1 + e) * separatingVelocity;

    float impulse = deltaSepVelocity / totalInvMass;

    Vec3 impulsePerMass = collisionNormal * impulse;

    boxObject.rigidBody.SetVelocity(boxObject.rigidBody.GetVelocity() + impulsePerMass * boxObject.rigidBody.GetInverseMass());
}

bool CollisionHandler::CheckCollision(PhysicsObject& object1, PhysicsObject& object2){
    Shape* shape1 = object1.GetShape();
    Shape* shape2 = object2.GetShape();

    if (Sphere* sphere1 = dynamic_cast<Sphere*>(shape1)){
        if (Sphere* sphere2 = dynamic_cast<Sphere*>(shape2)){
            // Sphere-Sphere collision
            Vec3 collisionNormal = sphere1->center - sphere2->center;
            float distance = Math::Magnitude(collisionNormal);
            collisionNormal = Math::Normalize(collisionNormal);

            return distance < sphere1->radius + sphere2->radius;
        }

        else if (Box* box2 = dynamic_cast<Box*>(shape2)){
            // Sphere-Box collision
            Vec3 closestPoint = Math::Clamp(object1.rigidBody.GetPosition(), box2->minCorner, box2->maxCorner);
            Vec3 collisionNormal = object1.rigidBody.GetPosition() - closestPoint;
            float distance = Math::Magnitude(collisionNormal);
            collisionNormal = Math::Normalize(collisionNormal);

            return distance < sphere1->radius;
        }

        else if (Plane* plane2 = dynamic_cast<Plane*>(shape2)){
            // Sphere-Plane collision
            Vec3 collisionNormal = plane2->normal;
            float distance = Math::Dot(object1.rigidBody.GetPosition() - plane2->center, collisionNormal);

            return distance < sphere1->radius;
        }
    }

    else if (Box* box1 = dynamic_cast<Box*>(shape1)){
        if (Sphere* sphere2 = dynamic_cast<Sphere*>(shape2)){
            // Sphere-Box collision
            Vec3 closestPoint = Math::Clamp(object2.rigidBody.GetPosition(), box1->minCorner, box1->maxCorner);
            Vec3 collisionNormal = object2.rigidBody.GetPosition() - closestPoint;
            float distance = Math::Magnitude(collisionNormal);
            collisionNormal = Math::Normalize(collisionNormal);

            return distance < sphere2->radius;
        }

        else if (Box* box2 = dynamic_cast<Box*>(shape2)){
            // Box-Box collision
            return (box1->minCorner.x <= box2->maxCorner.x && box1->maxCorner.x >= box2->minCorner.x) &&
                   (box1->minCorner.y <= box2->maxCorner.y && box1->maxCorner.y >= box2->minCorner.y) &&
                   (box1->minCorner.z <= box2->maxCorner.z && box1->maxCorner.z >= box2->minCorner.z);
        }

        else if (Plane* plane2 = dynamic_cast<Plane*>(shape2)){
            // Box-Plane collision
            Vec3 p = box1->center;
            Vec3 e = box1->maxCorner - box1->minCorner;
            Vec3 n = plane2->normal;
            Vec3 s = plane2->center;
            float r = Math::Dot(e, Math::Abs(n));
            float distance = Math::Dot(n, p - s);

            return std::abs(distance) <= r;
        }
    }

    else if (Plane* plane1 = dynamic_cast<Plane*>(shape1)){
        if (Sphere* sphere2 = dynamic_cast<Sphere*>(shape2)){
            // Sphere-Plane collision
            Vec3 collisionNormal = plane1->normal;
            float distance = Math::Dot(object2.rigidBody.GetPosition() - plane1->center, collisionNormal);

            return distance < sphere2->radius;
        }

        else if (Box* box2 = dynamic_cast<Box*>(shape2)){
            // Box-Plane collision
            Vec3 p = box2->center;
            Vec3 e = box2->maxCorner - box2->minCorner;
            Vec3 n = plane1->normal;
            Vec3 s = plane1->center;
            float r = Math::Dot(e, Math::Abs(n));
            float distance = Math::Dot(n, p - s);

            return std::abs(distance) <= r;
        }
    }

    return false;
}