#ifndef PDMATH_POINT3_HPP
#define PDMATH_POINT3_HPP

#include <iostream>

namespace pdm {
class Point4;
class Vec3;
class Vec4;
class Mat3;
class Mat4;
class Line;
class Plane;

class Point3 {
public:
    bool  are_collinear(const Point3 &b, const Point3 &c) const;
    bool  is_on_plane(const Plane &plane) const;

    float distance_to_line(const Line &line) const;
    float distance_to_plane(const Plane &plane) const;

    Point3 nearest_approach(const Line &line) const;
    Point3 nearest_approach_segment(const Line &line) const;
    Point3 nearest_approach_ray(const Line &line) const;

    float _x;
    float _y;
    float _z;

    Point3() noexcept;
    Point3(const float x, const float y, const float z) noexcept;
    explicit Point3(const Vec3 &v) noexcept;

    bool operator==(const Point3 &p) const;

    const Point3& operator+=(const Point3 &p);
    const Point3& operator-=(const Point3 &p);
    const Point3& operator+=(const Point4 &p);
    const Point3& operator-=(const Point4 &p);

    const Point3& operator+=(const float scalar);
    const Point3& operator-=(const float scalar);
    const Point3& operator*=(const float scalar);
    const Point3& operator/=(const float scalar);

    const Point3& operator+=(const Vec3 &v);
    const Point3& operator-=(const Vec3 &v);
    const Point3& operator+=(const Vec4 &v);
    const Point3& operator-=(const Vec4 &v);

    const Point3& operator*=(const Mat3 &m);
    const Point3& operator*=(const Mat4 &m);
};

Point3 operator+(const Point3 &p, const Point3 &t);
Point3 operator-(const Point3 &p, const Point3 &t);
Point3 operator+(const Point3 &p, const Point4 &t);
Point3 operator-(const Point3 &p, const Point4 &t);

Point3 operator+(const Point3 &p, const Vec3 &v);
Point3 operator-(const Point3 &p, const Vec3 &v);
Point3 operator+(const Point3 &p, const Vec4 &v);
Point3 operator-(const Point3 &p, const Vec4 &v);

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
