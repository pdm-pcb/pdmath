#ifndef PDMATH_POINT4_HPP
#define PDMATH_POINT4_HPP

#include <iostream>
#include <cmath>

namespace pdm {
    class Line;
    class Plane;
    class Mat4;

    class Point4 {
        public:
            Point4() = default;
            Point4(const float x, const float y, const float z, const float w);

            bool is_zero() const;

            static constexpr uint8_t _output_precision = 7;
            static constexpr float   _epsilon = 1.0e-6f;

            float _x;
            float _y;
            float _z;
            float _w;

            bool operator==(const Point4 &p) const;

            const Point4& operator+=(const Point4 &p);
            const Point4& operator-=(const Point4 &p);

            const Point4& operator+=(const float scalar);
            const Point4& operator-=(const float scalar);
            const Point4& operator*=(const float scalar);
            const Point4& operator/=(const float scalar);

            const Point4& operator*=(const Mat4 &m);
    };

    Point4 operator+(const Point4 &p, const Point4 &t);
    Point4 operator-(const Point4 &p, const Point4 &t);

    Point4 operator+(const Point4 &p, const float scalar);
    Point4 operator-(const Point4 &p, const float scalar);
    Point4 operator*(const Point4 &p, const float scalar);
    Point4 operator/(const Point4 &p, const float scalar);

    Point4 operator+(const float scalar, const Point4 &p);
    Point4 operator-(const float scalar, const Point4 &p);
    Point4 operator*(const float scalar, const Point4 &p);
    Point4 operator/(const float scalar, const Point4 &p);

    std::ostream& operator<<(std::ostream &os, const Point4 &p);
} // namespace pdm
#endif // PDMATH_POINT_HPP
