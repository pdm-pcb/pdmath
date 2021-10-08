#ifndef PDMATH_LINE_HPP
#define PDMATH_LINE_HPP

#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"

namespace pdm {
    class Plane;
    class Point;

    class Line {
        public:
            Line() = default;
            Line(const Point &a, const Point &b);
            Line(const Point &p, const Vec3 &vector);

            bool  parallel_to_plane(const Plane &plane) const;
            bool  within_plane (const Plane &plane) const;
            Point intersects_at(const Plane &plane) const;

            Point _p;
            Vec3 _v;
    };
} // namespace pdm

#endif // PDMATH_LINE_HPP