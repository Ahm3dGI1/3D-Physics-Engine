#include "math/math.h"

// Operators overloading
Vec3 operator+(const Vec3& a, const Vec3& b){
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b){
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& a, float scalar){
    return Vec3(a.x * scalar, a.y * scalar, a.z * scalar);
}

Vec3 operator/(const Vec3& a, float scalar){
    return Vec3(a.x / scalar, a.y / scalar, a.z / scalar);
}

Mat4 operator+(const Mat4& a, const Mat4& b){
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}

Mat4 operator-(const Mat4& a, const Mat4& b){
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
    return result;
}

Mat4 operator*(const Mat4& a, const Mat4& b){
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = a[i][0] * b[0][j] +
                           a[i][1] * b[1][j] +
                           a[i][2] * b[2][j] +
                           a[i][3] * b[3][j];
        }
    }
    return result;
}

Mat4 operator*(const Mat4& a, float scalar){
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = a[i][j] * scalar;
        }
    }
    return result;
}

Mat4 operator/(const Mat4& a, float scalar){
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = a[i][j] / scalar;
        }
    }
    return result;
}

Mat4 operator*(const Mat4& a, const Vec3& b){
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        result[i][0] = a[i][0] * b.x;
        result[i][1] = a[i][1] * b.y;
        result[i][2] = a[i][2] * b.z;
        result[i][3] = a[i][3];
    }
    return result;
}

Vec3 operator*(const Mat3& a, const Vec3& b){
    return Vec3(a[0][0] * b.x + a[0][1] * b.y + a[0][2] * b.z,
                a[1][0] * b.x + a[1][1] * b.y + a[1][2] * b.z,
                a[2][0] * b.x + a[2][1] * b.y + a[2][2] * b.z);
}

// Vec3 functions
float Math::Dot(const Vec3& a, const Vec3& b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Math::Cross(const Vec3& a, const Vec3& b){
    return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Vec3 Math::Normalize(const Vec3& a){
    float mag = Magnitude(a);
    return Vec3(a.x / mag, a.y / mag, a.z / mag);
}

float Math::Magnitude(const Vec3& a){
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// Mat4 functions
float Math::Determinant2x2(float a, float b, float c, float d){
    return a * d - b * c;
}

float Math::Determinant3x3(float a11, float a12, float a13,
                            float a21, float a22, float a23,
                            float a31, float a32, float a33){
    return a11 * Determinant2x2(a22, a23, a32, a33) -
           a12 * Determinant2x2(a21, a23, a31, a33) +
           a13 * Determinant2x2(a21, a22, a31, a32);
}

float Math::Determinant4x4(const Mat4& a){
    return a[0][0] * Determinant3x3(a[1][1], a[1][2], a[1][3],
                                     a[2][1], a[2][2], a[2][3],
                                     a[3][1], a[3][2], a[3][3]) -
           a[0][1] * Determinant3x3(a[1][0], a[1][2], a[1][3],
                                     a[2][0], a[2][2], a[2][3],
                                     a[3][0], a[3][2], a[3][3]) +
           a[0][2] * Determinant3x3(a[1][0], a[1][1], a[1][3],
                                     a[2][0], a[2][1], a[2][3],
                                     a[3][0], a[3][1], a[3][3]) -
           a[0][3] * Determinant3x3(a[1][0], a[1][1], a[1][2],
                                     a[2][0], a[2][1], a[2][2],
                                     a[3][0], a[3][1], a[3][2]);
}


Mat4 Math::Identity(){
    return Mat4(1.0f);
}

Mat4 Math::Transpose(const Mat4& a){
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = a.m[j][i];
        }
    }
    return result;
}

Mat4 Math::Inverse(const Mat4& a){
    Mat4 result;
    float det = 0.0f;

    // Compute the determinant of the 4x4 matrix
    for (int i = 0; i < 4; ++i) {
        float det3x3 = Determinant3x3(
            a[(i+1) % 4][1], a[(i+1) % 4][2], a[(i+1) % 4][3],
            a[(i+2) % 4][1], a[(i+2) % 4][2], a[(i+2) % 4][3],
            a[(i+3) % 4][1], a[(i+3) % 4][2], a[(i+3) % 4][3]
        );
        det += (i % 2 == 0 ? 1 : -1) * a[i][0] * det3x3;
    }

    if (det == 0.0f) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }

    float invDet = 1.0f / det;

    // Compute the adjugate matrix
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float det3x3 = Determinant3x3(
                a[(i+1) % 4][(j+1) % 4], a[(i+1) % 4][(j+2) % 4], a[(i+1) % 4][(j+3) % 4],
                a[(i+2) % 4][(j+1) % 4], a[(i+2) % 4][(j+2) % 4], a[(i+2) % 4][(j+3) % 4],
                a[(i+3) % 4][(j+1) % 4], a[(i+3) % 4][(j+2) % 4], a[(i+3) % 4][(j+3) % 4]
            );
            result[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * det3x3 * invDet;
        }
    }

    return result;
}

// Translate, rotate, scale
Mat4 Math::Translate(Mat4 m, const Vec3& translation){
    m[3][0] += translation.x;
    m[3][1] += translation.y;
    m[3][2] += translation.z;
    return m;
}

Mat4 Math::Rotate(const Vec3& axis, float angle){
    float c = cos(angle);
    float s = sin(angle);
    float t = 1.0f - c;

    Vec3 n = Normalize(axis);

    Mat4 result;
    result[0][0] = t * n.x * n.x + c;
    result[0][1] = t * n.x * n.y + s * n.z;
    result[0][2] = t * n.x * n.z - s * n.y;

    result[1][0] = t * n.x * n.y - s * n.z;
    result[1][1] = t * n.y * n.y + c;
    result[1][2] = t * n.y * n.z + s * n.x;

    result[2][0] = t * n.x * n.z + s * n.y;
    result[2][1] = t * n.y * n.z - s * n.x;
    result[2][2] = t * n.z * n.z + c;

    return result;
}

Mat4 Math::RotateX(float angle){
    float c = cos(angle);
    float s = sin(angle);

    Mat4 result;
    result[1][1] = c;
    result[1][2] = -s;
    result[2][1] = s;
    result[2][2] = c;

    return result;
}

Mat4 Math::RotateY(float angle){
    float c = cos(angle);
    float s = sin(angle);

    Mat4 result;
    result[0][0] = c;
    result[0][2] = s;
    result[2][0] = -s;
    result[2][2] = c;

    return result;
}

Mat4 Math::RotateZ(float angle){
    float c = cos(angle);
    float s = sin(angle);

    Mat4 result;
    result[0][0] = c;
    result[0][1] = -s;
    result[1][0] = s;
    result[1][1] = c;

    return result;
}

Mat4 Math::Scale(const Vec3& scale){
    Mat4 result = Identity();
    result[0][0] = scale.x;
    result[1][1] = scale.y;
    result[2][2] = scale.z;
    return result;
}

// LookAt, Perspective
Mat4 Math::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up){
    Vec3 f = Normalize(center - eye);
    Vec3 r = Normalize(Cross(f, up));
    Vec3 u = Cross(r, f);

    Mat4 result;
    result[0][0] = r.x;
    result[0][1] = r.y;
    result[0][2] = r.z;
    result[1][0] = u.x;
    result[1][1] = u.y;
    result[1][2] = u.z;
    result[2][0] = -f.x;
    result[2][1] = -f.y;
    result[2][2] = -f.z;
    result[3][0] = -Dot(r, eye);
    result[3][1] = -Dot(u, eye);
    result[3][2] = Dot(f, eye);

    return result;
}

Mat4 Math::Perspective(float fov, float aspect, float near, float far){
    Mat4 result;
    float q = 1.0f / tan(ToRadians(0.5f * fov));
    float a = q / aspect;
    float b = (near + far) / (near - far);
    float c = (2.0f * near * far) / (near - far);

    result[0][0] = a;
    result[1][1] = q;
    result[2][2] = b;
    result[2][3] = -1.0f;
    result[3][2] = c;

    return result;
}

// Utility functions
float Math::ToRadians(float degrees){
    return degrees * M_PI / 180.0f;
}

Vec3 Math::Clamp(const Vec3& value, const Vec3& min, const Vec3& max){
    return Vec3(
        value.x < min.x ? min.x : (value.x > max.x ? max.x : value.x),
        value.y < min.y ? min.y : (value.y > max.y ? max.y : value.y),
        value.z < min.z ? min.z : (value.z > max.z ? max.z : value.z)
    );
}

float Math::Abs(float value){
    return value < 0.0f ? -value : value;
}

Vec3 Math::Abs(const Vec3& value){
    return Vec3(Abs(value.x), Abs(value.y), Abs(value.z));
}