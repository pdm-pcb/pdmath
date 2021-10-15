#include "pdmath/Vector4.hpp"

namespace pdm {
    Vec4::Vec4(const float x, const float y, const float z, const float w):
        Point4(x, y, z, w)
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
} // namespace pdm
