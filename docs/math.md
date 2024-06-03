# Math Documentation
## Overview
The Math library provides a set of mathematical utilities for 3D graphics and physics simulations. This includes vector and matrix operations, as well as various mathematical functions for transformations and utility purposes.

## Operators Overloading
### Vec3
```cpp
Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& a, float scalar);
Vec3 operator/(const Vec3& a, float scalar);
```

### Mat4
```cpp
Mat4 operator+(const Mat4& a, const Mat4& b);
Mat4 operator-(const Mat4& a, const Mat4& b);
Mat4 operator*(const Mat4& a, const Mat4& b);
Mat4 operator*(const Mat4& a, float scalar);
Mat4 operator/(const Mat4& a, float scalar);
Mat4 operator*(const Mat4& a, const Vec3& b);
Vec3 operator*(const Mat3& a, const Vec3& b);
```

## Essential Functions
### Vec3
- Dot Product: Calculates the dot product and returns a floating-point value.
```cpp
float Math::Dot(const Vec3& a, const Vec3& b);
```

- Cross Product: Calculates the cross product of two vector and returns a Vec3 value.
```cpp
Vec3 Math::Cross(const Vec3& a, const Vec3& b);
```

- Normalize: Normalize the Vec3 to have a total magnitude of 1.
```cpp
Vec3 Math::Normalize(const Vec3& a);
```

- Magnitude: calculates the length of a Vec3.
```cpp
float Math::Magnitude(const Vec3& a);
```

### Mat4
- Determinant: Calculates the determinant of 2x2, 3x3, and 4x4 matrices.
```cpp
float Math::Determinant2x2(float a, float b, float c, float d);
float Math::Determinant3x3(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33);
float Math::Determinant4x4(const Mat4& a);
```

- Identity: Returns the identity matrix.
```cpp
Mat4 Math::Identity();
```
- Transpose: Returns the transpose of a matrix.
```cpp
Mat4 Math::Transpose(const Mat4& a);
```

- Inverse: Returns the inverse of a matrix. Throws an error if the matrix is singular.
```cpp
Mat4 Math::Inverse(const Mat4& a);
```

### Transformations:
- Translate: Translates a matrix by a given vector.
```cpp
Mat4 Math::Translate(Mat4 m, const Vec3& translation);
```

- Rotate: Rotates a matrix around an axis by a given angle or Rotates a matrix around the X, Y, or Z axis by a given angle.
```cpp
Mat4 Math::Rotate(const Vec3& axis, float angle);
Mat4 Math::RotateX(float angle);
Mat4 Math::RotateY(float angle);
Mat4 Math::RotateZ(float angle);
```

- Scale: Scales a matrix by a given vector.
```cpp
Mat4 Math::Scale(const Vec3& scale);
```
- LookAt: Creates a view matrix for a camera and is used next to the prespective and model matrices to create the projection matrix that results in the 3D look.
```cpp
Mat4 Math::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
```
- Perspective: Creates a perspective projection matrix.
```cpp
Mat4 Math::Perspective(float fov, float aspect, float near, float far);
```
## Utility Functions
- ToRadians: Converts degrees to radians.
```cpp
float Math::ToRadians(float degrees);
```
- Clamp: Clamps each component of a vector between given minimum and maximum values.
```cpp
Vec3 Math::Clamp(const Vec3& value, const Vec3& min, const Vec3& max);
```
- Abs: Returns the absolute value of a float or a vector with the absolute values of each component.
```cpp
float Math::Abs(float value);
Vec3 Math::Abs(const Vec3& value);
```