#include "pdmath/Matrix.hpp"

namespace pdm {
    Mat3::Mat3(const Vec3 &x, const Vec3 &y, const Vec3 &z) :
        _x{x}, _y{y}, _z{z}
    { }
} // namespace pdm