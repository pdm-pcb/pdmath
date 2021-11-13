#include "pdmath/Vector4.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Point3.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Vector3.hpp"

#include <iomanip>
#include <cmath>

namespace pdm {
const Vec4 Vec4::zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
const Vec4 Vec4::one  = Vec4(1.0f, 1.0f, 1.0f, 0.0f);

float Vec4::dot(const Vec4 &v) const {
    return this->_x * v._x +
           this->_y * v._y +
           this->_z * v._z +
           this->_w * v._w;
}

Vec4 Vec4::normalized() const {
    float _length = length();

    if(fabsf(_length - 1.0f) < float_epsilon) {
        return Vec4(*this);
    }
    return Vec4(_x / _length,
                _y / _length,
                _z / _length);
}

Vec4 Vec4::cross(const Vec4 &v) const {
    return Vec4(this->_y * v._z - this->_z * v._y,
                this->_z * v._x - this->_x * v._z,
                this->_x * v._y - this->_y * v._x);
}

Vec4 Vec4::project_onto(const Vec4 &v) const {
    float projection_length = dot(v)/v.dot(v);
    return Vec4(v * projection_length);
}

Vec4 Vec4::projection_perp(const Vec4 &v) const {
    Vec4 perp = *this - project_onto(v);
    return perp;
}

bool Vec4::operator==(const Vec4 &p) const {
    float x_diff = (fabsf(_x) - fabsf(p._x));
    float y_diff = (fabsf(_y) - fabsf(p._y));
    float z_diff = (fabsf(_z) - fabsf(p._z));
    float w_diff = (fabsf(_w) - fabsf(p._w));

    return x_diff < float_epsilon &&
           y_diff < float_epsilon &&
           z_diff < float_epsilon &&
           w_diff < float_epsilon;
}
Vec4 operator+(const Vec4 &v, const Vec3 &w) {
    return Vec4(v._x + w._x,
                v._y + w._y,
                v._z + w._z,
                v._w);
}

Vec4 operator-(const Vec4 &v, const Vec3 &w) {
    return Vec4(v._x - w._x,
                v._y - w._y,
                v._z - w._z,
                v._w);
}

Vec4 operator+(const Vec4 &v, const Vec4 &w) {
    return Vec4(v._x + w._x,
                v._y + w._y,
                v._z + w._z,
                v._w + w._w);
}

Vec4 operator-(const Vec4 &v, const Vec4 &w) {
    return Vec4(v._x - w._x,
                v._y - w._y,
                v._z - w._z,
                v._w - w._w);
}

Vec4 operator+(const Vec4 &v, const Point3 &p) {
    return Vec4(v._x + p._x,
                v._y + p._y,
                v._z + p._z,
                v._w);
}

Vec4 operator-(const Vec4 &v, const Point3 &p) {
    return Vec4(v._x - p._x,
                v._y - p._y,
                v._z - p._z,
                v._w);
}

Vec4 operator+(const Vec4 &v, const Point4 &p) {
    return Vec4(v._x + p._x,
                v._y + p._y,
                v._z + p._z,
                v._w + p._w);
}

Vec4 operator-(const Vec4 &v, const Point4 &p) {
    return Vec4(v._x - p._x,
                v._y - p._y,
                v._z - p._z,
                v._w - p._w);
}

Vec4 operator+(const Vec4 &v, const float scalar) {
    return Vec4(v._x + scalar,
                v._y + scalar,
                v._z + scalar,
                v._w + scalar);
}

Vec4 operator-(const Vec4 &v, const float scalar) {
    return Vec4(v._x - scalar,
                v._y - scalar,
                v._z - scalar,
                v._w - scalar);
}

Vec4 operator*(const Vec4 &v, const float scalar) {
    return Vec4(v._x * scalar,
                v._y * scalar,
                v._z * scalar,
                v._w * scalar);
}

Vec4 operator/(const Vec4 &v, const float scalar) {
    return Vec4(v._x / scalar,
                v._y / scalar,
                v._z / scalar,
                v._w / scalar);
}

Vec4 operator+(const float scalar, const Vec4 &v) {
    return v + scalar;
}

Vec4 operator-(const float scalar, const Vec4 &v) {
    return v - scalar;
}

Vec4 operator*(const float scalar, const Vec4 &v) {
    return v * scalar;
}

Vec4 operator/(const float scalar, const Vec4 &v) {
    return v / scalar;
}

std::ostream& operator<<(std::ostream &os, const Vec4 &p) {
    os << std::fixed << std::setprecision(float_precision) << "("
        << p._x << ", "
        << p._y << ", "
        << p._z << ", "
        << p._w << ")";
    return os;
}

} // namespace pdm