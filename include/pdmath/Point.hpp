#ifndef PDMATH_POINT_HPP
#define PDMATH_POINT_HPP

#include <iostream>
#include <cmath>

namespace pdm {
    class Vec3;
    class Line;
    class Plane;

    class Point {
        public:
            Point() = default;
            Point(const float x, const float y, const float z);

            static constexpr float epsilon = 1.0e-6f;
            static constexpr uint8_t _output_precision = 7;

            float _x;
            float _y;
            float _z;

            bool  are_collinear(const Point &b, const Point &c) const;
            float distance_to_line(const Line &line) const;
            bool  is_on_plane(const Plane &plane) const;
            float distance_to_plane(const Plane &plane) const;

            bool is_zero() const;
            bool operator==(const Point &p) const;

            Point& operator+=(const Point &p);
            Point& operator-=(const Point &p);

            Point& operator+=(const float scalar);
            Point& operator-=(const float scalar);
            Point& operator*=(const float scalar);
            Point& operator/=(const float scalar);

            operator Vec3() const;
    };

    Point operator+(const Point &p, const Point &t);
    Point operator-(const Point &p, const Point &t);

    Point operator+(const Point &p, const float scalar);
    Point operator-(const Point &p, const float scalar);
    Point operator*(const Point &p, const float scalar);
    Point operator/(const Point &p, const float scalar);

    Point operator+(const float scalar, const Point &p);
    Point operator-(const float scalar, const Point &p);
    Point operator*(const float scalar, const Point &p);
    Point operator/(const float scalar, const Point &p);

    std::ostream& operator<<(std::ostream &os, const Point &p);
} // namespace pdm

#endif // PDMATH_POINT_HPP
