#include "pdmath/Camera.hpp"

namespace pdm {
    Camera::Camera(Vec3 pos, Vec3 target, Vec3 up) :
        _position{pos}, _target{target}, _up{up}
    {
        set_gaze();
    }

    void Camera::set_gaze() {
        _gaze = (_target - _position).normalized();
        _gaze._x *= -1;
        _gaze._y *= -1;
        _gaze._z *= -1;
    }

    Mat4 Camera::view_to_world() const {
        Vec3 v_side = _up.cross(_gaze).normalized();
        Vec3 v_up   = _gaze.cross(v_side).normalized();

        return Mat4(v_side._x, v_up._x, _gaze._x, _position._x,
                    v_side._y, v_up._y, _gaze._y, _position._y,
                    v_side._z, v_up._z, _gaze._z, _position._z,
                    0,         0,       0,        1);
    }
}