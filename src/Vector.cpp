#include "pdmath/Vector.hpp"

#include <cmath>

namespace pdm {
    vec3::vec3(const float x, const float y, const float z):
        _x{x}, _y{y}, _z{z}
    { }

    void vec3::normalize() {
        float scaling_factor = 1.0f/length();

        _x *= scaling_factor;
        _y *= scaling_factor;
        _z *= scaling_factor;
    }

    float vec3::length() const {
        float sum_of_squares = { _x*_x + _y*_y + _z*_z };
        return std::sqrt(sum_of_squares);
    }

    float vec3::dot(const vec3 &other) const {
        return _x * other._x +
               _y * other._y +
               _z * other._z;
    }

    vec3 vec3::cross(const vec3 &other) const {
        vec3 result(_y * other._z - _z * other._y,
                    _z * other._x - _x * other._z,
                    _x * other._y - _y * other._x);
        return result;
    }

    vec3 vec3::project_onto(const vec3 &other) const {
        float projection_length = dot(other)/other.dot(other);
        vec3 projection = other;
        return projection * projection_length;
    }

    vec3 vec3::projection_perp(const vec3 &other) const {
        vec3 perp = *this - project_onto(other);
        return perp;
    }

    bool vec3::is_perpendicular(const vec3 &other) const {
        float dot_product = dot(other);

        return dot_product == 0.0f;
    }

    bool operator==(const vec3 &v, const vec3 &w) {
        if(&v == &w) {
            return true;
        }

        float x_diff = (std::fabs(v._x) - std::fabs(w._x));
        float y_diff = (std::fabs(v._y) - std::fabs(w._y));
        float z_diff = (std::fabs(v._z) - std::fabs(w._z));

        std::cout << x_diff << ", " << y_diff << ", " << z_diff << std::endl;

        return x_diff < vec3::epsilon &&
               y_diff < vec3::epsilon &&
               z_diff < vec3::epsilon;
    }

    vec3 operator+(const vec3 &v, const vec3 &w) {
        vec3 result(v._x + w._x,
                    v._y + w._y,
                    v._z + w._z);
        return result;
    }

    vec3 operator-(const vec3 &v, const vec3 &w) {
        vec3 result(v._x - w._x,
                    v._y - w._y,
                    v._z - w._z);
        return result;
    }

    vec3 operator*(vec3 &v, const float multiplier) {
        v._x *= multiplier;
        v._y *= multiplier;
        v._z *= multiplier;

        return v;
    }

    vec3 operator/(vec3 &v, const float divisor) {
        v._x /= divisor;
        v._y /= divisor;
        v._z /= divisor;

        return v;
    }

    vec3 operator/=(vec3 &v, const float divisor) {
        v._x /= divisor;
        v._y /= divisor;
        v._z /= divisor;

        return v;
    }

    vec3 operator*(const float multiplier, const vec3 &vec) {
        vec3 result = vec;

        result._x *= multiplier;
        result._y *= multiplier;
        result._z *= multiplier;

        return result;
    }

    std::ostream& operator<<(std::ostream &os, const vec3 &vec) {
        os << "(" << vec._x << ", "
                  << vec._y << ", "
                  << vec._z << ")";
        return os;
    }

}
