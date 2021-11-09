#include "pdmath/OBBox.hpp"

#include "pdmath/Vector4.hpp"

namespace pdm {

bool OBBox::collides(const OBBox &other) {
    // gather all the cross product vectors we'll be using
    Vec4 sideside_cross = side().cross(other.side());
    Vec4 upside_cross   = up().cross(other.side());
    Vec4 fwdside_cross  = forward().cross(other.side());

    Vec4 sideup_cross   = side().cross(other.up());
    Vec4 upup_cross     = up().cross(other.up());
    Vec4 fwdup_cross    = forward().cross(other.up());

    Vec4 sidefwd_cross  = side().cross(other.forward());
    Vec4 upfwd_cross    = up().cross(other.forward());
    Vec4 fwdfwd_cross   = forward().cross(other.forward());

    // the vector representing the two worldspace midpoints of the boxes
    Vec4 center_avg = static_cast<Vec4>(center_world()) - other.center_world();

    float side_dist_local =
        std::abs(center_avg.dot(side())) / side().length();
    float side_dist_other =
        std::abs(center_avg.dot(other.side())) / other.side().length();

    float up_dist_local =
        std::abs(center_avg.dot(up())) / up().length();
    float up_dist_other =
        std::abs(center_avg.dot(other.up())) / other.up().length();

    float fwd_dist_local =
        std::abs(center_avg.dot(forward())) / forward().length();
    float fwd_dist_other =
        std::abs(center_avg.dot(other.forward())) / other.forward().length();

    float sideside_dist =
        std::abs(center_avg.dot(sideside_cross)) / sideside_cross.length();
    float upside_dist   =
        std::abs(center_avg.dot(upside_cross)) / upside_cross.length();
    float fwdside_dist  =
        std::abs(center_avg.dot(fwdside_cross)) / fwdside_cross.length();

    float sideup_dist   =
        std::abs(center_avg.dot(sideup_cross)) / sideup_cross.length();
    float upup_dist     =
        std::abs(center_avg.dot(upup_cross)) / upup_cross.length();
    float fwdup_dist    =
        std::abs(center_avg.dot(fwdup_cross)) / fwdup_cross.length();

    float sidefwd_dist  =
        std::abs(center_avg.dot(sidefwd_cross)) / sidefwd_cross.length();
    float upfwd_dist    =
        std::abs(center_avg.dot(upfwd_cross)) / upfwd_cross.length();
    float fwdfwd_dist   = 
        std::abs(center_avg.dot(fwdfwd_cross)) / fwdfwd_cross.length();

    float side_proj_local = OBBox::scaled_projection(*this, this->side()) +
                            OBBox::scaled_projection(other, this->side());
    float side_proj_other = OBBox::scaled_projection(other, other.side()) +
                            OBBox::scaled_projection(*this, other.side());

    float up_proj_local   = OBBox::scaled_projection(*this, this->up()) +
                            OBBox::scaled_projection(other, this->up());
    float up_proj_other   = OBBox::scaled_projection(other, other.up()) +
                            OBBox::scaled_projection(*this, other.up());

    float fwd_proj_local  = OBBox::scaled_projection(*this, this->forward()) +
                            OBBox::scaled_projection(other, this->forward());
    float fwd_proj_other  = OBBox::scaled_projection(other, other.forward()) +
                            OBBox::scaled_projection(*this, other.forward());

    float sideside_proj   = OBBox::scaled_projection(*this, sideside_cross) +
                            OBBox::scaled_projection(other, sideside_cross);
    float upside_proj     = OBBox::scaled_projection(*this, upside_cross) +
                            OBBox::scaled_projection(other, upside_cross);
    float fwdside_proj    = OBBox::scaled_projection(*this, fwdside_cross) +
                            OBBox::scaled_projection(other, fwdside_cross);

    float sideup_proj     = OBBox::scaled_projection(*this, sideup_cross) +
                            OBBox::scaled_projection(other, sideup_cross);
    float upup_proj       = OBBox::scaled_projection(*this, upup_cross) +
                            OBBox::scaled_projection(other, upup_cross);
    float fwdup_proj      = OBBox::scaled_projection(*this, fwdup_cross) +
                            OBBox::scaled_projection(other, fwdup_cross);

    float sidefwd_proj    = OBBox::scaled_projection(*this, sidefwd_cross) +
                            OBBox::scaled_projection(other, sidefwd_cross);
    float upfwd_proj      = OBBox::scaled_projection(*this, upfwd_cross) +
                            OBBox::scaled_projection(other, upfwd_cross);
    float fwdfwd_proj     = OBBox::scaled_projection(*this, fwdfwd_cross) +
                            OBBox::scaled_projection(other, fwdfwd_cross);
    

    // std::cout << "o1 side : " << side()           << " / " << side().length()          << "\n"
    //           << "o1 up   : " << up()             << " / " << up().length()            << "\n"
    //           << "o1 fwd  : " << forward()        << " / " << forward().length()       << "\n\n"
    //           << "o2 side : " << other.side()     << " / " << other.side().length()    << "\n"
    //           << "o2 up   : " << other.up()       << " / " << other.up().length()      << "\n"
    //           << "o2 fwd  : " << other.forward()  << " / " << other.forward().length() << "\n\n"
    //           << "sxs     : " << sideside_cross   << "\n"
    //           << "uxs     : " << upside_cross     << "\n"
    //           << "fxs     : " << fwdside_cross    << "\n"
    //           << "sxu     : " << sideup_cross     << "\n"
    //           << "uxu     : " << upup_cross       << "\n"
    //           << "fxu     : " << fwdup_cross      << "\n"
    //           << "sxf     : " << sidefwd_cross    << "\n"
    //           << "uxf     : " << upfwd_cross      << "\n"
    //           << "fxf     : " << fwdfwd_cross     << "\n\n"
    //           << "side o1 :  " << side_dist_local << "\t<  " << side_proj_local << "\t?  " << ((side_dist_local < side_proj_local) ? "true\n" : "false\n")
    //           << "up   o1 :  " << up_dist_local   << "\t<  " << up_proj_local   << "\t?  " << ((up_dist_local   < up_proj_local)   ? "true\n" : "false\n")
    //           << "fwd  o1 :  " << fwd_dist_local  << "\t<  " << fwd_proj_local  << "\t?  " << ((fwd_dist_local  < fwd_proj_local)  ? "true\n" : "false\n")
    //           << "side o2 :  " << side_dist_other << "\t<  " << side_proj_other << "\t?  " << ((side_dist_other < side_proj_other) ? "true\n" : "false\n")
    //           << "up   o2 :  " << up_dist_other   << "\t<  " << up_proj_other   << "\t?  " << ((up_dist_other   < up_proj_other)   ? "true\n" : "false\n")
    //           << "fwd  o2 :  " << fwd_dist_other  << "\t<  " << fwd_proj_other  << "\t?  " << ((fwd_dist_other  < fwd_proj_other)  ? "true\n" : "false\n")
    //           << "sxs     :  " << sideside_dist   << "\t<  " << sideside_proj   << "\t?  " << ((sideside_dist   < sideside_proj)   ? "true\n" : "false\n")
    //           << "uxs     :  " << upside_dist     << "\t<  " << upside_proj     << "\t?  " << ((upside_dist     < upside_proj)     ? "true\n" : "false\n")
    //           << "fxs     :  " << fwdside_dist    << "\t<  " << fwdside_proj    << "\t?  " << ((fwdside_dist    < fwdside_proj)    ? "true\n" : "false\n")
    //           << "sxu     :  " << sideup_dist     << "\t<  " << sideup_proj     << "\t?  " << ((sideup_dist     < sideup_proj)     ? "true\n" : "false\n")
    //           << "uxu     :  " << upup_dist       << "\t<  " << upup_proj       << "\t?  " << ((upup_dist       < upup_proj)       ? "true\n" : "false\n")
    //           << "fxu     :  " << fwdup_dist      << "\t<  " << fwdup_proj      << "\t?  " << ((fwdup_dist      < fwdup_proj)      ? "true\n" : "false\n")
    //           << "sxf     :  " << sidefwd_dist    << "\t<  " << sidefwd_proj    << "\t?  " << ((sidefwd_dist    < sidefwd_proj)    ? "true\n" : "false\n")
    //           << "uxf     :  " << upfwd_dist      << "\t<  " << upfwd_proj      << "\t?  " << ((upfwd_dist      < upfwd_proj)      ? "true\n" : "false\n")
    //           << "fxf     :  " << fwdfwd_dist     << "\t<  " << fwdfwd_proj     << "\t?  " << ((fwdfwd_dist     < fwdfwd_proj)     ? "true\n" : "false\n")
    //           << std::endl;

    return (side_dist_local < side_proj_local) &&
           (up_dist_local   < up_proj_local)   &&
           (fwd_dist_local  < fwd_proj_local)  &&
           (side_dist_other < side_proj_other) &&
           (up_dist_other   < up_proj_other)   &&
           (fwd_dist_other  < fwd_proj_other)  &&
           (sideside_dist   < sideside_proj)   &&
           (upside_dist     < upside_proj)     &&
           (fwdside_dist    < fwdside_proj)    &&
           (sideup_dist     < sideup_proj)     &&
           (upup_dist       < upup_proj)       &&
           (fwdup_dist      < fwdup_proj)      &&
           (sidefwd_dist    < sidefwd_proj)    &&
           (upfwd_dist      < upfwd_proj)      &&
           (fwdfwd_dist     < fwdfwd_proj);
}

Vec4 OBBox::side() const {
    return Vec4(_world._m[0][0],
                _world._m[1][0],
                _world._m[2][0],
                _world._m[3][0]);
}

Vec4 OBBox::up() const {
    return Vec4(_world._m[0][1],
                _world._m[1][1],
                _world._m[2][1],
                _world._m[3][1]);
}

Vec4 OBBox::forward() const {
    return Vec4(_world._m[0][2],
                _world._m[1][2],
                _world._m[2][2],
                _world._m[3][2]);
}

Vec4 OBBox::side_local() const {
    return _local * side();
}

Vec4 OBBox::up_local() const {
    return _local * up();
}

Vec4 OBBox::forward_local() const {
    return _local * forward();
}

Vec4 OBBox::to_local(const Vec4 &v) const {
    return _local * v;
}

Vec4 OBBox::to_world(const Vec4 &v) const {
    return _world * v;
}

float OBBox::get_proj_scale() const {
    return powf(_world.get_x_scale(), 2.0f);
}

float OBBox::max_projection(const OBBox &local, const Vec4 &v) {
    // get the argument vector in this box's local space
    Vec4 local_v = local.to_local() * v;
    return ((std::abs(local_v._x * local.center()._x)) +
            (std::abs(local_v._y * local.center()._y)) +  // use the original length
            (std::abs(local_v._z * local.center()._z))) / v.length();
}

float OBBox::scaled_projection(const OBBox &local, const Vec4 &v) {
    return max_projection(local, v) * local.get_proj_scale();
}

OBBox::OBBox(const Point4 &min, const Point4 &max, const Mat4 &world) noexcept:
    _min{min},
    _max{max},
    _world{world},
    _local{_world.inverted()}
{
    _center = Point4((_max._x - _min._x) / 2.0f,
                     (_max._y - _min._y) / 2.0f,
                     (_max._z - _min._z) / 2.0f,
                     1.0f);

    _min_world = _world * _min;
    _max_world = _world * _max;

    _center_world = Point4((_min_world._x + _max_world._x) / 2.0f,
                           (_min_world._y + _max_world._y) / 2.0f,
                           (_min_world._z + _max_world._z) / 2.0f,
                           1.0f);
}

} // namespace pdm