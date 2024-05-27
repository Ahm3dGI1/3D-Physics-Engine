#include "math/mat4.h"

Mat4::Mat4(float m00, float m01, float m02, float m03,
           float m10, float m11, float m12, float m13,
           float m20, float m21, float m22, float m23,
           float m30, float m31, float m32, float m33) {
    m[0][0] = m00;      m[1][0] = m10;      m[2][0] = m20;      m[3][0] = m30;
    m[0][1] = m01;      m[1][1] = m11;      m[2][1] = m21;      m[3][1] = m31;
    m[0][2] = m02;      m[1][2] = m12;      m[2][2] = m22;      m[3][2] = m32;
    m[0][3] = m03;      m[1][3] = m13;      m[2][3] = m23;      m[3][3] = m33;
}

Mat4::Mat4(float a) {
    m[0][0] = a;        m[1][0] = 0.0f;     m[2][0] = 0.0f;     m[3][0] = 0.0f;
    m[0][1] = 0.0f;     m[1][1] = a;        m[2][1] = 0.0f;     m[3][1] = 0.0f;
    m[0][2] = 0.0f;     m[1][2] = 0.0f;     m[2][2] = a;        m[3][2] = 0.0f;
    m[0][3] = 0.0f;     m[1][3] = 0.0f;     m[2][3] = 0.0f;     m[3][3] = a;
}

Mat4 Mat4::operator+=(const Mat4& other) {
    m[0][0] += other.m[0][0];       m[1][0] += other.m[1][0];       m[2][0] += other.m[2][0];       m[3][0] += other.m[3][0];
    m[0][1] += other.m[0][1];       m[1][1] += other.m[1][1];       m[2][1] += other.m[2][1];       m[3][1] += other.m[3][1];
    m[0][2] += other.m[0][2];       m[1][2] += other.m[1][2];       m[2][2] += other.m[2][2];       m[3][2] += other.m[3][2];
    m[0][3] += other.m[0][3];       m[1][3] += other.m[1][3];       m[2][3] += other.m[2][3];       m[3][3] += other.m[3][3];
    return *this;
}

Mat4 Mat4::operator+=(float scalar) {
    m[0][0] += scalar;      m[1][0] += scalar;      m[2][0] += scalar;      m[3][0] += scalar;
    m[0][1] += scalar;      m[1][1] += scalar;      m[2][1] += scalar;      m[3][1] += scalar;
    m[0][2] += scalar;      m[1][2] += scalar;      m[2][2] += scalar;      m[3][2] += scalar;
    m[0][3] += scalar;      m[1][3] += scalar;      m[2][3] += scalar;      m[3][3] += scalar;
    return *this;
}

Mat4 Mat4::operator-=(const Mat4& other) {
    m[0][0] -= other.m[0][0];       m[1][0] -= other.m[1][0];       m[2][0] -= other.m[2][0];       m[3][0] -= other.m[3][0];
    m[0][1] -= other.m[0][1];       m[1][1] -= other.m[1][1];       m[2][1] -= other.m[2][1];       m[3][1] -= other.m[3][1];
    m[0][2] -= other.m[0][2];       m[1][2] -= other.m[1][2];       m[2][2] -= other.m[2][2];       m[3][2] -= other.m[3][2];
    m[0][3] -= other.m[0][3];       m[1][3] -= other.m[1][3];       m[2][3] -= other.m[2][3];       m[3][3] -= other.m[3][3];
    return *this;
}

Mat4 Mat4::operator-=(float scalar) {
    m[0][0] -= scalar;      m[1][0] -= scalar;      m[2][0] -= scalar;      m[3][0] -= scalar;
    m[0][1] -= scalar;      m[1][1] -= scalar;      m[2][1] -= scalar;      m[3][1] -= scalar;
    m[0][2] -= scalar;      m[1][2] -= scalar;      m[2][2] -= scalar;      m[3][2] -= scalar;
    m[0][3] -= scalar;      m[1][3] -= scalar;      m[2][3] -= scalar;      m[3][3] -= scalar;
    return *this;
}

Mat4 Mat4::operator*=(const Mat4& other) {
    float result[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = result[i][j];
        }
    }
    return *this;
}

Mat4 Mat4::operator*=(float scalar) {
    m[0][0] *= scalar;      m[1][0] *= scalar;      m[2][0] *= scalar;      m[3][0] *= scalar;
    m[0][1] *= scalar;      m[1][1] *= scalar;      m[2][1] *= scalar;      m[3][1] *= scalar;
    m[0][2] *= scalar;      m[1][2] *= scalar;      m[2][2] *= scalar;      m[3][2] *= scalar;
    m[0][3] *= scalar;      m[1][3] *= scalar;      m[2][3] *= scalar;      m[3][3] *= scalar;
    return *this;
}

Mat4 Mat4::operator/=(const Mat4& other) {
    m[0][0] /= other.m[0][0];       m[1][0] /= other.m[1][0];       m[2][0] /= other.m[2][0];       m[3][0] /= other.m[3][0];
    m[0][1] /= other.m[0][1];       m[1][1] /= other.m[1][1];       m[2][1] /= other.m[2][1];       m[3][1] /= other.m[3][1];
    m[0][2] /= other.m[0][2];       m[1][2] /= other.m[1][2];       m[2][2] /= other.m[2][2];       m[3][2] /= other.m[3][2];
    m[0][3] /= other.m[0][3];       m[1][3] /= other.m[1][3];       m[2][3] /= other.m[2][3];       m[3][3] /= other.m[3][3];
    return *this;
}

Mat4 Mat4::operator/=(float scalar) {
    m[0][0] /= scalar;      m[1][0] /= scalar;      m[2][0] /= scalar;      m[3][0] /= scalar;
    m[0][1] /= scalar;      m[1][1] /= scalar;      m[2][1] /= scalar;      m[3][1] /= scalar;
    m[0][2] /= scalar;      m[1][2] /= scalar;      m[2][2] /= scalar;      m[3][2] /= scalar;
    m[0][3] /= scalar;      m[1][3] /= scalar;      m[2][3] /= scalar;      m[3][3] /= scalar;
    return *this;
}

bool Mat4::operator==(const Mat4& other) const {
    return m[0][0] == other.m[0][0] && m[1][0] == other.m[1][0] && m[2][0] == other.m[2][0] && m[3][0] == other.m[3][0] &&
           m[0][1] == other.m[0][1] && m[1][1] == other.m[1][1] && m[2][1] == other.m[2][1] && m[3][1] == other.m[3][1] &&
           m[0][2] == other.m[0][2] && m[1][2] == other.m[1][2] && m[2][2] == other.m[2][2] && m[3][2] == other.m[3][2] &&
           m[0][3] == other.m[0][3] && m[1][3] == other.m[1][3] && m[2][3] == other.m[2][3] && m[3][3] == other.m[3][3];
}

bool Mat4::operator!=(const Mat4& other) const {
    return m[0][0] != other.m[0][0] || m[1][0] != other.m[1][0] || m[2][0] != other.m[2][0] || m[3][0] != other.m[3][0] ||
           m[0][1] != other.m[0][1] || m[1][1] != other.m[1][1] || m[2][1] != other.m[2][1] || m[3][1] != other.m[3][1] ||
           m[0][2] != other.m[0][2] || m[1][2] != other.m[1][2] || m[2][2] != other.m[2][2] || m[3][2] != other.m[3][2] ||
           m[0][3] != other.m[0][3] || m[1][3] != other.m[1][3] || m[2][3] != other.m[2][3] || m[3][3] != other.m[3][3];
}

float* Mat4::operator[](int index) {
    return m[index];
}

const float* Mat4::operator[](int index) const {
    return m[index];
}

std::ostream& operator<<(std::ostream& os, const Mat4& m) {
    os << m.m[0][0] << " " << m.m[1][0] << " " << m.m[2][0] << " " << m.m[3][0] << std::endl;
    os << m.m[0][1] << " " << m.m[1][1] << " " << m.m[2][1] << " " << m.m[3][1] << std::endl;
    os << m.m[0][2] << " " << m.m[1][2] << " " << m.m[2][2] << " " << m.m[3][2] << std::endl;
    os << m.m[0][3] << " " << m.m[1][3] << " " << m.m[2][3] << " " << m.m[3][3] << std::endl;
    return os;
}

