#include "pdmath/Line.hpp"

#include "pdmath/Plane.hpp"
#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"

namespace pdm {
    Line::Line(const Point &a, const Point &b) :
        _p{a}, _v{Vec3(b - a)}
    { }
    Line::Line(const Point &p, const Vec3 &vector) :
        _p{p}, _v{vector}
    { }

    bool Line::parallel_to_plane(const Plane &plane) const {
        return this->_v.dot(plane._n) == 0.0f;
    }

    bool Line::within_plane(const Plane &plane) const {
        return Vec3(this->_p - plane._p).dot(plane._n) == 0.0f;
    }

    Point Line::intersects_at(const Plane &plane) const {
        float lambda = (Vec3(plane._p - this->_p).dot(plane._n));
        lambda /= this->_v.dot(plane._n);

        return this->_p + this->_v * lambda;
    }
} // namespace pdm