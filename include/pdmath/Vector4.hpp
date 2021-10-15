#ifndef PDMATH_VECTOR4_HPP
#define PDMATH_VECTOR4_HPP

#include "pdmath/Point4.hpp"

namespace pdm {
    class Vec4 : public Point4 {
        public:
            Vec4() = default;
            Vec4(const float x, const float y, const float z, const float w);
            explicit Vec4(const Point4 &p);

            void  normalize();
            float length() const;
            float dot(const Vec4 &v) const;
    };
} // namespace pdm

#endif // PDMATH_VECTOR3_HPP
