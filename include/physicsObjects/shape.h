#ifndef SHAPE_H
#define SHAPE_H
#define M_PI 3.14159265358979323846


#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Shape{
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int numVertices;
    float shapeSize;

    virtual bool Intersects(Shape* other) const = 0;
    virtual ~Shape();
};

class Sphere : public Shape{
public:
    float radius;
    glm::vec3 center;

    const float X;
    const float Z;
    const float N;

    Sphere(float r, glm::vec3 c);

    bool Intersects(Shape* other) const override;

    void Subdivide(std::vector<float>& vertices, std::vector<unsigned int>& indices, int depth = 3);
};

class Box : public Shape{
public:
    glm::vec3 minCorner, maxCorner;  // For AABB
    glm::vec3 center;                // For OBB
    glm::quat orientation;           // For OBB


    Box(glm::vec3 min, glm::vec3 max, glm::vec3 c = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat o = glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

    bool Intersects(Shape* other) const override;
};

class Plane : public Shape{
public:
    glm::vec3 center;
    glm::vec3 normal;
    float distance;

    
    Plane(glm::vec3 c, glm::vec3 n, float d);

    bool Intersects(Shape* other) const override;
};

#endif //SHAPE_H