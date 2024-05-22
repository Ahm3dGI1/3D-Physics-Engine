#include "physicsObjects/shape.h"
#include <iostream>

Shape::~Shape(){}

Sphere::Sphere(float r, float d) : radius(r), X(.525731112119133606f), Z(.850650808352039932f), N(0.f){
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

    // Scale initial vertices to the correct radius
    for (size_t i = 0; i < vertices.size(); i += 6) {
        glm::vec3 v(vertices[i], vertices[i + 1], vertices[i + 2]);
        v = glm::normalize(v) * r;
        vertices[i] = v.x;
        vertices[i + 1] = v.y;
        vertices[i + 2] = v.z;
    }

    Subdivide(vertices, indices, d);

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
        glm::vec3 midpoint = glm::normalize(p1 + p2) * radius;

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

Box::Box() : minCorner(glm::vec3(-1.0f)), maxCorner(glm::vec3(1.0f)){
    originalVertices = {
        // Positions           // Colors
        -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  // 0
         1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  // 1
         1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  // 2
        -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  // 3
        -1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,  // 4
         1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  // 5
         1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  // 6
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f   // 7
    };

    vertices = originalVertices;

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

    numVertices = indices.size();
    shapeSize = vertices.size() * sizeof(float);
}

void Box::UpdateShape(const glm::vec3& position, const glm::mat3& orientation) {
    // Update the shape's position
    center = position;


    // Update the shape's verticies
    for (size_t i = 0; i < originalVertices.size(); i += 6) {
        glm::vec3 originalPos(originalVertices[i], originalVertices[i + 1], originalVertices[i + 2]);
        glm::vec3 transformedPos = orientation * originalPos;

        vertices[i] = transformedPos.x;
        vertices[i + 1] = transformedPos.y;
        vertices[i + 2] = transformedPos.z;

        // Colors remain unchanged
        vertices[i + 3] = originalVertices[i + 3];
        vertices[i + 4] = originalVertices[i + 4];
        vertices[i + 5] = originalVertices[i + 5];
    }
}

Plane::Plane() : normal(glm::vec3(0.0f, 1.0f, 0.0f)){
    vertices = {
            // Plane vertices
    // Positions              // Colors
     1.0f, 0.0f,  1.0f,    1.0f, 0.0f, 0.0f, // 0
     1.0f, 0.0f, -1.0f,    0.0f, 1.0f, 0.0f, // 1
    -1.0f, 0.0f, -1.0f,    0.0f, 0.0f, 1.0f, // 2
    -1.0f, 0.0f,  1.0f,    0.0f, 0.0f, 1.0f, // 3
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