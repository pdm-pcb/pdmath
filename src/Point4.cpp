#include "pdmath/Point4.hpp"

#include "pdmath/Vector4.hpp"
#include "pdmath/Matrix4.hpp"
#include "pdmath/Point3.hpp"

#include <iomanip>

namespace pdm {
    Point4::Point4(const float x, const float y, const float z, const float w) :
        _x{x}, _y{y}, _z{z}, _w{w}
    { }

    Point4::Point4(const Point3 &p, const float w) :
        _x{p._x}, _y{p._y}, _z{p._z}, _w{w}
    { }

    bool Point4::is_zero() const {
        return (_x == 0.0f) &&
               (_y == 0.0f) &&
               (_z == 0.0f) &&
               (_w == 0.0f);
    }

    bool Point4::operator==(const Point4 &p) const {
        float x_diff = (fabsf(this->_x) - fabsf(p._x));
        float y_diff = (fabsf(this->_y) - fabsf(p._y));
        float z_diff = (fabsf(this->_z) - fabsf(p._z));
        float w_diff = (fabsf(this->_w) - fabsf(p._w));

        return x_diff < Point4::_epsilon &&
               y_diff < Point4::_epsilon &&
               z_diff < Point4::_epsilon &&
               w_diff < Point4::_epsilon;
    }

    const Point4& Point4::operator+=(const Point4 &p) {
        this->_x += p._x;
        this->_y += p._y;
        this->_z += p._z;
        this->_w += p._w;
        return *this;
    }

    const Point4& Point4::operator-=(const Point4 &p) {
        this->_x -= p._x;
        this->_y -= p._y;
        this->_z -= p._z;
        this->_w -= p._w;
        return *this;
    }

    const Point4& Point4::operator+=(const float scalar) {
        this->_x += scalar;
        this->_y += scalar;
        this->_z += scalar;
        this->_w += scalar;
        return *this;
    }

    const Point4& Point4::operator-=(const float scalar) {
        this->_x -= scalar;
        this->_y -= scalar;
        this->_z -= scalar;
        this->_w -= scalar;
        return *this;
    }

    const Point4& Point4::operator*=(const float scalar) {
        this->_x *= scalar;
        this->_y *= scalar;
        this->_z *= scalar;
        this->_w *= scalar;
        return *this;
    }

    const Point4& Point4::operator/=(const float scalar) {
        this->_x /= scalar;
        this->_y /= scalar;
        this->_z /= scalar;
        this->_w /= scalar;
        return *this;
    }

    const Point4& Point4::operator*=(const Mat4 &m) {
        float x = this->_x * m._r1[0] +
                  this->_y * m._r1[1] +
                  this->_z * m._r1[2] +
                  this->_w * m._r1[3];

        float y = this->_x * m._r2[0] +
                  this->_y * m._r2[1] +
                  this->_z * m._r2[2] +
                  this->_w * m._r2[3];

        float z = this->_x * m._r3[0] +
                  this->_y * m._r3[1] +
                  this->_z * m._r3[2] +
                  this->_w * m._r3[3];

        float w = this->_x * m._r4[0] +
                  this->_y * m._r4[1] +
                  this->_z * m._r4[2] +
                  this->_w * m._r4[3];
        
        this->_x = x;
        this->_y = y;
        this->_z = z;
        this->_w = w;

        return *this;
    }

    Point4 operator+(const Point4 &p, const Point4 &t) {
        return Point4(p._x + t._x,
                      p._y + t._y,
                      p._z + t._z,
                      p._w + t._w);
    }

    Point4 operator-(const Point4 &p, const Point4 &t) {
        return Point4(p._x - t._x,
                      p._y - t._y,
                      p._z - t._z,
                      p._w - t._w);
    }

    Point4 operator+(const Point4 &p, const float scalar){
        return Point4(p._x + scalar,
                      p._y + scalar,
                      p._z + scalar,
                      p._w + scalar);
    }

    Point4 operator-(const Point4 &p, const float scalar){
        return Point4(p._x - scalar,
                      p._y - scalar,
                      p._z - scalar,
                      p._w - scalar);
    }

    Point4 operator*(const Point4 &p, const float scalar){
        return Point4(p._x * scalar,
                      p._y * scalar,
                      p._z * scalar,
                      p._w * scalar);
    }

    Point4 operator/(const Point4 &p, const float scalar){

        return Point4(p._x / scalar,
                      p._y / scalar,
                      p._z / scalar,
                      p._w / scalar);
    }

    Point4 operator+(const float scalar, const Point4 &p) {
        return (p + scalar);
    }

    Point4 operator-(const float scalar, const Point4 &p) {
        return (p - scalar);
    }
    
    Point4 operator*(const float scalar, const Point4 &p) {
        return (p * scalar);
    }

    Point4 operator/(const float scalar, const Point4 &p) {
        return (p / scalar);
    }

    std::ostream& operator<<(std::ostream &os, const Point4 &p) {
        os << std::fixed << std::setprecision(Point4::_output_precision) << "("
           << p._x << ", "
           << p._y << ", "
           << p._z << ", "
           << p._w << ")";
        return os;
    }
} // namespace pdm
