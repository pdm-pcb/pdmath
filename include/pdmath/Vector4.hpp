#ifndef PDMATH_VECTOR4_HPP
#define PDMATH_VECTOR4_HPP

#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"

#include <iostream>

namespace pdm {

class Vec4 : public Vec3 {
public:
    static const Vec4 zero;
    static const Vec4 one;

    float dot(const Vec4 &v) const;

    Vec4  normalized() const;
    Vec4  cross(const Vec4 &v) const;
    Vec4  project_onto(const Vec4 &v) const;
    Vec4  projection_perp(const Vec4 &v) const;

    float _w;

    Vec4() noexcept :
        Vec3(),
        _w{0.0f}
    { }

    Vec4(const float x, const float y, const float z) noexcept :
        Vec3(x, y, z),
        _w{0.0f}
    { }

    Vec4(const float x, const float y, const float z, const float w) noexcept :
        Vec3(x, y, z),
        _w{w}
    { }

    explicit Vec4(const Vec3 &v) noexcept :
        Vec3(v._x, v._y, v._z),
        _w{0.0f}
    { }

    explicit Vec4(const Point3 &p) noexcept :
        Vec3(p._x, p._y, p._z),
        _w{0.0f}
    { }

    bool operator==(const Vec4 &p) const;
};

Vec4 operator+(const Vec4 &v, const Vec3 &w);
Vec4 operator-(const Vec4 &v, const Vec3 &w);
Vec4 operator+(const Vec4 &v, const Vec4 &w);
Vec4 operator-(const Vec4 &v, const Vec4 &w);

Vec4 operator+(const Vec4 &v, const Point3 &p);
Vec4 operator-(const Vec4 &v, const Point3 &p);
Vec4 operator+(const Vec4 &v, const Point4 &p);
Vec4 operator-(const Vec4 &v, const Point4 &p);

Vec4 operator+(const Vec4 &v, const float scalar);
Vec4 operator-(const Vec4 &v, const float scalar);
Vec4 operator*(const Vec4 &v, const float scalar);
Vec4 operator/(const Vec4 &v, const float scalar);

Vec4 operator+(const float scalar, const Vec4 &v);
Vec4 operator-(const float scalar, const Vec4 &v);
Vec4 operator*(const float scalar, const Vec4 &v);
Vec4 operator/(const float scalar, const Vec4 &v);

std::ostream& operator<<(std::ostream &os, const Vec4 &p);

} // namespace pdm

#endif // PDMATH_VECTOR4_HPP
