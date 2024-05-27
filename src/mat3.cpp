#include "math/mat3.h"

Mat3::Mat3(float m00, float m01, float m02,
           float m10, float m11, float m12,
           float m20, float m21, float m22) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
}

Mat3::Mat3(float a) {
    m[0][0] = a;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = a;
    m[1][2] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = a;
}

Mat3 Mat3::operator+(const Mat3& other) const {
    return Mat3(m[0][0] + other.m[0][0], m[0][1] + other.m[0][1], m[0][2] + other.m[0][2],
                m[1][0] + other.m[1][0], m[1][1] + other.m[1][1], m[1][2] + other.m[1][2],
                m[2][0] + other.m[2][0], m[2][1] + other.m[2][1], m[2][2] + other.m[2][2]);
}

Mat3 Mat3::operator+=(const Mat3& other) {
    m[0][0] += other.m[0][0];
    m[0][1] += other.m[0][1];
    m[0][2] += other.m[0][2];
    m[1][0] += other.m[1][0];
    m[1][1] += other.m[1][1];
    m[1][2] += other.m[1][2];
    m[2][0] += other.m[2][0];
    m[2][1] += other.m[2][1];
    m[2][2] += other.m[2][2];
    return *this;
}

Mat3 Mat3::operator+(float scalar) const {
    return Mat3(m[0][0] + scalar, m[0][1] + scalar, m[0][2] + scalar,
                m[1][0] + scalar, m[1][1] + scalar, m[1][2] + scalar,
                m[2][0] + scalar, m[2][1] + scalar, m[2][2] + scalar);
}

Mat3 Mat3::operator+=(float scalar) {
    m[0][0] += scalar;
    m[0][1] += scalar;
    m[0][2] += scalar;
    m[1][0] += scalar;
    m[1][1] += scalar;
    m[1][2] += scalar;
    m[2][0] += scalar;
    m[2][1] += scalar;
    m[2][2] += scalar;
    return *this;
}

Mat3 Mat3::operator-(const Mat3& other) const {
    return Mat3(m[0][0] - other.m[0][0], m[0][1] - other.m[0][1], m[0][2] - other.m[0][2],
                m[1][0] - other.m[1][0], m[1][1] - other.m[1][1], m[1][2] - other.m[1][2],
                m[2][0] - other.m[2][0], m[2][1] - other.m[2][1], m[2][2] - other.m[2][2]);
}

Mat3 Mat3::operator-=(const Mat3& other) {
    m[0][0] -= other.m[0][0];
    m[0][1] -= other.m[0][1];
    m[0][2] -= other.m[0][2];
    m[1][0] -= other.m[1][0];
    m[1][1] -= other.m[1][1];
    m[1][2] -= other.m[1][2];
    m[2][0] -= other.m[2][0];
    m[2][1] -= other.m[2][1];
    m[2][2] -= other.m[2][2];
    return *this;
}

Mat3 Mat3::operator-(float scalar) const {
    return Mat3(m[0][0] - scalar, m[0][1] - scalar, m[0][2] - scalar,
                m[1][0] - scalar, m[1][1] - scalar, m[1][2] - scalar,
                m[2][0] - scalar, m[2][1] - scalar, m[2][2] - scalar);
}

Mat3 Mat3::operator-=(float scalar) {
    m[0][0] -= scalar;
    m[0][1] -= scalar;
    m[0][2] -= scalar;
    m[1][0] -= scalar;
    m[1][1] -= scalar;
    m[1][2] -= scalar;
    m[2][0] -= scalar;
    m[2][1] -= scalar;
    m[2][2] -= scalar;
    return *this;
}

Mat3 Mat3::operator*(const Mat3& other) const {
    return Mat3(m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0],
                m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1],
                m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2],
                m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0],
                m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1],
                m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2],
                m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0],
                m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1],
                m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2]);
}

Mat3 Mat3::operator*=(const Mat3& other) {
    float m00 = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0];
    float m01 = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1];
    float m02 = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2];
    float m10 = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0];
    float m11 = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1];
    float m12 = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2];
    float m20 = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0];
    float m21 = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1];
    float m22 = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2];
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    return *this;
}

Mat3 Mat3::operator*(float scalar) const {
    return Mat3(m[0][0] * scalar, m[0][1] * scalar, m[0][2] * scalar,
                m[1][0] * scalar, m[1][1] * scalar, m[1][2] * scalar,
                m[2][0] * scalar, m[2][1] * scalar, m[2][2] * scalar);
}

Mat3 Mat3::operator*=(float scalar) {
    m[0][0] *= scalar;
    m[0][1] *= scalar;
    m[0][2] *= scalar;
    m[1][0] *= scalar;
    m[1][1] *= scalar;
    m[1][2] *= scalar;
    m[2][0] *= scalar;
    m[2][1] *= scalar;
    m[2][2] *= scalar;
    return *this;
}

Mat3 Mat3::operator/(const Mat3& other) const {
    return Mat3(m[0][0] / other.m[0][0], m[0][1] / other.m[0][1], m[0][2] / other.m[0][2],
                m[1][0] / other.m[1][0], m[1][1] / other.m[1][1], m[1][2] / other.m[1][2],
                m[2][0] / other.m[2][0], m[2][1] / other.m[2][1], m[2][2] / other.m[2][2]);
}

Mat3 Mat3::operator/=(const Mat3& other) {
    m[0][0] /= other.m[0][0];
    m[0][1] /= other.m[0][1];
    m[0][2] /= other.m[0][2];
    m[1][0] /= other.m[1][0];
    m[1][1] /= other.m[1][1];
    m[1][2] /= other.m[1][2];
    m[2][0] /= other.m[2][0];
    m[2][1] /= other.m[2][1];
    m[2][2] /= other.m[2][2];
    return *this;
}

Mat3 Mat3::operator/(float scalar) const {
    return Mat3(m[0][0] / scalar, m[0][1] / scalar, m[0][2] / scalar,
                m[1][0] / scalar, m[1][1] / scalar, m[1][2] / scalar,
                m[2][0] / scalar, m[2][1] / scalar, m[2][2] / scalar);
}

Mat3 Mat3::operator/=(float scalar) {
    m[0][0] /= scalar;
    m[0][1] /= scalar;
    m[0][2] /= scalar;
    m[1][0] /= scalar;
    m[1][1] /= scalar;
    m[1][2] /= scalar;
    m[2][0] /= scalar;
    m[2][1] /= scalar;
    m[2][2] /= scalar;
    return *this;
}

bool Mat3::operator==(const Mat3& other) const {
    return m[0][0] == other.m[0][0] && m[0][1] == other.m[0][1] && m[0][2] == other.m[0][2] &&
           m[1][0] == other.m[1][0] && m[1][1] == other.m[1][1] && m[1][2] == other.m[1][2] &&
           m[2][0] == other.m[2][0] && m[2][1] == other.m[2][1] && m[2][2] == other.m[2][2];
}

bool Mat3::operator!=(const Mat3& other) const {
    return m[0][0] != other.m[0][0] || m[0][1] != other.m[0][1] || m[0][2] != other.m[0][2] ||
           m[1][0] != other.m[1][0] || m[1][1] != other.m[1][1] || m[1][2] != other.m[1][2] ||
           m[2][0] != other.m[2][0] || m[2][1] != other.m[2][1] || m[2][2] != other.m[2][2];
}

float* Mat3::operator[](int index) {
    return m[index];
}

const float* Mat3::operator[](int index) const {
    return m[index];
}

std::ostream& operator<<(std::ostream& os, const Mat3& m) {
    os << m.m[0][0] << ", " << m.m[0][1] << ", " << m.m[0][2] << std::endl;
    os << m.m[1][0] << ", " << m.m[1][1] << ", " << m.m[1][2] << std::endl;
    os << m.m[2][0] << ", " << m.m[2][1] << ", " << m.m[2][2];
    return os;
}