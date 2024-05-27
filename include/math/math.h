#ifndef MATH_H
#define MATH_H

#define M_PI 3.14159265358979323846
#define MAX_FLT 3.402823466e+38F


#include <math/vec3.h>
#include <math/mat3.h>
#include <math/mat4.h>



class Math{
public:
    static float Dot(const Vec3& a, const Vec3& b);
    static Vec3 Cross(const Vec3& a, const Vec3& b);
    static Vec3 Normalize(const Vec3& a);
    static float Magnitude(const Vec3& a);

    static float Determinant2x2(float a, float b, float c, float d);

    static float Determinant3x3(float a11, float a12, float a13,
                                float a21, float a22, float a23,
                                float a31, float a32, float a33);

    static float Determinant4x4(const Mat4& a);

    static Mat4 Identity();
    static Mat4 Transpose(const Mat4& a);
    static Mat4 Inverse(const Mat4& a);

    static Mat4 Translate(Mat4 m, const Vec3& translation);
    static Mat4 Rotate(const Vec3& axis, float angle);
    static Mat4 RotateX(float angle);
    static Mat4 RotateY(float angle);
    static Mat4 RotateZ(float angle);
    static Mat4 Scale(const Vec3& scale);

    static Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
    static Mat4 Perspective(float fov, float aspect, float near, float far);

    static float ToRadians(float degrees);
    static Vec3 Clamp(const Vec3& value, const Vec3& min, const Vec3& max);
    static float Abs(float value);
    static Vec3 Abs(const Vec3& value);

};

// Operators overloading
Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& a, float scalar);
Vec3 operator/(const Vec3& a, float scalar);

Mat4 operator+(const Mat4& a, const Mat4& b);
Mat4 operator-(const Mat4& a, const Mat4& b);
Mat4 operator*(const Mat4& a, const Mat4& b);
Mat4 operator*(const Mat4& a, float scalar);
Mat4 operator/(const Mat4& a, float scalar);

Vec3 operator*(const Mat3& a, const Vec3& b);


#endif //MATH_H