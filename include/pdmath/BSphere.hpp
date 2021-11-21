#ifndef PDMATH_BSPHERE_HPP
#define PDMATH_BSPHERE_HPP

#include "pdmath/Point3.hpp"
#include "pdmath/Matrix4.hpp"

namespace pdm {

class Point4;
class AABBox;
class OBBox;
class Plane;
class Line;

class BSphere {
public:
    bool collides(const BSphere &other) const;
    bool collides(const Point3  &point) const;
    bool collides(const Point4  &point) const;
    bool collides(const AABBox  &box)   const;
    bool collides(const OBBox   &box)   const;
    bool collides(const Plane   &plane) const;
    bool collides(const Line    &line)  const;
    
    bool above_plane(const Plane &plane) const;

    Vec3   center_to_center(const BSphere &other) const;
    Point3 center_clamped(const OBBox  &box)      const;
    Point3 center_clamped(const AABBox &box)      const;

    Point3 to_world(const Point3 &p) const;
    Point3 to_local(const Point3 &p) const;

    inline Mat4   world()          const { return _world; }
    inline Mat4   local()          const { return _local; }
    inline float  scale()          const { return _world.get_x_scale(); }
    inline Point3 center_world()   const { return _center_world; }
    inline Point3 center()         const { return _center; }
    inline float  radius()         const { return _radius; }
    inline float  scaled_radius()  const { return  _scaled_radius; }

    BSphere(const Point3 &center, const float radius, const Mat4 &world) :
        _center{center},
        _radius{radius},
        _world{world},
        _local{world.inverted()}
    {
        _center_world   = _world  * _center;
        _scaled_radius  = _radius * scale();
    }

    BSphere() = delete;

private:
    Point3 _center;
    Point3 _center_world;
    float  _radius;
    float  _scaled_radius;
    Mat4   _world;
    Mat4   _local;
};

} // namespace pdm

#endif // PDMATH_BSPHERE_HPP