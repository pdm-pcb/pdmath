#include "pdmath/Line4.hpp"

#include "pdmath/Plane.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Vector4.hpp"

namespace pdm {
Line4::Line4(const Point4 &a, const Point4 &b) :
    _p{a}, _v{Vec4(b - a)}
{ }
Line4::Line4(const Point4 &p, const Vec4 &vector) :
    _p{p}, _v{vector}
{ }

bool Line4::parallel_to_plane(const Plane &plane) const {
    return this->_v.dot(plane._n) == 0.0f;
}

bool Line4::within_plane(const Plane &plane) const {
    return Vec4(this->_p - plane._p).dot(plane._n) == 0.0f;
}

Point4 Line4::intersects_at(const Plane &plane) const {
    float lambda = (Vec4(plane._p - this->_p).dot(plane._n));
    lambda /= this->_v.dot(plane._n);

    return this->_p + this->_v * lambda;
}

float Line4::distance_to(const Line4 &other) const {
    float a = _v.dot(_v);
    float b = _v.dot(other._v);
    float c = other._v.dot(other._v);
    float d = Vec4(_p - other._p).dot(_v);
    float e = Vec4(_p - other._p).dot(other._v);

    // std::cout << "\na: " << a << "\n"
    //             << "b: " << b << "\n"
    //             << "c: " << c << "\n"
    //             << "d: " << d << "\n"
    //             << "e: " << e << "\n"
    //             << "p1 - p2: " << Vec4(_p - other._p) << "\n"
    //             << std::endl;

    float angle = b * b - a * c;

    if(angle == 0.0f) {
        return angle;
    }

    // std::cout << "angle: " << angle << std::endl;

    float t1 = (c * d - b * e) / angle;

    float t2 = (d * b - a * e) / angle;

    Point4 c1 = _p + t1 * _v;
    Point4 c2 = other._p + t2 * other._v;

    // std::cout << "t1: " << t1 << "\n"
    //           << "t2: " << t2 << "\n\n"
    //           << "c1: " << c1 << "\n"
    //           << "c2: " << c2 << "\n"
    //           << "dist: " << Vec4(c1 - c2).length() << "\n"
    //           << std::endl;

    return Vec4(c1 - c2).length();
}

} // namespace pdm