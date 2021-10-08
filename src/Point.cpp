#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"

#include <iomanip>

namespace pdm {
    Point::Point(const float x, const float y, const float z) :
        _x{x}, _y{y}, _z{z}
    { }

    bool Point::are_collinear(const Point &b, const Point &c) const {
        Vec3 vec_ab(*this, b);
        Vec3 vec_ac(*this, c);
#ifdef SOLVER_LOG
            std::cout << "Is vector ab collinear with vector ac?\n"
                      << (vec_ab.is_collinear(vec_ac)?"true":"false")
                      << std::endl;
#endif // SOLVER_LOG
        return vec_ab.is_collinear(vec_ac);
    }

    float Point::distance_to_line(const Line &line) const {
        Vec3 s_minus_p(*this, line._p);
        Vec3 perp = s_minus_p - ((s_minus_p.dot(line._v))/
                                 (line._v.dot(line._v))) * line._v;
        return perp.length();
    }

    bool Point::is_on_plane(const Plane &plane) const {
        Vec3 point_vector(*this - plane._p);
        return point_vector.dot(plane._n) == 0.0f;
    }

    float Point::distance_to_plane(const Plane &plane) const {
        Vec3 point_vector(*this - plane._p);
        return point_vector.dot(plane._n);
    }

    bool Point::is_zero() const {
        return (_x == 0.0f) &&
               (_y == 0.0f) &&
               (_z == 0.0f);
    }

    bool Point::operator==(const Point &p) const {
        if(&p == this) {
            return true;
        }

        float x_diff = (fabsf(p._x) - fabsf(this->_x));
        float y_diff = (fabsf(p._y) - fabsf(this->_y));
        float z_diff = (fabsf(p._z) - fabsf(this->_z));

        return x_diff < Point::epsilon &&
               y_diff < Point::epsilon &&
               z_diff < Point::epsilon;
    }

    Point& Point::operator+=(const Point &p) {
        this->_x += p._x;
        this->_y += p._y;
        this->_z += p._z;
        return *this;
    }

    Point& Point::operator-=(const Point &p) {
        this->_x -= p._x;
        this->_y -= p._y;
        this->_z -= p._z;
        return *this;
    }

    Point& Point::operator+=(const float scalar) {
        this->_x += scalar;
        this->_y += scalar;
        this->_z += scalar;
        return *this;
    }

    Point& Point::operator-=(const float scalar) {
        this->_x -= scalar;
        this->_y -= scalar;
        this->_z -= scalar;
        return *this;
    }

    Point& Point::operator*=(const float scalar) {
        this->_x *= scalar;
        this->_y *= scalar;
        this->_z *= scalar;
        return *this;
    }

    Point& Point::operator/=(const float scalar) {
        this->_x /= scalar;
        this->_y /= scalar;
        this->_z /= scalar;
        return *this;
    }

    Point::operator Vec3() const {
        return Vec3(this->_x, this->_y, this->_z);
    }

    Point operator+(Point p, const Point &t) {
        p += t;
        return p;
    }

    Point operator-(Point p, const Point &t) {
        p -= t;
        return p;
    }

    Point operator+(Point p, const float scalar) {
        p += scalar;
        return p;
    }

    Point operator-(Point p, const float scalar) {
        p -= scalar;
        return p;
    }
    
    Point operator*(Point p, const float scalar) {
        p *= scalar;
        return p;
    }
    
    Point operator/(Point p, const float scalar) {
        p /= scalar;
        return p;
    }

    Point operator+(const float scalar, Point p) {
        p += scalar;
        return p;
    }

    Point operator-(const float scalar, Point p) {
        p -= scalar;
        return p;
    }
    
    Point operator*(const float scalar, Point p) {
        p *= scalar;
        return p;
    }
    
    Point operator/(const float scalar, Point p) {
        p /= scalar;
        return p;
    }

    std::ostream& operator<<(std::ostream &os, const Point &p) {
        os << std::fixed << std::setprecision(Point::_output_precision) << "("
           << p._x << ", "
           << p._y << ", "
           << p._z << ")";
        return os;
    }
} // namespace pdm
