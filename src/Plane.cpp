#include "pdmath/Plane.hpp"
#include "pdmath/Line.hpp"

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

    float Plane::direction_test(const Line &bisect, const Point &p) const {
        Vec3 v_left = bisect._v.cross(this->_n);
        return v_left.dot(p);
    }
} // namespace pdm