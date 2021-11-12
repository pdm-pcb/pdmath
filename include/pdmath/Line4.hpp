#ifndef PDMATH_LINE4_HPP
#define PDMATH_LINE4_HPP

#include "pdmath/Point4.hpp"
#include "pdmath/Vector4.hpp"

namespace pdm {
class Plane;

class Line4 {
public:
    Line4() = default;
    Line4(const Point4 &a, const Point4 &b);
    Line4(const Point4 &p, const Vec4 &vector);

    bool   parallel_to_plane(const Plane &plane) const;
    bool   within_plane (const Plane &plane) const;
    Point4 intersects_at(const Plane &plane) const;
    float  distance_to(const Line4 &other) const;

    Point4 _p;
    Vec4   _v;
};
} // namespace pdm

#endif // PDMATH_LINE4_HPP