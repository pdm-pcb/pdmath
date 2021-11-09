#include "pdmath/BSphere.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/AABBox.hpp"
#include "pdmath/OBBox.hpp"

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
        clamp(box.x_interval(), _center._x),
        clamp(box.y_interval(), _center._y),
        clamp(box.z_interval(), _center._z),
        1.0f);

    return collides(center_clamped);
}

bool BSphere::collides(const OBBox &box) const {
    Point4 center_clamped = box.to_local() * _center;
    center_clamped._x = clamp(box.x_interval(), center_clamped._x);
    center_clamped._y = clamp(box.y_interval(), center_clamped._y);
    center_clamped._z = clamp(box.z_interval(), center_clamped._z);
    center_clamped *= box.to_world();

    return collides(center_clamped);
}

Vec4 BSphere::center_to_center(const BSphere &other) const {
    return static_cast<Vec4>(other.center()) - _center;
}

} // namespace pdm