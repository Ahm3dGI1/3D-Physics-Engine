#include "physicsObjects/shape.h"

Shape::~Shape(){}

Sphere::Sphere(float r, glm::vec3 c) : radius(r), center(c){}

bool Sphere::Intersects(Shape* other) const{
    if (auto sphere = dynamic_cast<Sphere*>(other)){
        float distance = glm::distance(center, sphere->center);
        return distance < radius + sphere->radius;
    }
    else if (auto box = dynamic_cast<Box*>(other)){
        // Implement sphere-box intersection
        return false;
    }
    return false;
}

Box::Box(glm::vec3 min, glm::vec3 max, glm::vec3 c, glm::quat o) : minCorner(min), maxCorner(max), center(c), orientation(o){}

bool Box::Intersects(Shape* other) const{
    if (auto sphere = dynamic_cast<Sphere*>(other)){
        // Implement box-sphere intersection
        return false;
    }
    else if (auto box = dynamic_cast<Box*>(other)){
        // Implement box-box intersection
        return false;
    }
    return false;
}