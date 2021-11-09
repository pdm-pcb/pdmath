#ifndef PDMATH_BSPHERE_HPP
#define PDMATH_BSPHERE_HPP

#include "pdmath/Point4.hpp"
#include "pdmath/Matrix4.hpp"

namespace pdm {

class BSphere {
public:
    bool collides(const BSphere &other) const;

    Vec4 center_to_center(const BSphere &other) const;

    inline float  scale()  const { return _world.get_x_scale(); }
    inline Point4 center() const { return _center; }
    inline float  radius() const { return _radius; }

    BSphere(const Point4 &center, const float radius, const Mat4 &world) :
        _center{center},
        _radius{radius},
        _world{world},
        _local{world.inverted()}
    { }
    BSphere() = delete;

private:
    Point4 _center;
    float  _radius;
    Mat4   _world;
    Mat4   _local;
};

} // namespace pdm

#endif // PDMATH_BSPHERE_HPP