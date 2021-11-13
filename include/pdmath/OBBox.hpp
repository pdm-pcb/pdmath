#ifndef PDMATH_OBBOX_HPP
#define PDMATH_OBBOX_HPP

#include "pdmath/Point3.hpp"
#include "pdmath/Matrix4.hpp"

#include <utility>

namespace pdm {

class Vec3;
class BSphere;
class Plane;

class OBBox {
public:
    bool collides(const OBBox &other)    const;
    bool collides(const Point3 &point)   const;
    bool collides(const BSphere &sphere) const;
    bool collides(const Plane &plane)    const;

    Vec3 side()    const;
    Vec3 up()      const;
    Vec3 forward() const;

    Vec3 side_local()    const;
    Vec3 up_local()      const;
    Vec3 forward_local() const;

    float get_proj_scale() const;
    static float max_projection(const OBBox &local, const Vec3 &v);
    static float scaled_projection(const OBBox &local, const Vec3 &v);
    
    Vec3 to_local(const Vec3 &v) const;
    Vec3 to_world(const Vec3 &v) const;

    Point3 to_local(const Point3 &p) const;
    Point3 to_world(const Point3 &p) const;

    inline Mat4   get_local()    const { return _local;        }
    inline Mat4   get_world()    const { return _world;        }
    inline Point3 center()       const { return _center;       }
    inline Point3 center_world() const { return _center_world; }

    std::pair<float, float> x_interval() const;
    std::pair<float, float> y_interval() const;
    std::pair<float, float> z_interval() const;

    OBBox(const Point3 &min, const Point3 &max, const Mat4 &world) noexcept;
    OBBox() = delete;

private:
    Point3 _min;
    Point3 _max;
    Point3 _center;

    Point3 _min_world;
    Point3 _max_world;
    Point3 _center_world;

    Mat4   _world;
    Mat4   _local;
};

} // namespace pdm

#endif // PDMATH_OBBOX_HPP