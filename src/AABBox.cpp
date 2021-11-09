#include "pdmath/AABBox.hpp"

#include "pdmath/util.hpp"
#include "pdmath/BSphere.hpp"

namespace pdm {

bool AABBox::collides(const AABBox &other) const {
    bool x_overlap = (x_interval().second >= other.x_interval().first) &&
                     (x_interval().first  <= other.x_interval().second);
    bool y_overlap = (y_interval().second >= other.y_interval().first) &&
                     (y_interval().first  <= other.y_interval().second);
    bool z_overlap = (z_interval().second >= other.z_interval().first) &&
                     (z_interval().first  <= other.z_interval().second);

    return x_overlap && y_overlap && z_overlap;
}

bool AABBox::collides(const BSphere &sphere) const {
    Point4 center_clamped(
        clamp(x_interval(), sphere.center()._x),
        clamp(y_interval(), sphere.center()._y),
        clamp(z_interval(), sphere.center()._z),
        1.0f);

    return sphere.collides(center_clamped);
}

bool AABBox::collides(const Point4 &point) const {
    return _min._x < point._x && point._x < _max._x &&
           _min._y < point._y && point._y < _max._y &&
           _min._z < point._z && point._z < _max._z;
}

std::pair<float, float> AABBox::x_interval() const {
    return std::pair<float, float>(_min._x, _max._x);
}

std::pair<float, float> AABBox::y_interval() const {
    return std::pair<float, float>(_min._y, _max._y);
}

std::pair<float, float> AABBox::z_interval() const {
    return std::pair<float, float>(_min._z, _max._z);
}

}