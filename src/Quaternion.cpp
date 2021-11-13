#include "pdmath/Quaternion.hpp"

#include "pdmath/util.hpp"

#include <cmath>
#include <numbers>
#include <iomanip>

namespace pdm {
    Quat::Quat(float theta, Vec3 axis) noexcept
    {
        if(theta == 0.0f) {
            _w = theta;
            _v = axis;
            return;
        }
        
        _w = std::cos(theta/2.0f);
        _v = axis.normalized();
        _v *= std::sin(theta/2.0f);
    }

    Quat::Quat(float theta, float x, float y, float z) noexcept {
        _w = theta;
        _v = Vec3(x, y, z);
    }

    const Quat Quat::identity(1.0f, 0.0f, 0.0f, 0.0f);

    Quat Quat::inverted() {
        return Quat(this->_w, -this->_v._x, -this->_v._y, -this->_v._z);
    }

    Quat Quat::normalized() {
        float _length = length();

        if(fabsf(_length - 1.0f) < float_epsilon) {
            return Quat(*this);
        }
        else {
            return Quat(_w    / _length,
                        _v._x / _length,
                        _v._y / _length,
                        _v._z / _length);
        }
    }

    float Quat::length() {
        return sqrtf(_w*_w + _v._x*_v._x + _v._y*_v._y + _v._z*_v._z);
    }

    bool Quat::operator==(const Quat &q) const {
        float diff = fabsf(this->_w) - fabsf(q._w);
        return fabsf(diff) < float_epsilon && this->_v == q._v;
    }

    const Quat& Quat::operator*=(const Quat &q) {
        float w = (this->_w * q._w) - this->_v.dot(q._v);
        Vec3 v((this->_w * q._v) + (q._w * this->_v) + this->_v.cross(q._v));

        this->_w = w;
        this->_v = v;

        return *this;
    }

    Quat operator*(const Quat &q, const Quat &p) {
        float w = (q._w * p._w) - q._v.dot(p._v);
        Vec3 v((q._w * p._v) + (p._w * q._v) + q._v.cross(p._v));

        return Quat(w, v._x, v._y, v._z);
    }

    std::ostream& operator<<(std::ostream &os, const Quat &q) {
        os << std::fixed << std::setprecision(float_precision) << "["
            << q._w << ", "
            << q._v << "]";
        return os;
    }
} // namespace pdm