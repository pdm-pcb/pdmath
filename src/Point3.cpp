#include "pdmath/Point3.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Matrix3.hpp"
#include "pdmath/Matrix4.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"

#include <iomanip>
#include <cmath>

namespace pdm {
bool Point3::are_collinear(const Point3 &b, const Point3 &c) const {
    Vec3 vec_ab(b - *this);
    Vec3 vec_ac(c - *this);
    return vec_ab.is_collinear(vec_ac);
}

float Point3::distance_to_line(const Line &line) const {
    Vec3 s_minus_p(line._p - *this);
    Vec3 perp = s_minus_p - line._v * (s_minus_p.dot(line._v) /
                line._v.dot(line._v));
    return perp.length();
}

bool Point3::is_on_plane(const Plane &plane) const {
    Vec3 point_vector(*this - plane._p);
    return point_vector.dot(plane._n) == 0.0f;
}

float Point3::distance_to_plane(const Plane &plane) const {
    Vec3 point_vector(*this - plane._p);
    return point_vector.dot(plane._n);
}

Point3 Point3::nearest_approach(const Line &line) const {
    Vec3 q_minus_p = static_cast<Vec3>(*this) - line._p;
    float t = line._v.dot(q_minus_p);
    t /= line._v.dot(line._v);
    Vec3 offset = line._v * t;

    std::cout << "\nQ-P: "    << q_minus_p << "\n"
                << "P1-P2: "  << line._v << "\n"
                << "t : "     << t << "\n"
                << "offset: " << offset << "\n"
                << "result: " << line._p + offset << "\n"
                << std::endl;

    return line._p + offset;
}

Point3 Point3::nearest_approach_segment(const Line &line) const {
    Vec3 q_minus_p = static_cast<Vec3>(*this) - line._p;
    // std::cout << "P1-P0: " << line._v << "\n"
    //           << "Q: " << *this << "\n"
    //           << "Q-P0: " << q_minus_p << "\n"
    //           << "(P1-P0).(Q-P0): " << line._v.dot(q_minus_p)
    //           << std::endl;

    float t = line._v.dot(q_minus_p);
    // std::cout << "t : " << t << std::endl;
    t /= line._v.dot(line._v);
    // std::cout << "t scaled : " << t << std::endl;

    if(t <= 0.0f) {
        // std::cout << "result: " << line._p << "\n" << std::endl;
        return line._p;
    }
    if(t >= 1.0f) {
        // std::cout << "result: " << line._v << "\n" << std::endl;
        return static_cast<Point3>(line._v);
    }

    Vec3 offset = line._v * t;
    // std::cout << "offset: " << offset << "\n"
    //           << "result: " << line._p + offset << "\n"
    //           << std::endl;

    return line._p + offset;
}

Point3 Point3::nearest_approach_ray(const Line &line) const {
    Vec3 q_minus_p = static_cast<Vec3>(*this) - line._p;
    // std::cout << "\nQ-P: " << q_minus_p << "\n"
    //           << "P1-P2: " << line._v << std::endl;

    float t = line._v.dot(q_minus_p);
    // std::cout << "t : " << t << std::endl;
    t /= line._v.dot(line._v);
    // std::cout << "t': " << t << std::endl;

    if(t <= 0.0f) {
        // std::cout << "result: " << line._p << "\n" << std::endl;
        return line._p;
    }

    Vec3 offset = line._v * t;
    // std::cout << "offset: " << offset << "\n"
    //           << "result: " << line._p + offset << "\n"
    //           << std::endl;

    return line._p + offset;
}

Point3::Point3() noexcept:
    _x{0.0f}, _y{0.0f}, _z{0.0f}
{ }

Point3::Point3(const float x, const float y, const float z) noexcept:
    _x{x}, _y{y}, _z{z}
{ }

Point3::Point3(const Vec3 &v) noexcept:
    _x{v._x}, _y{v._y}, _z{v._z}
{ }

bool Point3::operator==(const Point3 &p) const {
    float x_diff = (fabsf(_x) - fabsf(p._x));
    float y_diff = (fabsf(_y) - fabsf(p._y));
    float z_diff = (fabsf(_z) - fabsf(p._z));

    return x_diff < float_epsilon &&
           y_diff < float_epsilon &&
           z_diff < float_epsilon;
}

const Point3& Point3::operator+=(const Point3 &p) {
    this->_x += p._x;
    this->_y += p._y;
    this->_z += p._z;
    return *this;
}

const Point3& Point3::operator-=(const Point3 &p) {
    this->_x -= p._x;
    this->_y -= p._y;
    this->_z -= p._z;
    return *this;
}

const Point3& Point3::operator+=(const Point4 &p) {
    this->_x += p._x;
    this->_y += p._y;
    this->_z += p._z;
    return *this;
}

const Point3& Point3::operator-=(const Point4 &p) {
    this->_x -= p._x;
    this->_y -= p._y;
    this->_z -= p._z;
    return *this;
}

const Point3& Point3::operator+=(const float scalar) {
    this->_x += scalar;
    this->_y += scalar;
    this->_z += scalar;
    return *this;
}

const Point3& Point3::operator-=(const float scalar) {
    this->_x -= scalar;
    this->_y -= scalar;
    this->_z -= scalar;
    return *this;
}

const Point3& Point3::operator*=(const float scalar) {
    this->_x *= scalar;
    this->_y *= scalar;
    this->_z *= scalar;
    return *this;
}

const Point3& Point3::operator/=(const float scalar) {
    this->_x /= scalar;
    this->_y /= scalar;
    this->_z /= scalar;
    return *this;
}

const Point3& Point3::operator+=(const Vec3 &v) {
    this->_x += v._x;
    this->_y += v._y;
    this->_z += v._z;
    return *this;
}

const Point3& Point3::operator-=(const Vec3 &v) {
    this->_x -= v._x;
    this->_y -= v._y;
    this->_z -= v._z;
    return *this;
}

const Point3& Point3::operator+=(const Vec4 &v) {
    this->_x += v._x;
    this->_y += v._y;
    this->_z += v._z;
    return *this;
}

const Point3& Point3::operator-=(const Vec4 &v) {
    this->_x -= v._x;
    this->_y -= v._y;
    this->_z -= v._z;
    return *this;
}

const Point3& Point3::operator*=(const Mat3 &m) {
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

const Point3& Point3::operator*=(const Mat4 &m) {
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

Point3 operator+(const Point3 &p, const Point3 &t) {
    return Point3(p._x + t._x,
                  p._y + t._y,
                  p._z + t._z);
}

Point3 operator-(const Point3 &p, const Point3 &t) {
    return Point3(p._x - t._x,
                  p._y - t._y,
                  p._z - t._z);
}

Point3 operator+(const Point3 &p, const Point4 &t) {
    return Point3(p._x + t._x,
                  p._y + t._y,
                  p._z + t._z);
}

Point3 operator-(const Point3 &p, const Point4 &t) {
    return Point3(p._x - t._x,
                  p._y - t._y,
                  p._z - t._z);
}

Point3 operator+(const Point3 &p, const Vec3 &v) {
    return Point3(p._x + v._x,
                  p._y + v._y,
                  p._z + v._z);
}

Point3 operator-(const Point3 &p, const Vec3 &v) {
    return Point3(p._x + v._x,
                  p._y + v._y,
                  p._z + v._z);
}

Point3 operator+(const Point3 &p, const Vec4 &v) {
    return Point3(p._x + v._x,
                  p._y + v._y,
                  p._z + v._z);
}

Point3 operator-(const Point3 &p, const Vec4 &v) {
    return Point3(p._x + v._x,
                  p._y + v._y,
                  p._z + v._z);
}

Point3 operator+(const Point3 &p, const float scalar){
    return Point3(p._x + scalar,
                  p._y + scalar,
                  p._z + scalar);
}

Point3 operator-(const Point3 &p, const float scalar){
    return Point3(p._x - scalar,
                  p._y - scalar,
                  p._z - scalar);
}

Point3 operator*(const Point3 &p, const float scalar){
    return Point3(p._x * scalar,
                  p._y * scalar,
                  p._z * scalar);
}

Point3 operator/(const Point3 &p, const float scalar){

    return Point3(p._x / scalar,
                  p._y / scalar,
                  p._z / scalar);
}

Point3 operator+(const float scalar, const Point3 &p) {
    return p + scalar;
}

Point3 operator-(const float scalar, const Point3 &p) {
    return p - scalar;
}

Point3 operator*(const float scalar, const Point3 &p) {
    return p * scalar;
}

Point3 operator/(const float scalar, const Point3 &p) {
    return p / scalar;
}

std::ostream& operator<<(std::ostream &os, const Point3 &p) {
    os << std::fixed << std::setprecision(float_precision) << "("
        << p._x << ", "
        << p._y << ", "
        << p._z << ")";
    return os;
}
} // namespace pdm
