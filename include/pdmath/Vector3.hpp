#ifndef PDMATH_VECTOR3_HPP
#define PDMATH_VECTOR3_HPP

#include "pdmath/Point3.hpp"

namespace pdm {
    class Vec3 : public Point3 {
        public:
            Vec3() = default;
            Vec3(const float x, const float y, const float z);
            explicit Vec3(const Point3 &p);

            static const Vec3 zero;
            static const Vec3 one;

            float length() const;
            float dot(const Vec3 &v) const;

            Vec3  normalized() const;
            Vec3  cross(const Vec3 &v) const;
            Vec3  project_onto(const Vec3 &v) const;
            Vec3  projection_perp(const Vec3 &v) const;

            bool  is_collinear(const Vec3 &v) const;
            bool  is_perpendicular(const Vec3 &v) const;

            const Vec3& operator+=(const Vec3 &p);
            const Vec3& operator-=(const Vec3 &p);

            const Vec3& operator+=(const float scalar);
            const Vec3& operator-=(const float scalar);
            const Vec3& operator*=(const float scalar);
            const Vec3& operator/=(const float scalar);

            const Vec3& operator+=(const Point3 &p);
            const Vec3& operator-=(const Point3 &p);
            const Vec3& operator*=(const Mat3 &m);
    };

    Vec3 operator+(const Vec3 &v, const Vec3 &w);
    Vec3 operator-(const Vec3 &v, const Vec3 &w);

    Vec3 operator+(const Vec3 &v, const Point3 &p);
    Vec3 operator-(const Vec3 &v, const Point3 &p);
    Vec3 operator+(const Point3 &p, const Vec3 &v);
    Vec3 operator-(const Point3 &p, const Vec3 &v);

    Vec3 operator+(const Vec3 &v, const float scalar);
    Vec3 operator-(const Vec3 &v, const float scalar);
    Vec3 operator*(const Vec3 &v, const float scalar);
    Vec3 operator/(const Vec3 &v, const float scalar);

    Vec3 operator+(const float scalar, const Vec3 &v);
    Vec3 operator-(const float scalar, const Vec3 &v);
    Vec3 operator*(const float scalar, const Vec3 &v);
    Vec3 operator/(const float scalar, const Vec3 &v);
} // namespace pdm

#endif // PDMATH_VECTOR3_HPP
