#include "pdmath/Matrix3.hpp"

#include "pdmath/Vector3.hpp"
#include "pdmath/Point3.hpp"

#include <iomanip>
#include <cmath>
#include <numbers>

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
    
    const Mat3 Mat3::identity(1.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 1.0f);

    Mat3 Mat3::populate_rotation(float theta_x, float theta_y,  float theta_z) {
        Mat3 rot_x;
        if(theta_x != 1) {
            float cos_theta = std::cos(theta_x);
            float sin_theta = std::sin(theta_x);
            rot_x = Mat3(1.0f, 0.0f,       0.0f,
                         0.0f, cos_theta, -sin_theta,
                         0.0f, sin_theta,  cos_theta);
        }
        else {
            rot_x = identity;
        }

        Mat3 rot_y;
        if(theta_y != 1) {
            float cos_theta = std::cos(theta_y);
            float sin_theta = std::sin(theta_y);
            rot_y = Mat3( cos_theta,  0.0f, sin_theta,
                          0.0f,       1.0f,      0.0f,
                         -sin_theta,  0.0f, cos_theta);
        }
        else {
            rot_y = identity;
        }

        Mat3 rot_z;
        if(theta_z != 1) {
            float cos_theta = std::cos(theta_z);
            float sin_theta = std::sin(theta_z);
            rot_z = Mat3(cos_theta, -sin_theta, 0.0f,
                         sin_theta,  cos_theta, 0.0f,
                         0.0f,       0.0f,      1.0f);
        }
        else {
            rot_z = identity;
        }

        return rot_x * rot_y * rot_z;
    }

    Mat3 Mat3::transposed() const {
        return Mat3(_elem[0][0], _elem[1][0], _elem[2][0],
                    _elem[0][1], _elem[1][1], _elem[2][1],
                    _elem[0][2], _elem[1][2], _elem[2][2]);
    }

    Mat3 Mat3::inverted() const {
        return (1.0f/determinant()) * matrix_of_cofactors().transposed();
    }

    float Mat3::determinant() const {
        float cofactor_a = _elem[0][0] *
            ((_elem[1][1] * _elem[2][2]) - (_elem[1][2] * _elem[2][1]));
        float cofactor_b = _elem[0][1] *
            ((_elem[1][0] * _elem[2][2]) - (_elem[1][2] * _elem[2][0]));
        float cofactor_c = _elem[0][2] *
            ((_elem[1][0] * _elem[2][1]) - (_elem[1][1] * _elem[2][0]));

        return cofactor_a - cofactor_b + cofactor_c;
    }

    Mat3 Mat3::matrix_of_minors() const {
        return Mat3(
        /* 0,0 */ (_elem[1][1] * _elem[2][2]) - (_elem[1][2] * _elem[2][1]),
        /* 0,1 */ (_elem[1][0] * _elem[2][2]) - (_elem[1][2] * _elem[2][0]),
        /* 0,2 */ (_elem[1][0] * _elem[2][1]) - (_elem[1][1] * _elem[2][0]),
        /* 1,0 */ (_elem[0][1] * _elem[2][2]) - (_elem[0][2] * _elem[2][1]),
        /* 1,1 */ (_elem[0][0] * _elem[2][2]) - (_elem[0][2] * _elem[2][0]),
        /* 1,2 */ (_elem[0][0] * _elem[2][1]) - (_elem[0][1] * _elem[0][2]),
        /* 2,0 */ (_elem[0][1] * _elem[1][2]) - (_elem[0][2] * _elem[1][1]),
        /* 2,1 */ (_elem[0][0] * _elem[1][2]) - (_elem[0][2] * _elem[1][0]),
        /* 2,2 */ (_elem[0][0] * _elem[1][1]) - (_elem[0][1] * _elem[1][0])
        );
    }

    Mat3 Mat3::matrix_of_cofactors() const {
        return Mat3(
        /* 0,0 */ +((_elem[1][1] * _elem[2][2]) - (_elem[1][2] * _elem[2][1])),
        /* 0,1 */ -((_elem[1][0] * _elem[2][2]) - (_elem[1][2] * _elem[2][0])),
        /* 0,2 */ +((_elem[1][0] * _elem[2][1]) - (_elem[1][1] * _elem[2][0])),
        /* 1,0 */ -((_elem[0][1] * _elem[2][2]) - (_elem[0][2] * _elem[2][1])),
        /* 1,1 */ +((_elem[0][0] * _elem[2][2]) - (_elem[0][2] * _elem[2][0])),
        /* 1,2 */ -((_elem[0][0] * _elem[2][1]) - (_elem[0][1] * _elem[0][2])),
        /* 2,0 */ +((_elem[0][1] * _elem[1][2]) - (_elem[0][2] * _elem[1][1])),
        /* 2,1 */ -((_elem[0][0] * _elem[1][2]) - (_elem[0][2] * _elem[1][0])),
        /* 2,2 */ +((_elem[0][0] * _elem[1][1]) - (_elem[0][1] * _elem[1][0]))
        );
    }

    /*--------------------------------------------------------------------------
        Symbol expansion for an XYZ rotation matrix:

             cycz           −cysz           sy
         czsxsy + cxsz    cxcz − sxsysz   −cysx
        −cxczsy + sxsz    czsx + cxsysz    cxcy
    --------------------------------------------------------------------------*/
    void Mat3::get_euler_xyz(Vec3 &ans1, Vec3 &ans2) const {
        float theta_y1 = std::asin(_elem[0][2]);
        float theta_y2;

        if(theta_y1 >= 0.0f) {
            theta_y2 = std::numbers::pi_v<float> - theta_y1;
        }
        else {
            theta_y2 = -std::numbers::pi_v<float> - theta_y1;
        }

        float cos_theta_y1 = std::cos(theta_y1);
        float cos_theta_y2 = std::cos(theta_y2);

        float cos_z1 =  _elem[0][0]/cos_theta_y1;
        float sin_z1 = -_elem[0][1]/cos_theta_y1;

        float cos_z2 =  _elem[0][0]/cos_theta_y2;
        float sin_z2 = -_elem[0][1]/cos_theta_y2;

        float sin_x1 = -_elem[1][2]/cos_theta_y1;
        float cos_x1 =  _elem[2][2]/cos_theta_y1;

        float sin_x2 = -_elem[1][2]/cos_theta_y2;
        float cos_x2 =  _elem[2][2]/cos_theta_y2;

        float theta_z1 = atan2f(sin_z1, cos_z1);
        float theta_z2 = atan2f(sin_z2, cos_z2);

        float theta_x1 = atan2f(sin_x1, cos_x1);
        float theta_x2 = atan2f(sin_x2, cos_x2);

        ans1._x = theta_x1;
        ans1._y = theta_y1;
        ans1._z = theta_z1;

        ans2._x = theta_x2;
        ans2._y = theta_y2;
        ans2._z = theta_z2;
    
        return;
    }


    /*--------------------------------------------------------------------------
        Symbol expansion for an ZXY rotation matrix:

        cycz − sxsysz   −cxsz    czsy + cysxsz
        czsxsy + cysz    cxcz   −cyczsx + sysz
             −cxsy        sx         cxcy

        Or:

         CyCz    ...    ...
         Sz      CxCz   -SxCz
        -SyCz    ...    ...
    --------------------------------------------------------------------------*/
    void Mat3::get_euler_zxy(Vec3 &ans1, Vec3 &ans2) const {
        float theta_z1 = std::asin(_elem[1][0]);
        float theta_z2;

        if(theta_z1 >= 0.0f) {
            theta_z2 = std::numbers::pi_v<float> - theta_z1;
        }
        else {
            theta_z2 = -std::numbers::pi_v<float> - theta_z1;
        }

        float cos_theta_z1 = std::cos(theta_z1);
        float cos_theta_z2 = std::cos(theta_z2);

        float sin_x1 = -_elem[1][2]/cos_theta_z1;
        float sin_x2 = -_elem[1][2]/cos_theta_z2;
        float cos_x1 =  _elem[1][1]/cos_theta_z1;
        float cos_x2 =  _elem[1][1]/cos_theta_z2;

        float sin_y1 = -_elem[2][0]/cos_theta_z1;
        float sin_y2 = -_elem[2][0]/cos_theta_z2;
        float cos_y1 =  _elem[0][0]/cos_theta_z1;
        float cos_y2 =  _elem[0][0]/cos_theta_z2;

        float theta_x1 = atan2f(sin_x1, cos_x1);
        float theta_x2 = atan2f(sin_x2, cos_x2);

        float theta_y1 = atan2f(sin_y1, cos_y1);
        float theta_y2 = atan2f(sin_y2, cos_y2);

        ans1._x = theta_x1;
        ans1._y = theta_y1;
        ans1._z = theta_z1;

        ans2._x = theta_x2;
        ans2._y = theta_y2;
        ans2._z = theta_z2;
    
        return;
    }

    bool Mat3::operator==(const Mat3 &m) const {
        if(this == &m) {
            return true;
        }

        Vec3 x(_elem[0][0], _elem[1][0], _elem[2][0]);
        Vec3 y(_elem[0][1], _elem[1][1], _elem[2][1]);
        Vec3 z(_elem[0][2], _elem[1][2], _elem[2][2]);

        Vec3 m_x(m._elem[0][0], m._elem[1][0], m._elem[2][0]);
        Vec3 m_y(m._elem[0][1], m._elem[1][1], m._elem[2][1]);
        Vec3 m_z(m._elem[0][2], m._elem[1][2], m._elem[2][2]);
    
        return x == m_x && y == m_y && z == m_z;
    }

    const Mat3& Mat3::operator*=(const Mat3 &m) {
        float x1 = (_elem[0][0] * m._elem[0][0]) +
                   (_elem[0][1] * m._elem[1][0]) +
                   (_elem[0][2] * m._elem[2][0]);    
        float y1 = (_elem[0][0] * m._elem[0][1]) +
                   (_elem[0][1] * m._elem[1][1]) +
                   (_elem[0][2] * m._elem[2][1]);
        float z1 = (_elem[0][0] * m._elem[0][2]) +
                   (_elem[0][1] * m._elem[1][2]) +
                   (_elem[0][2] * m._elem[2][2]);

        float x2 = (_elem[1][0] * m._elem[0][0]) +
                   (_elem[1][1] * m._elem[1][0]) +
                   (_elem[1][2] * m._elem[2][0]);
        float y2 = (_elem[1][0] * m._elem[0][1]) +
                   (_elem[1][1] * m._elem[1][1]) +
                   (_elem[1][2] * m._elem[2][1]);
        float z2 = (_elem[1][0] * m._elem[0][2]) +
                   (_elem[1][1] * m._elem[1][2]) +
                   (_elem[1][2] * m._elem[2][2]);

        float x3 = (_elem[2][0] * m._elem[0][0]) +
                   (_elem[2][1] * m._elem[1][0]) +
                   (_elem[2][2] * m._elem[2][0]);
        float y3 = (_elem[2][0] * m._elem[0][1]) +
                   (_elem[2][1] * m._elem[1][1]) +
                   (_elem[2][2] * m._elem[2][1]);
        float z3 = (_elem[2][0] * m._elem[0][2]) +
                   (_elem[2][1] * m._elem[1][2]) +
                   (_elem[2][2] * m._elem[2][2]);

        _elem[0][0] = x1;
        _elem[1][0] = x2;
        _elem[2][0] = x3;

        _elem[0][1] = y1;
        _elem[1][1] = y2;
        _elem[2][1] = y3;

        _elem[0][2] = z1;
        _elem[1][2] = z2;
        _elem[2][2] = z3;

        return *this;
    }

    const Mat3& Mat3::operator*=(const float scalar) {
        this->_elem[0][0] *= scalar;
        this->_elem[1][0] *= scalar;
        this->_elem[2][0] *= scalar;

        this->_elem[0][1] *= scalar;
        this->_elem[1][1] *= scalar;
        this->_elem[2][1] *= scalar;

        this->_elem[0][2] *= scalar;
        this->_elem[1][2] *= scalar;
        this->_elem[2][2] *= scalar;

        return *this;
    }

    const Mat3& Mat3::operator+=(const Mat3 &m) {
        this->_elem[0][0] += m._elem[0][0];
        this->_elem[1][0] += m._elem[1][0];
        this->_elem[2][0] += m._elem[2][0];

        this->_elem[0][1] += m._elem[0][1];
        this->_elem[1][1] += m._elem[1][1];
        this->_elem[2][1] += m._elem[2][1];

        this->_elem[0][2] += m._elem[0][2];
        this->_elem[1][2] += m._elem[1][2];
        this->_elem[2][2] += m._elem[2][2];

        return *this;
    }

    const Mat3& Mat3::operator-=(const Mat3 &m) {
        this->_elem[0][0] -= m._elem[0][0];
        this->_elem[1][0] -= m._elem[1][0];
        this->_elem[2][0] -= m._elem[2][0];

        this->_elem[0][1] -= m._elem[0][1];
        this->_elem[1][1] -= m._elem[1][1];
        this->_elem[2][1] -= m._elem[2][1];

        this->_elem[0][2] -= m._elem[0][2];
        this->_elem[1][2] -= m._elem[1][2];
        this->_elem[2][2] -= m._elem[2][2];

        return *this;
    }

    Mat3 operator*(const Mat3 &m, const Mat3 &n) {
        return Mat3(m._elem[0][0] * n._elem[0][0] +
                    m._elem[0][1] * n._elem[1][0] +
                    m._elem[0][2] * n._elem[2][0],                    
                    m._elem[0][0] * n._elem[0][1] +
                    m._elem[0][1] * n._elem[1][1] +
                    m._elem[0][2] * n._elem[2][1],
                    m._elem[0][0] * n._elem[0][2] +
                    m._elem[0][1] * n._elem[1][2] +
                    m._elem[0][2] * n._elem[2][2],

                    m._elem[1][0] * n._elem[0][0] +
                    m._elem[1][1] * n._elem[1][0] +
                    m._elem[1][2] * n._elem[2][0],
                    m._elem[1][0] * n._elem[0][1] +
                    m._elem[1][1] * n._elem[1][1] +
                    m._elem[1][2] * n._elem[2][1],
                    m._elem[1][0] * n._elem[0][2] +
                    m._elem[1][1] * n._elem[1][2] +
                    m._elem[1][2] * n._elem[2][2],

                    m._elem[2][0] * n._elem[0][0] +
                    m._elem[2][1] * n._elem[1][0] +
                    m._elem[2][2] * n._elem[2][0],
                    m._elem[2][0] * n._elem[0][1] +
                    m._elem[2][1] * n._elem[1][1] +
                    m._elem[2][2] * n._elem[2][1],
                    m._elem[2][0] * n._elem[0][2] +
                    m._elem[2][1] * n._elem[1][2] +
                    m._elem[2][2] * n._elem[2][2]);
    }

    Mat3 operator*(const Mat3 &m, const float scalar) {
        return Mat3(m._elem[0][0] * scalar,
                    m._elem[0][1] * scalar,
                    m._elem[0][2] * scalar,

                    m._elem[1][0] * scalar,
                    m._elem[1][1] * scalar,
                    m._elem[1][2] * scalar,

                    m._elem[2][0] * scalar,
                    m._elem[2][1] * scalar,
                    m._elem[2][2] * scalar);
    }

    Mat3 operator*(const float scalar, const Mat3 &m) {
        return m * scalar;
    }

    Mat3 operator+(const Mat3 &m, const Mat3 &n) {
        return Mat3(m._elem[0][0] + n._elem[0][0],
                    m._elem[0][1] + n._elem[0][1],
                    m._elem[0][2] + n._elem[0][2],

                    m._elem[1][0] + n._elem[1][0],
                    m._elem[1][1] + n._elem[1][1],
                    m._elem[1][2] + n._elem[1][2],

                    m._elem[2][0] + n._elem[2][0],
                    m._elem[2][1] + n._elem[2][1],
                    m._elem[2][2] + n._elem[2][2]);
    }

    Mat3 operator-(const Mat3 &m, const Mat3 &n) {
        return Mat3(m._elem[0][0] - n._elem[0][0],
                    m._elem[0][1] - n._elem[0][1],
                    m._elem[0][2] - n._elem[0][2],

                    m._elem[1][0] - n._elem[1][0],
                    m._elem[1][1] - n._elem[1][1],
                    m._elem[1][2] - n._elem[1][2],
                    
                    m._elem[2][0] - n._elem[2][0],
                    m._elem[2][1] - n._elem[2][1],
                    m._elem[2][2] - n._elem[2][2]);
    }

    Point3 operator*(const Mat3 &m, const Point3 &p) {
        return Point3(p._x * m._elem[0][0] +
                      p._y * m._elem[0][1] +
                      p._z * m._elem[0][2],

                      p._x * m._elem[1][0] +
                      p._y * m._elem[1][1] +
                      p._z * m._elem[1][2],

                      p._x * m._elem[2][0] +
                      p._y * m._elem[2][1] +
                      p._z * m._elem[2][2]);
    }

    Vec3 operator*(const Mat3 &m, const Vec3 &v) {
        return Vec3(v._x * m._elem[0][0] +
                    v._y * m._elem[0][1] +
                    v._z * m._elem[0][2],

                    v._x * m._elem[1][0] +
                    v._y * m._elem[1][1] +
                    v._z * m._elem[1][2],
                    
                    v._x * m._elem[2][0] +
                    v._y * m._elem[2][1] +
                    v._z * m._elem[2][2]);
    }

    std::ostream& operator<<(std::ostream &os, const Mat3 &m) {
        os << std::fixed << std::setprecision(Point3::precision)
           << "[" << m._elem[0][0] << ", " << m._elem[0][1] << ", "
           << m._elem[0][2] << "]\n"
           << "[" << m._elem[1][0] << ", " << m._elem[1][1] << ", "
           << m._elem[1][2] << "]\n"
           << "[" << m._elem[2][0] << ", " << m._elem[2][1] << ", "
           << m._elem[2][2] << "]";
        return os;
    }
} // namespace pdm