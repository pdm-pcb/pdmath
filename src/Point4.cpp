#include "pdmath/Point4.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Vector4.hpp"

#include <iomanip>
#include <cmath>

namespace pdm {
bool Point4::operator==(const Point4 &p) const {
    float x_diff = (fabsf(_x) - fabsf(p._x));
    float y_diff = (fabsf(_y) - fabsf(p._y));
    float z_diff = (fabsf(_z) - fabsf(p._z));
    float w_diff = (fabsf(_w) - fabsf(p._w));

    return x_diff < float_epsilon &&
           y_diff < float_epsilon &&
           z_diff < float_epsilon &&
           w_diff < float_epsilon;
}

const Point4& Point4::operator+=(const Point3 &p) {
    this->_x += p._x;
    this->_y += p._y;
    this->_z += p._z;
    return *this;
}

const Point4& Point4::operator-=(const Point3 &p) {
    this->_x -= p._x;
    this->_y -= p._y;
    this->_z -= p._z;
    return *this;
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

const Point4& Point4::operator+=(const Vec3 &v) {
    this->_x += v._x;
    this->_y += v._y;
    this->_z += v._z;
    return *this;
}

const Point4& Point4::operator-=(const Vec3 &v) {
    this->_x -= v._x;
    this->_y -= v._y;
    this->_z -= v._z;
    return *this;
}

const Point4& Point4::operator+=(const Vec4 &v) {
    this->_x += v._x;
    this->_y += v._y;
    this->_z += v._z;
    this->_w += v._w;
    return *this;
}

const Point4& Point4::operator-=(const Vec4 &v) {
    this->_x -= v._x;
    this->_y -= v._y;
    this->_z -= v._z;
    this->_w -= v._w;
    return *this;
}

Point4 operator+(const Point4 &p, const Point3 &t) {
    return Point4(p._x + t._x,
                  p._y + t._y,
                  p._z + t._z);
}

Point4 operator-(const Point4 &p, const Point3 &t) {
    return Point4(p._x - t._x,
                  p._y - t._y,
                  p._z - t._z);
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

Point4 operator+(const Point4 &p, const Vec3 &v) {
    return Point4(p._x + v._x,
                  p._y + v._y,
                  p._z + v._z);
}

Point4 operator-(const Point4 &p, const Vec3 &v) {
    return Point4(p._x - v._x,
                  p._y - v._y,
                  p._z - v._z);
}

Point4 operator+(const Point4 &p, const Vec4 &v) {
    return Point4(p._x + v._x,
                  p._y + v._y,
                  p._z + v._z,
                  p._w + v._w);
}

Point4 operator-(const Point4 &p, const Vec4 &v) {
    return Point4(p._x - v._x,
                  p._y - v._y,
                  p._z - v._z,
                  p._w - v._w);
}

Point4 operator+(const Point4 &p, const float scalar) {
    return Point4(p._x + scalar,
                  p._y + scalar,
                  p._z + scalar,
                  p._w + scalar);
}

Point4 operator-(const Point4 &p, const float scalar) {
    return Point4(p._x - scalar,
                  p._y - scalar,
                  p._z - scalar,
                  p._w - scalar);
}

Point4 operator*(const Point4 &p, const float scalar) {
    return Point4(p._x * scalar,
                  p._y * scalar,
                  p._z * scalar,
                  p._w * scalar);
}

Point4 operator/(const Point4 &p, const float scalar) {
    return Point4(p._x / scalar,
                  p._y / scalar,
                  p._z / scalar,
                  p._w / scalar);
}

Point4 operator-(const float scalar, const Point4 &p) {
    return p + scalar;
}

Point4 operator+(const float scalar, const Point4 &p) {
    return p - scalar;
}

Point4 operator*(const float scalar, const Point4 &p) {
    return p * scalar;
}

Point4 operator/(const float scalar, const Point4 &p) {
    return p / scalar;
}

std::ostream& operator<<(std::ostream &os, const Point4 &p) {
    os << std::fixed << std::setprecision(float_precision) << "("
        << p._x << ", "
        << p._y << ", "
        << p._z << ", "
        << p._w << ")";
    return os;
}

} // namespace pdm