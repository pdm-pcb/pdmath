#include "pdmath/Point3.hpp"

#include "pdmath/Vector3.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"
#include "pdmath/Matrix3.hpp"

#include <iomanip>

namespace pdm {
    Point3::Point3(const float x, const float y, const float z) :
        _x{x}, _y{y}, _z{z}
    { }

    bool Point3::are_collinear(const Point3 &b, const Point3 &c) const {
        Vec3 vec_ab(b - *this);
        Vec3 vec_ac(c - *this);
        return vec_ab.is_collinear(vec_ac);
    }

    float Point3::distance_to_line(const Line &line) const {
        Vec3 s_minus_p(line._p - *this);
        Vec3 perp = s_minus_p - (s_minus_p.dot(line._v) /
                                 line._v.dot(line._v)) * line._v;
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

    bool Point3::is_zero() const {
        return (_x == 0.0f) &&
               (_y == 0.0f) &&
               (_z == 0.0f);
    }

    bool Point3::operator==(const Point3 &p) const {
        float x_diff = (fabsf(this->_x) - fabsf(p._x));
        float y_diff = (fabsf(this->_y) - fabsf(p._y));
        float z_diff = (fabsf(this->_z) - fabsf(p._z));

        return x_diff < Point3::_epsilon &&
               y_diff < Point3::_epsilon &&
               z_diff < Point3::_epsilon;
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

    const Point3& Point3::operator*=(const Mat3 &m) {
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
        return (p + scalar);
    }

    Point3 operator-(const float scalar, const Point3 &p) {
        return (p - scalar);
    }
    
    Point3 operator*(const float scalar, const Point3 &p) {
        return (p * scalar);
    }

    Point3 operator/(const float scalar, const Point3 &p) {
        return (p / scalar);
    }

    std::ostream& operator<<(std::ostream &os, const Point3 &p) {
        os << std::fixed << std::setprecision(Point3::_output_precision) << "("
           << p._x << ", "
           << p._y << ", "
           << p._z << ")";
        return os;
    }
} // namespace pdm
