#ifndef PDMATH_POINT_HPP
#define PDMATH_POINT_HPP

#include <iostream>
#include <cmath>

namespace pdm {
    class Line;
    class Plane;
    class Mat3;

    class Point3 {
        public:
            Point3() = default;
            Point3(const float x, const float y, const float z);

            bool  are_collinear(const Point3 &b, const Point3 &c) const;
            float distance_to_line(const Line &line) const;
            bool  is_on_plane(const Plane &plane) const;
            float distance_to_plane(const Plane &plane) const;

            bool is_zero() const;

            static constexpr uint8_t _output_precision = 7;
            static constexpr float   _epsilon = 1.0e-6f;

            float _x;
            float _y;
            float _z;

            const Point3& operator*=(const Mat3 &m);
    };

    std::ostream& operator<<(std::ostream &os, const Point3 &p);

    //==========================================================================
    // templated operator overloads to serve the various interchangable needs of
    // points and vectors

    // equivalence, based on the coordinates
    template<class A> bool operator==(const A &p, const A &t) {
        static_assert(std::is_base_of<Point3, A>::value);
        if(&p == &t) {
            return true;
        }

        float x_diff = (fabsf(p._x) - fabsf(t._x));
        float y_diff = (fabsf(p._y) - fabsf(t._y));
        float z_diff = (fabsf(p._z) - fabsf(t._z));

        return x_diff < Point3::_epsilon &&
               y_diff < Point3::_epsilon &&
               z_diff < Point3::_epsilon;
    }

    // summing of like types with non-cost rhs
    template<class A> A& operator+=(A &p, const A &t) {
        static_assert(std::is_base_of<Point3, A>::value);
        p._x += t._x;
        p._y += t._y;
        p._z += t._z;
        return p;
    }
    template<class A> A& operator-=(A &p, const A &t) {
        static_assert(std::is_base_of<Point3, A>::value);
        p._x -= t._x;
        p._y -= t._y;
        p._z -= t._z;
        return p;
    }

    // scalar operations with non-const rhs
    template<class A> A& operator+=(A &p, const float scalar) {
        static_assert(std::is_base_of<Point3, A>::value);
        p._x += scalar;
        p._y += scalar;
        p._z += scalar;
        return p;
    }
    template<class A> A& operator-=(A &p, const float scalar) {
        static_assert(std::is_base_of<Point3, A>::value);
        p._x -= scalar;
        p._y -= scalar;
        p._z -= scalar;
        return p;
    }
    template<class A> A& operator*=(A &p, const float scalar) {
        static_assert(std::is_base_of<Point3, A>::value);
        p._x *= scalar;
        p._y *= scalar;
        p._z *= scalar;
        return p;
    }
    template<class A> A& operator/=(A &p, const float scalar) {
        static_assert(std::is_base_of<Point3, A>::value);
        p._x /= scalar;
        p._y /= scalar;
        p._z /= scalar;
        return p;
    } 

    // summing of like types while const on both sides
    template<class A> A operator+(const A &p, const A &t) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x + t._x,
                 p._y + t._y,
                 p._z + t._z);

    }
    template<class A> A operator-(const A &p, const A &t) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x - t._x,
                 p._y - t._y,
                 p._z - t._z);
    }

    // summing of unlike types while const on both sides
    template<class A, class B> A operator+(const A &p, const B &t) {
        static_assert(std::is_base_of<Point3, A>::value);
        static_assert(std::is_base_of<Point3, B>::value);
        return A(p._x + t._x,
                 p._y + t._y,
                 p._z + t._z);

    }
    template<class A, class B> A operator-(const A &p, const B &t) {
        static_assert(std::is_base_of<Point3, A>::value);
        static_assert(std::is_base_of<Point3, B>::value);
        return A(p._x - t._x,
                 p._y - t._y,
                 p._z - t._z);
    }

    // scalar operations with const rhs
    template<class A> A operator+(const A &p, const float scalar) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x + scalar,
                 p._y + scalar,
                 p._z + scalar);

    }
    template<class A> A operator-(const A &p, const float scalar) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x - scalar,
                 p._y - scalar,
                 p._z - scalar);

    }
    template<class A> A operator*(const A &p, const float scalar) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x * scalar,
                 p._y * scalar,
                 p._z * scalar);

    }
    template<class A> A operator/(const A &p, const float scalar) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x / scalar,
                 p._y / scalar,
                 p._z / scalar);

    }
    
    // scalar operations with const lhs
    template<class A> A operator+(const float scalar, const A &p) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x + scalar,
                 p._y + scalar,
                 p._z + scalar);

    }
    template<class A> A operator-(const float scalar, const A &p) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x - scalar,
                 p._y - scalar,
                 p._z - scalar);

    }
    template<class A> A operator*(const float scalar, const A &p) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x * scalar,
                 p._y * scalar,
                 p._z * scalar);

    }
    template<class A> A operator/(const float scalar, const A &p) {
        static_assert(std::is_base_of<Point3, A>::value);
        return A(p._x / scalar,
                 p._y / scalar,
                 p._z / scalar);

    }

} // namespace pdm

#endif // PDMATH_POINT_HPP
