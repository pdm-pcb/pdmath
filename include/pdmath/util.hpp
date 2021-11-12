#ifndef PDMATH_UTIL_HPP
#define PDMATH_UTIL_HPP

#include <utility>

namespace pdm {

static float clamp(const float val, const float min, const float max) {
    if(val > max) {
        return max;
    }
    if(val < min) {
        return min;
    }
    
    return val;
}

static float clamp(const float val, const std::pair<float, float> &min_max) {
    if(val > min_max.second) {
        return min_max.second;
    }
    if(val < min_max.first) {
        return min_max.first;
    }
    
    return val;
}

static bool overlap(const std::pair<float, float> &a,
                    const std::pair<float, float> &b) {
    return (a.second >= b.first) && (a.first  <= b.second);
}

static bool overlap(const float a_min, const float a_max,
                    const float b_min, const float b_max) {
    return (a_max >= b_min) && (a_min  <= b_max);
}

} //namespace pdm

#endif // PDMATH_UTIL_HPP