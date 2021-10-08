#include "pdmath/Vector.hpp"

namespace pdm {
    Vec3::Vec3(const float x, const float y, const float z):
        Point(x, y, z)
    { }

    Vec3::Vec3(const Point &p, const Point &s) :
        Point(p - s)
    { }

    float Vec3::dot(const Vec3 &v) const {
        return this->_x * v._x +
               this->_y * v._y +
               this->_z * v._z;
    }

    Vec3 Vec3::cross(const Vec3 &v) const {
        return Vec3(this->_y * v._z - this->_z * v._y,
                    this->_z * v._x - this->_x * v._z,
                    this->_x * v._y - this->_y * v._x);
    }

    Vec3 Vec3::project_onto(const Vec3 &v) const {
        float projection_length = dot(v)/v.dot(v);
        return v * projection_length;
    }

    Vec3 Vec3::projection_perp(const Vec3 &v) const {
        Vec3 perp = *this - project_onto(v);
        return perp;
    }

    float Vec3::length() const {
        return sqrtf(_x*_x + _y*_y + _z*_z);
    }

    void Vec3::normalize() {
        float _length = length();
        _x /= _length;
        _y /= _length;
        _z /= _length;
    }

    bool Vec3::is_collinear(const Vec3 &v) const {
        return cross(v).is_zero();
    }

    bool Vec3::is_perpendicular(const Vec3 &v) const {
        return dot(v) == 0.0f;
    }
} // namespace pdm
