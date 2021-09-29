#ifndef PDM_VECTOR_HPP
#define PDM_VECTOR_HPP

#include <iostream>

namespace pdm {

    class vec3 {
        public:
            vec3() = default;
            vec3(const float x, const float y, const float z);

            void  normalize();

            float length() const;
            float dot(const vec3 &other) const;
            vec3  cross(const vec3 &other) const;
            vec3  project_onto(const vec3 &other) const;
            vec3  projection_perp(const vec3 &other) const;

            bool is_perpendicular(const vec3 &other) const;

            float _x;
            float _y;
            float _z;

            static constexpr float epsilon = 1.0e-5f;
    };


    bool operator==(const vec3 &v, const vec3 &w);
    vec3 operator+ (const vec3 &v, const vec3 &w);
    vec3 operator- (const vec3 &v, const vec3 &w);
    vec3 operator* (vec3 &v, const float multiplier);
    vec3 operator*(const float multiplier, const vec3 &vec);
    vec3 operator/ (vec3 &v, const float divisor);
    vec3 operator/=(vec3 &v, const float divisor);

    std::ostream& operator<<(std::ostream &os, const vec3 &vec);
}

#endif // PDM_VECTOR_HPP
