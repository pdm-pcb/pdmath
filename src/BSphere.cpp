#include "pdmath/BSphere.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/AABBox.hpp"
#include "pdmath/OBBox.hpp"
#include "pdmath/Plane.hpp"

namespace pdm{

bool BSphere::collides(const BSphere &other) const {
    return ((scale() * _radius) + (other.scale() * other.radius())) >=
            center_to_center(other).length();
}

bool BSphere::collides(const Point4 &point) const {
    return (static_cast<Vec4>(point) - _center).length() < _radius;
}

bool BSphere::collides(const AABBox &box) const {
    Point4 center_clamped(
        clamp(_center._x, box.x_interval()),
        clamp(_center._y, box.y_interval()),
        clamp(_center._z, box.z_interval()));

    return collides(center_clamped);
}

bool BSphere::collides(const OBBox &box) const {
    Point4 center_clamped = box.to_local() * _center;
    center_clamped._x = clamp(center_clamped._x, box.x_interval());
    center_clamped._y = clamp(center_clamped._y, box.y_interval());
    center_clamped._z = clamp(center_clamped._z, box.z_interval());
    center_clamped *= box.to_world();

    return collides(center_clamped);
}

bool BSphere::collides(const Plane &plane) const {
    Vec4 c_minus_p(static_cast<Vec4>(_center) - plane._p);
    // std::cout << "\nC-P0: " << c_minus_p << std::endl;
    // std::cout << "||n||: " << plane._n.length() << std::endl;

    float distance = std::abs(c_minus_p.dot(plane._n));
    // std::cout << "dist : " << distance << std::endl;
    distance /= plane._n.length();
    // std::cout << "dist': " << distance << std::endl;
    // std::cout << "r: " << _radius << std::endl;

    return distance < _radius;
}

bool BSphere::above_plane(const Plane &plane) const {
    Vec4 c_minus_p(static_cast<Vec4>(_center) - plane._p);
    // std::cout << "\nC-P0: " << c_minus_p << std::endl;

    float distance = c_minus_p.dot(plane._n);
    // std::cout << "dist : " << distance << std::endl;

    return distance > 0.0f;
}

Vec4 BSphere::center_to_center(const BSphere &other) const {
    return static_cast<Vec4>(other.center()) - _center;
}

} // namespace pdm