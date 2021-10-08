#ifndef PDMATH_VECTOR_HPP
#define PDMATH_VECTOR_HPP

#include "pdmath/Point.hpp"

namespace pdm {
    class Vec3 : public Point {
        public:
            Vec3() = default;
            Vec3(const float x, const float y, const float z);
            Vec3(const Point &p, const Point &s);

            void  normalize();

            float length() const;
            float dot(const Vec3 &other) const;
            Vec3  cross(const Vec3 &other) const;
            Vec3  project_onto(const Vec3 &other) const;
            Vec3  projection_perp(const Vec3 &other) const;

            bool  is_collinear(const Vec3 &other) const;
            bool  is_perpendicular(const Vec3 &other) const;
    };
} // namespace pdm

#endif // PDMATH_VECTOR_HPP
