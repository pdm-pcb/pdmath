#ifndef PDMATH_AABBOX_HPP
#define PDMATH_AABBOX_HPP

#include "pdmath/Point4.hpp"

#include <utility>

namespace pdm {

class BSphere;
class Line4;

class AABBox {
public:
    bool collides(const AABBox  &other)  const;
    bool collides(const BSphere &sphere) const;
    bool collides(const Point4  &point)  const;
    bool collides(const Line4   &line)   const;

    std::pair<float, float> x_interval() const;
    std::pair<float, float> y_interval() const;
    std::pair<float, float> z_interval() const;

    AABBox(const Point4 &min, const Point4 &max) :
        _min{min},
        _max{max}
    { }
    AABBox() = delete;

private:
    Point4 _min;
    Point4 _max;
};

} // namespace pdm

#endif // PDMATH_AABBOX_HPP