#ifndef PDMATH_VECTOR4_HPP
#define PDMATH_VECTOR4_HPP

#include "pdmath/Point4.hpp"

namespace pdm {
    class Vec3;
    class Mat4;

    class Vec4 : public Point4 {
        public:
            Vec4() = default;
            Vec4(const float x, const float y, const float z, const float w);
            Vec4(const Vec3 &v, const float w);
            explicit Vec4(const Point4 &p);

            void  normalize();
            float length() const;
            float dot(const Vec4 &v) const;

            const Vec4& operator+=(const Vec4 &v);
            const Vec4& operator-=(const Vec4 &v);

            const Vec4& operator+=(const float scalar);
            const Vec4& operator-=(const float scalar);
            const Vec4& operator*=(const float scalar);
            const Vec4& operator/=(const float scalar);

            const Vec4& operator*=(const Mat4 &m);
    };

    Vec4 operator+(const Vec4 &v, const Vec4 &w);
    Vec4 operator-(const Vec4 &v, const Vec4 &w);

    Vec4 operator+(const Vec4 &v, const Point4 &p);
    Vec4 operator-(const Vec4 &v, const Point4 &p);
    Vec4 operator+(const Point4 &p, const Vec4 &v);
    Vec4 operator-(const Point4 &p, const Vec4 &v);

    Vec4 operator+(const Vec4 &v, const float scalar);
    Vec4 operator-(const Vec4 &v, const float scalar);
    Vec4 operator*(const Vec4 &v, const float scalar);
    Vec4 operator/(const Vec4 &v, const float scalar);

    Vec4 operator+(const float scalar, const Vec4 &v);
    Vec4 operator-(const float scalar, const Vec4 &v);
    Vec4 operator*(const float scalar, const Vec4 &v);
    Vec4 operator/(const float scalar, const Vec4 &v);
} // namespace pdm

#endif // PDMATH_VECTOR3_HPP
