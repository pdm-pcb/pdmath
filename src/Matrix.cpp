#include "pdmath/Matrix.hpp"

#include "pdmath/Vector.hpp"
#include "pdmath/Point.hpp"

#include <iomanip>

namespace pdm {
    Mat3::Mat3(const Point &x, const Point &y, const Point &z) :
        _elem{{x._x, x._y, x._z},
              {y._x, y._y, y._z},
              {z._x, z._y, z._z}}
    { }

    Mat3::Mat3(const std::array<float, 3> &x,
               const std::array<float, 3> &y,
               const std::array<float, 3> &z) :
        _elem{{x[0], y[0], z[0]},
              {x[1], y[1], z[0]},
              {x[2], y[2], z[2]}}
    { }
    
    Mat3::Mat3(const float x1, const float y1, const float z1,
               const float x2, const float y2, const float z2,
               const float x3, const float y3, const float z3) :
        _elem{{x1, y1, z1},
              {x2, y2, z2},
              {x3, y3, z3}}
    { }

    Mat3 Mat3::inverse() {
        Mat3 identity(1, 0, 0,
                      0, 1, 0,
                      0, 0, 1);

        for(size_t col = 0; col < 3; col++) {
            this->_r1[col]     /= this->_r1[0];
            identity._r1[col]  /= this->_r1[0];

            this->_r2[col]     /= this->_r2[1];
            identity._r2[col]  /= this->_r2[1];

            this->_r3[col]     /= this->_r3[2];
            identity._r3[col]  /= this->_r3[2];
        }

        return identity;
    }

    void Mat3::_cofactor(const float mat[3][3],  float cofactors[3][3],
                         const size_t excl_row,  const size_t excl_col,
                         const size_t dimension) const {
        size_t cof_row = 0;
        size_t cof_col = 0;
    
        for(size_t row = 0; row < dimension; row++) {
            for(size_t col = 0; col < dimension; col++) {
                if(row != excl_row && col != excl_col) {
                    cofactors[cof_row][cof_col++] = mat[row][col];
                    if(cof_col == dimension - 1) {
                        cof_col = 0;
                        cof_row++;
                    }
                }
            }
        }
    }
 
    float Mat3::_determinant(const float mat[3][3],
                             const size_t dimension) const {
        if(dimension == 1) {
            return mat[0][0];
        }

        float determinant = 0.0f;
        float cofactors[3][3];
        int16_t sign = 1;
    
        for(size_t col = 0; col < dimension; col++) {
            _cofactor(mat, cofactors, 0, col, dimension);
    
            determinant += 
               sign * (mat[0][col] * _determinant(cofactors, dimension - 1));
    
            sign = -sign;
        }
    
        return determinant;
    }

    bool Mat3::operator==(const Mat3 &m) const {
        if(this == &m) {
            return true;
        }
    
        return _elem[0][0] == m._elem[0][0] &&
               _elem[1][0] == m._elem[1][0] &&
               _elem[2][0] == m._elem[2][0] &&
               _elem[0][1] == m._elem[0][1] &&
               _elem[1][1] == m._elem[1][1] &&
               _elem[2][1] == m._elem[2][1] &&
               _elem[0][2] == m._elem[0][2] &&
               _elem[1][2] == m._elem[1][2] &&
               _elem[2][2] == m._elem[2][2];
    }

    const Mat3& Mat3::operator*=(const Mat3 &m) {
        float x1 = (_elem[0][0] * m._elem[0][0]) +
                   (_elem[0][1] * m._elem[1][0]) +
                   (_elem[0][2] * m._elem[2][0]);
    
        float y1 = (_elem[0][0] * m._elem[0][1]) +
                   (_elem[0][1] * m._elem[1][1]) +
                   (_elem[0][2] * m._elem[2][1]);

        float z1 = (_elem[0][0] * m._elem[0][2]) +
                   (_elem[0][1] * m._elem[1][2]) +
                   (_elem[0][2] * m._elem[2][2]);

        float x2 = (_elem[1][0] * m._elem[0][0]) +
                   (_elem[1][1] * m._elem[1][0]) +
                   (_elem[1][2] * m._elem[2][0]);

        float y2 = (_elem[1][0] * m._elem[0][1]) +
                   (_elem[1][1] * m._elem[1][1]) +
                   (_elem[1][2] * m._elem[2][1]);

        float z2 = (_elem[1][0] * m._elem[0][2]) +
                   (_elem[1][1] * m._elem[1][2]) +
                   (_elem[1][2] * m._elem[2][2]);

        float x3 = (_elem[2][0] * m._elem[0][0]) +
                   (_elem[2][1] * m._elem[1][0]) +
                   (_elem[2][2] * m._elem[2][0]);

        float y3 = (_elem[2][0] * m._elem[0][1]) +
                   (_elem[2][1] * m._elem[1][1]) +
                   (_elem[2][2] * m._elem[2][1]);

        float z3 = (_elem[2][0] * m._elem[0][2]) +
                   (_elem[2][1] * m._elem[1][2]) +
                   (_elem[2][2] * m._elem[2][2]);

        _elem[0][0] = x1;
        _elem[1][0] = x2;
        _elem[2][0] = x3;

        _elem[0][1] = y1;
        _elem[1][1] = y2;
        _elem[2][1] = y3;

        _elem[0][2] = z1;
        _elem[1][2] = z2;
        _elem[2][2] = z3;

        return *this;
    }

    const Mat3& Mat3::operator*=(const float lambda) {
        this->_elem[0][0] *= lambda;
        this->_elem[1][0] *= lambda;
        this->_elem[2][0] *= lambda;

        this->_elem[0][1] *= lambda;
        this->_elem[1][1] *= lambda;
        this->_elem[2][1] *= lambda;

        this->_elem[0][2] *= lambda;
        this->_elem[1][2] *= lambda;
        this->_elem[2][2] *= lambda;

        return *this;
    }

    const Mat3& Mat3::operator+=(const Mat3 &m) {
        this->_elem[0][0] += m._elem[0][0];
        this->_elem[1][0] += m._elem[1][0];
        this->_elem[2][0] += m._elem[2][0];

        this->_elem[0][1] += m._elem[0][1];
        this->_elem[1][1] += m._elem[1][1];
        this->_elem[2][1] += m._elem[2][1];

        this->_elem[0][2] += m._elem[0][2];
        this->_elem[1][2] += m._elem[1][2];
        this->_elem[2][2] += m._elem[2][2];

        return *this;
    }

    const Mat3& Mat3::operator-=(const Mat3 &m) {
        this->_elem[0][0] -= m._elem[0][0];
        this->_elem[1][0] -= m._elem[1][0];
        this->_elem[2][0] -= m._elem[2][0];

        this->_elem[0][1] -= m._elem[0][1];
        this->_elem[1][1] -= m._elem[1][1];
        this->_elem[2][1] -= m._elem[2][1];

        this->_elem[0][2] -= m._elem[0][2];
        this->_elem[1][2] -= m._elem[1][2];
        this->_elem[2][2] -= m._elem[2][2];

        return *this;
    }

    Mat3 operator*(const Mat3 &m, const Mat3 &n) {
        Mat3 l = m;
        return l *= n;
    }

    Mat3 operator*(const Mat3 &m, const float lambda) {
        Mat3 n = m;
        n *= lambda;
        return n;
    }

    Mat3 operator*(const float lambda, const Mat3 &m) {
        Mat3 n = m;
        n *= lambda;
        return n;
    }

    Mat3 operator+(const Mat3 &m, const Mat3 &n) {
        Mat3 l = m;
        return l += n;
    }

    Mat3 operator-(const Mat3 &m, const Mat3 &n) {
        Mat3 l = m;
        return l -= n;
    }

    Vec3 operator*(const Mat3 &m, const Vec3 &v) {

        float x = (m._elem[0][0] * v._x) +
                  (m._elem[0][1] * v._y) +
                  (m._elem[0][2] * v._z);
    
        float y = (m._elem[1][0] * v._x) +
                  (m._elem[1][1] * v._y) +
                  (m._elem[1][2] * v._z);

        float z = (m._elem[2][0] * v._x) +
                  (m._elem[2][1] * v._y) +
                  (m._elem[2][2] * v._z);

        return Vec3(x, y, z);
    }

    std::ostream& operator<<(std::ostream &os, const Mat3 &m) {
        os << std::fixed << std::setprecision(Point::_output_precision)
           << "[" << m._elem[0][0] << ", " << m._elem[0][1] << ", "
           << m._elem[0][2] << "]\n"
           << "[" << m._elem[1][0] << ", " << m._elem[1][1] << ", "
           << m._elem[1][2] << "]\n"
           << "[" << m._elem[2][0] << ", " << m._elem[2][1] << ", "
           << m._elem[2][2] << "]";
        return os;
    }
} // namespace pdm