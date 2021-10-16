#include "pdmath/Vector4.hpp"

#include "pdmath/Vector3.hpp"
#include "pdmath/Matrix4.hpp"

namespace pdm {
    Vec4::Vec4(const float x, const float y, const float z, const float w):
        Point4(x, y, z, w)
    { }

    Vec4::Vec4(const Vec3 &v, const float w) :
        Point4(v._x, v._y, v._z, w)
    { }

    Vec4::Vec4(const Point4 &p):
        Point4(p)
    { }

    float Vec4::dot(const Vec4 &v) const {
        return this->_x * v._x +
               this->_y * v._y +
               this->_z * v._z +
               this->_w * v._w;
    }

    float Vec4::length() const {
        return sqrtf(_x*_x + _y*_y + _z*_z + _w*_w);
    }

    void Vec4::normalize() {
        float _length = length();
        _x /= _length;
        _y /= _length;
        _z /= _length;
        _w /= _length;
    }

    const Vec4& Vec4::operator+=(const Vec4 &v) {
        this->_x += v._x;
        this->_y += v._y;
        this->_z += v._z;
        this->_w += v._w;
        return *this;
    }

    const Vec4& Vec4::operator-=(const Vec4 &v) {
        this->_x -= v._x;
        this->_y -= v._y;
        this->_z -= v._z;
        this->_w -= v._w;
        return *this;
    }

    const Vec4& Vec4::operator+=(const float scalar) {
        this->_x += scalar;
        this->_y += scalar;
        this->_z += scalar;
        this->_w += scalar;
        return *this;
    }

    const Vec4& Vec4::operator-=(const float scalar) {
        this->_x -= scalar;
        this->_y -= scalar;
        this->_z -= scalar;
        this->_w -= scalar;
        return *this;
    }

    const Vec4& Vec4::operator*=(const float scalar) {
        this->_x *= scalar;
        this->_y *= scalar;
        this->_z *= scalar;
        this->_w *= scalar;
        return *this;
    }

    const Vec4& Vec4::operator/=(const float scalar) {
        this->_x /= scalar;
        this->_y /= scalar;
        this->_z /= scalar;
        this->_w /= scalar;
        return *this;
    }

    const Vec4& Vec4::operator*=(const Mat4 &m) {
        float x = this->_x * m._elem[0][0] +
                  this->_y * m._elem[0][1] +
                  this->_z * m._elem[0][2] +
                  this->_w * m._elem[0][3];

        float y = this->_x * m._elem[1][0] +
                  this->_y * m._elem[1][1] +
                  this->_z * m._elem[1][2] +
                  this->_w * m._elem[1][3];

        float z = this->_x * m._elem[2][0] +
                  this->_y * m._elem[2][1] +
                  this->_z * m._elem[2][2] +
                  this->_w * m._elem[2][3];

        float w = this->_x * m._elem[3][0] +
                  this->_y * m._elem[3][1] +
                  this->_z * m._elem[3][2] +
                  this->_w * m._elem[3][3];
        
        this->_x = x;
        this->_y = y;
        this->_z = z;
        this->_w = w;

        return *this;
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

    Vec4 operator+(const Point4 &p, const Vec4 &v) {
        return (v + p);
    }

    Vec4 operator-(const Point4 &p, const Vec4 &v) {
        return (v - p);
    }

    Vec4 operator+(const Vec4 &v, const float scalar){
        return Vec4(v._x + scalar,
                    v._y + scalar,
                    v._z + scalar,
                    v._w + scalar);
    }

    Vec4 operator-(const Vec4 &v, const float scalar){
        return Vec4(v._x - scalar,
                    v._y - scalar,
                    v._z - scalar,
                    v._w - scalar);
    }

    Vec4 operator*(const Vec4 &v, const float scalar){
        return Vec4(v._x * scalar,
                    v._y * scalar,
                    v._z * scalar,
                    v._w * scalar);
    }

    Vec4 operator/(const Vec4 &v, const float scalar){

        return Vec4(v._x / scalar,
                    v._y / scalar,
                    v._z / scalar,
                    v._w / scalar);
    }

    Vec4 operator+(const float scalar, const Vec4 &v) {
        return (v + scalar);
    }

    Vec4 operator-(const float scalar, const Vec4 &v) {
        return (v - scalar);
    }
    
    Vec4 operator*(const float scalar, const Vec4 &v) {
        return (v * scalar);
    }

    Vec4 operator/(const float scalar, const Vec4 &v) {
        return (v / scalar);
    }
} // namespace pdm
