#include "pdmath/BSphere.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/AABBox.hpp"
#include "pdmath/OBBox.hpp"
#include "pdmath/Plane.hpp"
#include "pdmath/Line.hpp"

namespace pdm{

bool BSphere::collides(const BSphere &other) const {
    Vec3 centers(_center_world - other.center_world());
    float radii_sum = scaled_radius() + other.scaled_radius();
    return centers.dot(centers) < radii_sum * radii_sum;
}

bool BSphere::collides(const Point3 &point) const {
    Vec3 p_minus_c(point - _center);
    return p_minus_c.dot(p_minus_c) < _scaled_radius * _scaled_radius;
}

bool BSphere::collides(const Point4 &point) const {
    Vec4 p_minus_c(point - _center);
    return p_minus_c.dot(p_minus_c) < _scaled_radius * _scaled_radius;
}

bool BSphere::collides(const AABBox &box) const {
return collides(center_clamped(box));
}

bool BSphere::collides(const OBBox &box) const {
    return collides(box.to_world(center_clamped(box)));
}

bool BSphere::collides(const Plane &plane) const {
    Vec3 c_minus_p(_center - plane.point());
    float distance = std::abs(c_minus_p.dot(plane.normal()));
    distance /= plane.normal().length();

    return distance < _radius;
}

bool BSphere::collides(const Line &line) const {
    Vec3 c_minus_p = _center_world - line.point_a();
    float t = (line.vec().dot(c_minus_p)) / line.vec().dot(line.vec());

    if(t < 0.0f) {
        t = 0.0f;
    }

    Point3 q = line.point_a() + t * line.vec();

    Vec3 c_minus_q = _center_world - q;

    return c_minus_q.dot(c_minus_q) < _scaled_radius * _scaled_radius;
}

bool BSphere::above_plane(const Plane &plane) const {
    Vec3 c_minus_p(_center - plane.point());
    float distance = c_minus_p.dot(plane.normal());

    return distance > 0.0f;
}

Vec3 BSphere::center_to_center(const BSphere &other) const {
    return _center - other.center();
}

Point3 BSphere::center_clamped(const AABBox &box) const {
    return Point3(clamp(_center._x, box.x_interval()),
                  clamp(_center._y, box.y_interval()),
                  clamp(_center._z, box.z_interval()));
}

Point3 BSphere::center_clamped(const OBBox &box) const {
    Point3 center_clamped = box.to_local(_center);
    center_clamped._x = clamp(center_clamped._x, box.x_interval());
    center_clamped._y = clamp(center_clamped._y, box.y_interval());
    center_clamped._z = clamp(center_clamped._z, box.z_interval());

    return center_clamped;
}

Point3 BSphere::to_world(const Point3 &p) const {
    return _world * p;
}

Point3 BSphere::to_local(const Point3 &p) const {
    return _local * p;
}

} // namespace pdm