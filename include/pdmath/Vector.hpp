#ifndef PDMATH_VECTOR_HPP
#define PDMATH_VECTOR_HPP

#include "pdmath/Point.hpp"

namespace pdm {
    class Vec3 : public Point3 {
        public:
            Vec3() = default;
            Vec3(const float x, const float y, const float z);
            explicit Vec3(const Point3 &p);

            void  normalize();

            float length() const;
            float dot(const Vec3 &v) const;
            Vec3  cross(const Vec3 &v) const;
            Vec3  project_onto(const Vec3 &v) const;
            Vec3  projection_perp(const Vec3 &v) const;

            bool  is_collinear(const Vec3 &v) const;
            bool  is_perpendicular(const Vec3 &v) const;
    };

    class Vec4 : public Point3 {
        public:
            Vec4() = default;
    };
} // namespace pdm

#endif // PDMATH_VECTOR_HPP
