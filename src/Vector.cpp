#include "pdmath/Vector.hpp"

namespace pdm {
    Vec3::Vec3(const float x, const float y, const float z):
        Point(x, y, z)
    { }

    Vec3::Vec3(const Point &p, const Point &s) :
        Point(p - s)
    { }

    float Vec3::dot(const Vec3 &v) const {
#ifdef SOLVER_LOG
            std::cout << *this << " dot " << other << std::endl;
#endif // SOLVER_LOG
        return this->_x * v._x +
               this->_y * v._y +
               this->_z * v._z;
    }

    Vec3 Vec3::cross(const Vec3 &v) const {
        Vec3 result(this->_y * v._z - this->_z * v._y,
                    this->_z * v._x - this->_x * v._z,
                    this->_x * v._y - this->_y * v._x);
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

    Vec3 Vec3::project_onto(const Vec3 &other) const {
        float projection_length = dot(other)/other.dot(other);
        Vec3 projection = other * projection_length;
#ifdef SOLVER_LOG
            std::cout << "v dot w = " << dot(other) << "\n"
                      << "w dot w = " << other.dot(other) << "\n"
                      << "projection length = " << projection_length << "\n"
                      << "projection = " << projection
                      << std::endl;
#endif // SOLVER_LOG
        return projection;
    }

    Vec3 Vec3::projection_perp(const Vec3 &other) const {
        Vec3 perp = *this - project_onto(other);
        return perp;
    }

    float Vec3::length() const {
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
