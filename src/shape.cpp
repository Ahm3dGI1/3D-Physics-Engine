#include "physicsObjects/shape.h"

Shape::~Shape(){}

Sphere::Sphere(float r, glm::vec3 c) : radius(r), center(c), X(.525731112119133606f), Z(.850650808352039932f), N(0.f){

    vertices = {
        -X,N,Z,  X,N, Z, -X,N,-Z,  X, N,-Z,
         N,Z,X,  N,Z,-X,  N,-Z,X,  N,-Z,-X,
         Z,X,N, -Z,X, N,  Z,-X,N, -Z,-X, N
    };

    indices = {
        1,4,0,   4,9,0,   4,5,9,   8,5,4,   1,8,4,
        1,10,8,  10,3,8,  8,3,5,   3,2,5,   3,7,2,
        3,10,7,  10,6,7,  6,11,7,  6,0,11,  6,1,0,
        10,1,6,  11,0,9,  2,11,9,  5,2,9,   11,2,7
    };
}



bool Sphere::Intersects(Shape* other) const{
    if (auto sphere = dynamic_cast<Sphere*>(other)){
        float distance = glm::distance(center, sphere->center);
        return distance < radius + sphere->radius;
    }
    else if (auto box = dynamic_cast<Box*>(other)){
        // Implement sphere-box intersection
            // Get box closest point to sphere center by clamping
        float x = glm::max(box->minCorner.x, glm::min(center.x, box->maxCorner.x));
        float y = glm::max(box->minCorner.y, glm::min(center.y, box->maxCorner.y));
        float z = glm::max(box->minCorner.z, glm::min(center.z, box->maxCorner.z));

            // This is the same as isPointInsideSphere
        float distance = glm::distance(glm::vec3(x, y, z), center);
        return distance < radius;
    }
    else if (auto plane = dynamic_cast<Plane*>(other)){
        // Implement sphere-plane intersection

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

    numVertices = 36;
    shapeSize = vertices.size() * sizeof(float);
}

bool Box::Intersects(Shape* other) const{
    if (auto sphere = dynamic_cast<Sphere*>(other)){
        // Implement box-sphere intersection
        float x = glm::max(minCorner.x, glm::min(sphere->center.x, maxCorner.x));
        float y = glm::max(minCorner.y, glm::min(sphere->center.y, maxCorner.y));
        float z = glm::max(minCorner.z, glm::min(sphere->center.z, maxCorner.z));

        float distance = glm::distance(glm::vec3(x, y, z), sphere->center);
        
        return distance < sphere->radius;
    }
    else if (auto box = dynamic_cast<Box*>(other)){
        // Implement box-box intersection
        return (minCorner.x <= box->maxCorner.x && maxCorner.x >= box->minCorner.x) &&
               (minCorner.y <= box->maxCorner.y && maxCorner.y >= box->minCorner.y) &&
               (minCorner.z <= box->maxCorner.z && maxCorner.z >= box->minCorner.z);
    }
    return false;
}

Plane::Plane(glm::vec3 c, glm::vec3 n, float d) : center(c), normal(n), distance(d){
    vertices = {
            // Plane vertices
    // Positions              // Colors
     2.0f, 0.0f,  2.0f,    1.0f, 0.0f, 0.0f,
     2.0f, 0.0f, -2.0f,    0.0f, 1.0f, 0.0f,
    -2.0f, 0.0f, -2.0f,    0.0f, 0.0f, 1.0f,
    -2.0f, 0.0f,  2.0f,    0.0f, 0.0f, 1.0f,
     2.0f, 0.0f,  2.0f,    1.0f, 0.0f, 0.0f,
    -2.0f, 0.0f, -2.0f,    0.0f, 1.0f, 0.0f
    };

    numVertices = 6;
    shapeSize = vertices.size() * sizeof(float);
}

bool Plane::Intersects(Shape* other) const{
    if (auto sphere = dynamic_cast<Sphere*>(other)){
        // Implement plane-sphere intersection
        float distance = glm::dot(sphere->center, normal);
        return distance < sphere->radius + distance;
    }
    else if (auto box = dynamic_cast<Box*>(other)){
        // Implement plane-box intersection
        return false;
    }
    return false;
}