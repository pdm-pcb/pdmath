#ifndef PDMATH_POINT_HPP
#define PDMATH_POINT_HPP

#include <iostream>
#include <cmath>

namespace pdm {
    class Line;
    class Plane;

    class Point {
        public:
            Point() = default;
            Point(const float x, const float y, const float z);

            static constexpr float epsilon = 1.0e-6f;
            static constexpr uint8_t _output_precision = 7;

            float _x;
            float _y;
            float _z;

            bool  are_collinear(const Point &b, const Point &c) const;
            float distance_to_line(const Line &line) const;
            bool  is_on_plane(const Plane &plane) const;
            float distance_to_plane(const Plane &plane) const;

            bool is_zero() const;
    };

    std::ostream& operator<<(std::ostream &os, const Point &p);

    template<class A> bool operator==(const A &p, const A &t) {
        static_assert(std::is_base_of<Point, A>::value);
        if(&p == &t) {
            return true;
        }

        float x_diff = (fabsf(p._x) - fabsf(t._x));
        float y_diff = (fabsf(p._y) - fabsf(t._y));
        float z_diff = (fabsf(p._z) - fabsf(t._z));

        return x_diff < Point::epsilon &&
               y_diff < Point::epsilon &&
               z_diff < Point::epsilon;
    }

    template<class A> A& operator+=(A &p, const A &t) {
        static_assert(std::is_base_of<Point, A>::value);
        p._x += t._x;
        p._y += t._y;
        p._z += t._z;
        return p;
    }
    template<class A> A& operator-=(A &p, const A &t) {
        static_assert(std::is_base_of<Point, A>::value);
        p._x -= t._x;
        p._y -= t._y;
        p._z -= t._z;
        return p;
    }

    template<class A> A& operator+=(A &p, const float scalar) {
        static_assert(std::is_base_of<Point, A>::value);
        p._x += scalar;
        p._y += scalar;
        p._z += scalar;
        return p;
    }
    template<class A> A& operator-=(A &p, const float scalar) {
        static_assert(std::is_base_of<Point, A>::value);
        p._x -= scalar;
        p._y -= scalar;
        p._z -= scalar;
        return p;
    }
    template<class A> A& operator*=(A &p, const float scalar) {
        static_assert(std::is_base_of<Point, A>::value);
        p._x *= scalar;
        p._y *= scalar;
        p._z *= scalar;
        return p;
    }
    template<class A> A& operator/=(A &p, const float scalar) {
        static_assert(std::is_base_of<Point, A>::value);
        p._x /= scalar;
        p._y /= scalar;
        p._z /= scalar;
        return p;
    }

    template<class A> A operator+(const A &p, const A &t) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x + t._x,
                 p._y + t._y,
                 p._z + t._z);

    }
    template<class A> A operator-(const A &p, const A &t) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x - t._x,
                 p._y - t._y,
                 p._z - t._z);
    }
    template<class A, class B> A operator+(const A &p, const B &t) {
        static_assert(std::is_base_of<Point, A>::value);
        static_assert(std::is_base_of<Point, B>::value);
        return A(p._x + t._x,
                 p._y + t._y,
                 p._z + t._z);

    }
    template<class A, class B> A operator-(const A &p, const B &t) {
        static_assert(std::is_base_of<Point, A>::value);
        static_assert(std::is_base_of<Point, B>::value);
        return A(p._x - t._x,
                 p._y - t._y,
                 p._z - t._z);
    }

    template<class A> A operator+(const A &p, const float scalar) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x + scalar,
                 p._y + scalar,
                 p._z + scalar);

    }
    template<class A> A operator-(const A &p, const float scalar) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x - scalar,
                 p._y - scalar,
                 p._z - scalar);

    }
    template<class A> A operator*(const A &p, const float scalar) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x * scalar,
                 p._y * scalar,
                 p._z * scalar);

    }
    template<class A> A operator/(const A &p, const float scalar) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x / scalar,
                 p._y / scalar,
                 p._z / scalar);

    }
    
    template<class A> A operator+(const float scalar, const A &p) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x + scalar,
                 p._y + scalar,
                 p._z + scalar);

    }
    template<class A> A operator-(const float scalar, const A &p) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x - scalar,
                 p._y - scalar,
                 p._z - scalar);

    }
    template<class A> A operator*(const float scalar, const A &p) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x * scalar,
                 p._y * scalar,
                 p._z * scalar);

    }
    template<class A> A operator/(const float scalar, const A &p) {
        static_assert(std::is_base_of<Point, A>::value);
        return A(p._x / scalar,
                 p._y / scalar,
                 p._z / scalar);

    }

} // namespace pdm

#endif // PDMATH_POINT_HPP
