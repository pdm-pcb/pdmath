#include "pdmath/Point.hpp"

#include <iomanip>

namespace pdm {
    point::point(const float x, const float y, const float z) :
        _x{x}, _y{y}, _z{z}
    { }

    point point::operator-(const point &p) {
        return point(_x - p._x,
                     _y - p._y,
                     _z - p._z);
    }

    std::ostream& operator<<(std::ostream &os, const point &p) {
        os << std::fixed << std::setprecision(2) << "("
           << p._x << ", "
           << p._y << ", "
           << p._z << ")";
        return os;
    }
}
