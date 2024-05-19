#include "physicsObjects/physicsObjects.h"

PhysicsObject::PhysicsObject(std::unique_ptr<Shape> s, glm::vec3 pos, float m, float damp)
        : shape(std::move(s)), rigidBody(pos, m, damp){}
    
void PhysicsObject::Update(float deltaTime){
    rigidBody.Update(deltaTime);

    // Update the shape's position
    if (auto sphere = dynamic_cast<Sphere*>(shape.get())){
        sphere->center = rigidBody.GetPosition();
    }
    else if (auto box = dynamic_cast<Box*>(shape.get())){
        box->center = rigidBody.GetPosition();
        box->minCorner = box->center - glm::vec3(0.5f);
        box->maxCorner = box->center + glm::vec3(0.5f);
    }
}