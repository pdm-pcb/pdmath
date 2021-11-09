#include "pdmath/AABBox.hpp"

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