#include "pdmath/Vector.hpp"

#include <cmath>

namespace pdm {
    vec3::vec3(const float x, const float y, const float z):
        point(x, y, z)
    { }

    vec3::vec3(const point &p) :
        point(p)
    { }

    vec3::vec3(const point &p, const point &s) :
        point(s - p)
    { }

    float vec3::dot(const vec3 &other) const {
#ifdef SOLVER_LOG
            std::cout << *this << " dot " << other << std::endl;
#endif // SOLVER_LOG
        return _x * other._x +
               _y * other._y +
               _z * other._z;
    }

    vec3 vec3::cross(const vec3 &other) const {
        vec3 result(_y * other._z - _z * other._y,
                    _z * other._x - _x * other._z,
                    _x * other._y - _y * other._x);
#ifdef SOLVER_LOG
            std::cout << *this << " cross " << other << " = " << result
                      << "\n"
                      << "perpendicular to v? "
                      << (result.is_perpendicular(*this)?"true":"false")
                      << "\n"
                      << "perpendicular to w? "
                      << (result.is_perpendicular(other)?"true":"false")
                      << std::endl;
#endif // SOLVER_LOG
        return result;
    }

    vec3 vec3::project_onto(const vec3 &other) const {
        float projection_length = dot(other)/other.dot(other);
        vec3 projection = other * projection_length;
#ifdef SOLVER_LOG
            std::cout << "v dot w = " << dot(other) << "\n"
                      << "w dot w = " << other.dot(other) << "\n"
                      << "projection length = " << projection_length << "\n"
                      << "projection = " << projection
                      << std::endl;
#endif // SOLVER_LOG
        return projection;
    }

    vec3 vec3::projection_perp(const vec3 &other) const {
        vec3 perp = *this - project_onto(other);
        return perp;
    }

    float vec3::length() const {
        float sum_of_squares { _x*_x + _y*_y + _z*_z };
#ifdef SOLVER_LOG
            std::cout << *this << "\n"
                      << "x^2: " << _x*_x << ", "
                      << "y^2: " << _y*_y << ", "
                      << "z^2: " << _z*_z << "\n"
                      << "Sum of suqares: " << sum_of_squares << "\n"
                      << "sqrt(sum): " << sqrtf(sum_of_squares)
                      << std::endl;
#endif // SOLVER_LOG
        return sqrtf(sum_of_squares);
    }

    void vec3::normalize() {
        float _length = length();
        _x /= _length;
        _y /= _length;
        _z /= _length;
    }

    bool vec3::is_collinear(const vec3 &other) const {
        return cross(other).is_zero();
    }

    bool vec3::is_perpendicular(const vec3 &other) const {
        return dot(other) == 0.0f;
    }

    bool vec3::is_zero() const {
        return (_x == 0.0f) &&
               (_y == 0.0f) &&
               (_z == 0.0f);
    }

    bool operator==(const vec3 &v, const vec3 &w) {
        if(&v == &w) {
            return true;
        }

        float x_diff = (fabsf(v._x) - fabsf(w._x));
        float y_diff = (fabsf(v._y) - fabsf(w._y));
        float z_diff = (fabsf(v._z) - fabsf(w._z));

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

    vec3 operator*(const vec3 &v, const float multiplier) {
        vec3 result(v._x * multiplier,
                    v._y * multiplier,
                    v._z * multiplier);
        return result;
    }

    vec3 operator*(const float multiplier, const vec3 &v) {
        return v * multiplier;
    }

    vec3 operator/(const vec3 &v, const float divisor) {
        vec3 result(v._x / divisor,
                    v._y / divisor,
                    v._z / divisor);
        return result;
    }

    vec3 operator/(const float divisor, const vec3 &v) {
        return v / divisor;
    }

    vec3 operator*=(vec3 &v, const float multiplier) {
        v._x /= multiplier;
        v._y /= multiplier;
        v._z /= multiplier;

        return v;
    }

    vec3 operator/=(vec3 &v, const float divisor) {
        v._x /= divisor;
        v._y /= divisor;
        v._z /= divisor;

        return v;
    }
}
