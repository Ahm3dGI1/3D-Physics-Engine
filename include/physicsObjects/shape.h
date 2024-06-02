#ifndef SHAPE_H
#define SHAPE_H
#define M_PI 3.14159265358979323846


#include <vector>
#include <map>
#include <math/math.h>
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
    Vec3 center;

    const float X;
    const float Z;
    const float N;

    Sphere(float r, float d);

    void Subdivide(std::vector<float>& vertices, std::vector<unsigned int>& indices, int depth = 3);
};

class Box : public Shape{
public:
    Vec3 minCorner, maxCorner;  // For AABB
    Vec3 center;                // For OBB
    Mat3 orientation;           // For OBB


    Box();
    void UpdateShape(const Vec3& position, const Mat3& orientation);
};

class Plane : public Shape{
public:
    Vec3 center;
    Vec3 normal;
    
    Plane();
};

#endif //SHAPE_H