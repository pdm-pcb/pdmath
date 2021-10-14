#ifndef PDMATH_MATRIX_HPP
#define PDMATH_MATRIX_HPP

#include <array>
#include <iostream>

namespace pdm {
    class Vec3;
    class Point;

    class Mat3 {
        public:
            Mat3() : _x{0}, _y{0}, _z{0} { }
            Mat3(const Vec3 &x, const Vec3 &y, const Vec3 &z);
            Mat3(const Point &x, const Point &y, const Point &z);
            Mat3(const std::array<float, 3> &x,
                 const std::array<float, 3> &y,
                 const std::array<float, 3> &z);
            Mat3(const float x1, const float y1, const float z1,
                 const float x2, const float y2, const float z2,
                 const float x3, const float y3, const float z3);

            std::array<float, 3> _x;
            std::array<float, 3> _y;
            std::array<float, 3> _z;

            bool operator==(const Mat3 &m) const;

            const Mat3& operator*=(const Mat3 &m);
            const Mat3& operator*=(const Vec3 &v);
            const Mat3& operator*=(const float lambda);

            const Mat3& operator+=(const Mat3 &m);
            const Mat3& operator-=(const Mat3 &m);
    };

    std::ostream& operator<<(std::ostream &os, const Mat3 &m);
} // namespace pdm

#endif // PDMATH_MATRIX_HPP