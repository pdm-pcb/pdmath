#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"

#include <iomanip>

namespace pdm {
    point::point(const float x, const float y, const float z) :
        _x{x}, _y{y}, _z{z}
    { }

    point point::operator-(const point &p) {
        return point(_x - p._x,
                     _y - p._y,
                     _z - p._z);
    }

    bool point::are_collinear(const point &b, const point &c) const {
        vec3 vec_ab(*this, b);
        vec3 vec_ac(*this, c);
#ifdef SOLVER_LOG
            std::cout << "Is vector ab collinear with vector ac?\n"
                      << (vec_ab.is_collinear(vec_ac)?"true":"false")
                      << std::endl;
#endif // SOLVER_LOG
        return vec_ab.is_collinear(vec_ac);
    }

    std::ostream& operator<<(std::ostream &os, const point &p) {
        os << std::fixed << std::setprecision(2) << "("
           << p._x << ", "
           << p._y << ", "
           << p._z << ")";
        return os;
    }
}
