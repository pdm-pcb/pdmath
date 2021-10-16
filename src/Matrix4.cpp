#include "pdmath/Matrix4.hpp"

#include "pdmath/Vector4.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Matrix3.hpp"

#include <iomanip>

namespace pdm {
    Mat4::Mat4(const Point4 &x, const Point4 &y,
               const Point4 &z, const Point4 &w) :
        _elem{{x._x, y._x, z._x, w._x},
              {x._y, y._y, z._y, w._y},
              {x._z, y._z, z._z, w._z},
              {x._w, y._w, z._w, w._w}}
    { }

    Mat4::Mat4(const std::array<float, 4> &x,
               const std::array<float, 4> &y,
               const std::array<float, 4> &z,
               const std::array<float, 4> &w) :
        _elem{{x[0], y[0], z[0], w[0]},
              {x[1], y[1], z[0], w[0]},
              {x[2], y[2], z[2], w[2]},
              {x[3], y[3], z[3], w[3]}}
    { }
    
    Mat4::Mat4(const float x1, const float y1, const float z1, const float w1,
               const float x2, const float y2, const float z2, const float w2,
               const float x3, const float y3, const float z3, const float w3,
               const float x4, const float y4, const float z4, const float w4) :
        _elem{{x1, y1, z1, w1},
              {x2, y2, z2, w2},
              {x3, y3, z3, w3},
              {x4, y4, z4, w4}}
    { }

    Mat4::Mat4(const Mat3 &m) {
        _elem[0][0] = m._elem[0][0];
        _elem[0][1] = m._elem[0][1];
        _elem[0][2] = m._elem[0][2];
        _elem[0][3] = 0.0f;

        _elem[1][0] = m._elem[1][0];
        _elem[1][1] = m._elem[1][1];
        _elem[1][2] = m._elem[1][2];
        _elem[1][3] = 0.0f;

        _elem[2][0] = m._elem[2][0];
        _elem[2][1] = m._elem[2][1];
        _elem[2][2] = m._elem[2][2];
        _elem[2][3] = 0.0f;

        _elem[3][0] = 0.0f;
        _elem[3][1] = 0.0f;
        _elem[3][2] = 0.0f;
        _elem[3][3] = 1.0f;
    }

    Point4 Mat4::transform(const Point4 &point, const Vec3 &translation,
            const float theta_x, const float theta_y, const float theta_z,
            const Vec3 &prev_translation, const Mat3 &prev_rotation,
            const Vec3& scale) {
        Vec3 _translation = prev_translation + (prev_rotation * translation);

        Mat3 rot_x;
        if(theta_x != 1) {
            float cos_theta = std::cos(theta_x);
            float sin_theta = std::sin(theta_x);
            rot_x = Mat3(1.0f, 0.0f,       0.0f,
                         0.0f, cos_theta, -sin_theta,
                         0.0f, sin_theta,  cos_theta);
        }
        else {
            rot_x = Identity3;
        }

        Mat3 rot_y;
        if(theta_y != 1) {
            float cos_theta = std::cos(theta_y);
            float sin_theta = std::sin(theta_y);
            rot_y = Mat3( cos_theta,  0.0f, sin_theta,
                          0.0f,       1.0f,      0.0f,
                         -sin_theta,  0.0f, cos_theta);
        }
        else {
            rot_y = Identity3;
        }

        Mat3 rot_z;
        if(theta_z != 1) {
            float cos_theta = std::cos(theta_z);
            float sin_theta = std::sin(theta_z);
            rot_z = Mat3(cos_theta, -sin_theta, 0.0f,
                         sin_theta,  cos_theta, 0.0f,
                         0.0f,       0.0f,      1.0f);
        }
        else {
            rot_z = Identity3;
        }

        Mat4 transform = static_cast<Mat4>(prev_rotation *
                                           rot_x * rot_y * rot_z);
        transform.set_translation(_translation);
        transform.apply_scale(scale);

        return transform * point;
    }

    Vec4 Mat4::get_world_position() const {
        return Vec4(this->_elem[0][3],
                    this->_elem[1][3],
                    this->_elem[2][3],
                    this->_elem[3][3]);
    }

    float Mat4::get_x_scale() const {
        return Vec3 (this->_elem[0][0],
                     this->_elem[1][0],
                     this->_elem[2][0]).length();
    }

    float Mat4::get_y_scale() const {
        return Vec3 (this->_elem[0][1],
                     this->_elem[1][1],
                     this->_elem[2][1]).length();
    }

    float Mat4::get_z_scale() const {
        return Vec3 (this->_elem[0][2],
                     this->_elem[1][2],
                     this->_elem[2][2]).length();
    }

    Vec3 Mat4::get_x_unit_vector() const {
        return Vec3(this->_elem[0][0],
                    this->_elem[1][0],
                    this->_elem[2][0]).normalize();
    }

    Vec3 Mat4::get_y_unit_vector() const {
        return Vec3(this->_elem[0][1],
                    this->_elem[1][1],
                    this->_elem[2][1]).normalize();

    }

    Vec3 Mat4::get_z_unit_vector() const {
        return Vec3(this->_elem[0][2],
                    this->_elem[1][2],
                    this->_elem[2][2]).normalize();

    }

    Mat4 Mat4::inverse() const {
        float x_scale = get_x_scale();
        float y_scale = get_y_scale();
        float z_scale = get_z_scale();
    
        Vec3 x_rot(this->_elem[0][0] / x_scale,
                   this->_elem[1][0] / x_scale,
                   this->_elem[2][0] / x_scale);
    
        Vec3 y_rot(this->_elem[0][1] / y_scale,
                   this->_elem[1][1] / y_scale,
                   this->_elem[2][1] / y_scale);
    
        Vec3 z_rot(this->_elem[0][2] / z_scale,
                   this->_elem[1][2] / z_scale,
                   this->_elem[2][2] / z_scale);
        
        Mat4 t(1.0f, 0.0f, 0.0f, -_elem[0][3],
               0.0f, 1.0f, 0.0f, -_elem[1][3],
               0.0f, 0.0f, 1.0f, -_elem[2][3],
               0.0f, 0.0f, 0.0f, 1.0f);

        Mat4 r(x_rot._x, x_rot._y, x_rot._z, 0.0f,
               y_rot._x, y_rot._y, y_rot._z, 0.0f,
               z_rot._x, z_rot._y, z_rot._z, 0.0f,
               0.0f,     0.0f,     0.0f,     1.0f);
        
        Mat4 s(1/x_scale, 0.0f,      0.0f,      0.0f,
               0.0f,      1/y_scale, 0.0f,      0.0f,
               0.0f,      0.0f,      1/z_scale, 0.0f,
               0.0f,      0.0f,      0.0f,      1.0f );

        return s * r * t;
    }

    Mat4 Mat4::transpose() const {
        return Mat4(_elem[0][0], _elem[1][0], _elem[2][0], _elem[3][0],
                    _elem[0][1], _elem[1][1], _elem[2][1], _elem[3][1],
                    _elem[0][2], _elem[1][2], _elem[2][2], _elem[3][2],
                    _elem[0][3], _elem[1][3], _elem[2][3], _elem[3][3]);
    }
    
    const Mat4& Mat4::set_translation(const Vec4& v) {
        _elem[0][3] = v._x;
        _elem[1][3] = v._y;
        _elem[2][3] = v._z;
        _elem[3][3] = v._w;

        return *this;
    }
    
    const Mat4& Mat4::set_translation(const Vec3& v) {
        _elem[0][3] = v._x;
        _elem[1][3] = v._y;
        _elem[2][3] = v._z;
        _elem[3][3] = 1.0f;

        return *this;
    }

    const Mat4& Mat4::apply_scale(const Vec4 &v) {
        _elem[0][0] *= v._x;
        _elem[1][0] *= v._x;
        _elem[2][0] *= v._x;
        
        _elem[0][1] *= v._y;
        _elem[1][1] *= v._y;
        _elem[2][1] *= v._y;
        
        _elem[0][2] *= v._z;
        _elem[1][2] *= v._z;
        _elem[2][2] *= v._z;

        return *this;   
    }

    const Mat4& Mat4::apply_scale(const Vec3 &v) {
        _elem[0][0] *= v._x;
        _elem[1][0] *= v._x;
        _elem[2][0] *= v._x;
        
        _elem[0][1] *= v._y;
        _elem[1][1] *= v._y;
        _elem[2][1] *= v._y;
        
        _elem[0][2] *= v._z;
        _elem[1][2] *= v._z;
        _elem[2][2] *= v._z;

        return *this;
    }

    bool Mat4::operator==(const Mat4 &m) const {
        if(this == &m) {
            return true;
        }

        Vec4 x(_elem[0][0], _elem[1][0], _elem[2][0], _elem[3][0]);
        Vec4 y(_elem[0][1], _elem[1][1], _elem[2][1], _elem[3][1]);
        Vec4 z(_elem[0][2], _elem[1][2], _elem[2][2], _elem[3][2]);
        Vec4 t(_elem[0][3], _elem[1][3], _elem[2][3], _elem[3][3]);

        Vec4 m_x(m._elem[0][0], m._elem[1][0], m._elem[2][0], m._elem[3][0]);
        Vec4 m_y(m._elem[0][1], m._elem[1][1], m._elem[2][1], m._elem[3][1]);
        Vec4 m_z(m._elem[0][2], m._elem[1][2], m._elem[2][2], m._elem[3][2]);
        Vec4 m_t(m._elem[0][3], m._elem[1][3], m._elem[2][3], m._elem[3][3]);
    
        return x == m_x && y == m_y && z == m_z && t == m_t;
    }

    const Mat4& Mat4::operator*=(const Mat4 &m) {
        float x1 = (_elem[0][0] * m._elem[0][0]) +
                   (_elem[0][1] * m._elem[1][0]) +
                   (_elem[0][2] * m._elem[2][0]) +
                   (_elem[0][3] * m._elem[3][0]);    
        float y1 = (_elem[0][0] * m._elem[0][1]) +
                   (_elem[0][1] * m._elem[1][1]) +
                   (_elem[0][2] * m._elem[2][1]) +
                   (_elem[0][3] * m._elem[3][1]);
        float z1 = (_elem[0][0] * m._elem[0][2]) +
                   (_elem[0][1] * m._elem[1][2]) +
                   (_elem[0][2] * m._elem[2][2]) +
                   (_elem[0][3] * m._elem[3][2]);
        float w1 = (_elem[0][0] * m._elem[0][3]) +
                   (_elem[0][1] * m._elem[1][3]) +
                   (_elem[0][2] * m._elem[2][3]) +
                   (_elem[0][3] * m._elem[3][3]);

        float x2 = (_elem[1][0] * m._elem[0][0]) +
                   (_elem[1][1] * m._elem[1][0]) +
                   (_elem[1][2] * m._elem[2][0]) +
                   (_elem[1][3] * m._elem[3][0]);    
        float y2 = (_elem[1][0] * m._elem[0][1]) +
                   (_elem[1][1] * m._elem[1][1]) +
                   (_elem[1][2] * m._elem[2][1]) +
                   (_elem[1][3] * m._elem[3][1]);
        float z2 = (_elem[1][0] * m._elem[0][2]) +
                   (_elem[1][1] * m._elem[1][2]) +
                   (_elem[1][2] * m._elem[2][2]) +
                   (_elem[1][3] * m._elem[3][2]);
        float w2 = (_elem[1][0] * m._elem[0][3]) +
                   (_elem[1][1] * m._elem[1][3]) +
                   (_elem[1][2] * m._elem[2][3]) +
                   (_elem[1][3] * m._elem[3][3]);

        float x3 = (_elem[2][0] * m._elem[0][0]) +
                   (_elem[2][1] * m._elem[1][0]) +
                   (_elem[2][2] * m._elem[2][0]) +
                   (_elem[2][3] * m._elem[3][0]);    
        float y3 = (_elem[2][0] * m._elem[0][1]) +
                   (_elem[2][1] * m._elem[1][1]) +
                   (_elem[2][2] * m._elem[2][1]) +
                   (_elem[2][3] * m._elem[3][1]);
        float z3 = (_elem[2][0] * m._elem[0][2]) +
                   (_elem[2][1] * m._elem[1][2]) +
                   (_elem[2][2] * m._elem[2][2]) +
                   (_elem[2][3] * m._elem[3][2]);
        float w3 = (_elem[2][0] * m._elem[0][3]) +
                   (_elem[2][1] * m._elem[1][3]) +
                   (_elem[2][2] * m._elem[2][3]) +
                   (_elem[2][3] * m._elem[3][3]);

        float x4 = (_elem[3][0] * m._elem[0][0]) +
                   (_elem[3][1] * m._elem[1][0]) +
                   (_elem[3][2] * m._elem[2][0]) +
                   (_elem[3][3] * m._elem[3][0]);    
        float y4 = (_elem[3][0] * m._elem[0][1]) +
                   (_elem[3][1] * m._elem[1][1]) +
                   (_elem[3][2] * m._elem[2][1]) +
                   (_elem[3][3] * m._elem[3][1]);
        float z4 = (_elem[3][0] * m._elem[0][2]) +
                   (_elem[3][1] * m._elem[1][2]) +
                   (_elem[3][2] * m._elem[2][2]) +
                   (_elem[3][3] * m._elem[3][2]);
        float w4 = (_elem[3][0] * m._elem[0][3]) +
                   (_elem[3][1] * m._elem[1][3]) +
                   (_elem[3][2] * m._elem[2][3]) +
                   (_elem[3][3] * m._elem[3][3]);

        _elem[0][0] = x1;
        _elem[1][0] = x2;
        _elem[2][0] = x3;
        _elem[3][0] = x4;

        _elem[0][1] = y1;
        _elem[1][1] = y2;
        _elem[2][1] = y3;
        _elem[3][1] = y4;

        _elem[0][2] = z1;
        _elem[1][2] = z2;
        _elem[2][2] = z3;
        _elem[3][2] = z4;

        _elem[0][3] = w1;
        _elem[1][3] = w2;
        _elem[2][3] = w3;
        _elem[3][3] = w4;

        return *this;
    }

    const Mat4& Mat4::operator*=(const float scalar) {
        this->_elem[0][0] *= scalar;
        this->_elem[1][0] *= scalar;
        this->_elem[2][0] *= scalar;
        this->_elem[3][0] *= scalar;

        this->_elem[0][1] *= scalar;
        this->_elem[1][1] *= scalar;
        this->_elem[2][1] *= scalar;
        this->_elem[3][1] *= scalar;

        this->_elem[0][2] *= scalar;
        this->_elem[1][2] *= scalar;
        this->_elem[2][2] *= scalar;
        this->_elem[3][2] *= scalar;

        this->_elem[0][3] *= scalar;
        this->_elem[1][3] *= scalar;
        this->_elem[2][3] *= scalar;
        this->_elem[3][3] *= scalar;

        return *this;
    }

    const Mat4& Mat4::operator+=(const Mat4 &m) {
        this->_elem[0][0] += m._elem[0][0];
        this->_elem[1][0] += m._elem[1][0];
        this->_elem[2][0] += m._elem[2][0];
        this->_elem[3][0] += m._elem[3][0];

        this->_elem[0][1] += m._elem[0][1];
        this->_elem[1][1] += m._elem[1][1];
        this->_elem[2][1] += m._elem[2][1];
        this->_elem[3][1] += m._elem[3][1];

        this->_elem[0][2] += m._elem[0][2];
        this->_elem[1][2] += m._elem[1][2];
        this->_elem[2][2] += m._elem[2][2];
        this->_elem[3][2] += m._elem[3][2];

        this->_elem[0][3] += m._elem[0][3];
        this->_elem[1][3] += m._elem[1][3];
        this->_elem[2][3] += m._elem[2][3];
        this->_elem[3][3] += m._elem[3][3];

        return *this;
    }

    const Mat4& Mat4::operator-=(const Mat4 &m) {
        this->_elem[0][0] -= m._elem[0][0];
        this->_elem[1][0] -= m._elem[1][0];
        this->_elem[2][0] -= m._elem[2][0];
        this->_elem[3][0] -= m._elem[3][0];

        this->_elem[0][1] -= m._elem[0][1];
        this->_elem[1][1] -= m._elem[1][1];
        this->_elem[2][1] -= m._elem[2][1];
        this->_elem[3][1] -= m._elem[3][1];

        this->_elem[0][2] -= m._elem[0][2];
        this->_elem[1][2] -= m._elem[1][2];
        this->_elem[2][2] -= m._elem[2][2];
        this->_elem[3][2] -= m._elem[3][2];

        this->_elem[0][3] -= m._elem[0][3];
        this->_elem[1][3] -= m._elem[1][3];
        this->_elem[2][3] -= m._elem[2][3];
        this->_elem[3][3] -= m._elem[3][3];

        return *this;
    }

    Mat4 operator*(const Mat4 &m, const Mat4 &n) {
        return Mat4(m._elem[0][0] * n._elem[0][0] +
                    m._elem[0][1] * n._elem[1][0] +
                    m._elem[0][2] * n._elem[2][0] +
                    m._elem[0][3] * n._elem[3][0],
                    m._elem[0][0] * n._elem[0][1] +
                    m._elem[0][1] * n._elem[1][1] +
                    m._elem[0][2] * n._elem[2][1] +
                    m._elem[0][3] * n._elem[3][1],
                    m._elem[0][0] * n._elem[0][2] +
                    m._elem[0][1] * n._elem[1][2] +
                    m._elem[0][2] * n._elem[2][2] +
                    m._elem[0][3] * n._elem[3][2],
                    m._elem[0][0] * n._elem[0][3] +
                    m._elem[0][1] * n._elem[1][3] +
                    m._elem[0][2] * n._elem[2][3] +
                    m._elem[0][3] * n._elem[3][3],

                    m._elem[1][0] * n._elem[0][0] +
                    m._elem[1][1] * n._elem[1][0] +
                    m._elem[1][2] * n._elem[2][0] +
                    m._elem[1][3] * n._elem[3][0],
                    m._elem[1][0] * n._elem[0][1] +
                    m._elem[1][1] * n._elem[1][1] +
                    m._elem[1][2] * n._elem[2][1] +
                    m._elem[1][3] * n._elem[3][1],
                    m._elem[1][0] * n._elem[0][2] +
                    m._elem[1][1] * n._elem[1][2] +
                    m._elem[1][2] * n._elem[2][2] +
                    m._elem[1][3] * n._elem[3][2],
                    m._elem[1][0] * n._elem[0][3] +
                    m._elem[1][1] * n._elem[1][3] +
                    m._elem[1][2] * n._elem[2][3] +
                    m._elem[1][3] * n._elem[3][3],

                    m._elem[2][0] * n._elem[0][0] +
                    m._elem[2][1] * n._elem[1][0] +
                    m._elem[2][2] * n._elem[2][0] +
                    m._elem[2][3] * n._elem[3][0],
                    m._elem[2][0] * n._elem[0][1] +
                    m._elem[2][1] * n._elem[1][1] +
                    m._elem[2][2] * n._elem[2][1] +
                    m._elem[2][3] * n._elem[3][1],
                    m._elem[2][0] * n._elem[0][2] +
                    m._elem[2][1] * n._elem[1][2] +
                    m._elem[2][2] * n._elem[2][2] +
                    m._elem[2][3] * n._elem[3][2],
                    m._elem[2][0] * n._elem[0][3] +
                    m._elem[2][1] * n._elem[1][3] +
                    m._elem[2][2] * n._elem[2][3] +
                    m._elem[2][3] * n._elem[3][3],

                    m._elem[3][0] * n._elem[0][0] +
                    m._elem[3][1] * n._elem[1][0] +
                    m._elem[3][2] * n._elem[2][0] +
                    m._elem[3][3] * n._elem[3][0],
                    m._elem[3][0] * n._elem[0][1] +
                    m._elem[3][1] * n._elem[1][1] +
                    m._elem[3][2] * n._elem[2][1] +
                    m._elem[3][3] * n._elem[3][1],
                    m._elem[3][0] * n._elem[0][2] +
                    m._elem[3][1] * n._elem[1][2] +
                    m._elem[3][2] * n._elem[2][2] +
                    m._elem[3][3] * n._elem[3][2],
                    m._elem[3][0] * n._elem[0][3] +
                    m._elem[3][1] * n._elem[1][3] +
                    m._elem[3][2] * n._elem[2][3] +
                    m._elem[3][3] * n._elem[3][3]);
    }

    Mat4 operator*(const Mat4 &m, const float scalar) {
        return Mat4(m._elem[0][0] * scalar,
                    m._elem[0][1] * scalar,
                    m._elem[0][2] * scalar,
                    m._elem[0][3] * scalar,

                    m._elem[1][0] * scalar,
                    m._elem[1][1] * scalar,
                    m._elem[1][2] * scalar,
                    m._elem[1][3] * scalar,

                    m._elem[2][0] * scalar,
                    m._elem[2][1] * scalar,
                    m._elem[2][2] * scalar,
                    m._elem[2][3] * scalar,

                    m._elem[3][0] * scalar,
                    m._elem[3][1] * scalar,
                    m._elem[3][2] * scalar,
                    m._elem[3][3] * scalar);
    }

    Mat4 operator*(const float scalar, const Mat4 &m) {
        return m * scalar;
    }

    Mat4 operator+(const Mat4 &m, const Mat4 &n) {
        return Mat4(m._elem[0][0] + n._elem[0][0],
                    m._elem[0][1] + n._elem[0][1],
                    m._elem[0][2] + n._elem[0][2],
                    m._elem[0][3] + n._elem[0][3],

                    m._elem[1][0] + n._elem[1][0],
                    m._elem[1][1] + n._elem[1][1],
                    m._elem[1][2] + n._elem[1][2],
                    m._elem[1][3] + n._elem[1][3],
                    
                    m._elem[2][0] + n._elem[2][0],
                    m._elem[2][1] + n._elem[2][1],
                    m._elem[2][2] + n._elem[2][2],
                    m._elem[2][3] + n._elem[2][3],
                    
                    m._elem[3][0] + n._elem[3][0],
                    m._elem[3][1] + n._elem[3][1],
                    m._elem[3][2] + n._elem[3][2],
                    m._elem[3][3] + n._elem[3][3]);
    }

    Mat4 operator-(const Mat4 &m, const Mat4 &n) {
        return Mat4(m._elem[0][0] - n._elem[0][0],
                    m._elem[0][1] - n._elem[0][1],
                    m._elem[0][2] - n._elem[0][2],
                    m._elem[0][3] - n._elem[0][3],

                    m._elem[1][0] - n._elem[1][0],
                    m._elem[1][1] - n._elem[1][1],
                    m._elem[1][2] - n._elem[1][2],
                    m._elem[1][3] - n._elem[1][3],
                    
                    m._elem[2][0] - n._elem[2][0],
                    m._elem[2][1] - n._elem[2][1],
                    m._elem[2][2] - n._elem[2][2],
                    m._elem[2][3] - n._elem[2][3],
                    
                    m._elem[3][0] - n._elem[3][0],
                    m._elem[3][1] - n._elem[3][1],
                    m._elem[3][2] - n._elem[3][2],
                    m._elem[3][3] - n._elem[3][3]);
    }

    Point4 operator*(const Mat4 &m,   const Point4 &p) {
        return Point4((m._elem[0][0] * p._x) +
                      (m._elem[0][1] * p._y) +
                      (m._elem[0][2] * p._z) +
                      (m._elem[0][3] * p._w),
                      (m._elem[1][0] * p._x) +
                      (m._elem[1][1] * p._y) +
                      (m._elem[1][2] * p._z) +
                      (m._elem[1][3] * p._w),
                      (m._elem[2][0] * p._x) +
                      (m._elem[2][1] * p._y) +
                      (m._elem[2][2] * p._z) +
                      (m._elem[2][3] * p._w),
                      (m._elem[3][0] * p._x) +
                      (m._elem[3][1] * p._y) +
                      (m._elem[3][2] * p._z) +
                      (m._elem[3][3] * p._w));
    }

    Vec4 operator*(const Mat4 &m,   const Vec4 &v) {
        return Vec4((m._elem[0][0] * v._x) +
                    (m._elem[0][1] * v._y) +
                    (m._elem[0][2] * v._z) +
                    (m._elem[0][3] * v._w), 
                    (m._elem[1][0] * v._x) +
                    (m._elem[1][1] * v._y) +
                    (m._elem[1][2] * v._z) +
                    (m._elem[1][3] * v._w),
                    (m._elem[2][0] * v._x) +
                    (m._elem[2][1] * v._y) +
                    (m._elem[2][2] * v._z) +
                    (m._elem[2][3] * v._w),
                    (m._elem[3][0] * v._x) +
                    (m._elem[3][1] * v._y) +
                    (m._elem[3][2] * v._z) +
                    (m._elem[3][3] * v._w));
    }

    std::ostream& operator<<(std::ostream &os, const Mat4 &m) {
        os << std::fixed << std::setprecision(Point4::_output_precision)
           << "[" << m._elem[0][0] << ", " << m._elem[0][1] << ", "
           << m._elem[0][2] << ", " << m._elem[0][3] << "]\n"
           << "[" << m._elem[1][0] << ", " << m._elem[1][1] << ", "
           << m._elem[1][2] << ", " << m._elem[1][3] << "]\n"
           << "[" << m._elem[2][0] << ", " << m._elem[2][1] << ", "
           << m._elem[2][2] << ", " << m._elem[2][3] << "]\n"
           << "[" << m._elem[3][0] << ", " << m._elem[3][1] << ", "
           << m._elem[3][2] << ", " << m._elem[3][3] << "]";
        return os;
    }
} // namespace pdm