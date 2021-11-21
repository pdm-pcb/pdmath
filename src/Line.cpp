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
    float d = (_p - other._p).dot(_v);
    float e = (_p - other._p).dot(other._v);

    float angle = b * b - a * c;

    if(angle == 0.0f) {
        return angle;
    }

    float t1 = (c * d - b * e) / angle; 
    float t2 = (d * b - a * e) / angle;

    Point3 c1 = _p + t1 * _v;
    Point3 c2 = other._p + t2 * other._v;

    return Vec3(c1 - c2).length();
}

bool Line::parallel_to(const Line &other) const {
    return _v.cross(other.vec()) == Vec3::zero;
}

bool Line::parallel_to_plane(const Plane &plane) const {
    return this->_v.dot(plane.normal()) == 0.0f;
}

bool Line::within_plane(const Plane &plane) const {
    return Vec3(this->_p - plane.point()).dot(plane.normal()) == 0.0f;
}

bool Line::collides(const Line &other) const {
    float a = _v.dot(_v);
    float b = _v.dot(other.vec());
    float c = other.vec().dot(other.vec());
    float d = (_p - other.point_a()).dot(vec());
    float e = (_p - other.point_a()).dot(other.vec());

    Point3 point1;
    Point3 point2;

    if(parallel_to(other)) {
        point1 = _p;
        point2 = other.point_a() + (e / c) * other.vec();
    }
    else {
        point1 = _p + ((c * d - b * e) / (b * b - a * c)) * _v;
        point2 = other.point_a() +
                 ((d * b - a * e) / (b * b - a * c)) *
                 other.vec();
    }

    return point1 == point2;
}

bool Line::collides(const Plane &plane) const {
    Vec3 s1_minus_p(_p - plane.point());
    Vec3 s2_minus_p(_t - plane.point());
    float d1 = s1_minus_p.dot(plane.normal());
    float d2 = s2_minus_p.dot(plane.normal());

    return (d1 < 0.0f && d2 > 0.0f) ||
           (d2 < 0.0f && d1 > 0.0f);
}

float Line::collides_depth(const Plane &plane) const {
    Vec3 p_minus_s1(plane.point() - _p);
    Vec3 s2_minus_s1(_t - _p);
    float t_num = p_minus_s1.dot(plane.normal());
    float t_den = s2_minus_s1.dot(plane.normal());

    if(t_den != 0.0f) {
        return t_num / t_den;
    }

    return 0.0f;
}

Point3 Line::collides_at(const Plane &plane) const {
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