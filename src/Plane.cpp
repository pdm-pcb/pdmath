#include "pdmath/Plane.hpp"

namespace pdm {
    Plane::Plane(const Point &a, const Point &b, const Point &c) :
        _p{a}, _n{}
    {
        Vec3 ab(a, b);
        Vec3 ac(a, c);
        _n = ab.cross(ac);
    }
    Plane::Plane(const Point &p, const Vec3 &normal) :
        _p{p}, _n{normal}
    { }
} // namespace pdm