#ifndef PDMATH_CAMERA_HPP
#define PDMATH_CAMERA_HPP

#include "pdmath/Vector3.hpp"
#include "pdmath/Matrix4.hpp"

namespace pdm {
    class Camera {
        public:
            Camera()  = default;
            Camera(Vec3 pos, Vec3 target, Vec3 up);
            ~Camera() = default;

            Vec3 _position;
            Vec3 _target;
            Vec3 _gaze;
            Vec3 _up;

            void set_gaze();
            Mat4 view_to_world() const;
    };
}

#endif // PDMATH_CAMERA_HPP