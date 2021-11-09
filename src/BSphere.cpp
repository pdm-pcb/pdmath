#include "pdmath/BSphere.hpp"

#include "pdmath/Vector4.hpp"
#include "pdmath/AABBox.hpp"
#include "pdmath/util.hpp"

namespace pdm{

bool BSphere::collides(const BSphere &other) const {
    return ((scale() * _radius) + (other.scale() * other.radius())) >=
            center_to_center(other).length();
}

bool BSphere::collides(const Point4 &point) const {
    return (static_cast<Vec4>(point) - _center).length() < _radius;
}

bool BSphere::collides(const AABBox &other) const {
    Point4 center_clamped(
        clamp(other.x_interval(), _center._x),
        clamp(other.y_interval(), _center._y),
        clamp(other.z_interval(), _center._z),
        1.0f);

    return collides(center_clamped);
}

Vec4 BSphere::center_to_center(const BSphere &other) const {
    return static_cast<Vec4>(other.center()) - _center;
}

} // namespace pdm