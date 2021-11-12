#include "pdmath/Line3.hpp"

#include "pdmath/Plane.hpp"
#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"

namespace pdm {
Line3::Line3(const Point3 &a, const Point3 &b) :
    _p{a}, _t{b}, _v{Vec3(b - a)}
{ }
Line3::Line3(const Point3 &p, const Vec3 &vector) :
    _p{p}, _t{Point3()}, _v{vector}
{ }

bool Line3::parallel_to_plane(const Plane &plane) const {
    return this->_v.dot(plane._n) == 0.0f;
}

bool Line3::within_plane(const Plane &plane) const {
    return Vec3(this->_p - plane._p).dot(plane._n) == 0.0f;
}

bool Line3::intersects(const Plane &plane) const {
    Vec3 s1_minus_p(_p - plane._p);
    Vec3 s2_minus_p(_t - plane._p);
    float d1 = s1_minus_p.dot(plane._n);
    float d2 = s2_minus_p.dot(plane._n);

    // std::cout << "\nS1 - P0: " << s1_minus_p << "\n"
    //           << "S2 - P0: "   << s2_minus_p << "\n"
    //           << "d1: " << d1 << "\n"
    //           << "d2: " << d2 << "\n"
    //           << std::endl;

    return (d1 < 0.0f && d2 > 0.0f) ||
           (d2 < 0.0f && d1 > 0.0f);
}

float Line3::intersects_depth(const Plane &plane) const {
    Vec3 p_minus_s1(plane._p - _p);
    Vec3 s2_minus_s1(_t - _p);
    float t_num = p_minus_s1.dot(plane._n);
    float t_den = s2_minus_s1.dot(plane._n);

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

Point3 Line3::intersects_at(const Plane &plane) const {
    float lambda = (Vec3(plane._p - this->_p).dot(plane._n));
    lambda /= this->_v.dot(plane._n);

    return this->_p + this->_v * lambda;
}
} // namespace pdm