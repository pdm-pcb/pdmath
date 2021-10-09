#ifndef PDMATH_MATRIX_HPP
#define PDMATH_MATRIX_HPP

#include "pdmath/Vector.hpp"

namespace pdm {
    class Mat3 {
        public:
            Mat3() = default;
            Mat3(const Vec3 &x, const Vec3 &y, const Vec3 &z);

            Vec3 _x;
            Vec3 _y;
            Vec3 _z;
    };
} // namespace pdm

#endif // PDMATH_MATRIX_HPP