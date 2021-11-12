#ifndef PDMATH_POINT4_HPP
#define PDMATH_POINT4_HPP

#include <iostream>
#include <cmath>

namespace pdm {
class Point3;
class Line4;
class Mat4;
class Plane;

class Point4 {
public:
    bool  are_collinear(const Point4 &b, const Point4 &c) const;
    Point4 nearest_approach(const Line4 &line) const;
    Point4 nearest_approach_segment(const Line4 &line) const;
    Point4 nearest_approach_ray(const Line4 &line) const;
    float distance_to_line(const Line4 &line) const;
    bool  is_on_plane(const Plane &plane) const;
    float distance_to_plane(const Plane &plane) const;

    bool is_zero() const;

    static constexpr uint8_t precision = 7;
    static constexpr float   epsilon = 1.0e-6f;

    float _x;
    float _y;
    float _z;
    float _w;

    Point4() = default;
    Point4(const float x, const float y, const float z, const float w);
    Point4(const float x, const float y, const float z);
    Point4(const Point3 &p, const float w);
    explicit Point4(const Point3 &p);
    
    bool operator==(const Point4 &p) const;

    const Point4& operator+=(const Point4 &p);
    const Point4& operator-=(const Point4 &p);

    const Point4& operator+=(const Point3 &p);
    const Point4& operator-=(const Point3 &p);

    const Point4& operator+=(const float scalar);
    const Point4& operator-=(const float scalar);
    const Point4& operator*=(const float scalar);
    const Point4& operator/=(const float scalar);

    const Point4& operator*=(const Mat4 &m);
};

Point4 operator+(const Point4 &p, const Point4 &t);
Point4 operator-(const Point4 &p, const Point4 &t);

Point4 operator+(const Point4 &p, const Point3 &t);
Point4 operator-(const Point4 &p, const Point3 &t);

Point4 operator+(const Point3 &p, const Point4 &t);
Point4 operator-(const Point3 &p, const Point4 &t);

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
#endif // PDMATH_POINT4_HPP
