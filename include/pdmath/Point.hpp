#ifndef PDM_POINT_HPP
#define PDM_POINT_HPP

#include <iostream>

namespace pdm {
    class vec3;

    class point {
        public:
            point() = default;
            point(const float x, const float y, const float z);

            static constexpr float epsilon = 1.0e-6f;

            float _x;
            float _y;
            float _z;

            bool are_collinear(const point &b, const point &c) const;
            float distance_to_line(const vec3 &v, const point &s) const;

            point operator-(const point &p);
    };

    std::ostream& operator<<(std::ostream &os, const point &p);
}

#endif //PDM_POINT_HPP
