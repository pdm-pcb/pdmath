#include "pdmath/Vector3.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Point3.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Matrix3.hpp"
#include "pdmath/Matrix4.hpp"

#include <iomanip>
#include <cmath>

namespace pdm {
const Vec3 Vec3::zero(0.0f, 0.0f, 0.0f);
const Vec3 Vec3::one(1.0f, 1.0f, 1.0f);

float Vec3::length() const {
    return sqrtf(_x*_x + _y*_y + _z*_z);
}

float Vec3::dot(const Vec3 &v) const {
    return this->_x * v._x +
           this->_y * v._y +
           this->_z * v._z;
}

Vec3 Vec3::normalized() const {
    float _length = length();

    if(fabsf(_length - 1.0f) < float_epsilon) {
        return Vec3(*this);
    }
    return Vec3(_x / _length,
                _y / _length,
                _z / _length);
}

Vec3 Vec3::cross(const Vec3 &v) const {
    return Vec3(this->_y * v._z - this->_z * v._y,
                this->_z * v._x - this->_x * v._z,
                this->_x * v._y - this->_y * v._x);
}

Vec3 Vec3::project_onto(const Vec3 &v) const {
    float projection_length = dot(v)/v.dot(v);
    return Vec3(v * projection_length);
}

Vec3 Vec3::projection_perp(const Vec3 &v) const {
    Vec3 perp = *this - project_onto(v);
    return perp;
}

bool Vec3::is_collinear(const Vec3 &v) const {
    Vec3 product = cross(v);

    return product._x == 0.0f &&
           product._y == 0.0f &&
           product._z == 0.0f;
}

bool Vec3::is_perpendicular(const Vec3 &v) const {
    return dot(v) == 0.0f;
}

Vec3::Vec3() noexcept :
    _x{0.0f}, _y{0.0f}, _z{0.0f}
{ }

Vec3::Vec3(const float x, const float y, const float z) noexcept :
    _x{x}, _y{y}, _z{z}
{ }

Vec3::Vec3(const Point3 &p) noexcept :
    _x{p._x}, _y{p._y}, _z{p._z}
{ }

bool Vec3::operator==(const Vec3 &v) const {
    float x_diff = (fabsf(_x) - fabsf(v._x));
    float y_diff = (fabsf(_y) - fabsf(v._y));
    float z_diff = (fabsf(_z) - fabsf(v._z));

    return x_diff < float_epsilon &&
            y_diff < float_epsilon &&
            z_diff < float_epsilon;
}

const Vec3& Vec3::operator+=(const Vec3 &v) {
    this->_x += v._x;
    this->_y += v._y;
    this->_z += v._z;
    return *this;
}

const Vec3& Vec3::operator-=(const Vec3 &v) {
    this->_x -= v._x;
    this->_y -= v._y;
    this->_z -= v._z;
    return *this;
}

const Vec3& Vec3::operator+=(const Vec4 &v) {
    this->_x += v._x;
    this->_y += v._y;
    this->_z += v._z;
    return *this;
}

const Vec3& Vec3::operator-=(const Vec4 &v) {
    this->_x -= v._x;
    this->_y -= v._y;
    this->_z -= v._z;
    return *this;
}

const Vec3& Vec3::operator+=(const float scalar) {
    this->_x += scalar;
    this->_y += scalar;
    this->_z += scalar;
    return *this;
}

const Vec3& Vec3::operator-=(const float scalar) {
    this->_x -= scalar;
    this->_y -= scalar;
    this->_z -= scalar;
    return *this;
}

const Vec3& Vec3::operator*=(const float scalar) {
    this->_x *= scalar;
    this->_y *= scalar;
    this->_z *= scalar;
    return *this;
}

const Vec3& Vec3::operator/=(const float scalar) {
    this->_x /= scalar;
    this->_y /= scalar;
    this->_z /= scalar;
    return *this;
}

const Vec3& Vec3::operator+=(const Point3 &p) {
    this->_x += p._x;
    this->_y += p._y;
    this->_z += p._z;
    return *this;
}

const Vec3& Vec3::operator-=(const Point3 &p) {
    this->_x -= p._x;
    this->_y -= p._y;
    this->_z -= p._z;
    return *this;
}

const Vec3& Vec3::operator+=(const Point4 &p) {
    this->_x += p._x;
    this->_y += p._y;
    this->_z += p._z;
    return *this;
}

const Vec3& Vec3::operator-=(const Point4 &p) {
    this->_x -= p._x;
    this->_y -= p._y;
    this->_z -= p._z;
    return *this;
}

const Vec3& Vec3::operator*=(const Mat3 &m) {
    float x = this->_x * m._m[0][0] +
                this->_y * m._m[0][1] +
                this->_z * m._m[0][2];

    float y = this->_x * m._m[1][0] +
                this->_y * m._m[1][1] +
                this->_z * m._m[1][2];

    float z = this->_x * m._m[2][0] +
                this->_y * m._m[2][1] +
                this->_z * m._m[2][2];
    
    this->_x = x;
    this->_y = y;
    this->_z = z;

    return *this;
}

const Vec3& Vec3::operator*=(const Mat4 &m) {
    float x = this->_x * m._m[0][0] +
                this->_y * m._m[0][1] +
                this->_z * m._m[0][2];

    float y = this->_x * m._m[1][0] +
                this->_y * m._m[1][1] +
                this->_z * m._m[1][2];

    float z = this->_x * m._m[2][0] +
                this->_y * m._m[2][1] +
                this->_z * m._m[2][2];
    
    this->_x = x;
    this->_y = y;
    this->_z = z;

    return *this;
}

Vec3 operator+(const Vec3 &v, const Vec3 &w) {
    return Vec3(v._x + w._x,
                v._y + w._y,
                v._z + w._z);
}

Vec3 operator-(const Vec3 &v, const Vec3 &w) {
    return Vec3(v._x - w._x,
                v._y - w._y,
                v._z - w._z);
}

Vec3 operator+(const Vec3 &v, const Point3 &p) {
    return Vec3(v._x + p._x,
                v._y + p._y,
                v._z + p._z);
}

Vec3 operator-(const Vec3 &v, const Point3 &p) {
    return Vec3(v._x - p._x,
                v._y - p._y,
                v._z - p._z);
}

Vec3 operator-(const Point3 &p, const Point3 &t) {
    return Vec3(p._x - t._x,
                p._y - t._y,
                p._z - t._z);
}

Vec3 operator-(const Point3 &p, const Point4 &t) {
    return Vec3(p._x - t._x,
                p._y - t._y,
                p._z - t._z);
}

Vec3 operator+(const Vec3 &v, const float scalar){
    return Vec3(v._x + scalar,
                v._y + scalar,
                v._z + scalar);
}

Vec3 operator-(const Vec3 &v, const float scalar){
    return Vec3(v._x - scalar,
                v._y - scalar,
                v._z - scalar);
}

Vec3 operator*(const Vec3 &v, const float scalar){
    return Vec3(v._x * scalar,
                v._y * scalar,
                v._z * scalar);
}

Vec3 operator/(const Vec3 &v, const float scalar){

    return Vec3(v._x / scalar,
                v._y / scalar,
                v._z / scalar);
}

Vec3 operator+(const float scalar, const Vec3 &v) {
    return v + scalar;
}

Vec3 operator-(const float scalar, const Vec3 &v) {
    return v - scalar;
}

Vec3 operator*(const float scalar, const Vec3 &v) {
    return v * scalar;
}

Vec3 operator/(const float scalar, const Vec3 &v) {
    return v / scalar;
}

std::ostream& operator<<(std::ostream &os, const Vec3 &p) {
    os << std::fixed << std::setprecision(float_precision) << "("
        << p._x << ", "
        << p._y << ", "
        << p._z << ")";
    return os;
}

} // namespace pdm
