#ifndef PDMATH_MATRIX_HPP
#define PDMATH_MATRIX_HPP

#include <array>
#include <iostream>

namespace pdm {
    class Vec3;
    class Point;

    class Mat3 {
        public:
            Mat3() :
                _elem{{0}, {0}, {0}}
            { }

            Mat3(const Point &x, const Point &y, const Point &z);
            
            Mat3(const std::array<float, 3> &x,
                 const std::array<float, 3> &y,
                 const std::array<float, 3> &z);
            
            Mat3(const float x1, const float y1, const float z1,
                 const float x2, const float y2, const float z2,
                 const float x3, const float y3, const float z3);

            Mat3 inverse();
            inline float determinant() const { return _determinant(_elem, 3); }

            float _elem[3][3];

            float *_r1 = _elem[0];
            float *_r2 = _elem[1];
            float *_r3 = _elem[2];
    
            bool operator==(const Mat3 &m) const;

            const Mat3& operator*=(const Mat3 &m);
            const Mat3& operator*=(const float lambda);
            const Mat3& operator+=(const Mat3 &m);
            const Mat3& operator-=(const Mat3 &m);
        
        private:
            float _determinant (const float mat[3][3], const size_t n) const;

            void  _cofactor(const float mat[3][3],  float cofactors[3][3],
                            const size_t excl_row,  const size_t excl_col,
                            const size_t dimension) const;
    };

    Mat3 operator*(const Mat3 &m, const Mat3 &n);
    Mat3 operator*(const Mat3 &m, const float lambda);
    Mat3 operator*(const float lambda, const Mat3 &m);
    Mat3 operator+(const Mat3 &m, const Mat3 &n);
    Mat3 operator-(const Mat3 &m, const Mat3 &n);

    Vec3 operator*(const Mat3 &m, const Vec3 &v);

    std::ostream& operator<<(std::ostream &os, const Mat3 &m);
} // namespace pdm

#endif // PDMATH_MATRIX_HPP