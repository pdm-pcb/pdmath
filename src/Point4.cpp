#include "pdmath/Point4.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Matrix4.hpp"
#include "pdmath/Line4.hpp"
#include "pdmath/Plane.hpp"
#include "pdmath/Point3.hpp"

#include <iomanip>

namespace pdm {
    bool Point4::are_collinear(const Point4 &b, const Point4 &c) const {
        Vec4 vec_ab(b - *this);
        Vec4 vec_ac(c - *this);
        return vec_ab.is_collinear(vec_ac);
    }

    Point4 Point4::nearest_approach(const Line4 &line) const {
        Vec4 q_minus_p = static_cast<Vec4>(*this) - line._p;
        // std::cout << "\nQ-P: " << q_minus_p << "\n"
        //           << "P1-P2: " << line._v << std::endl;

        float t = line._v.dot(q_minus_p);
        // std::cout << "t : " << t << std::endl;
        t /= line._v.dot(line._v);
        // std::cout << "t': " << t << std::endl;

        Vec4 offset = t * line._v;
        // std::cout << "offset: " << offset << "\n"
        //           << "result: " << line._p + offset << "\n"
        //           << std::endl;
    
        return line._p + offset;
    }

    Point4 Point4::nearest_approach_segment(const Line4 &line) const {
        Vec4 q_minus_p = static_cast<Vec4>(*this) - line._p;
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
            return static_cast<Point4>(line._v);
        }

        Vec4 offset = t * line._v;
        // std::cout << "offset: " << offset << "\n"
        //           << "result: " << line._p + offset << "\n"
        //           << std::endl;

        return line._p + offset;
    }

    Point4 Point4::nearest_approach_ray(const Line4 &line) const {
        Vec4 q_minus_p = static_cast<Vec4>(*this) - line._p;
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

        Vec4 offset = t * line._v;
        // std::cout << "offset: " << offset << "\n"
        //           << "result: " << line._p + offset << "\n"
        //           << std::endl;

        return line._p + offset;
    }

    float Point4::distance_to_line(const Line4 &line) const {
        Vec4 s_minus_p(line._p - *this);
        Vec4 perp = s_minus_p - (s_minus_p.dot(line._v) /
                                 line._v.dot(line._v)) * line._v;
        return perp.length();
    }

    bool Point4::is_on_plane(const Plane &plane) const {
        Vec4 point_vector(*this - plane._p);
        return point_vector.dot(plane._n) == 0.0f;
    }

    float Point4::distance_to_plane(const Plane &plane) const {
        Vec4 point_vector(*this - plane._p);
        return point_vector.dot(plane._n);
    }

    bool Point4::is_zero() const {
        return (_x == 0.0f) &&
               (_y == 0.0f) &&
               (_z == 0.0f) &&
               (_w == 0.0f);
    }

    Point4::Point4(const float x, const float y, const float z, const float w) :
        _x{x}, _y{y}, _z{z}, _w{w}
    { }

    Point4::Point4(const float x, const float y, const float z) :
        _x{x}, _y{y}, _z{z}, _w{1.0f}
    { }

    Point4::Point4(const Point3 &p, const float w) :
        _x{p._x}, _y{p._y}, _z{p._z}, _w{w}
    { }

    Point4::Point4(const Point3 &p) :
        _x{p._x}, _y{p._y}, _z{p._z}, _w{1.0f}
    { }

    bool Point4::operator==(const Point4 &p) const {
        float x_diff = (fabsf(this->_x) - fabsf(p._x));
        float y_diff = (fabsf(this->_y) - fabsf(p._y));
        float z_diff = (fabsf(this->_z) - fabsf(p._z));
        float w_diff = (fabsf(this->_w) - fabsf(p._w));

        return x_diff < Point4::epsilon &&
               y_diff < Point4::epsilon &&
               z_diff < Point4::epsilon &&
               w_diff < Point4::epsilon;
    }

    const Point4& Point4::operator+=(const Point4 &p) {
        this->_x += p._x;
        this->_y += p._y;
        this->_z += p._z;
        this->_w += p._w;
        return *this;
    }

    const Point4& Point4::operator-=(const Point4 &p) {
        this->_x -= p._x;
        this->_y -= p._y;
        this->_z -= p._z;
        this->_w -= p._w;
        return *this;
    }

    const Point4& Point4::operator+=(const Point3 &p) {
        this->_x += p._x;
        this->_y += p._y;
        this->_z += p._z;
        return *this;
    }

    const Point4& Point4::operator-=(const Point3 &p) {
        this->_x -= p._x;
        this->_y -= p._y;
        this->_z -= p._z;
        return *this;
    }

    const Point4& Point4::operator+=(const float scalar) {
        this->_x += scalar;
        this->_y += scalar;
        this->_z += scalar;
        this->_w += scalar;
        return *this;
    }

    const Point4& Point4::operator-=(const float scalar) {
        this->_x -= scalar;
        this->_y -= scalar;
        this->_z -= scalar;
        this->_w -= scalar;
        return *this;
    }

    const Point4& Point4::operator*=(const float scalar) {
        this->_x *= scalar;
        this->_y *= scalar;
        this->_z *= scalar;
        this->_w *= scalar;
        return *this;
    }

    const Point4& Point4::operator/=(const float scalar) {
        this->_x /= scalar;
        this->_y /= scalar;
        this->_z /= scalar;
        this->_w /= scalar;
        return *this;
    }

    const Point4& Point4::operator*=(const Mat4 &m) {
        float x = this->_x * m._m[0][0] +
                  this->_y * m._m[0][1] +
                  this->_z * m._m[0][2] +
                  this->_w * m._m[0][3];

        float y = this->_x * m._m[1][0] +
                  this->_y * m._m[1][1] +
                  this->_z * m._m[1][2] +
                  this->_w * m._m[1][3];

        float z = this->_x * m._m[2][0] +
                  this->_y * m._m[2][1] +
                  this->_z * m._m[2][2] +
                  this->_w * m._m[2][3];

        float w = this->_x * m._m[3][0] +
                  this->_y * m._m[3][1] +
                  this->_z * m._m[3][2] +
                  this->_w * m._m[3][3];
        
        this->_x = x;
        this->_y = y;
        this->_z = z;
        this->_w = w;

        return *this;
    }

    Point4 operator+(const Point4 &p, const Point4 &t) {
        return Point4(p._x + t._x,
                      p._y + t._y,
                      p._z + t._z,
                      p._w + t._w);
    }

    Point4 operator-(const Point4 &p, const Point4 &t) {
        return Point4(p._x - t._x,
                      p._y - t._y,
                      p._z - t._z,
                      p._w - t._w);
    }

    Point4 operator+(const Point4 &p, const Point3 &t) {
        return Point4(p._x + t._x,
                      p._y + t._y,
                      p._z + t._z,
                      p._w);
    }

    Point4 operator-(const Point4 &p, const Point3 &t) {
        return Point4(p._x - t._x,
                      p._y - t._y,
                      p._z - t._z,
                      p._w);
    }

    Point4 operator+(const Point3 &p, const Point4 &t) {
        return Point4(p._x + t._x,
                      p._y + t._y,
                      p._z + t._z,
                      t._w);
    }

    Point4 operator-(const Point3 &p, const Point4 &t) {
        return Point4(p._x - t._x,
                      p._y - t._y,
                      p._z - t._z,
                      t._w);
    }

    Point4 operator+(const Point4 &p, const float scalar){
        return Point4(p._x + scalar,
                      p._y + scalar,
                      p._z + scalar,
                      p._w + scalar);
    }

    Point4 operator-(const Point4 &p, const float scalar){
        return Point4(p._x - scalar,
                      p._y - scalar,
                      p._z - scalar,
                      p._w - scalar);
    }

    Point4 operator*(const Point4 &p, const float scalar){
        return Point4(p._x * scalar,
                      p._y * scalar,
                      p._z * scalar,
                      p._w * scalar);
    }

    Point4 operator/(const Point4 &p, const float scalar){

        return Point4(p._x / scalar,
                      p._y / scalar,
                      p._z / scalar,
                      p._w / scalar);
    }

    Point4 operator+(const float scalar, const Point4 &p) {
        return (p + scalar);
    }

    Point4 operator-(const float scalar, const Point4 &p) {
        return (p - scalar);
    }
    
    Point4 operator*(const float scalar, const Point4 &p) {
        return (p * scalar);
    }

    Point4 operator/(const float scalar, const Point4 &p) {
        return (p / scalar);
    }

    std::ostream& operator<<(std::ostream &os, const Point4 &p) {
        os << std::fixed << std::setprecision(Point4::precision) << "("
           << p._x << ", "
           << p._y << ", "
           << p._z << ", "
           << p._w << ")";
        return os;
    }
} // namespace pdm
