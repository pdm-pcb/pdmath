#ifndef PDMATH_UTIL_HPP
#define PDMATH_UTIL_HPP

#include <utility>

namespace pdm {

static float clamp(const float min, const float max, const float val) {
    if(val > max) {
        return max;
    }
    if(val < min) {
        return min;
    }
    
    return val;
}

static float clamp(const std::pair<float, float> &min_max, const float val) {
    if(val > min_max.second) {
        return min_max.second;
    }
    if(val < min_max.first) {
        return min_max.first;
    }
    
    return val;
}

} //namespace pdm

#endif // PDMATH_UTIL_HPP