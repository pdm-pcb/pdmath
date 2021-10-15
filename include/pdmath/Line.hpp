#ifndef PDMATH_LINE_HPP
#define PDMATH_LINE_HPP

#include "pdmath/Point3.hpp"
#include "pdmath/Vector.hpp"

namespace pdm {
    class Plane;
    class Point3;

    class Line {
        public:
            Line() = default;
            Line(const Point3 &a, const Point3 &b);
            Line(const Point3 &p, const Vec3 &vector);

            bool  parallel_to_plane(const Plane &plane) const;
            bool  within_plane (const Plane &plane) const;
            Point3 intersects_at(const Plane &plane) const;

            Point3 _p;
            Vec3 _v;
    };
} // namespace pdm

#endif // PDMATH_LINE_HPP