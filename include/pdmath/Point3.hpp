#ifndef PDMATH_POINT3_HPP
#define PDMATH_POINT3_HPP

#include <iostream>
#include <cmath>

namespace pdm {
class Line;
class Plane;
class Mat3;

class Point3 {
public:
    Point3() = default;
    Point3(const float x, const float y, const float z);

    bool  are_collinear(const Point3 &b, const Point3 &c) const;
    float distance_to_line(const Line &line) const;
    bool  is_on_plane(const Plane &plane) const;
    float distance_to_plane(const Plane &plane) const;

    bool is_zero() const;

    static constexpr uint8_t precision = 7;
    static constexpr float   epsilon = 1.0e-6f;

    float _x;
    float _y;
    float _z;

    bool operator==(const Point3 &p) const;

    const Point3& operator+=(const Point3 &p);
    const Point3& operator-=(const Point3 &p);

    const Point3& operator+=(const float scalar);
    const Point3& operator-=(const float scalar);
    const Point3& operator*=(const float scalar);
    const Point3& operator/=(const float scalar);

    const Point3& operator*=(const Mat3 &m);
};

Point3 operator+(const Point3 &p, const Point3 &t);
Point3 operator-(const Point3 &p, const Point3 &t);

Point3 operator+(const Point3 &p, const float scalar);
Point3 operator-(const Point3 &p, const float scalar);
Point3 operator*(const Point3 &p, const float scalar);
Point3 operator/(const Point3 &p, const float scalar);

Point3 operator+(const float scalar, const Point3 &p);
Point3 operator-(const float scalar, const Point3 &p);
Point3 operator*(const float scalar, const Point3 &p);
Point3 operator/(const float scalar, const Point3 &p);

std::ostream& operator<<(std::ostream &os, const Point3 &p);
} // namespace pdm

#endif // PDMATH_POINT3_HPP
