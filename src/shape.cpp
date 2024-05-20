#include "physicsObjects/shape.h"

Shape::~Shape(){}

Sphere::Sphere(float r, glm::vec3 c) : radius(r), center(c), X(.525731112119133606f), Z(.850650808352039932f), N(0.f){
    vertices = {
        -X,  N,  Z,         1.0f, 0.0f, 0.0f,
         X,  N,  Z,         0.0f, 1.0f, 0.0f,
        -X,  N, -Z,         0.0f, 0.0f, 1.0f,
         X,  N, -Z,         1.0f, 0.0f, 0.0f,
         N,  Z,  X,         0.0f, 1.0f, 0.0f,
         N,  Z, -X,         0.0f, 0.0f, 1.0f,
         N, -Z,  X,         1.0f, 0.0f, 0.0f,
         N, -Z, -X,         0.0f, 1.0f, 0.0f,
         Z,  X,  N,         0.0f, 0.0f, 1.0f,
        -Z,  X,  N,         1.0f, 0.0f, 0.0f,
         Z, -X,  N,         0.0f, 1.0f, 0.0f,
        -Z, -X,  N,         0.0f, 0.0f, 1.0f
    };

    indices = {
        //1            2           3           4           5
        0, 1, 4,    0, 4, 9,    9, 4, 5,    4, 8, 5,    4, 1, 8,
        //6            7           8           9           10
        8, 1, 10,   8, 10, 3,   5, 8, 3,    5, 3, 2,    2, 3, 7,
        //11           12          13          14          15
        7, 3, 10,   7, 10, 6,   7, 6, 11,   11, 6, 0,   0, 6, 1,
        //16           17          18          19          20
        6, 10, 1,   9, 11, 0,   9, 2, 11,   9, 5, 2,    7, 11, 2
    };

    Subdivide(vertices, indices), 3;

    numVertices = indices.size();
    shapeSize = vertices.size() * sizeof(float);
}

void Sphere::Subdivide(std::vector<float>& vertices, std::vector<unsigned int>& indices, int depth) {
    std::map<std::pair<int, int>, int> midpointIndexCache;
    std::vector<unsigned int> newIndices;

    auto getMidpointIndex = [&](int i1, int i2) {
        auto edge = std::make_pair(std::min(i1, i2), std::max(i1, i2));
        if (midpointIndexCache.find(edge) != midpointIndexCache.end()) {
            return midpointIndexCache[edge];
        }

        // Calculate midpoint
        int idx1 = i1 * 6; // Start index of vertex coordinates
        int idx2 = i2 * 6;
        glm::vec3 p1(vertices[idx1], vertices[idx1 + 1], vertices[idx1 + 2]);
        glm::vec3 p2(vertices[idx2], vertices[idx2 + 1], vertices[idx2 + 2]);
        glm::vec3 midpoint = glm::normalize(p1 + p2);

        // Add new vertex in the array
        int newIdx = vertices.size() / 6;
        vertices.push_back(midpoint.x);
        vertices.push_back(midpoint.y);
        vertices.push_back(midpoint.z);
        vertices.push_back((vertices[idx1 + 3] + vertices[idx2 + 3]) * 0.5); // Average color
        vertices.push_back((vertices[idx1 + 4] + vertices[idx2 + 4]) * 0.5);
        vertices.push_back((vertices[idx1 + 5] + vertices[idx2 + 5]) * 0.5);

        // Cache it
        midpointIndexCache[edge] = newIdx;
        return newIdx;
    };

    for (size_t i = 0; i < indices.size(); i += 3) {
        int v1 = indices[i];
        int v2 = indices[i + 1];
        int v3 = indices[i + 2];

        // Get midpoints
        int m1 = getMidpointIndex(v1, v2);
        int m2 = getMidpointIndex(v2, v3);
        int m3 = getMidpointIndex(v3, v1);

        // Create new triangles
        newIndices.push_back(v1); newIndices.push_back(m1); newIndices.push_back(m3);
        newIndices.push_back(v2); newIndices.push_back(m2); newIndices.push_back(m1);
        newIndices.push_back(v3); newIndices.push_back(m3); newIndices.push_back(m2);
        newIndices.push_back(m1); newIndices.push_back(m2); newIndices.push_back(m3);
    }

    indices = std::move(newIndices);

    if (--depth > 0) {
        Subdivide(vertices, indices, depth);
    }
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
    // Positions           // Colors
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 0
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // 1
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // 2
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 3
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // 4
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  // 5
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 6
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f   // 7
    };

    indices = {
    // Front face
    0, 1, 2,  0, 2, 3,
    // Back face
    4, 5, 6,  4, 6, 7,
    // Left face
    0, 3, 7,  0, 7, 4,
    // Right face
    1, 2, 6,  1, 6, 5,
    // Top face
    3, 2, 6,  3, 6, 7,
    // Bottom face
    0, 1, 5,  0, 5, 4
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
     2.0f, 0.0f,  2.0f,    1.0f, 0.0f, 0.0f, // 0
     2.0f, 0.0f, -2.0f,    0.0f, 1.0f, 0.0f, // 1
    -2.0f, 0.0f, -2.0f,    0.0f, 0.0f, 1.0f, // 2
    -2.0f, 0.0f,  2.0f,    0.0f, 0.0f, 1.0f, // 3
    };

    indices = {
        // First Triangle
        0, 1, 2,
        // Second Triangle
        0, 2, 3
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