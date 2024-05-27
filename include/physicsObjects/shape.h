#ifndef SHAPE_H
#define SHAPE_H
#define M_PI 3.14159265358979323846


#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Shape{
public:
    std::vector<float> vertices;
    std::vector<float> originalVertices;
    std::vector<unsigned int> indices;
    int numVertices;
    float shapeSize;

    virtual ~Shape();
};

class Sphere : public Shape{
public:
    float radius;
    glm::vec3 center;

    const float X;
    const float Z;
    const float N;

    Sphere(float r, float d);

    void Subdivide(std::vector<float>& vertices, std::vector<unsigned int>& indices, int depth = 3);
};

class Box : public Shape{
public:
    glm::vec3 minCorner, maxCorner;  // For AABB
    glm::vec3 center;                // For OBB
    glm::mat3 orientation;           // For OBB


    Box();
    void UpdateShape(const glm::vec3& position, const glm::mat3& orientation);
};

class Plane : public Shape{
public:
    glm::vec3 center;
    glm::vec3 normal;
    
    Plane();
};

#endif //SHAPE_H