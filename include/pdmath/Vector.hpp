#ifndef PDM_VECTOR_HPP
#define PDM_VECTOR_HPP

#include "pdmath/Point.hpp"

namespace pdm {
    class vec3 : public point {
        public:
            vec3() = default;
            vec3(const float x, const float y, const float z);
            vec3(const point &p);
            vec3(const point &p, const point &s);

            float dot(const vec3 &other,              bool log = false) const;
            vec3  cross(const vec3 &other,            bool log = false) const;
            vec3  project_onto(const vec3 &other,     bool log = false) const;
            vec3  projection_perp(const vec3 &other,  bool log = false) const;

            float length(bool log = false) const;
            void  normalize(bool log = false);

            bool  is_collinear(const vec3 &other,     bool log = false) const;
            bool  is_perpendicular(const vec3 &other, bool log = false) const;
            bool  is_zero() const;
    };

    bool operator==(const vec3 &v, const vec3 &);
    vec3 operator+ (const vec3 &v, const vec3 &w);
    vec3 operator- (const vec3 &v, const vec3 &w);
    vec3 operator* (const vec3 &v, const float multiplier);
    vec3 operator* (const float multiplier, const vec3 &v);
    vec3 operator/ (const vec3 &v, const float divisor);
    vec3 operator/ (const float divisor, const vec3 &v);

    vec3 operator*=(vec3 &v, const float multiplier);
    vec3 operator*=(const float multiplier, vec3 &vec);
    vec3 operator/=(vec3 &v, const float divisor);
    vec3 operator/=(const float divisor, vec3 &v);
}

#endif // PDM_VECTOR_HPP
