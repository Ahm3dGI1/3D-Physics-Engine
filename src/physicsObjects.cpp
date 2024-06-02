#include "physicsObjects/physicsObjects.h"

PhysicsObject::PhysicsObject(std::unique_ptr<Shape> s, Vec3 pos, float m, float damp)
        : shape(std::move(s)), rigidBody(pos, m, damp){}

Shape* PhysicsObject::GetShape() const{
    return shape.get();
}
    
void PhysicsObject::Update(float deltaTime){
    rigidBody.Update(deltaTime);

    // Update the shape's position
    if (auto sphere = dynamic_cast<Sphere*>(shape.get())){
        sphere->center = rigidBody.GetPosition();
    }
    else if (auto box = dynamic_cast<Box*>(shape.get())){
        
        box->UpdateShape(rigidBody.GetPosition(), rigidBody.GetOrientation());

        box->maxCorner = box->center + Vec3(1.0f);
        box->minCorner = box->center - Vec3(1.0f);

    }


    
}