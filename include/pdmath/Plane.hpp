#ifndef PDMATH_PLANE_HPP
#define PDMATH_PLANE_HPP

#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"

namespace pdm {
    class Line;
    class Plane {
        public:
            Plane() = default;
            Plane(const Point &a, const Point &b, const Point &c);
            Plane(const Point &p, const Vec3 &normal);

            float direction_test(const Line &bisect, const Point &p) const;

            Point _p;
            Vec3 _n;
    };
} // namespace pdm

#endif // PDMATH_PLANE_HPP