#ifndef PDMATH_VECTOR3_HPP
#define PDMATH_VECTOR3_HPP

#include <iostream>

namespace pdm {
class Point3;
class Point4;
class Vec4;
class Mat3;
class Mat4;

class Vec3 {
public:
    static const Vec3 zero;
    static const Vec3 one;

    float length() const;
    float dot(const Vec3 &v) const;

    Vec3  normalized() const;
    Vec3  cross(const Vec3 &v) const;
    Vec3  project_onto(const Vec3 &v) const;
    Vec3  projection_perp(const Vec3 &v) const;

    bool  is_collinear(const Vec3 &v) const;
    bool  is_perpendicular(const Vec3 &v) const;

    float _x;
    float _y;
    float _z;
    
    Vec3() noexcept;
    Vec3(const float x, const float y, const float z) noexcept;
    explicit Vec3(const Point3 &p) noexcept;

    bool operator==(const Vec3 &v) const;

    const Vec3& operator+=(const Vec3 &v);
    const Vec3& operator-=(const Vec3 &v);
    const Vec3& operator+=(const Vec4 &v);
    const Vec3& operator-=(const Vec4 &v);

    const Vec3& operator+=(const float scalar);
    const Vec3& operator-=(const float scalar);
    const Vec3& operator*=(const float scalar);
    const Vec3& operator/=(const float scalar);

    const Vec3& operator+=(const Point3 &p);
    const Vec3& operator-=(const Point3 &p);
    const Vec3& operator+=(const Point4 &p);
    const Vec3& operator-=(const Point4 &p);

    const Vec3& operator*=(const Mat3 &m);
    const Vec3& operator*=(const Mat4 &m);
};

Vec3 operator+(const Vec3 &v, const Vec3 &w);
Vec3 operator-(const Vec3 &v, const Vec3 &w);
Vec3 operator+(const Vec3 &v, const Vec4 &w);
Vec3 operator-(const Vec3 &v, const Vec4 &w);

Vec3 operator+(const Vec3 &v, const Point3 &p);
Vec3 operator-(const Vec3 &v, const Point3 &p);
Vec3 operator+(const Vec3 &v, const Point4 &p);
Vec3 operator-(const Vec3 &v, const Point4 &p);

Vec3 operator-(const Point3 &p, const Point3 &t);
Vec3 operator-(const Point3 &p, const Point4 &t);

Vec3 operator+(const Vec3 &v, const float scalar);
Vec3 operator-(const Vec3 &v, const float scalar);
Vec3 operator*(const Vec3 &v, const float scalar);
Vec3 operator/(const Vec3 &v, const float scalar);

Vec3 operator+(const float scalar, const Vec3 &v);
Vec3 operator-(const float scalar, const Vec3 &v);
Vec3 operator*(const float scalar, const Vec3 &v);
Vec3 operator/(const float scalar, const Vec3 &v);

std::ostream& operator<<(std::ostream &os, const Vec3 &p);
} // namespace pdm

#endif // PDMATH_VECTOR3_HPP
