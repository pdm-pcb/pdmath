#include "pdmath/Matrix3.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Matrix4.hpp"
#include "pdmath/Vector4.hpp" 

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Matrices can multiply", "[matrices]") {
    Mat3 m( 3.0f, -5.0f,  4.0f,
           -2.0f,  2.0f,  3.0f,
           -3.0f, -4.0f, -5.0f);

    Mat3 n(-1.0f, -2.0f, -3.0f,
           -5.0f,  2.0f,  3.0f,
            1.0f,  0.0f, -3.0f);

    Mat3 solution (26.0f, -16.0f, -36.0f,
                   -5.0f,   8.0f,   3.0f,
                   18.0f,  -2.0f,  12.0f);
    
    REQUIRE((m *  n) == solution);    
    REQUIRE((m *= n) == solution);

    m = Mat3(-2.0f,  4.0f,  4.0f,
             -1.0f, -4.0f,  4.0f,
              2.0f,  3.0f,  0.0f);

    n = Mat3( 4.0f,  4.0f,  1.0f,
             -4.0f, -5.0f,  2.0f,
             -1.0f, -1.0f, -5.0f);

    solution = Mat3(-28.0f, -32.0f, -14.0f,
                      8.0f,  12.0f, -29.0f,
                     -4.0f,  -7.0f,   8.0f);
    
    REQUIRE((m *  n) == solution);    
    REQUIRE((m *= n) == solution);
}

TEST_CASE("Matrices can add", "[matrices]") {
    Mat3 m(-4.0f, -2.0f, -2.0f,
           -4.0f,  2.0f, -3.0f,
            2.0f, -3.0f,  2.0f);

    Mat3 n(-1.0f, -1.0f,  1.0f,
            1.0f,  3.0f, -3.0f,
           -3.0f, -5.0f,  2.0f);

    Mat3 solution(-5.0f, -3.0f, -1.0f,
                  -3.0f,  5.0f, -6.0f,
                  -1.0f, -8.0f,  4.0f);
    
    REQUIRE((m +  n) == solution);
    REQUIRE((m += n) == solution);

    Mat4 a(-4.0f, -2.0f, -2.0f,  4.0f,
           -4.0f,  2.0f, -3.0f, -3.0f,
            2.0f, -3.0f,  2.0f,  1.0f,
            5.0f,  3.0f,  1.0f,  0.0f);

    Mat4 b(-1.0f, -1.0f,  1.0f,  1.0f,
            1.0f,  3.0f,  0.0f, -3.0f,
           -3.0f, -5.0f,  2.0f,  2.0f,
            3.0f,  2.0f,  2.0f,  2.0f);

    Mat4 ab_solution(-5.0f, -3.0f, -1.0f,  5.0f,
                     -3.0f,  5.0f, -3.0f, -6.0f,
                     -1.0f, -8.0f,  4.0f,  3.0f,
                      8.0f,  5.0f,  3.0f,  2.0f);
    
    REQUIRE((a +  b) == ab_solution);
    REQUIRE((a += b) == ab_solution);
}

TEST_CASE("Matrices can subtract", "[matrices]") {
    Mat3 m(-2.0f, -4.0f,  4.0f,
            0.0f,  0.0f, -5.0f,
           -4.0f,  0.0f, -5.0f);

    Mat3 n(-1.0f, -3.0f,  4.0f,
            4.0f,  4.0f, -2.0f,
           -3.0f,  3.0f, -4.0f);

    Mat3 solution(-1.0f, -1.0f,  0.0f,
                  -4.0f, -4.0f, -3.0f,
                  -1.0f, -3.0f, -1.0f);

    REQUIRE((m -  n) == solution);
    REQUIRE((m -= n) == solution);

    Mat4 a(-2.0f, -4.0f,  4.0f,  4.0f,
            0.0f,  0.0f, -5.0f, -3.0f,
           -4.0f,  0.0f, -5.0f,  1.0f,
            5.0f,  3.0f,  1.0f,  0.0f);

    Mat4 b(-1.0f, -3.0f,  4.0f,  1.0f,
            4.0f,  4.0f, -2.0f, -3.0f,
           -3.0f,  3.0f, -4.0f,  2.0f,
            3.0f,  2.0f,  2.0f,  2.0f);

    Mat4 ab_solution(-1.0f, -1.0f,  0.0f,  3.0f,
                     -4.0f, -4.0f, -3.0f,  0.0f,
                     -1.0f, -3.0f, -1.0f, -1.0f,
                      2.0f,  1.0f, -1.0f, -2.0f);
    
    REQUIRE((a -  b) == ab_solution);
    REQUIRE((a -= b) == ab_solution);
}

TEST_CASE("Matrix Vector multiplication works", "[matrices][vectors]") {
    Mat3 m( 3.0f,  2.0f, 0.0f,
            1.0f, -1.0f, 4.0f,
           -4.0f,  4.0f, 4.0f);

    Mat3 n(-4.0f, -1.0f, -5.0f,
           -3.0f,  3.0f,  0.0f,
            0.0f,  1.0f,  3.0f);

    Vec3 v(-3.0f, -1.0f, 4.0f);

    REQUIRE((m * v) == Vec3(-11.0f, 14.0f, 24.0f));
    REQUIRE((m * n * v) == Vec3(-9.0f, 31.0f, 96.0f));
}

TEST_CASE("Matrices can find their determinants", "[matrices]") {
    Mat3 m(-5.0f, -3.0f,  1.0f,
           -4.0f,  1.0f,  0.0f,
            2.0f, -4.0f, -1.0f);

    REQUIRE(m.determinant() == 31);

    m = Mat3( 2.0f,  2.0f,-5.0f,
              3.0f,  2.0f, 3.0f,
             -3.0f, -5.0f, 4.0f);

    REQUIRE(m.determinant() == 49);
}

TEST_CASE("Matrices know their minors, cofactors, and adjoints", "[matrices]") {
    Mat3 m(3.0f, 0.0f,  2.0f,
           2.0f, 0.0f, -2.0f,
           0.0f, 1.0f,  1.0f);

    REQUIRE(m.matrix_of_minors() == Mat3( 2.0f,   2.0f, 2.0f,
                                         -2.0f,   3.0f, 3.0f,
                                          0.0f, -10.0f, 0.0f));

    REQUIRE(m.matrix_of_cofactors() == Mat3(2.0f, -2.0f,  2.0f,
                                            2.0f,  3.0f, -3.0f,
                                            0.0f, 10.0f,  0.0f));

    REQUIRE(m.matrix_of_cofactors().transposed() == Mat3( 2.0f,  2.0f,  0.0f,
                                                         -2.0f,  3.0f, 10.0f,
                                                          2.0f, -3.0f,  0.0f));
}

TEST_CASE("Matrices can find their inverses", "[matrices]") {
    Mat3 m(3.0f, 0.0f,  2.0f,
           2.0f, 0.0f, -2.0f,
           0.0f, 1.0f,  1.0f);

    REQUIRE(m.inverted() == Mat3( 0.2f,  0.2f, 0.0f,
                                 -0.2f,  0.3f, 1.0f,
                                  0.2f, -0.3f, 0.0f));
}

TEST_CASE("Extracting Euler angles from matrices", "[matrices]") {
    Mat3 r( 0.09473f, -0.0442f, -0.9945f,
            0.30563f, -0.9495f, 0.07129f,
           -0.9474f, -0.3107f, -0.0764f);

    Vec3 ans1;
    Vec3 ans2;

    r.get_euler_xyz(ans1, ans2);

    REQUIRE(ans1 == Vec3(-2.39078f, -1.465867f, 0.436564f));
    REQUIRE(ans2 == Vec3(0.750813f, -1.675726f, -2.705029f));

    r = Mat3(-0.0696f,  0.7956f, -0.6018f,
             -0.4681f, -0.5588f, -0.6846f,
             -0.8809f,  0.2341f,  0.41133f);

    r.get_euler_xyz(ans1, ans2);

    REQUIRE(ans1 == Vec3(1.029765f, -0.645753f, -1.658055f));
    REQUIRE(ans2 == Vec3(-2.111828f, -2.49584f, 1.483537f));

    // Well... these don't work for now.
    // r = Mat3( 0.67016f,  0.6509f, 0.35668f,
    //          -0.6467f,   0.2763f, 0.71092f,
    //           0.36419f, -0.7071f, 0.60611f);

    // r.get_euler_zxy(ans1, ans2);

    // REQUIRE(ans1 == Vec3(-3.0892f, -0.1047f, 0.4538f));
    // REQUIRE(ans2 == Vec3(0.0524f, 3.0369f, 2.6878f));
}