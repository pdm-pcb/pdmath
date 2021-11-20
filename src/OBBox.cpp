#include "pdmath/OBBox.hpp"

#include "pdmath/util.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/BSphere.hpp"
#include "pdmath/Plane.hpp"

#include <cmath>

namespace pdm {

bool OBBox::collides(const OBBox &other) const {
    // using cross products to get face normals
    Vec3 sideside_cross = side().cross(other.side());
    Vec3 upside_cross   = up().cross(other.side());
    Vec3 fwdside_cross  = forward().cross(other.side());

    Vec3 sideup_cross   = side().cross(other.up());
    Vec3 upup_cross     = up().cross(other.up());
    Vec3 fwdup_cross    = forward().cross(other.up());

    Vec3 sidefwd_cross  = side().cross(other.forward());
    Vec3 upfwd_cross    = up().cross(other.forward());
    Vec3 fwdfwd_cross   = forward().cross(other.forward());

    // the vector connecting the two worldspace midpoints of the boxes
    Vec3 center_dist = other.center_world() - center_world();

    // length of the projection of the center-to-center vector onto the
    // related axes
    float side_center_dist_this =
        std::abs(center_dist.dot(side())) / side().length();
    float side_center_dist_other =
        std::abs(center_dist.dot(other.side())) / other.side().length();

    float up_center_dist_this =
        std::abs(center_dist.dot(up())) / up().length();
    float up_center_dist_other =
        std::abs(center_dist.dot(other.up())) / other.up().length();

    float fwd_center_dist_this =
        std::abs(center_dist.dot(forward())) / forward().length();
    float fwd_center_dist_other =
        std::abs(center_dist.dot(other.forward())) / other.forward().length();

    // same as above, except now it's the cross product axes of the two boxes
    float sideside_center_dist =
        std::abs(center_dist.dot(sideside_cross)) / sideside_cross.length();
    float upside_center_dist   =
        std::abs(center_dist.dot(upside_cross)) / upside_cross.length();
    float fwdside_center_dist  =
        std::abs(center_dist.dot(fwdside_cross)) / fwdside_cross.length();

    float sideup_center_dist   =
        std::abs(center_dist.dot(sideup_cross)) / sideup_cross.length();
    float upup_center_dist     =
        std::abs(center_dist.dot(upup_cross)) / upup_cross.length();
    float fwdup_center_dist    =
        std::abs(center_dist.dot(fwdup_cross)) / fwdup_cross.length();

    float sidefwd_center_dist  =
        std::abs(center_dist.dot(sidefwd_cross)) / sidefwd_cross.length();
    float upfwd_center_dist    =
        std::abs(center_dist.dot(upfwd_cross)) / upfwd_cross.length();
    float fwdfwd_center_dist   = 
        std::abs(center_dist.dot(fwdfwd_cross)) / fwdfwd_cross.length();

    // sum of the length of the projections of each "best" diagonal onto the
    // related axes
    float side_proj_this =  OBBox::scaled_projection(*this, this->side()) +
                            OBBox::scaled_projection(other, this->side());
    float side_proj_other = OBBox::scaled_projection(other, other.side()) +
                            OBBox::scaled_projection(*this, other.side());

    float up_proj_this   =  OBBox::scaled_projection(*this, this->up()) +
                            OBBox::scaled_projection(other, this->up());
    float up_proj_other   = OBBox::scaled_projection(other, other.up()) +
                            OBBox::scaled_projection(*this, other.up());

    float fwd_proj_this  =  OBBox::scaled_projection(*this, this->forward()) +
                            OBBox::scaled_projection(other, this->forward());
    float fwd_proj_other  = OBBox::scaled_projection(other, other.forward()) +
                            OBBox::scaled_projection(*this, other.forward());

    // again, same as above, but now the projections are onto the cross product
    // axes
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

    //std::cout << "\n=========================================================\n"
    //          << "center dist     : " << center_dist          << "\n"
    //          << "o1 local center : " << center()             << "\n"
    //          << "o2 local center : " << other.center()       << "\n"
    //          << "o1 world center : " << center_world()       << "\n"
    //          << "o2 world center : " << other.center_world() << "\n\n"
    //          << "o1 side : " << side()          << "\tlength: " << side().length()          << "\n"
    //          << "o1 up   : " << up()            << "\tlength: " << up().length()            << "\n"
    //          << "o1 fwd  : " << forward()       << "\tlength: " << forward().length()       << "\n\n"
    //          << "o2 side : " << other.side()    << "\tlength: " << other.side().length()    << "\n"
    //          << "o2 up   : " << other.up()      << "\tlength: " << other.up().length()      << "\n"
    //          << "o2 fwd  : " << other.forward() << "\tlength: " << other.forward().length() << "\n\n"
    //          << "sxs     : " << sideside_cross  << "\tlength: " << sideside_cross.length()  << "\n"
    //          << "uxs     : " << upside_cross    << "\tlength: " << upside_cross.length()    << "\n"
    //          << "fxs     : " << fwdside_cross   << "\tlength: " << fwdside_cross.length()   << "\n"
    //          << "sxu     : " << sideup_cross    << "\tlength: " << sideup_cross.length()    << "\n"
    //          << "uxu     : " << upup_cross      << "\tlength: " << upup_cross.length()      << "\n"
    //          << "fxu     : " << fwdup_cross     << "\tlength: " << fwdup_cross.length()     << "\n"
    //          << "sxf     : " << sidefwd_cross   << "\tlength: " << sidefwd_cross.length()   << "\n"
    //          << "uxf     : " << upfwd_cross     << "\tlength: " << upfwd_cross.length()     << "\n"
    //          << "fxf     : " << fwdfwd_cross    << "\tlength: " << fwdfwd_cross.length()    << "\n\n"
    //          << "f1 proj_max local 1 : " << max_projection(*this, this->forward()) << " via " << this->to_local(this->forward()) << "\t/  scaled : " << scaled_projection(*this, this->forward()) << " by scaling factor: " << this->get_local().get_z_scale() << "\n"
    //          << "f2 proj_max local 1 : " << max_projection(*this, other.forward()) << " via " << this->to_local(other.forward()) << "\t/  scaled : " << scaled_projection(*this, other.forward()) << " by scaling factor: " << this->get_local().get_z_scale() << "\n"
    //          << "f1 proj_max local 2 : " << max_projection(other, this->forward()) << " via " << other.to_local(this->forward()) << "\t/  scaled : " << scaled_projection(other, this->forward()) << " by scaling factor: " << other.get_local().get_z_scale() << "\n"
    //          << "f2 proj_max local 2 : " << max_projection(other, other.forward()) << " via " << other.to_local(other.forward()) << "\t/  scaled : " << scaled_projection(other, other.forward()) << " by scaling factor: " << other.get_local().get_z_scale() << "\n\n"
    //          << "side o1 dist  :  " << side_center_dist_this  << "\t<=   proj length sum: " << side_proj_this  << "\t?  " << ((side_center_dist_this  <= side_proj_this)  ? "true\n" : "false\n")
    //          << "up   o1 dist  :  " << up_center_dist_this    << "\t<=   proj length sum: " << up_proj_this    << "\t?  " << ((up_center_dist_this    <= up_proj_this)    ? "true\n" : "false\n")
    //          << "fwd  o1 dist  :  " << fwd_center_dist_this   << "\t<=   proj length sum: " << fwd_proj_this   << "\t?  " << ((fwd_center_dist_this   <= fwd_proj_this)   ? "true\n" : "false\n")
    //          << "side o2 dist  :  " << side_center_dist_other << "\t<=   proj length sum: " << side_proj_other << "\t?  " << ((side_center_dist_other <= side_proj_other) ? "true\n" : "false\n")
    //          << "up   o2 dist  :  " << up_center_dist_other   << "\t<=   proj length sum: " << up_proj_other   << "\t?  " << ((up_center_dist_other   <= up_proj_other)   ? "true\n" : "false\n")
    //          << "fwd  o2 dist  :  " << fwd_center_dist_other  << "\t<=   proj length sum: " << fwd_proj_other  << "\t?  " << ((fwd_center_dist_other  <= fwd_proj_other)  ? "true\n" : "false\n")
    //          << "sxs dist      :  " << sideside_center_dist   << "\t<=   proj length sum: " << sideside_proj   << "\t?  " << ((sideside_center_dist   <= sideside_proj)   ? "true\n" : "false\n")
    //          << "uxs dist      :  " << upside_center_dist     << "\t<=   proj length sum: " << upside_proj     << "\t?  " << ((upside_center_dist     <= upside_proj)     ? "true\n" : "false\n")
    //          << "fxs dist      :  " << fwdside_center_dist    << "\t<=   proj length sum: " << fwdside_proj    << "\t?  " << ((fwdside_center_dist    <= fwdside_proj)    ? "true\n" : "false\n")
    //          << "sxu dist      :  " << sideup_center_dist     << "\t<=   proj length sum: " << sideup_proj     << "\t?  " << ((sideup_center_dist     <= sideup_proj)     ? "true\n" : "false\n")
    //          << "uxu dist      :  " << upup_center_dist       << "\t<=   proj length sum: " << upup_proj       << "\t?  " << ((upup_center_dist       <= upup_proj)       ? "true\n" : "false\n")
    //          << "fxu dist      :  " << fwdup_center_dist      << "\t<=   proj length sum: " << fwdup_proj      << "\t?  " << ((fwdup_center_dist      <= fwdup_proj)      ? "true\n" : "false\n")
    //          << "sxf dist      :  " << sidefwd_center_dist    << "\t<=   proj length sum: " << sidefwd_proj    << "\t?  " << ((sidefwd_center_dist    <= sidefwd_proj)    ? "true\n" : "false\n")
    //          << "uxf dist      :  " << upfwd_center_dist      << "\t<=   proj length sum: " << upfwd_proj      << "\t?  " << ((upfwd_center_dist      <= upfwd_proj)      ? "true\n" : "false\n")
    //          << "fxf dist      :  " << fwdfwd_center_dist     << "\t<=   proj length sum: " << fwdfwd_proj     << "\t?  " << ((fwdfwd_center_dist     <= fwdfwd_proj)     ? "true\n" : "false\n")
    //          << std::endl;

    // If the length of the center distance projection is less than the sum
    // length of the best diagonal projection, then there is overlap. If all
    // pairs report overlap, there is intersection.
    //
    // Also, if any vectors were facing the same direction, their cross is the
    // zero vector, which will give NaN for these cacluations. If that happens,
    // just skip the vector.

    return ((std::isnan(side_center_dist_this) ||
             std::isnan(side_proj_this)) ||
            (side_center_dist_this <= side_proj_this)) &&

           ((std::isnan(up_center_dist_this) ||
             std::isnan(up_proj_this)) ||
            (up_center_dist_this <= up_proj_this)) && 

           ((std::isnan(fwd_center_dist_this) || 
             std::isnan(fwd_proj_this)) || 
            (fwd_center_dist_this <= fwd_proj_this)) &&

           ((std::isnan(side_center_dist_other) || 
             std::isnan(side_proj_other)) || 
            (side_center_dist_other <= side_proj_other)) &&

           ((std::isnan(up_center_dist_other) ||
             std::isnan(up_proj_other)) ||
            (up_center_dist_other <= up_proj_other)) &&

           ((std::isnan(fwd_center_dist_other) ||
             std::isnan(fwd_proj_other)) || 
            (fwd_center_dist_other <= fwd_proj_other)) &&

           ((std::isnan(sideside_center_dist) ||
             std::isnan(sideside_proj)) ||
            (sideside_center_dist <= sideside_proj)) &&
            
           ((std::isnan(upside_center_dist) ||
             std::isnan(upside_proj)) ||
            (upside_center_dist <= upside_proj)) &&
            
           ((std::isnan(fwdside_center_dist) ||
             std::isnan(fwdside_proj)) ||
            (fwdside_center_dist <= fwdside_proj)) &&
            
           ((std::isnan(sideup_center_dist) ||
             std::isnan(sideup_proj)) ||
            (sideup_center_dist <= sideup_proj)) &&

           ((std::isnan(upup_center_dist) ||
             std::isnan(upup_proj)) ||  
            (upup_center_dist <= upup_proj)) &&
            
           ((std::isnan(fwdup_center_dist) ||
             std::isnan(fwdup_proj)) ||
            (fwdup_center_dist <= fwdup_proj)) &&
            
           ((std::isnan(sidefwd_center_dist) ||
             std::isnan(sidefwd_proj)) ||
            (sidefwd_center_dist <= sidefwd_proj)) &&
            
           ((std::isnan(upfwd_center_dist) ||
             std::isnan(upfwd_proj)) ||
            (upfwd_center_dist <= upfwd_proj)) &&
            
           ((std::isnan(fwdfwd_center_dist) ||
             std::isnan(fwdfwd_proj)) || 
            (fwdfwd_center_dist <= fwdfwd_proj));
}

bool OBBox::collides(const Point3 &point) const {
    Point3 local_point = _local * point;
    return _min._x < local_point._x && local_point._x < _max._x &&
           _min._y < local_point._y && local_point._y < _max._y &&
           _min._z < local_point._z && local_point._z < _max._z;
}

bool OBBox::collides(const BSphere &sphere) const {
    return sphere.collides(*this);
}

bool OBBox::collides(const Plane &plane) const {
    Point3 world_center = center_world();
    float  scale = get_proj_scale();
    float  proj_max = max_projection(*this, plane.normal());
    float  proj_scaled = scaled_projection(*this, plane.normal());

    Vec3 plane_normal_normalized = plane.normal().normalized();

    Vec3 s1(center_world() - proj_scaled * plane_normal_normalized);
    Vec3 s2(center_world() + proj_scaled * plane_normal_normalized);

    Vec3 s1_minus_p0(s1 - plane.point());
    Vec3 s2_minus_p0(s2 - plane.point());

    float d1 = s1_minus_p0.dot(plane.normal());
    float d2 = s2_minus_p0.dot(plane.normal());

    return d1 < 0 and d2 > 0;
}

Vec3 OBBox::side() const {
    return Vec3(_world._m[0][0],
                _world._m[1][0],
                _world._m[2][0]);
}

Vec3 OBBox::up() const {
    return Vec3(_world._m[0][1],
                _world._m[1][1],
                _world._m[2][1]);
}

Vec3 OBBox::forward() const {
    return Vec3(_world._m[0][2],
                _world._m[1][2],
                _world._m[2][2]);
}

Vec3 OBBox::side_local() const {
    return _local * side();
}

Vec3 OBBox::up_local() const {
    return _local * up();
}

Vec3 OBBox::forward_local() const {
    return _local * forward();
}

Vec3 OBBox::to_local(const Vec3 &v) const {
    return _local * v;
}

Vec3 OBBox::to_world(const Vec3 &v) const {
    return _world * v;
}

Point3 OBBox::to_local(const Point3 &p) const {
    return _local * p;
}

Point3 OBBox::to_world(const Point3 &p) const {
    return _world * p;
}

Point4 OBBox::to_local(const Point4 &p) const {
    return _local * p;
}

Point4 OBBox::to_world(const Point4 &p) const {
    return _world * p;
}

float OBBox::get_proj_scale() const {
    return powf(_world.get_x_scale(), 2.0f);
}

float OBBox::max_projection(const OBBox &local, const Vec3 &v) {
    // put the projection vector into this OBB's local space
    Vec3 local_v = local.to_local(v);

    //--------------------------------------------------------------------------
    // (|v'_x * a| + |v'_y * b| + |v'_z * c|) / ||v||
    //
    // where v is the vector onto which we're projecting, v' is that vector in
    // the object local space for this OBB, and (a,b,c) are the x, y, z
    // values for this OBB's center point, again in local space

    return (std::abs(local_v._x * local.best_diag()._x) +
            std::abs(local_v._y * local.best_diag()._y) +
            std::abs(local_v._z * local.best_diag()._z)) / v.length();
                                                 // use the original length!
}

float OBBox::scaled_projection(const OBBox &local, const Vec3 &v) {
    return max_projection(local, v) * local.get_proj_scale();
}

float OBBox::max_projection(const Vec3 &v) {
    // put the projection vector into this OBB's local space
    Vec3 local_v = to_local(v);

    //--------------------------------------------------------------------------
    // (|v'_x * a| + |v'_y * b| + |v'_z * c|) / ||v||
    //
    // where v is the vector onto which we're projecting, v' is that vector in
    // the object local space for this OBB, and (a,b,c) are the x, y, z
    // values for this OBB's center point, again in local space

    return (std::abs(local_v._x * best_diag()._x) +
            std::abs(local_v._y * best_diag()._y) +
            std::abs(local_v._z * best_diag()._z)) / v.length();
                                                 // use the original length!
}

float OBBox::scaled_projection(const Vec3 &v) {
    return max_projection(v) * get_proj_scale();
}

std::pair<float, float> OBBox::x_interval() const {
    return std::pair<float, float>(_min._x, _max._x);
}

std::pair<float, float> OBBox::y_interval() const {
    return std::pair<float, float>(_min._y, _max._y);
}

std::pair<float, float> OBBox::z_interval() const {
    return std::pair<float, float>(_min._z, _max._z);
}

OBBox::OBBox(const Point3 &min, const Point3 &max, const Mat4 &world) noexcept:
    _min{min},
    _max{max},
    _world{world},
    _local{_world.inverted()}
{
    _center    = (_max + _min) / 2.0f;
    _best_diag = (_max - _min) / 2.0f;

    _min_world    = _world * _min;
    _max_world    = _world * _max;
    _center_world = _world * _center;
}

} // namespace pdm