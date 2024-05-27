#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3
{
public:
    float x, y, z;

    Vec3(float a = 0.0f);
    Vec3(float x, float y, float z);

    // Static functions
    static float dot(const Vec3& a, const Vec3& b);
    static Vec3 cross(const Vec3& a, const Vec3& b);
    static Vec3 normalize(const Vec3& a);
    static float magnitude(const Vec3& a);

    // Operator overloads
    Vec3 operator+=(const Vec3& other);
    Vec3 operator+=(float scalar);

    Vec3 operator-=(const Vec3& other);
    Vec3 operator-=(float scalar);

    Vec3 operator*=(const Vec3& other);
    Vec3 operator*=(float scalar);

    Vec3 operator/=(const Vec3& other);
    Vec3 operator/=(float scalar);

    bool operator==(const Vec3& other) const;
    bool operator!=(const Vec3& other) const;
    
    Vec3 operator-() const;
    
    float& operator[](int index);
    const float& operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

};

#endif //VEC3_H