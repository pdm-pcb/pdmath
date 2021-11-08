#ifndef PDMATH_QUATERNION_HPP
#define PDMATH_QUATERNION_HPP

#include "pdmath/Vector3.hpp"

#include <iostream>

namespace pdm {
    class Quat {
        public:
            Quat() noexcept = default;
            Quat(float theta, Vec3 axis) noexcept;
            Quat(float theta, float x, float y, float z) noexcept;

            Quat inverted();
            Quat normalized();
            float length();

            static const Quat identity;

            float _w;
            Vec3  _v;

            bool operator==(const Quat &q) const;
            const Quat& operator*=(const Quat &q);
    };

    Quat operator*(const Quat &q, const Quat &p);

    std::ostream& operator<<(std::ostream &os, const Quat &q);
} // namespace pdm

#endif // PDMATH_QUATERNION_HPP