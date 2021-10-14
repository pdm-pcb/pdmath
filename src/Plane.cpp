#include "pdmath/Plane.hpp"

#include "pdmath/Line.hpp"

namespace pdm {
    Plane::Plane(const Point &a, const Point &b, const Point &c) :
        _p{a}, _n{}
    {
        Vec3 ab(b - a);
        Vec3 ac(c - a);
        _n = ab.cross(ac);
    }
    Plane::Plane(const Point &p, const Vec3 &normal) :
        _p{p}, _n{normal}
    { }

    float Plane::direction_test(const Line &bisect, const Point &p) const {
        Vec3 v_left = this->_n.cross(bisect._v);
        return v_left.dot(static_cast<Vec3>(p - this->_p));
    }
} // namespace pdm