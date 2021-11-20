#include "pdmath/Line.hpp"

#include "pdmath/Point3.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Plane.hpp"

namespace pdm {

float Line::distance_to(const Line &other) const {
    float a = _v.dot(_v);
    float b = _v.dot(other._v);
    float c = other._v.dot(other._v);
    float d = Vec3(_p - other._p).dot(_v);
    float e = Vec3(_p - other._p).dot(other._v);

    // std::cout << "\na: " << a << "\n"
    //             << "b: " << b << "\n"
    //             << "c: " << c << "\n"
    //             << "d: " << d << "\n"
    //             << "e: " << e << "\n"
    //             << "p1 - p2: " << Vec4(_p - other.point()) << "\n"
    //             << std::endl;

    float angle = b * b - a * c;

    if(angle == 0.0f) {
        return angle;
    }

    // std::cout << "angle: " << angle << std::endl;

    float t1 = (c * d - b * e) / angle;

    float t2 = (d * b - a * e) / angle;

    Point3 c1 = _p + t1 * _v;
    Point3 c2 = other._p + t2 * other._v;

    // std::cout << "t1: " << t1 << "\n"
    //           << "t2: " << t2 << "\n\n"
    //           << "c1: " << c1 << "\n"
    //           << "c2: " << c2 << "\n"
    //           << "dist: " << Vec4(c1 - c2).length() << "\n"
    //           << std::endl;

    return Vec3(c1 - c2).length();
}

bool Line::parallel_to_plane(const Plane &plane) const {
    return this->_v.dot(plane.normal()) == 0.0f;
}

bool Line::within_plane(const Plane &plane) const {
    return Vec3(this->_p - plane.point()).dot(plane.normal()) == 0.0f;
}

bool Line::intersects(const Plane &plane) const {
    Vec3 s1_minus_p(_p - plane.point());
    Vec3 s2_minus_p(_t - plane.point());
    float d1 = s1_minus_p.dot(plane.normal());
    float d2 = s2_minus_p.dot(plane.normal());

    // std::cout << "\nS1 - P0: " << s1_minus_p << "\n"
    //           << "S2 - P0: "   << s2_minus_p << "\n"
    //           << "d1: " << d1 << "\n"
    //           << "d2: " << d2 << "\n"
    //           << std::endl;

    return (d1 < 0.0f && d2 > 0.0f) ||
           (d2 < 0.0f && d1 > 0.0f);
}

float Line::intersects_depth(const Plane &plane) const {
    Vec3 p_minus_s1(plane.point() - _p);
    Vec3 s2_minus_s1(_t - _p);
    float t_num = p_minus_s1.dot(plane.normal());
    float t_den = s2_minus_s1.dot(plane.normal());

    // std::cout << "\nP0 - S1: " << p_minus_s1 << "\n"
    //           << "S2 - S1: "   << s2_minus_s1 << "\n"
    //           << "t num  : "   << t_num << "\n"
    //           << "t den  : "   << t_den << "\n"
    //           << "t: " << ((t_den != 0) ? (t_num / t_den) : (0.0f)) << "\n"
    //           << std::endl;

    if(t_den != 0.0f) {
        return t_num / t_den;
    }

    return 0.0f;
}

Point3 Line::intersects_at(const Plane &plane) const {
    float lambda = (Vec3(plane.point() - this->_p).dot(plane.normal()));
    lambda /= this->_v.dot(plane.normal());

    return this->_p + static_cast<Point3>(this->_v) * lambda;
}

Line::Line(const Point3 &a, const Point3 &b) :
    _p{a}, _t{b}, _v{Vec3(b - a)}
{ }

Line::Line(const Point4 &a, const Point4 &b) :
    _p{a}, _t{b}, _v{Vec3(b - a)}
{ }

Line::Line(const Point3 &p, const Vec3 &v) :
    _p{p}, _t{Point3()}, _v{v}
{ }

Line::Line(const Point4 &p, const Vec4 &v) :
    _p{p}, _t{Point3()}, _v{v}
{ }

} // namespace pdm