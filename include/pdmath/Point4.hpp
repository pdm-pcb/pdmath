#ifndef PDMATH_POINT4_HPP
#define PDMATH_POINT4_HPP

#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"

#include <iostream>

namespace pdm {

class Point4 : public Point3 {
public:

    float _w;

    Point4() noexcept :
        Point3(),
        _w{1.0f}
    { }

    Point4(const float x, const float y, const float z) noexcept :
        Point3(x, y, z),
        _w{1.0f}
    { }

    Point4(const float x, const float y, const float z, const float w) noexcept:
        Point3(x, y, z),
        _w{w}
    { }

    explicit Point4(const Point3 &p) noexcept :
        Point3(p._x, p._y, p._z),
        _w{1.0f}
    { }

    explicit Point4(const Vec3 &v) noexcept :
        Point3(v._x, v._y, v._z),
        _w{1.0f}
    { }

    bool operator==(const Point4 &p) const;
    
    const Point4& operator+=(const Point3 &p);
    const Point4& operator+=(const Point4 &p);

    const Point4& operator+=(const float scalar);
    const Point4& operator-=(const float scalar);
    const Point4& operator*=(const float scalar);
    const Point4& operator/=(const float scalar);

    const Point4& operator+=(const Vec3 &v);
    const Point4& operator-=(const Vec3 &v);
    const Point4& operator+=(const Vec4 &v);
    const Point4& operator-=(const Vec4 &v);

    const Point4& operator*=(const Mat3 &m);
    const Point4& operator*=(const Mat4 &m);
};

Point4 operator+(const Point4 &p, const Point3 &t);
Point4 operator+(const Point4 &p, const Point4 &t);

Point4 operator+(const Point4 &p, const Vec3 &v);
Point4 operator-(const Point4 &p, const Vec3 &v);
Point4 operator+(const Point4 &p, const Vec4 &v);
Point4 operator-(const Point4 &p, const Vec4 &v);

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
