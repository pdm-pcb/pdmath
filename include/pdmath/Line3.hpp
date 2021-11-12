#ifndef PDMATH_LINE3_HPP
#define PDMATH_LINE3_HPP

#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"

namespace pdm {
class Plane;

class Line3 {
public:
    Line3() = default;
    Line3(const Point3 &a, const Point3 &b);
    Line3(const Point3 &p, const Vec3 &vector);

    bool   parallel_to_plane(const Plane &plane) const;
    bool   within_plane (const Plane &plane)     const;
    bool   intersects(const Plane &plane)        const;
    float  intersects_depth(const Plane &plane) const;
    Point3 intersects_at(const Plane &plane)     const;

    Point3 _p;
    Point3 _t;
    Vec3   _v;
};
} // namespace pdm

#endif // PDMATH_LINE3_HPP