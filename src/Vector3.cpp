#include "pdmath/Vector3.hpp"

#include "pdmath/Matrix3.hpp"

namespace pdm {
    Vec3::Vec3(const float x, const float y, const float z):
        Point3(x, y, z)
    { }

    Vec3::Vec3(const Point3 &p):
        Point3(p)
    { }

    void Vec3::normalize() {
        float _length = length();
        _x /= _length;
        _y /= _length;
        _z /= _length;
    }

    float Vec3::dot(const Vec3 &v) const {
        return this->_x * v._x +
               this->_y * v._y +
               this->_z * v._z;
    }

    float Vec3::length() const {
        return sqrtf(_x*_x + _y*_y + _z*_z);
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
        return cross(v).is_zero();
    }

    bool Vec3::is_perpendicular(const Vec3 &v) const {
        return dot(v) == 0.0f;
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

    const Vec3& Vec3::operator*=(const Mat3 &m) {
        float x = (m._elem[0][0] * this->_x) +
                  (m._elem[0][1] * this->_y) +
                  (m._elem[0][2] * this->_z);
    
        float y = (m._elem[1][0] * this->_x) +
                  (m._elem[1][1] * this->_y) +
                  (m._elem[1][2] * this->_z);

        float z = (m._elem[2][0] * this->_x) +
                  (m._elem[2][1] * this->_y) +
                  (m._elem[2][2] * this->_z);
        
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

    Vec3 operator+(const Point3 &p, const Vec3 &v) {
        return (v + p);
    }

    Vec3 operator-(const Point3 &p, const Vec3 &v) {
        return (v - p);
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
        return (v + scalar);
    }
    
    Vec3 operator-(const float scalar, const Vec3 &v) {
        return (v - scalar);
    }
    
    Vec3 operator*(const float scalar, const Vec3 &v) {
        return (v * scalar);
    }

    Vec3 operator/(const float scalar, const Vec3 &v) {
        return (v / scalar);
    }

} // namespace pdm
