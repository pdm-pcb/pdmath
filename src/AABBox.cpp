#include "pdmath/AABBox.hpp"

#include "pdmath/util.hpp"
#include "pdmath/BSphere.hpp"
#include "pdmath/Line.hpp"

namespace pdm {

bool AABBox::collides(const AABBox &other) const {
    bool x_overlap = overlap(x_interval(), other.x_interval());
    bool y_overlap = overlap(y_interval(), other.y_interval());
    bool z_overlap = overlap(z_interval(), other.z_interval());

    return x_overlap && y_overlap && z_overlap;
}

bool AABBox::collides(const BSphere &sphere) const {
    Point4 center_clamped(
        clamp(sphere.center()._x, x_interval()),
        clamp(sphere.center()._y, y_interval()),
        clamp(sphere.center()._z, z_interval()));

    return sphere.collides(center_clamped);
}

bool AABBox::collides(const Point3 &point) const {
    return _min._x < point._x && point._x < _max._x &&
           _min._y < point._y && point._y < _max._y &&
           _min._z < point._z && point._z < _max._z;
}

bool AABBox::collides(const Point4 &point) const {
    return _min._x < point._x && point._x < _max._x &&
           _min._y < point._y && point._y < _max._y &&
           _min._z < point._z && point._z < _max._z;
}

bool AABBox::collides(const Line &line) const {
    if(line.vec()._x == 0.0f) {
        if(line.point_a()._x < _min._x || line.point_a()._x > _max._x) {
            // std::cout << "\nline's x value is zero and outside." << std::endl;
            return false;
        }
    }
    if(line.vec()._y == 0.0f) {
        if(line.point_a()._y < _min._y || line.point_a()._y > _max._y) {
            // std::cout << "\nline's y value is zero and outside." << std::endl;
            return false;
        }
    }
    if(line.vec()._z == 0.0f) {
        if(line.point_a()._z < _min._z || line.point_a()._z > _max._z) {
            // std::cout << "\nline's z value is zero and outside." << std::endl;
            return false;
        }
    }

    float ax = (_min._x - line.point_a()._x) / line.vec()._x;
    float bx = (_max._x - line.point_a()._x) / line.vec()._x;

    float sx = (ax < bx ? ax : bx);
    float tx = (ax > bx ? ax : bx);

    float ay = (_min._y - line.point_a()._y) / line.vec()._y;
    float by = (_max._y - line.point_a()._y) / line.vec()._y;

    float sy = (ay < by ? ay : by);
    float ty = (ay > by ? ay : by);

    float az = (_min._z - line.point_a()._z) / line.vec()._z;
    float bz = (_max._z - line.point_a()._z) / line.vec()._z;

    float sz = (az < bz ? az : bz);
    float tz = (az > bz ? az : bz);

    // std::cout << "\nx interval: " << sx << ", " << tx << "\n"
    //           << "y interval: "   << sy << ", " << ty << "\n"
    //           << "z interval: "   << sz << ", " << tz << "\n"
    //           << std::endl;

    return overlap(sx, tx, sy, ty) &&
           overlap(sy, ty, sz, tz) &&
           overlap(sz, tz, sx, tx);
}

std::pair<float, float> AABBox::x_interval() const {
    return std::pair<float, float>(_min._x, _max._x);
}

std::pair<float, float> AABBox::y_interval() const {
    return std::pair<float, float>(_min._y, _max._y);
}

std::pair<float, float> AABBox::z_interval() const {
    return std::pair<float, float>(_min._z, _max._z);
}

} // namespace pdm