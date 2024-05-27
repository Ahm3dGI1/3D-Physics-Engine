#ifndef MAT3_H
#define MAT3_H

#include <iostream>

class Mat3
{
public:
    float m[3][3];

    Mat3(float m00, float m01, float m02,
         float m10, float m11, float m12,
         float m20, float m21, float m22);
    Mat3(float a = 1.0f);

    // Operator overloads
    Mat3 operator+(const Mat3& other) const;
    Mat3 operator+=(const Mat3& other);
    Mat3 operator+(float scalar) const;
    Mat3 operator+=(float scalar);

    Mat3 operator-(const Mat3& other) const;
    Mat3 operator-=(const Mat3& other);
    Mat3 operator-(float scalar) const;
    Mat3 operator-=(float scalar);

    Mat3 operator*(const Mat3& other) const;
    Mat3 operator*=(const Mat3& other);
    Mat3 operator*(float scalar) const;
    Mat3 operator*=(float scalar);

    Mat3 operator/(const Mat3& other) const;
    Mat3 operator/=(const Mat3& other);
    Mat3 operator/(float scalar) const;
    Mat3 operator/=(float scalar);

    bool operator==(const Mat3& other) const;
    bool operator!=(const Mat3& other) const;

    float* operator[](int index);
    const float* operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const Mat3& m);
};


#endif //MAT3_H