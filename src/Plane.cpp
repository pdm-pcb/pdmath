#include "pdmath/Plane.hpp"

#include "pdmath/Line.hpp"

namespace pdm {
    Plane::Plane(const Point3 &a, const Point3 &b, const Point3 &c) :
        _point{a}
    {
        Vec3 ab(b - a);
        Vec3 ac(c - a);
        _normal = ab.cross(ac);
    }
    Plane::Plane(const Point3 &point, const Vec3 &normal) :
        _point{point}, _normal{normal}
    { }

    float Plane::direction_test(const Line &bisect, const Point3 &p) const {
        Vec3 v_left = this->_normal.cross(bisect.vec());
        return v_left.dot(static_cast<Vec3>(p - this->_point));
    }
} // namespace pdm