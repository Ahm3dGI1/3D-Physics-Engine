#ifndef MAT4_H
#define MAT4_H

#include <iostream>

class Mat4{
public:
    float m[4][4];

    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33);
    Mat4(float a = 1.0f);

    // Operator overloads
    Mat4 operator+=(const Mat4& other);
    Mat4 operator+=(float scalar);

    Mat4 operator-=(const Mat4& other);
    Mat4 operator-=(float scalar);

    Mat4 operator*=(const Mat4& other);
    Mat4 operator*=(float scalar);

    Mat4 operator/=(const Mat4& other);
    Mat4 operator/=(float scalar);

    bool operator==(const Mat4& other) const;
    bool operator!=(const Mat4& other) const;

    float* operator[](int index);
    const float* operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const Mat4& m);
};

#endif //MAT4_H