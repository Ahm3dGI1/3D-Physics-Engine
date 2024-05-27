#ifndef PHYSICS_OBJECTS_H
#define PHYSICS_OBJECTS_H

#include <memory>

#include "shape.h"
#include "rigidbody.h"

class PhysicsObject{
public:
    std::unique_ptr<Shape> shape;
    Rigidbody rigidBody;

    PhysicsObject(std::unique_ptr<Shape> s, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), float m = 1.0f, float damp = 0.9f);

    Shape* GetShape() const;
    
    void Update(float deltaTime);
};




#endif //PHYSICS_OBJECTS_H