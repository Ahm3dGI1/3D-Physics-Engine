#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Shape{
public:
    virtual bool Intersects(Shape* other) const = 0;

    virtual ~Shape();
};

class Sphere : public Shape{
public:
    float radius;
    glm::vec3 center;

    Sphere(float r, glm::vec3 c);

    bool Intersects(Shape* other) const override;
};

class Box : public Shape{
public:
    glm::vec3 minCorner, maxCorner;  // For AABB
    glm::vec3 center;                // For OBB
    glm::quat orientation;           // For OBB

    Box(glm::vec3 min, glm::vec3 max, glm::vec3 c = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat o = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

    bool Intersects(Shape* other) const override;
};

#endif //SHAPE_H