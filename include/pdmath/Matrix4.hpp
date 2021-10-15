#ifndef PDMATH_MATRIX4_HPP
#define PDMATH_MATRIX4_HPP

#include <array>
#include <iostream>

namespace pdm {
    class Point4;
    class Vec4;

    class Mat4 {
        public:
            Mat4() :
                _elem{{0}, {0}, {0}}
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

            Mat4 transpose() const;

            float _elem[4][4];

            float *_r1 = _elem[0];
            float *_r2 = _elem[1];
            float *_r3 = _elem[2];
            float *_r4 = _elem[3];
    
            bool operator==(const Mat4 &m) const;

            const Mat4& operator*=(const Mat4 &m);
            const Mat4& operator*=(const float lambda);
            const Mat4& operator+=(const Mat4 &m);
            const Mat4& operator-=(const Mat4 &m);
    };

    Mat4 operator*(const Mat4 &m, const Mat4 &n);
    Mat4 operator*(const Mat4 &m, const float lambda);
    Mat4 operator*(const float lambda, const Mat4 &m);
    Mat4 operator+(const Mat4 &m, const Mat4 &n);
    Mat4 operator-(const Mat4 &m, const Mat4 &n);

    Point4 operator*(const Mat4 &m,   const Point4 &p);
    Point4 operator*(const Point4 &p, const Mat4 &m);
    Vec4   operator*(const Mat4 &m,   const Vec4 &v);
    Vec4   operator*(const Vec4 &v,   const Mat4 &m);

    std::ostream& operator<<(std::ostream &os, const Mat4 &m);
} // namespace pdm

#endif // PDMATH_MATRIX3_HPP