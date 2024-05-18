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

Box::Box(glm::vec3 min, glm::vec3 max, glm::vec3 c, glm::quat o) : minCorner(min), maxCorner(max), center(c), orientation(o){
    vertices = {
    // Box vertices
        // Positions           // Colors
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
    };
}

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

Plane::Plane(glm::vec3 c, glm::vec3 n, float d) : center(c), normal(n), distance(d){
    vertices = {
            // Plane vertices
    // Positions              // Colors
     1.5f,  1.5f, 0.0f,    1.0f, 0.0f, 0.0f,
     1.5f, -1.5f, 0.0f,    0.0f, 1.0f, 0.0f,
    -1.5f, -1.5f, 0.0f,    0.0f, 0.0f, 1.0f,
    -1.5f,  1.5f, 0.0f,    0.0f, 0.0f, 1.0f,
     1.5f,  1.5f, 0.0f,    1.0f, 0.0f, 0.0f,
    -1.5f, -1.5f, 0.0f,    0.0f, 1.0f, 0.0f
    };
}

bool Plane::Intersects(Shape* other) const{
    if (auto sphere = dynamic_cast<Sphere*>(other)){
        // Implement plane-sphere intersection
        return false;
    }
    else if (auto box = dynamic_cast<Box*>(other)){
        // Implement plane-box intersection
        return false;
    }
    return false;
}