#ifndef PDMATH_LINE_HPP
#define PDMATH_LINE_HPP

#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"

namespace pdm {
class Point4;
class Vec4;
class Plane;

class Line {
public:
    float  distance_to(const Line &other)        const;
    bool   parallel_to(const Line &other)        const;
    bool   parallel_to_plane(const Plane &plane) const;
    bool   within_plane (const Plane &plane)     const;
    bool   collides(const Line &other)           const;
    bool   collides(const Plane &plane)          const;
    float  collides_depth(const Plane &plane)    const;
    Point3 collides_at(const Plane &plane)       const;

    Line();
    Line(const Point3 &a, const Point3 &b);
    Line(const Point4 &a, const Point4 &b);
    Line(const Point3 &p, const Vec3 &v);
    Line(const Point4 &p, const Vec4 &v);

    Point3 point_a() const { return _p; }
    Point3 point_b() const { return _t; }
    Vec3   vec()     const { return _v; }

private:
    Point3 _p;
    Point3 _t;
    Vec3   _v;
};
} // namespace pdm

#endif // PDMATH_LINE_HPP