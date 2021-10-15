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
        return Mat4(_elem[0][0], _elem[1][0], _elem[2][0], _elem[3][0],
                    _elem[0][1], _elem[1][1], _elem[2][1], _elem[3][1],
                    _elem[0][2], _elem[1][2], _elem[2][2], _elem[3][2],
                    _elem[0][3], _elem[1][3], _elem[2][3], _elem[3][3]);
    }

    bool Mat4::operator==(const Mat4 &m) const {
        if(this == &m) {
            return true;
        }
    
        return _elem[0][0] == m._elem[0][0] &&
               _elem[1][0] == m._elem[1][0] &&
               _elem[2][0] == m._elem[2][0] &&
               _elem[3][0] == m._elem[3][0] &&
               _elem[0][1] == m._elem[0][1] &&
               _elem[1][1] == m._elem[1][1] &&
               _elem[2][1] == m._elem[2][1] &&
               _elem[3][1] == m._elem[3][1] &&
               _elem[0][2] == m._elem[0][2] &&
               _elem[1][2] == m._elem[1][2] &&
               _elem[2][2] == m._elem[2][2] &&
               _elem[3][2] == m._elem[3][2] &&
               _elem[0][3] == m._elem[0][3] &&
               _elem[1][3] == m._elem[1][3] &&
               _elem[2][3] == m._elem[2][3] &&
               _elem[3][3] == m._elem[3][3];
    }

    const Mat4& Mat4::operator*=(const Mat4 &m) {
        float x1 = (_elem[0][0] * m._elem[0][0]) +
                   (_elem[0][1] * m._elem[1][0]) +
                   (_elem[0][2] * m._elem[2][0]) +
                   (_elem[0][3] * m._elem[3][0]);
    
        float y1 = (_elem[0][0] * m._elem[0][1]) +
                   (_elem[0][1] * m._elem[1][1]) +
                   (_elem[0][2] * m._elem[2][1]) +
                   (_elem[0][3] * m._elem[3][1]);

        float z1 = (_elem[0][0] * m._elem[0][2]) +
                   (_elem[0][1] * m._elem[1][2]) +
                   (_elem[0][2] * m._elem[2][2]) +
                   (_elem[0][3] * m._elem[3][2]);

        float w1 = (_elem[0][0] * m._elem[0][3]) +
                   (_elem[0][1] * m._elem[1][3]) +
                   (_elem[0][2] * m._elem[2][3]) +
                   (_elem[0][3] * m._elem[3][3]);

        float x2 = (_elem[1][0] * m._elem[0][0]) +
                   (_elem[1][1] * m._elem[1][0]) +
                   (_elem[1][2] * m._elem[2][0]) +
                   (_elem[1][3] * m._elem[3][0]);
    
        float y2 = (_elem[1][0] * m._elem[0][1]) +
                   (_elem[1][1] * m._elem[1][1]) +
                   (_elem[1][2] * m._elem[2][1]) +
                   (_elem[1][3] * m._elem[3][1]);

        float z2 = (_elem[1][0] * m._elem[0][2]) +
                   (_elem[1][1] * m._elem[1][2]) +
                   (_elem[1][2] * m._elem[2][2]) +
                   (_elem[1][3] * m._elem[3][2]);

        float w2 = (_elem[1][0] * m._elem[0][3]) +
                   (_elem[1][1] * m._elem[1][3]) +
                   (_elem[1][2] * m._elem[2][3]) +
                   (_elem[1][3] * m._elem[3][3]);

        float x3 = (_elem[2][0] * m._elem[0][0]) +
                   (_elem[2][1] * m._elem[1][0]) +
                   (_elem[2][2] * m._elem[2][0]) +
                   (_elem[2][3] * m._elem[3][0]);
    
        float y3 = (_elem[2][0] * m._elem[0][1]) +
                   (_elem[2][1] * m._elem[1][1]) +
                   (_elem[2][2] * m._elem[2][1]) +
                   (_elem[2][3] * m._elem[3][1]);

        float z3 = (_elem[2][0] * m._elem[0][2]) +
                   (_elem[2][1] * m._elem[1][2]) +
                   (_elem[2][2] * m._elem[2][2]) +
                   (_elem[2][3] * m._elem[3][2]);

        float w3 = (_elem[2][0] * m._elem[0][3]) +
                   (_elem[2][1] * m._elem[1][3]) +
                   (_elem[2][2] * m._elem[2][3]) +
                   (_elem[2][3] * m._elem[3][3]);

        float x4 = (_elem[3][0] * m._elem[0][0]) +
                   (_elem[3][1] * m._elem[1][0]) +
                   (_elem[3][2] * m._elem[2][0]) +
                   (_elem[3][3] * m._elem[3][0]);
    
        float y4 = (_elem[3][0] * m._elem[0][1]) +
                   (_elem[3][1] * m._elem[1][1]) +
                   (_elem[3][2] * m._elem[2][1]) +
                   (_elem[3][3] * m._elem[3][1]);

        float z4 = (_elem[3][0] * m._elem[0][2]) +
                   (_elem[3][1] * m._elem[1][2]) +
                   (_elem[3][2] * m._elem[2][2]) +
                   (_elem[3][3] * m._elem[3][2]);

        float w4 = (_elem[3][0] * m._elem[0][3]) +
                   (_elem[3][1] * m._elem[1][3]) +
                   (_elem[3][2] * m._elem[2][3]) +
                   (_elem[3][3] * m._elem[3][3]);

        _elem[0][0] = x1;
        _elem[1][0] = x2;
        _elem[2][0] = x3;
        _elem[3][0] = x4;

        _elem[0][1] = y1;
        _elem[1][1] = y2;
        _elem[2][1] = y3;
        _elem[3][1] = y4;

        _elem[0][2] = z1;
        _elem[1][2] = z2;
        _elem[2][2] = z3;
        _elem[3][2] = z4;

        _elem[0][3] = w1;
        _elem[1][3] = w2;
        _elem[2][3] = w3;
        _elem[3][3] = w4;

        return *this;
    }

    const Mat4& Mat4::operator*=(const float lambda) {
        this->_elem[0][0] *= lambda;
        this->_elem[1][0] *= lambda;
        this->_elem[2][0] *= lambda;
        this->_elem[3][0] *= lambda;

        this->_elem[0][1] *= lambda;
        this->_elem[1][1] *= lambda;
        this->_elem[2][1] *= lambda;
        this->_elem[3][1] *= lambda;

        this->_elem[0][2] *= lambda;
        this->_elem[1][2] *= lambda;
        this->_elem[2][2] *= lambda;
        this->_elem[3][2] *= lambda;

        this->_elem[0][3] *= lambda;
        this->_elem[1][3] *= lambda;
        this->_elem[2][3] *= lambda;
        this->_elem[3][3] *= lambda;

        return *this;
    }

    const Mat4& Mat4::operator+=(const Mat4 &m) {
        this->_elem[0][0] += m._elem[0][0];
        this->_elem[1][0] += m._elem[1][0];
        this->_elem[2][0] += m._elem[2][0];
        this->_elem[3][0] += m._elem[3][0];

        this->_elem[0][1] += m._elem[0][1];
        this->_elem[1][1] += m._elem[1][1];
        this->_elem[2][1] += m._elem[2][1];
        this->_elem[3][1] += m._elem[3][1];

        this->_elem[0][2] += m._elem[0][2];
        this->_elem[1][2] += m._elem[1][2];
        this->_elem[2][2] += m._elem[2][2];
        this->_elem[3][2] += m._elem[3][2];

        this->_elem[0][3] += m._elem[0][3];
        this->_elem[1][3] += m._elem[1][3];
        this->_elem[2][3] += m._elem[2][3];
        this->_elem[3][3] += m._elem[3][3];

        return *this;
    }

    const Mat4& Mat4::operator-=(const Mat4 &m) {
        this->_elem[0][0] -= m._elem[0][0];
        this->_elem[1][0] -= m._elem[1][0];
        this->_elem[2][0] -= m._elem[2][0];
        this->_elem[3][0] -= m._elem[3][0];

        this->_elem[0][1] -= m._elem[0][1];
        this->_elem[1][1] -= m._elem[1][1];
        this->_elem[2][1] -= m._elem[2][1];
        this->_elem[3][1] -= m._elem[3][1];

        this->_elem[0][2] -= m._elem[0][2];
        this->_elem[1][2] -= m._elem[1][2];
        this->_elem[2][2] -= m._elem[2][2];
        this->_elem[3][2] -= m._elem[3][2];

        this->_elem[0][3] -= m._elem[0][3];
        this->_elem[1][3] -= m._elem[1][3];
        this->_elem[2][3] -= m._elem[2][3];
        this->_elem[3][3] -= m._elem[3][3];

        return *this;
    }

    Mat4 operator*(const Mat4 &m, const Mat4 &n) {
        Mat4 l = m;
        return l *= n;
    }

    Mat4 operator*(const Mat4 &m, const float lambda) {
        Mat4 n = m;
        n *= lambda;
        return n;
    }

    Mat4 operator*(const float lambda, const Mat4 &m) {
        Mat4 n = m;
        n *= lambda;
        return n;
    }

    Mat4 operator+(const Mat4 &m, const Mat4 &n) {
        Mat4 l = m;
        return l += n;
    }

    Mat4 operator-(const Mat4 &m, const Mat4 &n) {
        Mat4 l = m;
        return l -= n;
    }

    Point4 operator*(const Mat4 &m, const Point4 &p) {
        return Point4((m._elem[0][0] * p._x) +
                      (m._elem[0][1] * p._y) +
                      (m._elem[0][2] * p._z) +
                      (m._elem[0][3] * p._w), 
                      (m._elem[1][0] * p._x) +
                      (m._elem[1][1] * p._y) +
                      (m._elem[1][2] * p._z) +
                      (m._elem[1][3] * p._w),
                      (m._elem[2][0] * p._x) +
                      (m._elem[2][1] * p._y) +
                      (m._elem[2][2] * p._z) +
                      (m._elem[2][3] * p._w),
                      (m._elem[3][0] * p._x) +
                      (m._elem[3][1] * p._y) +
                      (m._elem[3][2] * p._z) +
                      (m._elem[3][3] * p._w));
    }

    Point4 operator*(const Point4 &p, const Mat4 &m) {
        return m * p;
    }

    Vec4 operator*(const Mat4 &m, const Vec4 &v) {
        return Vec4((m._elem[0][0] * v._x) +
                    (m._elem[0][1] * v._y) +
                    (m._elem[0][2] * v._z) +
                    (m._elem[0][3] * v._w), 
                    (m._elem[1][0] * v._x) +
                    (m._elem[1][1] * v._y) +
                    (m._elem[1][2] * v._z) +
                    (m._elem[1][3] * v._w),
                    (m._elem[2][0] * v._x) +
                    (m._elem[2][1] * v._y) +
                    (m._elem[2][2] * v._z) +
                    (m._elem[2][3] * v._w),
                    (m._elem[3][0] * v._x) +
                    (m._elem[3][1] * v._y) +
                    (m._elem[3][2] * v._z) +
                    (m._elem[3][3] * v._w));
    }

    Vec4 operator*(const Vec4 &v, const Mat4 &m) {
        return m * v;
    }

    std::ostream& operator<<(std::ostream &os, const Mat4 &m) {
        os << std::fixed << std::setprecision(Point4::_output_precision)
           << "[" << m._elem[0][0] << ", " << m._elem[0][1] << ", "
           << m._elem[0][2] << ", " << m._elem[0][3] << "]\n"
           << "[" << m._elem[1][0] << ", " << m._elem[1][1] << ", "
           << m._elem[1][2] << ", " << m._elem[1][3] << "]\n"
           << "[" << m._elem[2][0] << ", " << m._elem[2][1] << ", "
           << m._elem[2][2] << ", " << m._elem[2][3] << "]\n"
           << "[" << m._elem[3][0] << ", " << m._elem[3][1] << ", "
           << m._elem[3][2] << ", " << m._elem[3][3] << "]";
        return os;
    }
} // namespace pdm