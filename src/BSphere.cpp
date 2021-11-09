#include "pdmath/BSphere.hpp"

#include "pdmath/Vector4.hpp"

namespace pdm{

bool BSphere::collides(const BSphere &other) const {
    return ((scale() * _radius) + (other.scale() * other.radius())) >=
            center_to_center(other).length();
}

Vec4 BSphere::center_to_center(const BSphere &other) const {
    return static_cast<Vec4>(other.center()) - _center;
}

} // namespace pdm