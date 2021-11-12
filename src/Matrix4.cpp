#include "pdmath/Matrix4.hpp"

#include "pdmath/Vector4.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Matrix3.hpp"

#include <iomanip>

namespace pdm {
    const Mat4 Mat4::identity(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);

    Point4 Mat4::transform(const Point4 &point, const Vec3 &translation,
            const float theta_x, const float theta_y, const float theta_z,
            const Vec3& scale,
            Vec3 &prev_translation, Mat3 &prev_rotation) {
        Vec3 _translation = prev_translation + (prev_rotation * translation);

        Mat3 _rotation = prev_rotation * Mat3::populate_rotation(theta_x,
                                                                 theta_y,
                                                                 theta_z);
        Mat4 transform(_rotation);
        transform.apply_scale(scale);
        transform.set_translation(_translation);

        prev_translation = _translation;
        prev_rotation    = _rotation;

        return transform * point;
    }

    Point4 Mat4::transform(const Point4 &point, const Vec3 &translation,
                const float theta_x, const float theta_y, const float theta_z,
                const Vec3 &scale, Mat4 &prev_transform) {
        Mat4 transform(Mat3::populate_rotation(theta_x, theta_y, theta_z));
        transform.apply_scale(scale);
        transform *= prev_transform;
        transform.set_translation(translation);

        prev_transform = transform;

        return transform * point;
    }

    Vec4 Mat4::get_world_position() const {
        return Vec4(this->_m[0][3],
                    this->_m[1][3],
                    this->_m[2][3],
                    this->_m[3][3]);
    }

    float Mat4::get_x_scale() const {
        return Vec3 (this->_m[0][0],
                     this->_m[1][0],
                     this->_m[2][0]).length();
    }

    float Mat4::get_y_scale() const {
        return Vec3 (this->_m[0][1],
                     this->_m[1][1],
                     this->_m[2][1]).length();
    }

    float Mat4::get_z_scale() const {
        return Vec3 (this->_m[0][2],
                     this->_m[1][2],
                     this->_m[2][2]).length();
    }

    Vec3 Mat4::get_x_unit_vector() const {
        return Vec3(this->_m[0][0],
                    this->_m[1][0],
                    this->_m[2][0]).normalized();
    }

    Vec3 Mat4::get_y_unit_vector() const {
        return Vec3(this->_m[0][1],
                    this->_m[1][1],
                    this->_m[2][1]).normalized();

    }

    Vec3 Mat4::get_z_unit_vector() const {
        return Vec3(this->_m[0][2],
                    this->_m[1][2],
                    this->_m[2][2]).normalized();

    }

    Mat4 Mat4::inverted_trs() const {
        float x_scale = get_x_scale();
        float y_scale = get_y_scale();
        float z_scale = get_z_scale();
    
        Vec3 x_rot(this->_m[0][0] / x_scale,
                   this->_m[1][0] / x_scale,
                   this->_m[2][0] / x_scale);
    
        Vec3 y_rot(this->_m[0][1] / y_scale,
                   this->_m[1][1] / y_scale,
                   this->_m[2][1] / y_scale);
    
        Vec3 z_rot(this->_m[0][2] / z_scale,
                   this->_m[1][2] / z_scale,
                   this->_m[2][2] / z_scale);

        Mat4 t_inv(1.0f, 0.0f, 0.0f, -_m[0][3],
                   0.0f, 1.0f, 0.0f, -_m[1][3],
                   0.0f, 0.0f, 1.0f, -_m[2][3],
                   0.0f, 0.0f, 0.0f,  1.0f);

        Mat4 r_inv(x_rot._x, x_rot._y, x_rot._z, 0.0f,
                   y_rot._x, y_rot._y, y_rot._z, 0.0f,
                   z_rot._x, z_rot._y, z_rot._z, 0.0f,
                   0.0f,     0.0f,     0.0f,     1.0f);
        
        Mat4 s_inv(1/x_scale, 0.0f,      0.0f,      0.0f,
                   0.0f,      1/y_scale, 0.0f,      0.0f,
                   0.0f,      0.0f,      1/z_scale, 0.0f,
                   0.0f,      0.0f,      0.0f,      1.0f);

        return s_inv * r_inv * t_inv;
    }

    Mat4 Mat4::inverted() const {
        float A2323 = _m[2][2] * _m[3][3] - _m[2][3] * _m[3][2];
        float A1323 = _m[2][1] * _m[3][3] - _m[2][3] * _m[3][1];
        float A1223 = _m[2][1] * _m[3][2] - _m[2][2] * _m[3][1];
        float A0323 = _m[2][0] * _m[3][3] - _m[2][3] * _m[3][0];
        float A0223 = _m[2][0] * _m[3][2] - _m[2][2] * _m[3][0];
        float A0123 = _m[2][0] * _m[3][1] - _m[2][1] * _m[3][0];
        float A2313 = _m[1][2] * _m[3][3] - _m[1][3] * _m[3][2];
        float A1313 = _m[1][1] * _m[3][3] - _m[1][3] * _m[3][1];
        float A1213 = _m[1][1] * _m[3][2] - _m[1][2] * _m[3][1];
        float A2312 = _m[1][2] * _m[2][3] - _m[1][3] * _m[2][2];
        float A1312 = _m[1][1] * _m[2][3] - _m[1][3] * _m[2][1];
        float A1212 = _m[1][1] * _m[2][2] - _m[1][2] * _m[2][1];
        float A0313 = _m[1][0] * _m[3][3] - _m[1][3] * _m[3][0];
        float A0213 = _m[1][0] * _m[3][2] - _m[1][2] * _m[3][0];
        float A0312 = _m[1][0] * _m[2][3] - _m[1][3] * _m[2][0];
        float A0212 = _m[1][0] * _m[2][2] - _m[1][2] * _m[2][0];
        float A0113 = _m[1][0] * _m[3][1] - _m[1][1] * _m[3][0];
        float A0112 = _m[1][0] * _m[2][1] - _m[1][1] * _m[2][0];

        float det = 
            _m[0][0] * (_m[1][1] * A2323 - _m[1][2] * A1323 + _m[1][3] * A1223)
          - _m[0][1] * (_m[1][0] * A2323 - _m[1][2] * A0323 + _m[1][3] * A0223)
          + _m[0][2] * (_m[1][0] * A1323 - _m[1][1] * A0323 + _m[1][3] * A0123)
          - _m[0][3] * (_m[1][0] * A1223 - _m[1][1] * A0223 + _m[1][2] * A0123);
        det = 1 / det;

        return Mat4(
            det *  (_m[1][1] * A2323 - _m[1][2] * A1323 + _m[1][3] * A1223),
            det * -(_m[0][1] * A2323 - _m[0][2] * A1323 + _m[0][3] * A1223),
            det *  (_m[0][1] * A2313 - _m[0][2] * A1313 + _m[0][3] * A1213),
            det * -(_m[0][1] * A2312 - _m[0][2] * A1312 + _m[0][3] * A1212),
            det * -(_m[1][0] * A2323 - _m[1][2] * A0323 + _m[1][3] * A0223),
            det *  (_m[0][0] * A2323 - _m[0][2] * A0323 + _m[0][3] * A0223),
            det * -(_m[0][0] * A2313 - _m[0][2] * A0313 + _m[0][3] * A0213),
            det *  (_m[0][0] * A2312 - _m[0][2] * A0312 + _m[0][3] * A0212),
            det *  (_m[1][0] * A1323 - _m[1][1] * A0323 + _m[1][3] * A0123),
            det * -(_m[0][0] * A1323 - _m[0][1] * A0323 + _m[0][3] * A0123),
            det *  (_m[0][0] * A1313 - _m[0][1] * A0313 + _m[0][3] * A0113),
            det * -(_m[0][0] * A1312 - _m[0][1] * A0312 + _m[0][3] * A0112),
            det * -(_m[1][0] * A1223 - _m[1][1] * A0223 + _m[1][2] * A0123),
            det *  (_m[0][0] * A1223 - _m[0][1] * A0223 + _m[0][2] * A0123),
            det * -(_m[0][0] * A1213 - _m[0][1] * A0213 + _m[0][2] * A0113),
            det *  (_m[0][0] * A1212 - _m[0][1] * A0212 + _m[0][2] * A0112));
    }

    Mat4 Mat4::transposed() const {
        return Mat4(_m[0][0], _m[1][0], _m[2][0], _m[3][0],
                    _m[0][1], _m[1][1], _m[2][1], _m[3][1],
                    _m[0][2], _m[1][2], _m[2][2], _m[3][2],
                    _m[0][3], _m[1][3], _m[2][3], _m[3][3]);
    }
    
    const Mat4& Mat4::set_translation(const Vec4& v) {
        _m[0][3] = v._x;
        _m[1][3] = v._y;
        _m[2][3] = v._z;
        _m[3][3] = v._w;

        return *this;
    }
    
    const Mat4& Mat4::set_translation(const Vec3& v) {
        _m[0][3] = v._x;
        _m[1][3] = v._y;
        _m[2][3] = v._z;
        _m[3][3] = 1.0f;

        return *this;
    }

    const Mat4& Mat4::apply_scale(const Vec4 &v) {
        _m[0][0] *= v._x;
        _m[1][0] *= v._x;
        _m[2][0] *= v._x;
        
        _m[0][1] *= v._y;
        _m[1][1] *= v._y;
        _m[2][1] *= v._y;
        
        _m[0][2] *= v._z;
        _m[1][2] *= v._z;
        _m[2][2] *= v._z;

        return *this;   
    }

    const Mat4& Mat4::apply_scale(const Vec3 &v) {
        _m[0][0] *= v._x;
        _m[1][0] *= v._x;
        _m[2][0] *= v._x;
        
        _m[0][1] *= v._y;
        _m[1][1] *= v._y;
        _m[2][1] *= v._y;
        
        _m[0][2] *= v._z;
        _m[1][2] *= v._z;
        _m[2][2] *= v._z;

        return *this;
    }

    Mat4::Mat4(const Point4 &x, const Point4 &y,
               const Point4 &z, const Point4 &w) noexcept:
        _m{{x._x, y._x, z._x, w._x},
           {x._y, y._y, z._y, w._y},
           {x._z, y._z, z._z, w._z},
           {x._w, y._w, z._w, w._w}}
    { }

    Mat4::Mat4(const std::array<float, 4> &x,
               const std::array<float, 4> &y,
               const std::array<float, 4> &z,
               const std::array<float, 4> &w) noexcept:
        _m{{x[0], y[0], z[0], w[0]},
              {x[1], y[1], z[0], w[0]},
              {x[2], y[2], z[2], w[2]},
              {x[3], y[3], z[3], w[3]}}
    { }
    
    Mat4::Mat4(const float x1, const float y1, const float z1, const float w1,
               const float x2, const float y2, const float z2, const float w2,
               const float x3, const float y3, const float z3, const float w3,
               const float x4, const float y4, const float z4, const float w4)
               noexcept :
        _m{{x1, y1, z1, w1},
           {x2, y2, z2, w2},
           {x3, y3, z3, w3},
           {x4, y4, z4, w4}}
    { }

    Mat4::Mat4(const Mat3 &m) noexcept {
        _m[0][0] = m._m[0][0];
        _m[0][1] = m._m[0][1];
        _m[0][2] = m._m[0][2];
        _m[0][3] = 0.0f;

        _m[1][0] = m._m[1][0];
        _m[1][1] = m._m[1][1];
        _m[1][2] = m._m[1][2];
        _m[1][3] = 0.0f;

        _m[2][0] = m._m[2][0];
        _m[2][1] = m._m[2][1];
        _m[2][2] = m._m[2][2];
        _m[2][3] = 0.0f;

        _m[3][0] = 0.0f;
        _m[3][1] = 0.0f;
        _m[3][2] = 0.0f;
        _m[3][3] = 1.0f;
    }

    bool Mat4::operator==(const Mat4 &m) const {
        if(this == &m) {
            return true;
        }

        Vec4 x(_m[0][0], _m[1][0], _m[2][0], _m[3][0]);
        Vec4 y(_m[0][1], _m[1][1], _m[2][1], _m[3][1]);
        Vec4 z(_m[0][2], _m[1][2], _m[2][2], _m[3][2]);
        Vec4 t(_m[0][3], _m[1][3], _m[2][3], _m[3][3]);

        Vec4 m_x(m._m[0][0], m._m[1][0], m._m[2][0], m._m[3][0]);
        Vec4 m_y(m._m[0][1], m._m[1][1], m._m[2][1], m._m[3][1]);
        Vec4 m_z(m._m[0][2], m._m[1][2], m._m[2][2], m._m[3][2]);
        Vec4 m_t(m._m[0][3], m._m[1][3], m._m[2][3], m._m[3][3]);
    
        return x == m_x && y == m_y && z == m_z && t == m_t;
    }

    const Mat4& Mat4::operator*=(const Mat4 &m) {
        float x1 = (_m[0][0] * m._m[0][0]) +
                   (_m[0][1] * m._m[1][0]) +
                   (_m[0][2] * m._m[2][0]) +
                   (_m[0][3] * m._m[3][0]);    
        float y1 = (_m[0][0] * m._m[0][1]) +
                   (_m[0][1] * m._m[1][1]) +
                   (_m[0][2] * m._m[2][1]) +
                   (_m[0][3] * m._m[3][1]);
        float z1 = (_m[0][0] * m._m[0][2]) +
                   (_m[0][1] * m._m[1][2]) +
                   (_m[0][2] * m._m[2][2]) +
                   (_m[0][3] * m._m[3][2]);
        float w1 = (_m[0][0] * m._m[0][3]) +
                   (_m[0][1] * m._m[1][3]) +
                   (_m[0][2] * m._m[2][3]) +
                   (_m[0][3] * m._m[3][3]);

        float x2 = (_m[1][0] * m._m[0][0]) +
                   (_m[1][1] * m._m[1][0]) +
                   (_m[1][2] * m._m[2][0]) +
                   (_m[1][3] * m._m[3][0]);    
        float y2 = (_m[1][0] * m._m[0][1]) +
                   (_m[1][1] * m._m[1][1]) +
                   (_m[1][2] * m._m[2][1]) +
                   (_m[1][3] * m._m[3][1]);
        float z2 = (_m[1][0] * m._m[0][2]) +
                   (_m[1][1] * m._m[1][2]) +
                   (_m[1][2] * m._m[2][2]) +
                   (_m[1][3] * m._m[3][2]);
        float w2 = (_m[1][0] * m._m[0][3]) +
                   (_m[1][1] * m._m[1][3]) +
                   (_m[1][2] * m._m[2][3]) +
                   (_m[1][3] * m._m[3][3]);

        float x3 = (_m[2][0] * m._m[0][0]) +
                   (_m[2][1] * m._m[1][0]) +
                   (_m[2][2] * m._m[2][0]) +
                   (_m[2][3] * m._m[3][0]);    
        float y3 = (_m[2][0] * m._m[0][1]) +
                   (_m[2][1] * m._m[1][1]) +
                   (_m[2][2] * m._m[2][1]) +
                   (_m[2][3] * m._m[3][1]);
        float z3 = (_m[2][0] * m._m[0][2]) +
                   (_m[2][1] * m._m[1][2]) +
                   (_m[2][2] * m._m[2][2]) +
                   (_m[2][3] * m._m[3][2]);
        float w3 = (_m[2][0] * m._m[0][3]) +
                   (_m[2][1] * m._m[1][3]) +
                   (_m[2][2] * m._m[2][3]) +
                   (_m[2][3] * m._m[3][3]);

        float x4 = (_m[3][0] * m._m[0][0]) +
                   (_m[3][1] * m._m[1][0]) +
                   (_m[3][2] * m._m[2][0]) +
                   (_m[3][3] * m._m[3][0]);    
        float y4 = (_m[3][0] * m._m[0][1]) +
                   (_m[3][1] * m._m[1][1]) +
                   (_m[3][2] * m._m[2][1]) +
                   (_m[3][3] * m._m[3][1]);
        float z4 = (_m[3][0] * m._m[0][2]) +
                   (_m[3][1] * m._m[1][2]) +
                   (_m[3][2] * m._m[2][2]) +
                   (_m[3][3] * m._m[3][2]);
        float w4 = (_m[3][0] * m._m[0][3]) +
                   (_m[3][1] * m._m[1][3]) +
                   (_m[3][2] * m._m[2][3]) +
                   (_m[3][3] * m._m[3][3]);

        _m[0][0] = x1;
        _m[1][0] = x2;
        _m[2][0] = x3;
        _m[3][0] = x4;

        _m[0][1] = y1;
        _m[1][1] = y2;
        _m[2][1] = y3;
        _m[3][1] = y4;

        _m[0][2] = z1;
        _m[1][2] = z2;
        _m[2][2] = z3;
        _m[3][2] = z4;

        _m[0][3] = w1;
        _m[1][3] = w2;
        _m[2][3] = w3;
        _m[3][3] = w4;

        return *this;
    }

    const Mat4& Mat4::operator*=(const float scalar) {
        this->_m[0][0] *= scalar;
        this->_m[1][0] *= scalar;
        this->_m[2][0] *= scalar;
        this->_m[3][0] *= scalar;

        this->_m[0][1] *= scalar;
        this->_m[1][1] *= scalar;
        this->_m[2][1] *= scalar;
        this->_m[3][1] *= scalar;

        this->_m[0][2] *= scalar;
        this->_m[1][2] *= scalar;
        this->_m[2][2] *= scalar;
        this->_m[3][2] *= scalar;

        this->_m[0][3] *= scalar;
        this->_m[1][3] *= scalar;
        this->_m[2][3] *= scalar;
        this->_m[3][3] *= scalar;

        return *this;
    }

    const Mat4& Mat4::operator+=(const Mat4 &m) {
        this->_m[0][0] += m._m[0][0];
        this->_m[1][0] += m._m[1][0];
        this->_m[2][0] += m._m[2][0];
        this->_m[3][0] += m._m[3][0];

        this->_m[0][1] += m._m[0][1];
        this->_m[1][1] += m._m[1][1];
        this->_m[2][1] += m._m[2][1];
        this->_m[3][1] += m._m[3][1];

        this->_m[0][2] += m._m[0][2];
        this->_m[1][2] += m._m[1][2];
        this->_m[2][2] += m._m[2][2];
        this->_m[3][2] += m._m[3][2];

        this->_m[0][3] += m._m[0][3];
        this->_m[1][3] += m._m[1][3];
        this->_m[2][3] += m._m[2][3];
        this->_m[3][3] += m._m[3][3];

        return *this;
    }

    const Mat4& Mat4::operator-=(const Mat4 &m) {
        this->_m[0][0] -= m._m[0][0];
        this->_m[1][0] -= m._m[1][0];
        this->_m[2][0] -= m._m[2][0];
        this->_m[3][0] -= m._m[3][0];

        this->_m[0][1] -= m._m[0][1];
        this->_m[1][1] -= m._m[1][1];
        this->_m[2][1] -= m._m[2][1];
        this->_m[3][1] -= m._m[3][1];

        this->_m[0][2] -= m._m[0][2];
        this->_m[1][2] -= m._m[1][2];
        this->_m[2][2] -= m._m[2][2];
        this->_m[3][2] -= m._m[3][2];

        this->_m[0][3] -= m._m[0][3];
        this->_m[1][3] -= m._m[1][3];
        this->_m[2][3] -= m._m[2][3];
        this->_m[3][3] -= m._m[3][3];

        return *this;
    }

    Mat4 operator*(const Mat4 &m, const Mat4 &n) {
        return Mat4(m._m[0][0] * n._m[0][0] +
                    m._m[0][1] * n._m[1][0] +
                    m._m[0][2] * n._m[2][0] +
                    m._m[0][3] * n._m[3][0],
                    m._m[0][0] * n._m[0][1] +
                    m._m[0][1] * n._m[1][1] +
                    m._m[0][2] * n._m[2][1] +
                    m._m[0][3] * n._m[3][1],
                    m._m[0][0] * n._m[0][2] +
                    m._m[0][1] * n._m[1][2] +
                    m._m[0][2] * n._m[2][2] +
                    m._m[0][3] * n._m[3][2],
                    m._m[0][0] * n._m[0][3] +
                    m._m[0][1] * n._m[1][3] +
                    m._m[0][2] * n._m[2][3] +
                    m._m[0][3] * n._m[3][3],

                    m._m[1][0] * n._m[0][0] +
                    m._m[1][1] * n._m[1][0] +
                    m._m[1][2] * n._m[2][0] +
                    m._m[1][3] * n._m[3][0],
                    m._m[1][0] * n._m[0][1] +
                    m._m[1][1] * n._m[1][1] +
                    m._m[1][2] * n._m[2][1] +
                    m._m[1][3] * n._m[3][1],
                    m._m[1][0] * n._m[0][2] +
                    m._m[1][1] * n._m[1][2] +
                    m._m[1][2] * n._m[2][2] +
                    m._m[1][3] * n._m[3][2],
                    m._m[1][0] * n._m[0][3] +
                    m._m[1][1] * n._m[1][3] +
                    m._m[1][2] * n._m[2][3] +
                    m._m[1][3] * n._m[3][3],

                    m._m[2][0] * n._m[0][0] +
                    m._m[2][1] * n._m[1][0] +
                    m._m[2][2] * n._m[2][0] +
                    m._m[2][3] * n._m[3][0],
                    m._m[2][0] * n._m[0][1] +
                    m._m[2][1] * n._m[1][1] +
                    m._m[2][2] * n._m[2][1] +
                    m._m[2][3] * n._m[3][1],
                    m._m[2][0] * n._m[0][2] +
                    m._m[2][1] * n._m[1][2] +
                    m._m[2][2] * n._m[2][2] +
                    m._m[2][3] * n._m[3][2],
                    m._m[2][0] * n._m[0][3] +
                    m._m[2][1] * n._m[1][3] +
                    m._m[2][2] * n._m[2][3] +
                    m._m[2][3] * n._m[3][3],

                    m._m[3][0] * n._m[0][0] +
                    m._m[3][1] * n._m[1][0] +
                    m._m[3][2] * n._m[2][0] +
                    m._m[3][3] * n._m[3][0],
                    m._m[3][0] * n._m[0][1] +
                    m._m[3][1] * n._m[1][1] +
                    m._m[3][2] * n._m[2][1] +
                    m._m[3][3] * n._m[3][1],
                    m._m[3][0] * n._m[0][2] +
                    m._m[3][1] * n._m[1][2] +
                    m._m[3][2] * n._m[2][2] +
                    m._m[3][3] * n._m[3][2],
                    m._m[3][0] * n._m[0][3] +
                    m._m[3][1] * n._m[1][3] +
                    m._m[3][2] * n._m[2][3] +
                    m._m[3][3] * n._m[3][3]);
    }

    Mat4 operator*(const Mat4 &m, const float scalar) {
        return Mat4(m._m[0][0] * scalar,
                    m._m[0][1] * scalar,
                    m._m[0][2] * scalar,
                    m._m[0][3] * scalar,

                    m._m[1][0] * scalar,
                    m._m[1][1] * scalar,
                    m._m[1][2] * scalar,
                    m._m[1][3] * scalar,

                    m._m[2][0] * scalar,
                    m._m[2][1] * scalar,
                    m._m[2][2] * scalar,
                    m._m[2][3] * scalar,

                    m._m[3][0] * scalar,
                    m._m[3][1] * scalar,
                    m._m[3][2] * scalar,
                    m._m[3][3] * scalar);
    }

    Mat4 operator*(const float scalar, const Mat4 &m) {
        return m * scalar;
    }

    Mat4 operator+(const Mat4 &m, const Mat4 &n) {
        return Mat4(m._m[0][0] + n._m[0][0],
                    m._m[0][1] + n._m[0][1],
                    m._m[0][2] + n._m[0][2],
                    m._m[0][3] + n._m[0][3],

                    m._m[1][0] + n._m[1][0],
                    m._m[1][1] + n._m[1][1],
                    m._m[1][2] + n._m[1][2],
                    m._m[1][3] + n._m[1][3],
                    
                    m._m[2][0] + n._m[2][0],
                    m._m[2][1] + n._m[2][1],
                    m._m[2][2] + n._m[2][2],
                    m._m[2][3] + n._m[2][3],
                    
                    m._m[3][0] + n._m[3][0],
                    m._m[3][1] + n._m[3][1],
                    m._m[3][2] + n._m[3][2],
                    m._m[3][3] + n._m[3][3]);
    }

    Mat4 operator-(const Mat4 &m, const Mat4 &n) {
        return Mat4(m._m[0][0] - n._m[0][0],
                    m._m[0][1] - n._m[0][1],
                    m._m[0][2] - n._m[0][2],
                    m._m[0][3] - n._m[0][3],

                    m._m[1][0] - n._m[1][0],
                    m._m[1][1] - n._m[1][1],
                    m._m[1][2] - n._m[1][2],
                    m._m[1][3] - n._m[1][3],
                    
                    m._m[2][0] - n._m[2][0],
                    m._m[2][1] - n._m[2][1],
                    m._m[2][2] - n._m[2][2],
                    m._m[2][3] - n._m[2][3],
                    
                    m._m[3][0] - n._m[3][0],
                    m._m[3][1] - n._m[3][1],
                    m._m[3][2] - n._m[3][2],
                    m._m[3][3] - n._m[3][3]);
    }

    Point4 operator*(const Mat4 &m,   const Point4 &p) {
        return Point4((m._m[0][0] * p._x) +
                      (m._m[0][1] * p._y) +
                      (m._m[0][2] * p._z) +
                      (m._m[0][3] * p._w),
                      (m._m[1][0] * p._x) +
                      (m._m[1][1] * p._y) +
                      (m._m[1][2] * p._z) +
                      (m._m[1][3] * p._w),
                      (m._m[2][0] * p._x) +
                      (m._m[2][1] * p._y) +
                      (m._m[2][2] * p._z) +
                      (m._m[2][3] * p._w),
                      (m._m[3][0] * p._x) +
                      (m._m[3][1] * p._y) +
                      (m._m[3][2] * p._z) +
                      (m._m[3][3] * p._w));
    }

    Vec4 operator*(const Mat4 &m,   const Vec4 &v) {
        return Vec4((m._m[0][0] * v._x) +
                    (m._m[0][1] * v._y) +
                    (m._m[0][2] * v._z) +
                    (m._m[0][3] * v._w), 
                    (m._m[1][0] * v._x) +
                    (m._m[1][1] * v._y) +
                    (m._m[1][2] * v._z) +
                    (m._m[1][3] * v._w),
                    (m._m[2][0] * v._x) +
                    (m._m[2][1] * v._y) +
                    (m._m[2][2] * v._z) +
                    (m._m[2][3] * v._w),
                    (m._m[3][0] * v._x) +
                    (m._m[3][1] * v._y) +
                    (m._m[3][2] * v._z) +
                    (m._m[3][3] * v._w));
    }

    std::ostream& operator<<(std::ostream &os, const Mat4 &m) {
        os << std::fixed << std::setprecision(Point4::precision)
           << "[" << m._m[0][0] << ", " << m._m[0][1] << ", "
           << m._m[0][2] << ", " << m._m[0][3] << "]\n"
           << "[" << m._m[1][0] << ", " << m._m[1][1] << ", "
           << m._m[1][2] << ", " << m._m[1][3] << "]\n"
           << "[" << m._m[2][0] << ", " << m._m[2][1] << ", "
           << m._m[2][2] << ", " << m._m[2][3] << "]\n"
           << "[" << m._m[3][0] << ", " << m._m[3][1] << ", "
           << m._m[3][2] << ", " << m._m[3][3] << "]";
        return os;
    }
} // namespace pdm