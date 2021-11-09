#ifndef PDMATH_MATRIX3_HPP
#define PDMATH_MATRIX3_HPP

#include <array>
#include <iostream>

namespace pdm {
class Vec3;
class Point3;

class Mat3 {
public:
    Mat3() noexcept:
        _m{{0}, {0}, {0}}
    { }

    Mat3(const Point3 &x, const Point3 &y, const Point3 &z) noexcept;
    
    Mat3(const std::array<float, 3> &x,
            const std::array<float, 3> &y,
            const std::array<float, 3> &z) noexcept;
    
    Mat3(const float x1, const float y1, const float z1,
            const float x2, const float y2, const float z2,
            const float x3, const float y3, const float z3) noexcept;

    static const Mat3 identity;

    static Mat3 populate_rotation(float theta_x, float theta_y,
                                    float theta_z);
    Mat3 transposed() const;
    Mat3 inverted() const;
    float determinant() const;
    Mat3 matrix_of_minors() const;
    Mat3 matrix_of_cofactors() const;

    void get_euler_xyz(Vec3 &ans1, Vec3 &ans2) const;
    void get_euler_zxy(Vec3 &ans1, Vec3 &ans2) const;

    float _m[3][3];

    bool operator==(const Mat3 &m) const;

    const Mat3& operator*=(const Mat3 &m);
    const Mat3& operator*=(const float scalar);
    const Mat3& operator+=(const Mat3 &m);
    const Mat3& operator-=(const Mat3 &m);
};

Mat3 operator*(const Mat3 &m, const Mat3 &n);
Mat3 operator*(const Mat3 &m, const float scalar);
Mat3 operator*(const float scalar, const Mat3 &m);
Mat3 operator+(const Mat3 &m, const Mat3 &n);
Mat3 operator-(const Mat3 &m, const Mat3 &n);

Point3 operator*(const Mat3 &m,   const Point3 &p);
Vec3   operator*(const Mat3 &m,   const Vec3 &v);

std::ostream& operator<<(std::ostream &os, const Mat3 &m);
} // namespace pdm

#endif // PDMATH_MATRIX3_HPP