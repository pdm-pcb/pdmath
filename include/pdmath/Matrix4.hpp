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
    static const Mat4 identity;

    static Point3 transform(const Point3 &point,
        const Vec3 &translation,
        const float theta_x, const float theta_y, const float theta_z,
        const Vec3 &scale,
        Vec3 &prev_translation, Mat3 &prev_rotation);

    static Point3 transform(const Point3 &point,
        const Vec3 &translation,
        const float theta_x, const float theta_y, const float theta_z,
        const Vec3 &scale, Mat4 &prev_transform);

    static Point4 transform(const Point4 &point,
        const Vec3 &translation,
        const float theta_x, const float theta_y, const float theta_z,
        const Vec3 &scale,
        Vec3 &prev_translation, Mat3 &prev_rotation);

    static Point4 transform(const Point4 &point,
        const Vec3 &translation,
        const float theta_x, const float theta_y, const float theta_z,
        const Vec3 &scale, Mat4 &prev_transform);
    
    Vec3 get_world_position() const;

    float get_x_scale() const;
    float get_y_scale() const;
    float get_z_scale() const;
    inline float determinant() const { return get_x_scale() *
                                                get_y_scale() *
                                                get_z_scale();}

    Vec3 get_x_vec() const;

    Vec3 get_x_unit_vector() const;
    Vec3 get_y_unit_vector() const;
    Vec3 get_z_unit_vector() const;

    Mat4 inverted() const;
    Mat4 inverted_trs() const;
    Mat4 inverted_matt() const;
    Mat4 transposed() const;
    const Mat4& set_translation(const Vec4& v);
    const Mat4& set_translation(const Vec3& v);
    const Mat4& apply_scale(const Vec4& v);
    const Mat4& apply_scale(const Vec3& v);

    float _m[4][4];
    
    Mat4() noexcept:
        _m{{0}, {0}, {0}, {0}}
    { }

    Mat4(const Point4 &x, const Point4 &y,
         const Point4 &z, const Point4 &w) noexcept;
    
    Mat4(const std::array<float, 4> &x,
         const std::array<float, 4> &y,
         const std::array<float, 4> &z,
         const std::array<float, 4> &w) noexcept;
    
    Mat4(const float x1, const float y1, const float z1, const float w1,
         const float x2, const float y2, const float z2, const float w2,
         const float x3, const float y3, const float z3, const float w3,
         const float x4, const float y4, const float z4, const float w4)
         noexcept;

    explicit Mat4(const Mat3 &m) noexcept;

    bool operator==(const Mat4 &m) const;

    const Mat4& operator*=(const Mat4 &m);
    const Mat4& operator*=(const float scalar);
    const Mat4& operator+=(const Mat4 &m);
    const Mat4& operator-=(const Mat4 &m);
};

Mat4 operator*(const Mat4 &m, const Mat4 &n);
Mat4 operator+(const Mat4 &m, const Mat4 &n);
Mat4 operator-(const Mat4 &m, const Mat4 &n);

Mat4 operator*(const Mat4 &m, const float scalar);
Mat4 operator*(const float scalar, const Mat4 &m);

Point4 operator*(const Mat4 &m, const Point4 &p);
Vec4   operator*(const Mat4 &m, const Vec4 &v);
Point3 operator*(const Mat4 &m, const Point3 &p);
Vec3   operator*(const Mat4 &m, const Vec3 &v);

std::ostream& operator<<(std::ostream &os, const Mat4 &m);
} // namespace pdm

#endif // PDMATH_MATRIX4_HPP