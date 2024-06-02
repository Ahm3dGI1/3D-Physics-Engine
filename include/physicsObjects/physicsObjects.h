#ifndef PHYSICS_OBJECTS_H
#define PHYSICS_OBJECTS_H

#include <memory>

#include "physicsObjects/shape.h"
#include "physicsObjects/rigidbody.h"

class PhysicsObject{
public:
    std::unique_ptr<Shape> shape;
    Rigidbody rigidBody;

    PhysicsObject(std::unique_ptr<Shape> s, Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), float m = 1.0f, float damp = 0.9f);

    Shape* GetShape() const;
    
    void Update(float deltaTime);
};




#endif //PHYSICS_OBJECTS_H