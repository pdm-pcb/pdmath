#include "pdmath/Matrix.hpp"

#include "pdmath/Vector.hpp"
#include "pdmath/Point.hpp"

#include <iomanip>

namespace pdm {
    Mat3::Mat3(const Vec3 &x, const Vec3 &y, const Vec3 &z) :
        _x{x._x, x._y, x._z},
        _y{y._x, y._y, y._z},
        _z{z._x, z._y, z._z}
    { }

    Mat3::Mat3(const Point &x, const Point &y, const Point &z) :
        _x{x._x, x._y, x._z},
        _y{y._x, y._y, y._z},
        _z{z._x, z._y, z._z}
    { }

    Mat3::Mat3(const std::array<float, 3> &x,
               const std::array<float, 3> &y,
               const std::array<float, 3> &z) :
        _x{x[0], x[1], x[2]},
        _y{y[0], y[1], y[2]},
        _z{z[0], z[1], z[2]}
    { }
    
    Mat3::Mat3(const float x1, const float y1, const float z1,
               const float x2, const float y2, const float z2,
               const float x3, const float y3, const float z3) :
        _x{x1, x2, x3},
        _y{y1, y2, y3},
        _z{z1, z2, z3}
    { }

    bool Mat3::operator==(const Mat3 &m) const {
        if(this == &m) {
            return true;
        }
    
        return _x[0] == m._x[0] && _x[1] == m._x[1] && _x[2] == m._x[2] &&
               _y[0] == m._y[0] && _y[1] == m._y[1] && _y[2] == m._y[2] &&
               _z[0] == m._z[0] && _z[1] == m._z[1] && _z[2] == m._z[2];
    }

    const Mat3& Mat3::operator*=(const Mat3 &m) {
        float x1 = (_x[0] * m._x[0]) + (_y[0] * m._x[1]) + (_z[0] * m._x[2]);
        float x2 = (_x[1] * m._x[0]) + (_y[1] * m._x[1]) + (_z[1] * m._x[2]);
        float x3 = (_x[2] * m._x[0]) + (_y[2] * m._x[1]) + (_z[2] * m._x[2]);

        float y1 = (_x[0] * m._y[0]) + (_y[0] * m._y[1]) + (_z[0] * m._y[2]);
        float y2 = (_x[1] * m._y[0]) + (_y[1] * m._y[1]) + (_z[1] * m._y[2]);        
        float y3 = (_x[2] * m._y[0]) + (_y[2] * m._y[1]) + (_z[2] * m._y[2]);

        float z1 = (_x[0] * m._z[0]) + (_y[0] * m._z[1]) + (_z[0] * m._z[2]);
        float z2 = (_x[1] * m._z[0]) + (_y[1] * m._z[1]) + (_z[1] * m._z[2]);
        float z3 = (_x[2] * m._z[0]) + (_y[2] * m._z[1]) + (_z[2] * m._z[2]);

        _x = {x1, x2, x3};
        _y = {y1, y2, y3};
        _z = {z1, z2, z3};

        return *this;
    }

    const Mat3& Mat3::operator*=(const Vec3 &v) {

        return *this;
    }

    const Mat3& Mat3::operator*=(const float lambda) {
        this->_x[0] *= lambda;
        this->_x[1] *= lambda;
        this->_x[2] *= lambda;

        this->_y[0] *= lambda;
        this->_y[1] *= lambda;
        this->_y[2] *= lambda;

        this->_z[0] *= lambda;
        this->_z[1] *= lambda;
        this->_z[2] *= lambda;

        return *this;
    }

    const Mat3& Mat3::operator+=(const Mat3 &m) {
        this->_x[0] += m._x[0];
        this->_x[1] += m._x[1];
        this->_x[2] += m._x[2];

        this->_y[0] += m._y[0];
        this->_y[1] += m._y[1];
        this->_y[2] += m._y[2];

        this->_z[0] += m._z[0];
        this->_z[1] += m._z[1];
        this->_z[2] += m._z[2];

        return *this;
    }

    const Mat3& Mat3::operator-=(const Mat3 &m) {
        this->_x[0] -= m._x[0];
        this->_x[1] -= m._x[1];
        this->_x[2] -= m._x[2];

        this->_y[0] -= m._y[0];
        this->_y[1] -= m._y[1];
        this->_y[2] -= m._y[2];
    
        this->_z[0] -= m._z[0];
        this->_z[1] -= m._z[1];
        this->_z[2] -= m._z[2];

        return *this;
    }

    std::ostream& operator<<(std::ostream &os, const Mat3 &m) {
        os << std::fixed << std::setprecision(Point::_output_precision)
           << "[" << m._x[0] << ", " << m._y[0] << ", " << m._z[0] << "]\n"
           << "[" << m._x[1] << ", " << m._y[1] << ", " << m._z[1] << "]\n"
           << "[" << m._x[2] << ", " << m._y[2] << ", " << m._z[2] << "]";
        return os;
    }
} // namespace pdm