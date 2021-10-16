#include "pdmath/Matrix3.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Matrix4.hpp"
#include "pdmath/Vector4.hpp" 

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Matrices can multiply", "[matrices]") {
    Mat3 m( 3, -5,  4,
           -2,  2,  3,
           -3, -4, -5);

    Mat3 n(-1, -2, -3,
           -5,  2,  3,
            1,  0, -3);

    Mat3 solution (26, -16, -36,
                   -5,   8,   3,
                   18,  -2,  12);
    
    REQUIRE((m *  n)  == solution);    
    REQUIRE((m *= n) == solution);

    m = Mat3(-2,  4,  4,
             -1, -4,  4,
              2,  3,  0);

    n = Mat3( 4,  4,  1,
             -4, -5,  2,
             -1, -1, -5);

    solution = Mat3(-28, -32, -14,
                      8,  12, -29,
                     -4,  -7,  8);
    
    REQUIRE((m *  n)  == solution);    
    REQUIRE((m *= n) == solution);

    Mat4 a( 3, -5,  4,  4,
           -2,  2,  3,  1,
           -3, -4, -5,  0,
           -3, -4, -5,  3);

    Mat4 b(-1, -2, -3, -3,
           -5,  2,  3,  0,
            1,  0, -3,  3,
            1,  0, -3,  2);

    Mat4 ab_solution (30, -16, -48, 11,
                      -4,   8,   0, 17,
                      18,  -2,  12, -6,
                      21,  -2,   3,  0);
    
    REQUIRE((a *  b) == ab_solution);    
    REQUIRE((a *= b) == ab_solution);
}

TEST_CASE("Matrices can add", "[matrices]") {
    Mat3 m(-4, -2, -2,
           -4,  2, -3,
            2, -3,  2);

    Mat3 n(-1, -1,  1,
            1,  3, -3,
           -3, -5,  2);

    Mat3 solution(-5, -3, -1,
                  -3,  5, -6,
                  -1, -8,  4);
    
    REQUIRE((m + n)  == solution);
    REQUIRE((m += n) == solution);

    Mat4 a(-4, -2, -2,  4,
           -4,  2, -3, -3,
            2, -3,  2,  1,
            5,  3,  1,  0);

    Mat4 b(-1, -1,  1,  1,
            1,  3,  0, -3,
           -3, -5,  2,  2,
            3,  2,  2,  2);

    Mat4 ab_solution(-5, -3, -1,  5,
                     -3,  5, -3, -6,
                     -1, -8,  4,  3,
                      8,  5,  3,  2);
    
    REQUIRE((a +  b) == ab_solution);
    REQUIRE((a += b) == ab_solution);
}

TEST_CASE("Matrices can subtract", "[matrices]") {
    Mat3 m(-2, -4,  4,
            0,  0, -5,
           -4,  0, -5);

    Mat3 n(-1, -3,  4,
            4,  4, -2,
           -3,  3, -4);

    Mat3 solution(-1, -1,  0,
                  -4, -4, -3,
                  -1, -3, -1);

    REQUIRE((m - n)  == solution);
    REQUIRE((m -= n) == solution);

    Mat4 a(-2, -4,  4,  4,
            0,  0, -5, -3,
           -4,  0, -5,  1,
            5,  3,  1,  0);

    Mat4 b(-1, -3,  4,  1,
            4,  4, -2, -3,
           -3,  3, -4,  2,
            3,  2,  2,  2);

    Mat4 ab_solution(-1, -1,  0,  3,
                     -4, -4, -3,  0,
                     -1, -3, -1, -1,
                      2,  1, -1, -2);
    
    REQUIRE((a -  b) == ab_solution);
    REQUIRE((a -= b) == ab_solution);
}

TEST_CASE("Matrix Vector multiplication works", "[matrices][vectors]") {
    Mat3 m( 3,  2, 0,
            1, -1, 4,
           -4,  4, 4);

    Mat3 n(-4, -1, -5,
           -3,  3,  0,
            0,  1,  3);

    Vec3 v(-3, -1, 4);

    REQUIRE((m * v) == Vec3(-11, 14, 24));
    REQUIRE((m * n * v) == Vec3(-9, 31, 96));

    Mat4 a( 3,  2, 0, -1,
            1, -1, 4, -4,
           -4,  4, 4,  0,
            2, -3, 5,  2);

    Mat4 b(-4, -1, -5, 2,
           -3,  3,  0, 3,
            1,  1,  3, 0,
            4, -2, -1, 3);

    Vec4 w(-3, -1, 4, 1);

    REQUIRE((a * w)     == Vec4(-12, 10, 24,  19));
    REQUIRE((a * b * w) == Vec4( 14, 62, 88, -19));
}

TEST_CASE("Matrices can find their determinants", "[matrices]") {
    Mat3 m(-5, -3,  1,
           -4,  1,  0,
            2, -4, -1);

    REQUIRE(m.determinant() == 31);

    m = Mat3( 2, 2, -5,
              3, 2,  3,
             -3, -5, 4);

    REQUIRE(m.determinant() == 49);
}

TEST_CASE("Matrices know their minors, cofactors, and adjoints", "[matrices]") {
    Mat3 m(3, 0,  2,
           2, 0, -2,
           0, 1,  1);

    REQUIRE(m.matrix_of_minors() == Mat3( 2,   2, 2,
                                         -2,   3, 3,
                                          0, -10, 0));

    REQUIRE(m.matrix_of_cofactors() == Mat3( 2, -2,  2,
                                             2,  3, -3,
                                             0, 10,  0));

    REQUIRE(m.matrix_of_cofactors().transpose() == Mat3( 2,  2,  0,
                                                        -2,  3, 10,
                                                         2, -3,  0));
}

TEST_CASE("Matrices can find their inverses", "[matrices]") {
    Mat3 m(3, 0,  2,
           2, 0, -2,
           0, 1,  1);

    REQUIRE(m.inverse() == Mat3( 0.2f,  0.2f, 0.0f,
                                -0.2f,  0.3f, 1.0f,
                                 0.2f, -0.3f, 0.0f));
}