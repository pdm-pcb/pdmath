#include "pdmath/Camera.hpp"

namespace pdm {
    Camera::Camera(const Vec3 &pos, const Vec3 &target, const Vec3 &up) :
        _position{pos}, _target{target}, _up{up}
    {
        set_view(_position, _target, _up);
    }

    void Camera::set_view(const Vec3 &pos, const Vec3 &target, const Vec3 &up) {
        _position = pos;
        _target = target;
        _up = up;

        _gaze = (_target - _position).normalized();
        _gaze._x *= -1;
        _gaze._y *= -1;
        _gaze._z *= -1;
        
        // std::cout << "\n\n-----------------------------------------\n";
        // std::cout << "gaze: " << (_target - _position) << std::endl;
        // std::cout << "gaze normalized: " << _gaze << std::endl;

        Vec3 v_side = _up.cross(_gaze);
        // std::cout << "v_side: " << v_side << std::endl;
        v_side = v_side.normalized();
        // std::cout << "v_side n: " << v_side << std::endl;
        Vec3 v_up   = _gaze.cross(v_side);
        // std::cout << "v_up: " << v_up << std::endl;
        v_up = v_up.normalized();
        // std::cout << "v_up n: " << v_up << std::endl;

        _view_to_world = Mat4(v_side._x, v_up._x, _gaze._x, _position._x,
                              v_side._y, v_up._y, _gaze._y, _position._y,
                              v_side._z, v_up._z, _gaze._z, _position._z,
                              0,         0,       0,        1);
        _world_to_view = _view_to_world.inverted();
    }

    void Camera::set_ortho(const float left,  const float right,
                           const float top,   const float bottom,
                           const float near,  const float far,
                           const float x_res, const float y_res,
                           const float z_depth) {
        _ortho_ndc =
            Mat4((2/(right - left)), 0, 0, -((right + left)/(right - left)),
                 0, (2/(top - bottom)), 0, -((top + bottom)/(top - bottom)),
                 0, 0, -(2/(far - near)),  -((far + near)/(far - near)),
                 0, 0, 0, 1);

        _screen =
            Mat4(x_res/2.0f, 0.0f,        0.0f,         x_res/2.0f,
                 0.0f,       -y_res/2.0f, 0.0f,         y_res/2.0f,
                 0.0f,       0.0f,        z_depth/2.0f, z_depth/2.0f,
                 0.0f,       0.0f,        0.0f,         1.0f);
    }

    void Camera::set_persp(const float near,  const float far,
                           const float x_res, const float y_res,
                           const float fov,   const float z_depth) {
        float aspect   = x_res / y_res;
        float half_fov = fov / 2.0f;
        float distance = std::cos(half_fov) / std::sin(half_fov);

        _persp_ndc =
            Mat4((distance / aspect), 0, 0, 0,
                 0, distance, 0, 0,
                 0, 0,
                 -((far + near)/(far - near)),
                 ((-2 * far * near)/(far - near)),
                 0, 0, -1, 0);

        _screen =
            Mat4(x_res/2.0f, 0.0f,        0.0f,         x_res/2.0f,
                 0.0f,       -y_res/2.0f, 0.0f,         y_res/2.0f,
                 0.0f,       0.0f,        z_depth/2.0f, z_depth/2.0f,
                 0.0f,       0.0f,        0.0f,         1.0f);
    }

    Point4 Camera::view(const Point4 &point) const {
        return _world_to_view * point;
    }

    Point4 Camera::ortho_ndc(const Point4 &point) const {
        return _ortho_ndc * _world_to_view * point;
    }

    Point4 Camera::ortho_screen(const Point4 &point) const {
        return _screen * _ortho_ndc * _world_to_view * point;
    }

    Point4 Camera::persp_ndc(const Point4 &point) const {
        Point4 result(_persp_ndc * _world_to_view * point);
        result /= result._w;
        return result;
    }

    Point4 Camera::persp_screen(const Point4 &point) const {
        return _screen * persp_ndc(point);
    }

    Vec4 Camera::face_normal(const Point4 &a, const Point4 &b,
                             const Point4 &c) {
        Point3 _a(a._x, a._y, a._z);
        Point3 _b(b._x, b._y, b._z);
        Point3 _c(c._x, c._y, c._z);

        return Vec4(
        ((static_cast<Vec3>(_b) - _a).cross(static_cast<Vec3>(_c) - _a)), 1.0f);
    }

    Vec4 Camera::direction_to_point(const Point4 &p) const {
        return p - Vec4(_position, 0.0f) *= -1;
    }
} // namespace pdm