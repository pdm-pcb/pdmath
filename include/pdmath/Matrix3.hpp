#ifndef PDMATH_MATRIX3_HPP
#define PDMATH_MATRIX3_HPP

#include <array>
#include <iostream>

namespace pdm {
    class Vec3;
    class Point3;

    class Mat3 {
        public:
            Mat3() :
                _elem{{0}, {0}, {0}}
            { }

            Mat3(const Point3 &x, const Point3 &y, const Point3 &z);
            
            Mat3(const std::array<float, 3> &x,
                 const std::array<float, 3> &y,
                 const std::array<float, 3> &z);
            
            Mat3(const float x1, const float y1, const float z1,
                 const float x2, const float y2, const float z2,
                 const float x3, const float y3, const float z3);

            Mat3 transpose() const;
            Mat3 inverse() const;
            float determinant() const;
            Mat3 matrix_of_minors() const;
            Mat3 matrix_of_cofactors() const;

            float _elem[3][3];
    
            bool operator==(const Mat3 &m) const;

            const Mat3& operator*=(const Mat3 &m);
            const Mat3& operator*=(const float lambda);
            const Mat3& operator+=(const Mat3 &m);
            const Mat3& operator-=(const Mat3 &m);
    };

    Mat3 operator*(const Mat3 &m, const Mat3 &n);
    Mat3 operator*(const Mat3 &m, const float lambda);
    Mat3 operator*(const float lambda, const Mat3 &m);
    Mat3 operator+(const Mat3 &m, const Mat3 &n);
    Mat3 operator-(const Mat3 &m, const Mat3 &n);

    Point3 operator*(const Mat3 &m,   const Point3 &p);
    Vec3   operator*(const Mat3 &m,   const Vec3 &v);

    std::ostream& operator<<(std::ostream &os, const Mat3 &m);
} // namespace pdm

#endif // PDMATH_MATRIX3_HPP