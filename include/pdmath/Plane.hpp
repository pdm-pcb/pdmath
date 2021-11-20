#ifndef PDMATH_PLANE_HPP
#define PDMATH_PLANE_HPP

#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"

namespace pdm {

class Line;

class Plane {
public:
    Plane() = default;
    Plane(const Point3 &a, const Point3 &b, const Point3 &c);
    Plane(const Point3 &point, const Vec3 &normal);

    float direction_test(const Line &bisect, const Point3 &p) const;

    Point3 point()  const { return _point; }
    Vec3   normal() const { return _normal; }

private:
    Point3 _point;
    Vec3   _normal;
};
} // namespace pdm

#endif // PDMATH_PLANE_HPP