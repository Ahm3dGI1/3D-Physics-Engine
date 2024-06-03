#include "math/vec3.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::Vec3(float a) : x(a), y(a), z(a) {}

// Static Functions
float Vec3::dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Vec3 Vec3::normalize(const Vec3& a) {
    float mag = magnitude(a);
    return Vec3(a.x / mag, a.y / mag, a.z / mag);
}

float Vec3::magnitude(const Vec3& a) {
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// Operator overloads
Vec3 Vec3::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3 Vec3::operator+=(float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

Vec3 Vec3::operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3 Vec3::operator-=(float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}

Vec3 Vec3::operator*=(const Vec3& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vec3 Vec3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3 Vec3::operator/=(const Vec3& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vec3 Vec3::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool Vec3::operator==(const Vec3& other) const {
    return x == other.x && y == other.y && z == other.z;
}

bool Vec3::operator!=(const Vec3& other) const {
    return x != other.x || y != other.y || z != other.z;
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

float& Vec3::operator[](int index) {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    throw std::out_of_range("Index out of range");
}

const float& Vec3::operator[](int index) const {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    throw std::out_of_range("Index out of range");
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}