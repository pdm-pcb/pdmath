#include "pdmath/Matrix3.hpp"

#include "pdmath/Vector3.hpp"
#include "pdmath/Point3.hpp"

#include <iomanip>

namespace pdm {
    Mat3::Mat3(const Point3 &x, const Point3 &y, const Point3 &z) :
        _elem{{x._x, y._x, z._x},
              {x._y, y._y, z._y},
              {x._z, y._z, z._z}}
    { }

    Mat3::Mat3(const std::array<float, 3> &x,
               const std::array<float, 3> &y,
               const std::array<float, 3> &z) :
        _elem{{x[0], y[0], z[0]},
              {x[1], y[1], z[0]},
              {x[2], y[2], z[2]}}
    { }
    
    Mat3::Mat3(const float x1, const float y1, const float z1,
               const float x2, const float y2, const float z2,
               const float x3, const float y3, const float z3) :
        _elem{{x1, y1, z1},
              {x2, y2, z2},
              {x3, y3, z3}}
    { }

    Mat3 Mat3::transpose() const {
        return Mat3(_r1[0], _r2[0], _r3[0],
                    _r1[1], _r2[1], _r3[1],
                    _r1[2], _r2[2], _r3[2]);
    }

    Mat3 Mat3::inverse() const {
        return (1.0f/determinant()) * matrix_of_cofactors().transpose();
    }

    float Mat3::determinant() const {
        float cofactor_a = _r1[0] * ((_r2[1] * _r3[2]) - (_r2[2] * _r3[1]));
        float cofactor_b = _r1[1] * ((_r2[0] * _r3[2]) - (_r2[2] * _r3[0]));
        float cofactor_c = _r1[2] * ((_r2[0] * _r3[1]) - (_r2[1] * _r3[0]));

        return cofactor_a - cofactor_b + cofactor_c;
    }

    Mat3 Mat3::matrix_of_minors() const {
        return Mat3(
        /* 0,0 */ (_r2[1] * _r3[2]) - (_r2[2] * _r3[1]),
        /* 0,1 */ (_r2[0] * _r3[2]) - (_r2[2] * _r3[0]),
        /* 0,2 */ (_r2[0] * _r3[1]) - (_r2[1] * _r3[0]),
        /* 1,0 */ (_r1[1] * _r3[2]) - (_r1[2] * _r3[1]),
        /* 1,1 */ (_r1[0] * _r3[2]) - (_r1[2] * _r3[0]),
        /* 1,2 */ (_r1[0] * _r3[1]) - (_r1[1] * _r1[2]),
        /* 2,0 */ (_r1[1] * _r2[2]) - (_r1[2] * _r2[1]),
        /* 2,1 */ (_r1[0] * _r2[2]) - (_r1[2] * _r2[0]),
        /* 2,2 */ (_r1[0] * _r2[1]) - (_r1[1] * _r2[0])
        );
    }

    Mat3 Mat3::matrix_of_cofactors() const {
        return Mat3(
        /* 0,0 */ +((_r2[1] * _r3[2]) - (_r2[2] * _r3[1])),
        /* 0,1 */ -((_r2[0] * _r3[2]) - (_r2[2] * _r3[0])),
        /* 0,2 */ +((_r2[0] * _r3[1]) - (_r2[1] * _r3[0])),
        /* 1,0 */ -((_r1[1] * _r3[2]) - (_r1[2] * _r3[1])),
        /* 1,1 */ +((_r1[0] * _r3[2]) - (_r1[2] * _r3[0])),
        /* 1,2 */ -((_r1[0] * _r3[1]) - (_r1[1] * _r1[2])),
        /* 2,0 */ +((_r1[1] * _r2[2]) - (_r1[2] * _r2[1])),
        /* 2,1 */ -((_r1[0] * _r2[2]) - (_r1[2] * _r2[0])),
        /* 2,2 */ +((_r1[0] * _r2[1]) - (_r1[1] * _r2[0]))
        );
    }

    bool Mat3::operator==(const Mat3 &m) const {
        if(this == &m) {
            return true;
        }
    
        return _r1[0] == m._r1[0] &&
               _r2[0] == m._r2[0] &&
               _r3[0] == m._r3[0] &&
               _r1[1] == m._r1[1] &&
               _r2[1] == m._r2[1] &&
               _r3[1] == m._r3[1] &&
               _r1[2] == m._r1[2] &&
               _r2[2] == m._r2[2] &&
               _r3[2] == m._r3[2];
    }

    const Mat3& Mat3::operator*=(const Mat3 &m) {
        float x1 = (_r1[0] * m._r1[0]) +
                   (_r1[1] * m._r2[0]) +
                   (_r1[2] * m._r3[0]);    
        float y1 = (_r1[0] * m._r1[1]) +
                   (_r1[1] * m._r2[1]) +
                   (_r1[2] * m._r3[1]);
        float z1 = (_r1[0] * m._r1[2]) +
                   (_r1[1] * m._r2[2]) +
                   (_r1[2] * m._r3[2]);

        float x2 = (_r2[0] * m._r1[0]) +
                   (_r2[1] * m._r2[0]) +
                   (_r2[2] * m._r3[0]);
        float y2 = (_r2[0] * m._r1[1]) +
                   (_r2[1] * m._r2[1]) +
                   (_r2[2] * m._r3[1]);
        float z2 = (_r2[0] * m._r1[2]) +
                   (_r2[1] * m._r2[2]) +
                   (_r2[2] * m._r3[2]);

        float x3 = (_r3[0] * m._r1[0]) +
                   (_r3[1] * m._r2[0]) +
                   (_r3[2] * m._r3[0]);
        float y3 = (_r3[0] * m._r1[1]) +
                   (_r3[1] * m._r2[1]) +
                   (_r3[2] * m._r3[1]);
        float z3 = (_r3[0] * m._r1[2]) +
                   (_r3[1] * m._r2[2]) +
                   (_r3[2] * m._r3[2]);

        _r1[0] = x1;
        _r2[0] = x2;
        _r3[0] = x3;

        _r1[1] = y1;
        _r2[1] = y2;
        _r3[1] = y3;

        _r1[2] = z1;
        _r2[2] = z2;
        _r3[2] = z3;

        return *this;
    }

    const Mat3& Mat3::operator*=(const float scalar) {
        this->_r1[0] *= scalar;
        this->_r2[0] *= scalar;
        this->_r3[0] *= scalar;

        this->_r1[1] *= scalar;
        this->_r2[1] *= scalar;
        this->_r3[1] *= scalar;

        this->_r1[2] *= scalar;
        this->_r2[2] *= scalar;
        this->_r3[2] *= scalar;

        return *this;
    }

    const Mat3& Mat3::operator+=(const Mat3 &m) {
        this->_r1[0] += m._r1[0];
        this->_r2[0] += m._r2[0];
        this->_r3[0] += m._r3[0];

        this->_r1[1] += m._r1[1];
        this->_r2[1] += m._r2[1];
        this->_r3[1] += m._r3[1];

        this->_r1[2] += m._r1[2];
        this->_r2[2] += m._r2[2];
        this->_r3[2] += m._r3[2];

        return *this;
    }

    const Mat3& Mat3::operator-=(const Mat3 &m) {
        this->_r1[0] -= m._r1[0];
        this->_r2[0] -= m._r2[0];
        this->_r3[0] -= m._r3[0];

        this->_r1[1] -= m._r1[1];
        this->_r2[1] -= m._r2[1];
        this->_r3[1] -= m._r3[1];

        this->_r1[2] -= m._r1[2];
        this->_r2[2] -= m._r2[2];
        this->_r3[2] -= m._r3[2];

        return *this;
    }

    Mat3 operator*(const Mat3 &m, const Mat3 &n) {
        float x1 = (m._r1[0] * n._r1[0]) +
                   (m._r1[1] * n._r2[0]) +
                   (m._r1[2] * n._r3[0]);    
        float y1 = (m._r1[0] * n._r1[1]) +
                   (m._r1[1] * n._r2[1]) +
                   (m._r1[2] * n._r3[1]);
        float z1 = (m._r1[0] * n._r1[2]) +
                   (m._r1[1] * n._r2[2]) +
                   (m._r1[2] * n._r3[2]);

        float x2 = (m._r2[0] * n._r1[0]) +
                   (m._r2[1] * n._r2[0]) +
                   (m._r2[2] * n._r3[0]);    
        float y2 = (m._r2[0] * n._r1[1]) +
                   (m._r2[1] * n._r2[1]) +
                   (m._r2[2] * n._r3[1]);
        float z2 = (m._r2[0] * n._r1[2]) +
                   (m._r2[1] * n._r2[2]) +
                   (m._r2[2] * n._r3[2]);

        float x3 = (m._r3[0] * n._r1[0]) +
                   (m._r3[1] * n._r2[0]) +
                   (m._r3[2] * n._r3[0]);    
        float y3 = (m._r3[0] * n._r1[1]) +
                   (m._r3[1] * n._r2[1]) +
                   (m._r3[2] * n._r3[1]);
        float z3 = (m._r3[0] * n._r1[2]) +
                   (m._r3[1] * n._r2[2]) +
                   (m._r3[2] * n._r3[2]);

        return Mat3(x1, y1, z1,
                    x2, y2, z2,
                    x3, y3, z3);
    }

    Mat3 operator*(const Mat3 &m, const float scalar) {
        return Mat3(m._r1[0] * scalar,
                    m._r1[1] * scalar,
                    m._r1[2] * scalar,

                    m._r2[0] * scalar,
                    m._r2[1] * scalar,
                    m._r2[2] * scalar,

                    m._r3[0] * scalar,
                    m._r3[1] * scalar,
                    m._r3[2] * scalar);
    }

    Mat3 operator*(const float scalar, const Mat3 &m) {
        return m * scalar;
    }

    Mat3 operator+(const Mat3 &m, const Mat3 &n) {
        return Mat3(m._r1[0] + n._r1[0],
                    m._r1[1] + n._r1[1],
                    m._r1[2] + n._r1[2],

                    m._r2[0] + n._r2[0],
                    m._r2[1] + n._r2[1],
                    m._r2[2] + n._r2[2],

                    m._r3[0] + n._r3[0],
                    m._r3[1] + n._r3[1],
                    m._r3[2] + n._r3[2]);
    }

    Mat3 operator-(const Mat3 &m, const Mat3 &n) {
        return Mat3(m._r1[0] - n._r1[0],
                    m._r1[1] - n._r1[1],
                    m._r1[2] - n._r1[2],

                    m._r2[0] - n._r2[0],
                    m._r2[1] - n._r2[1],
                    m._r2[2] - n._r2[2],
                    
                    m._r3[0] - n._r3[0],
                    m._r3[1] - n._r3[1],
                    m._r3[2] - n._r3[2]);
    }

    Point3 operator*(const Mat3 &m, const Point3 &p) {
        return Point3(p._x * m._r1[0] +
                      p._y * m._r1[1] +
                      p._z * m._r1[2],

                      p._x * m._r2[0] +
                      p._y * m._r2[1] +
                      p._z * m._r2[2],

                      p._x * m._r3[0] +
                      p._y * m._r3[1] +
                      p._z * m._r3[2]);
    }

    Vec3 operator*(const Mat3 &m, const Vec3 &v) {
        return Vec3(v._x * m._r1[0] +
                    v._y * m._r1[1] +
                    v._z * m._r1[2],

                    v._x * m._r2[0] +
                    v._y * m._r2[1] +
                    v._z * m._r2[2],
                    
                    v._x * m._r3[0] +
                    v._y * m._r3[1] +
                    v._z * m._r3[2]);
    }

    std::ostream& operator<<(std::ostream &os, const Mat3 &m) {
        os << std::fixed << std::setprecision(Point3::_output_precision)
           << "[" << m._r1[0] << ", " << m._r1[1] << ", "
           << m._r1[2] << "]\n"
           << "[" << m._r2[0] << ", " << m._r2[1] << ", "
           << m._r2[2] << "]\n"
           << "[" << m._r3[0] << ", " << m._r3[1] << ", "
           << m._r3[2] << "]";
        return os;
    }
} // namespace pdm