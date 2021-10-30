#ifndef PDMATH_CAMERA_HPP
#define PDMATH_CAMERA_HPP

#include "pdmath/Point4.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Matrix4.hpp"

namespace pdm {
    class Camera {
        public:

            void set_view(const Vec3 &pos, const Vec3 &target, const Vec3 &up);

            void set_ortho(const float left,  const float right,
                           const float top,   const float bottom,
                           const float near,  const float far,
                           const float x_res, const float y_res,
                           const float z_depth);

            void set_persp(const float near,  const float far,
                           const float x_res, const float y_res,
                           const float fov,   const float z_depth);

            Point4 view(const Point4 &point) const;

            Point4 ortho_ndc(const Point4 &point) const;
            Point4 ortho_screen(const Point4 &point) const;

            Point4 persp_ndc(const Point4 &point) const;
            Point4 persp_screen(const Point4 &point) const;

            Vec4 face_normal(const Point4 &a, const Point4 &b,
                             const Point4 &c) const;

            Vec4 direction_to_point(const Point4 &p) const;

            Mat4 _view_to_world;
            Mat4 _world_to_view;
            Mat4 _screen;

            Mat4 _ortho_ndc;
            Mat4 _persp_ndc;
    
            Camera()  = default;
            Camera(const Vec3 &pos, const Vec3 &target, const Vec3 &up);
            ~Camera() = default;

        private:
            Vec3 _position;
            Vec3 _target;
            Vec3 _gaze;
            Vec3 _up;
    };
}

#endif // PDMATH_CAMERA_HPP