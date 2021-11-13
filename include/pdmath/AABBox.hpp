#ifndef PDMATH_AABBOX_HPP
#define PDMATH_AABBOX_HPP

#include "pdmath/Point3.hpp"

#include <utility>

namespace pdm {

class BSphere;
class Line;

class AABBox {
public:
    bool collides(const AABBox  &other)  const;
    bool collides(const BSphere &sphere) const;
    bool collides(const Point3  &point)  const;
    bool collides(const Point4  &point)  const;
    bool collides(const Line   &line)   const;

    std::pair<float, float> x_interval() const;
    std::pair<float, float> y_interval() const;
    std::pair<float, float> z_interval() const;

    AABBox(const Point3 &min, const Point3 &max) :
        _min{min},
        _max{max}
    { }
    AABBox() = delete;

private:
    Point3 _min;
    Point3 _max;
};

} // namespace pdm

#endif // PDMATH_AABBOX_HPP