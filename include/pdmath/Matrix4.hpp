#ifndef PDMATH_MATRIX4_HPP
#define PDMATH_MATRIX4_HPP

#include <pdmath/Vector3.hpp>
#include <pdmath/Matrix3.hpp>

#include <array>
#include <iostream>

namespace pdm {
    class Point4;
    class Vec4;

    class Mat4 {
        public:
            Mat4() :
                _elem{{0}, {0}, {0}, {0}}
            { }

            Mat4(const Point4 &x, const Point4 &y,
                 const Point4 &z, const Point4 &w);
            
            Mat4(const std::array<float, 4> &x,
                 const std::array<float, 4> &y,
                 const std::array<float, 4> &z,
                 const std::array<float, 4> &w);
            
            Mat4(const float x1, const float y1, const float z1, const float w1,
                 const float x2, const float y2, const float z2, const float w2,
                 const float x3, const float y3, const float z3, const float w3,
                 const float x4, const float y4, const float z4, const float w4);

            explicit Mat4(const Mat3 &m);

            static Point4 transform(const Point4 &point,
                const Vec3 &translation,
                const float theta_x, const float theta_y, const float theta_z,
                const Vec3 &scale,
                Vec3 &prev_translation, Mat3 &prev_rotation);

            static Point4 transform(const Point4 &point,
                const Vec3 &translation,
                const float theta_x, const float theta_y, const float theta_z,
                const Vec3 &scale, Mat4 &prev_transform);
            
            Vec4 get_world_position() const;

            float get_x_scale() const;
            float get_y_scale() const;
            float get_z_scale() const;
            inline float determinant() const { return get_x_scale() *
                                                      get_y_scale() *
                                                      get_z_scale();}

            Vec3 get_x_unit_vector() const;
            Vec3 get_y_unit_vector() const;
            Vec3 get_z_unit_vector() const;

            Mat4 inverse() const;
            Mat4 transpose() const;
            const Mat4& set_translation(const Vec4& v);
            const Mat4& set_translation(const Vec3& v);
            const Mat4& apply_scale(const Vec4& v);
            const Mat4& apply_scale(const Vec3& v);

            float _elem[4][4];
    
            bool operator==(const Mat4 &m) const;

            const Mat4& operator*=(const Mat4 &m);
            const Mat4& operator*=(const float scalar);
            const Mat4& operator+=(const Mat4 &m);
            const Mat4& operator-=(const Mat4 &m);
    };

    Mat4 operator*(const Mat4 &m, const Mat4 &n);
    Mat4 operator*(const Mat4 &m, const float scalar);
    Mat4 operator*(const float scalar, const Mat4 &m);
    Mat4 operator+(const Mat4 &m, const Mat4 &n);
    Mat4 operator-(const Mat4 &m, const Mat4 &n);

    Point4 operator*(const Mat4 &m,   const Point4 &p);
    Vec4   operator*(const Mat4 &m,   const Vec4 &v);

    std::ostream& operator<<(std::ostream &os, const Mat4 &m);

    static const Mat4 Identity4(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);
} // namespace pdm

#endif // PDMATH_MATRIX3_HPP