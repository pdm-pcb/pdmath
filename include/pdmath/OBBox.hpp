#ifndef PDMATH_OBBOX_HPP
#define PDMATH_OBBOX_HPP

#include "pdmath/Point4.hpp"
#include "pdmath/Matrix4.hpp"
#include "pdmath/BSphere.hpp"

#include <utility>

namespace pdm {

class Vec4;
class Mat4;

class OBBox {
public:
    bool collides(const OBBox &other) const;
    bool collides(const BSphere &sphere) const;
    bool collides(const Point4 &point) const;

    Vec4 side()    const;
    Vec4 up()      const;
    Vec4 forward() const;

    Vec4 side_local()    const;
    Vec4 up_local()      const;
    Vec4 forward_local() const;

    float get_proj_scale() const;
    static float max_projection(const OBBox &local, const Vec4 &v);
    static float scaled_projection(const OBBox &local, const Vec4 &v);
    
    Vec4 to_local(const Vec4 &v) const;
    Vec4 to_world(const Vec4 &v) const;

    inline Mat4   to_local()     const { return _local;        }
    inline Mat4   to_world()     const { return _world;        }
    inline Point4 center()       const { return _center;       }
    inline Point4 center_world() const { return _center_world; }

    std::pair<float, float> x_interval() const;
    std::pair<float, float> y_interval() const;
    std::pair<float, float> z_interval() const;

    OBBox(const Point4 &min, const Point4 &max, const Mat4 &world) noexcept;
    OBBox() = delete;

private:
    Point4 _min;
    Point4 _max;
    Point4 _center;

    Point4 _min_world;
    Point4 _max_world;
    Point4 _center_world;

    Mat4   _world;
    Mat4   _local;
};

} // namespace pdm

#endif // PDMATH_OBBOX_HPP