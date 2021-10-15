#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"
#include "pdmath/Matrix.hpp"

#include <iomanip>

namespace pdm {
    Point::Point(const float x, const float y, const float z) :
        _x{x}, _y{y}, _z{z}
    { }

    bool Point::are_collinear(const Point &b, const Point &c) const {
        Vec3 vec_ab(b - *this);
        Vec3 vec_ac(c - *this);
        return vec_ab.is_collinear(vec_ac);
    }

    float Point::distance_to_line(const Line &line) const {
        Vec3 s_minus_p(line._p - *this);
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

    const Point& Point::operator*=(const Mat3 &m) {
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

    std::ostream& operator<<(std::ostream &os, const Point &p) {
        os << std::fixed << std::setprecision(Point::_output_precision) << "("
           << p._x << ", "
           << p._y << ", "
           << p._z << ")";
        return os;
    }
} // namespace pdm
