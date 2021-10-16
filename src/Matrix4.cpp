#include "pdmath/Matrix4.hpp"

#include "pdmath/Vector4.hpp"
#include "pdmath/Point4.hpp"

#include <iomanip>

namespace pdm {
    Mat4::Mat4(const Point4 &x, const Point4 &y,
               const Point4 &z, const Point4 &w) :
        _elem{{x._x, y._x, z._x, w._x},
              {x._y, y._y, z._y, w._y},
              {x._z, y._z, z._z, w._z},
              {x._w, y._w, z._w, w._w}}
    { }

    Mat4::Mat4(const std::array<float, 4> &x,
               const std::array<float, 4> &y,
               const std::array<float, 4> &z,
               const std::array<float, 4> &w) :
        _elem{{x[0], y[0], z[0], w[0]},
              {x[1], y[1], z[0], w[0]},
              {x[2], y[2], z[2], w[2]},
              {x[3], y[3], z[3], w[3]}}
    { }
    
    Mat4::Mat4(const float x1, const float y1, const float z1, const float w1,
               const float x2, const float y2, const float z2, const float w2,
               const float x3, const float y3, const float z3, const float w3,
               const float x4, const float y4, const float z4, const float w4) :
        _elem{{x1, y1, z1, w1},
              {x2, y2, z2, w2},
              {x3, y3, z3, w3},
              {x4, y4, z4, w4}}
    { }

    Mat4 Mat4::transpose() const {
        return Mat4(_r1[0], _r2[0], _r3[0], _r4[0],
                    _r1[1], _r2[1], _r3[1], _r4[1],
                    _r1[2], _r2[2], _r3[2], _r4[2],
                    _r1[3], _r2[3], _r3[3], _r4[3]);
    }

    const Mat4& Mat4::set_translate(const Vec4& t) {
        _r1[3] = t._x;
        _r2[3] = t._y;
        _r3[3] = t._z;
        _r4[3] = t._w;

        return *this;
    }

    bool Mat4::operator==(const Mat4 &m) const {
        if(this == &m) {
            return true;
        }
    
        return _r1[0] == m._r1[0] &&
               _r2[0] == m._r2[0] &&
               _r3[0] == m._r3[0] &&
               _r4[0] == m._r4[0] &&
               _r1[1] == m._r1[1] &&
               _r2[1] == m._r2[1] &&
               _r3[1] == m._r3[1] &&
               _r4[1] == m._r4[1] &&
               _r1[2] == m._r1[2] &&
               _r2[2] == m._r2[2] &&
               _r3[2] == m._r3[2] &&
               _r4[2] == m._r4[2] &&
               _r1[3] == m._r1[3] &&
               _r2[3] == m._r2[3] &&
               _r3[3] == m._r3[3] &&
               _r4[3] == m._r4[3];
    }

    const Mat4& Mat4::operator*=(const Mat4 &m) {
        float x1 = (_r1[0] * m._r1[0]) +
                   (_r1[1] * m._r2[0]) +
                   (_r1[2] * m._r3[0]) +
                   (_r1[3] * m._r4[0]);    
        float y1 = (_r1[0] * m._r1[1]) +
                   (_r1[1] * m._r2[1]) +
                   (_r1[2] * m._r3[1]) +
                   (_r1[3] * m._r4[1]);
        float z1 = (_r1[0] * m._r1[2]) +
                   (_r1[1] * m._r2[2]) +
                   (_r1[2] * m._r3[2]) +
                   (_r1[3] * m._r4[2]);
        float w1 = (_r1[0] * m._r1[3]) +
                   (_r1[1] * m._r2[3]) +
                   (_r1[2] * m._r3[3]) +
                   (_r1[3] * m._r4[3]);

        float x2 = (_r2[0] * m._r1[0]) +
                   (_r2[1] * m._r2[0]) +
                   (_r2[2] * m._r3[0]) +
                   (_r2[3] * m._r4[0]);    
        float y2 = (_r2[0] * m._r1[1]) +
                   (_r2[1] * m._r2[1]) +
                   (_r2[2] * m._r3[1]) +
                   (_r2[3] * m._r4[1]);
        float z2 = (_r2[0] * m._r1[2]) +
                   (_r2[1] * m._r2[2]) +
                   (_r2[2] * m._r3[2]) +
                   (_r2[3] * m._r4[2]);
        float w2 = (_r2[0] * m._r1[3]) +
                   (_r2[1] * m._r2[3]) +
                   (_r2[2] * m._r3[3]) +
                   (_r2[3] * m._r4[3]);

        float x3 = (_r3[0] * m._r1[0]) +
                   (_r3[1] * m._r2[0]) +
                   (_r3[2] * m._r3[0]) +
                   (_r3[3] * m._r4[0]);    
        float y3 = (_r3[0] * m._r1[1]) +
                   (_r3[1] * m._r2[1]) +
                   (_r3[2] * m._r3[1]) +
                   (_r3[3] * m._r4[1]);
        float z3 = (_r3[0] * m._r1[2]) +
                   (_r3[1] * m._r2[2]) +
                   (_r3[2] * m._r3[2]) +
                   (_r3[3] * m._r4[2]);
        float w3 = (_r3[0] * m._r1[3]) +
                   (_r3[1] * m._r2[3]) +
                   (_r3[2] * m._r3[3]) +
                   (_r3[3] * m._r4[3]);

        float x4 = (_r4[0] * m._r1[0]) +
                   (_r4[1] * m._r2[0]) +
                   (_r4[2] * m._r3[0]) +
                   (_r4[3] * m._r4[0]);    
        float y4 = (_r4[0] * m._r1[1]) +
                   (_r4[1] * m._r2[1]) +
                   (_r4[2] * m._r3[1]) +
                   (_r4[3] * m._r4[1]);
        float z4 = (_r4[0] * m._r1[2]) +
                   (_r4[1] * m._r2[2]) +
                   (_r4[2] * m._r3[2]) +
                   (_r4[3] * m._r4[2]);
        float w4 = (_r4[0] * m._r1[3]) +
                   (_r4[1] * m._r2[3]) +
                   (_r4[2] * m._r3[3]) +
                   (_r4[3] * m._r4[3]);

        _r1[0] = x1;
        _r2[0] = x2;
        _r3[0] = x3;
        _r4[0] = x4;

        _r1[1] = y1;
        _r2[1] = y2;
        _r3[1] = y3;
        _r4[1] = y4;

        _r1[2] = z1;
        _r2[2] = z2;
        _r3[2] = z3;
        _r4[2] = z4;

        _r1[3] = w1;
        _r2[3] = w2;
        _r3[3] = w3;
        _r4[3] = w4;

        return *this;
    }

    const Mat4& Mat4::operator*=(const float scalar) {
        this->_r1[0] *= scalar;
        this->_r2[0] *= scalar;
        this->_r3[0] *= scalar;
        this->_r4[0] *= scalar;

        this->_r1[1] *= scalar;
        this->_r2[1] *= scalar;
        this->_r3[1] *= scalar;
        this->_r4[1] *= scalar;

        this->_r1[2] *= scalar;
        this->_r2[2] *= scalar;
        this->_r3[2] *= scalar;
        this->_r4[2] *= scalar;

        this->_r1[3] *= scalar;
        this->_r2[3] *= scalar;
        this->_r3[3] *= scalar;
        this->_r4[3] *= scalar;

        return *this;
    }

    const Mat4& Mat4::operator+=(const Mat4 &m) {
        this->_r1[0] += m._r1[0];
        this->_r2[0] += m._r2[0];
        this->_r3[0] += m._r3[0];
        this->_r4[0] += m._r4[0];

        this->_r1[1] += m._r1[1];
        this->_r2[1] += m._r2[1];
        this->_r3[1] += m._r3[1];
        this->_r4[1] += m._r4[1];

        this->_r1[2] += m._r1[2];
        this->_r2[2] += m._r2[2];
        this->_r3[2] += m._r3[2];
        this->_r4[2] += m._r4[2];

        this->_r1[3] += m._r1[3];
        this->_r2[3] += m._r2[3];
        this->_r3[3] += m._r3[3];
        this->_r4[3] += m._r4[3];

        return *this;
    }

    const Mat4& Mat4::operator-=(const Mat4 &m) {
        this->_r1[0] -= m._r1[0];
        this->_r2[0] -= m._r2[0];
        this->_r3[0] -= m._r3[0];
        this->_r4[0] -= m._r4[0];

        this->_r1[1] -= m._r1[1];
        this->_r2[1] -= m._r2[1];
        this->_r3[1] -= m._r3[1];
        this->_r4[1] -= m._r4[1];

        this->_r1[2] -= m._r1[2];
        this->_r2[2] -= m._r2[2];
        this->_r3[2] -= m._r3[2];
        this->_r4[2] -= m._r4[2];

        this->_r1[3] -= m._r1[3];
        this->_r2[3] -= m._r2[3];
        this->_r3[3] -= m._r3[3];
        this->_r4[3] -= m._r4[3];

        return *this;
    }

    Mat4 operator*(const Mat4 &m, const Mat4 &n) {
        float x1 = (m._r1[0] * n._r1[0]) +
                   (m._r1[1] * n._r2[0]) +
                   (m._r1[2] * n._r3[0]) +
                   (m._r1[3] * n._r4[0]);    
        float y1 = (m._r1[0] * n._r1[1]) +
                   (m._r1[1] * n._r2[1]) +
                   (m._r1[2] * n._r3[1]) +
                   (m._r1[3] * n._r4[1]);
        float z1 = (m._r1[0] * n._r1[2]) +
                   (m._r1[1] * n._r2[2]) +
                   (m._r1[2] * n._r3[2]) +
                   (m._r1[3] * n._r4[2]);
        float w1 = (m._r1[0] * n._r1[3]) +
                   (m._r1[1] * n._r2[3]) +
                   (m._r1[2] * n._r3[3]) +
                   (m._r1[3] * n._r4[3]);

        float x2 = (m._r2[0] * n._r1[0]) +
                   (m._r2[1] * n._r2[0]) +
                   (m._r2[2] * n._r3[0]) +
                   (m._r2[3] * n._r4[0]);    
        float y2 = (m._r2[0] * n._r1[1]) +
                   (m._r2[1] * n._r2[1]) +
                   (m._r2[2] * n._r3[1]) +
                   (m._r2[3] * n._r4[1]);
        float z2 = (m._r2[0] * n._r1[2]) +
                   (m._r2[1] * n._r2[2]) +
                   (m._r2[2] * n._r3[2]) +
                   (m._r2[3] * n._r4[2]);
        float w2 = (m._r2[0] * n._r1[3]) +
                   (m._r2[1] * n._r2[3]) +
                   (m._r2[2] * n._r3[3]) +
                   (m._r2[3] * n._r4[3]);

        float x3 = (m._r3[0] * n._r1[0]) +
                   (m._r3[1] * n._r2[0]) +
                   (m._r3[2] * n._r3[0]) +
                   (m._r3[3] * n._r4[0]);    
        float y3 = (m._r3[0] * n._r1[1]) +
                   (m._r3[1] * n._r2[1]) +
                   (m._r3[2] * n._r3[1]) +
                   (m._r3[3] * n._r4[1]);
        float z3 = (m._r3[0] * n._r1[2]) +
                   (m._r3[1] * n._r2[2]) +
                   (m._r3[2] * n._r3[2]) +
                   (m._r3[3] * n._r4[2]);
        float w3 = (m._r3[0] * n._r1[3]) +
                   (m._r3[1] * n._r2[3]) +
                   (m._r3[2] * n._r3[3]) +
                   (m._r3[3] * n._r4[3]);

        float x4 = (m._r4[0] * n._r1[0]) +
                   (m._r4[1] * n._r2[0]) +
                   (m._r4[2] * n._r3[0]) +
                   (m._r4[3] * n._r4[0]);    
        float y4 = (m._r4[0] * n._r1[1]) +
                   (m._r4[1] * n._r2[1]) +
                   (m._r4[2] * n._r3[1]) +
                   (m._r4[3] * n._r4[1]);
        float z4 = (m._r4[0] * n._r1[2]) +
                   (m._r4[1] * n._r2[2]) +
                   (m._r4[2] * n._r3[2]) +
                   (m._r4[3] * n._r4[2]);
        float w4 = (m._r4[0] * n._r1[3]) +
                   (m._r4[1] * n._r2[3]) +
                   (m._r4[2] * n._r3[3]) +
                   (m._r4[3] * n._r4[3]);

        return Mat4(x1, y1, z1, w1,
                    x2, y2, z2, w2,
                    x3, y3, z3, w3,
                    x4, y4, z4, w4);
    }

    Mat4 operator*(const Mat4 &m, const float scalar) {
        return Mat4(m._r1[0] * scalar,
                    m._r1[1] * scalar,
                    m._r1[2] * scalar,
                    m._r1[3] * scalar,

                    m._r2[0] * scalar,
                    m._r2[1] * scalar,
                    m._r2[2] * scalar,
                    m._r2[3] * scalar,

                    m._r3[0] * scalar,
                    m._r3[1] * scalar,
                    m._r3[2] * scalar,
                    m._r3[3] * scalar,

                    m._r4[0] * scalar,
                    m._r4[1] * scalar,
                    m._r4[2] * scalar,
                    m._r4[3] * scalar);
    }

    Mat4 operator*(const float scalar, const Mat4 &m) {
        return m * scalar;
    }

    Mat4 operator+(const Mat4 &m, const Mat4 &n) {
        return Mat4(m._r1[0] + n._r1[0],
                    m._r1[1] + n._r1[1],
                    m._r1[2] + n._r1[2],
                    m._r1[3] + n._r1[3],

                    m._r2[0] + n._r2[0],
                    m._r2[1] + n._r2[1],
                    m._r2[2] + n._r2[2],
                    m._r2[3] + n._r2[3],
                    
                    m._r3[0] + n._r3[0],
                    m._r3[1] + n._r3[1],
                    m._r3[2] + n._r3[2],
                    m._r3[3] + n._r3[3],
                    
                    m._r4[0] + n._r4[0],
                    m._r4[1] + n._r4[1],
                    m._r4[2] + n._r4[2],
                    m._r4[3] + n._r4[3]);
    }

    Mat4 operator-(const Mat4 &m, const Mat4 &n) {
        return Mat4(m._r1[0] - n._r1[0],
                    m._r1[1] - n._r1[1],
                    m._r1[2] - n._r1[2],
                    m._r1[3] - n._r1[3],

                    m._r2[0] - n._r2[0],
                    m._r2[1] - n._r2[1],
                    m._r2[2] - n._r2[2],
                    m._r2[3] - n._r2[3],
                    
                    m._r3[0] - n._r3[0],
                    m._r3[1] - n._r3[1],
                    m._r3[2] - n._r3[2],
                    m._r3[3] - n._r3[3],
                    
                    m._r4[0] - n._r4[0],
                    m._r4[1] - n._r4[1],
                    m._r4[2] - n._r4[2],
                    m._r4[3] - n._r4[3]);
    }

    Point4 operator*(const Mat4 &m,   const Point4 &p) {
        return Point4((m._r1[0] * p._x) +
                      (m._r1[1] * p._y) +
                      (m._r1[2] * p._z) +
                      (m._r1[3] * p._w),
                      (m._r2[0] * p._x) +
                      (m._r2[1] * p._y) +
                      (m._r2[2] * p._z) +
                      (m._r2[3] * p._w),
                      (m._r3[0] * p._x) +
                      (m._r3[1] * p._y) +
                      (m._r3[2] * p._z) +
                      (m._r3[3] * p._w),
                      (m._r4[0] * p._x) +
                      (m._r4[1] * p._y) +
                      (m._r4[2] * p._z) +
                      (m._r4[3] * p._w));
    }

    Vec4 operator*(const Mat4 &m,   const Vec4 &v) {
        return Vec4((m._r1[0] * v._x) +
                    (m._r1[1] * v._y) +
                    (m._r1[2] * v._z) +
                    (m._r1[3] * v._w), 
                    (m._r2[0] * v._x) +
                    (m._r2[1] * v._y) +
                    (m._r2[2] * v._z) +
                    (m._r2[3] * v._w),
                    (m._r3[0] * v._x) +
                    (m._r3[1] * v._y) +
                    (m._r3[2] * v._z) +
                    (m._r3[3] * v._w),
                    (m._r4[0] * v._x) +
                    (m._r4[1] * v._y) +
                    (m._r4[2] * v._z) +
                    (m._r4[3] * v._w));
    }

    std::ostream& operator<<(std::ostream &os, const Mat4 &m) {
        os << std::fixed << std::setprecision(Point4::_output_precision)
           << "[" << m._r1[0] << ", " << m._r1[1] << ", "
           << m._r1[2] << ", " << m._r1[3] << "]\n"
           << "[" << m._r2[0] << ", " << m._r2[1] << ", "
           << m._r2[2] << ", " << m._r2[3] << "]\n"
           << "[" << m._r3[0] << ", " << m._r3[1] << ", "
           << m._r3[2] << ", " << m._r3[3] << "]\n"
           << "[" << m._r4[0] << ", " << m._r4[1] << ", "
           << m._r4[2] << ", " << m._r4[3] << "]";
        return os;
    }
} // namespace pdm