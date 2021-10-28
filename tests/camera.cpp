#include "pdmath/Camera.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

#include <numbers>
#include <cmath>

using namespace pdm;
using namespace Catch;

Camera ortho(Vec3(2, -1, -4), Vec3(-569, 399, -61), Vec3(0, 1, 0));

TEST_CASE("Orthographic camera gives correct View-to-World matrix",
          "[cameras][matrices]") {
    ortho.set_ortho(-700, 700, 394, -394, 1, 7000, 1280, 720, 1);
    Mat4 vtw(0.099331f, 0.569014f,  0.816305f,  2.0f,
             0.0f,      0.820363f, -0.571843f, -1.0f,
            -0.995054f, 0.056801f,  0.081487f, -4.0f,
             0.0f,       0.0f,        0.0f,     1.0f);

    REQUIRE(ortho._view_to_world == vtw);
}

TEST_CASE("Orthographic camera gives correct World-to-View matrix",
          "[cameras][matrices]") {
    ortho.set_ortho(-700, 700, 394, -394, 1, 7000, 1280, 720, 1);
    Mat4 wtv(0.099331f,  0.000000f, -0.995054f, -4.178880f,
             0.569015f,  0.820363f,  0.056801f, -0.090459f,
             0.816305f, -0.571843f,  0.081487f, -1.878504f,
             0.0f,       0.0f,       0.0f,       1.0f);

    REQUIRE(ortho._world_to_view == wtv);
}

TEST_CASE("Orthographic camera can set it's NDC projection matrix",
          "[cameras][matrices]") {
    ortho.set_ortho(-700, 700, 394, -394, 1, 7000, 1280, 720, 1);
    Mat4 ortho_ndc(0.001429f,    0.0f,          0.0f,       0.0f,
                   0.0f,         0.0025381f,    0.0f,       0.0f,
                   0.0f,         0.0f,         -0.000286f, -1.000286f,
                   0.0f,         0.0f,          0.0f,       1.0f);

    REQUIRE(ortho._ortho_ndc == ortho_ndc);
}

TEST_CASE("Orthographic camera can set it's screen projection matrix",
          "[cameras][matrices]") {
    ortho.set_ortho(-700, 700, 394, -394, 1, 7000, 1280, 720, 1);
    Mat4 ortho_screen(640.0f,  0.0f,   0.0f, 640.0f,
                      0.0f,   -360.0f, 0.0f, 360.0f,
                      0.0f,    0.0f,   0.5f, 0.5f,
                      0.0f,    0.0f,   0.0f, 1.0f);

    REQUIRE(ortho._screen == ortho_screen);
}

TEST_CASE("Orthographic camera can transform points properly", "[cameras]") {
    ortho.set_ortho(-700, 700, 394, -394, 1, 7000, 1280, 720, 1);
    Point4 p1(-4549.0f, 3260.0f, -259.0f, 1.0f);
    Point4 p2(-4500.0f, 3323.0f, -309.0f, 1.0f);
    Point4 p3(-4510.0f, 3305.0f, -332.0f, 1.0f);

    REQUIRE(ortho.view(p1) ==
            Point4(-198.317367f, 71.132431f, -5600.567871f, 1.0f));
    REQUIRE(ortho.view(p2) ==
            Point4(-143.697403f, 147.85704f, -5600.668945f, 1.0f));
    REQUIRE(ortho.view(p3) ==
            Point4(-121.804458f, 126.094047f, -5600.412597f, 1.0f));

    REQUIRE(ortho.ortho_ndc(p1) ==
            Point4(-0.28331f, 0.180539f, 0.600104f, 1.0f));
    REQUIRE(ortho.ortho_ndc(p2) ==
            Point4(-0.205282f, 0.375272f, 0.600134f, 1.0f));
    REQUIRE(ortho.ortho_ndc(p3) ==
            Point4(-0.174006f, 0.320036f, 0.600061f, 1.0f));

    REQUIRE(ortho.ortho_screen(p1) ==
            Point4(458.681274f, 295.005493f, 0.800052f, 1.0f));
    REQUIRE(ortho.ortho_screen(p2) ==
            Point4(508.619537f, 224.901779f, 0.800067f, 1.0f));
    REQUIRE(ortho.ortho_screen(p3) ==
            Point4(528.635925f, 244.786895f, 0.80003f, 1.0f));
}

TEST_CASE("Orthographic camera can pick points in space", "[cameras]") {
    ortho.set_ortho(-700, 700, 394, -394, 1, 7000, 1280, 720, 1);
    Point4 screen_near(505, 558, 0, 1);
    Point4 screen_far (505, 558, 1, 1);

    REQUIRE((ortho._screen.inverted() * screen_near) == 
            Point4(-0.210937f, -0.55f, -1.0f, 1.0f));
    REQUIRE((ortho._screen.inverted() * screen_near) == 
            Point4(-0.210937f, -0.55f, 1.0f, 1.0f));

    REQUIRE((ortho._ortho_ndc.inverted() * ortho._screen.inverted() *
             screen_near) == 
            Point4(-147.65625f, -216.700012f, -1.0f, 1.0f));
    REQUIRE((ortho._ortho_ndc.inverted() * ortho._screen.inverted() *
             screen_far) == 
            Point4(-147.65625f, -216.7000122f, -7000.0f, 1.0f));

    REQUIRE((ortho._view_to_world *
             ortho._ortho_ndc.inverted() *
             ortho._screen.inverted() *
             screen_near) == 
            Point4(-136.788696f, -178.200805f, 130.535583f, 1.0f));
    REQUIRE((ortho._view_to_world *
             ortho._ortho_ndc.inverted() *
             ortho._screen.inverted() *
             screen_far) == 
            Point4(-5850.113281f, 3824.128418f, -439.796264f, 1.0f));
}

//
//
// Perspective Camera Tests
//
//

Camera persp(Vec3(6, -1, 3), Vec3(197, 633, -449), Vec3(0, 1, 0));

TEST_CASE("Perspective camera gives correct View-to-World matrix",
          "[cameras][matrices]") {
    persp.set_persp(1.0f, 8000.0f, 1280.0f, 720.0f,
                    std::numbers::pi_v<float> / 4.0f, 1.0f);
    Mat4 vtw(0.921135f, -0.307815f, -0.238240f,  6.0f,
             0.0f,       0.612063f, -0.790808f, -1.0f,
             0.389241f,  0.728442f,  0.563794f,  3.0f,
             0.0f,       0.0f,       0.0f,       1.0f);

    REQUIRE(persp._view_to_world == vtw);
}


TEST_CASE("Perspective camera gives correct World-to-View matrix",
          "[cameras][matrices]") {
    persp.set_persp(1.0f, 8000.0f, 1280.0f, 720.0f,
                    std::numbers::pi_v<float> / 4.0f, 1.0f);
    Mat4 wtv(0.921135f,  0.0f,      0.389241f, -6.694538f,
            -0.307815f,  0.612063f, 0.728442f,  0.273628f,
            -0.238240f, -0.790808f, 0.563794f, -1.052748f,
             0.0f,       0.0f,      0.0f,       1.0f);
         

    REQUIRE(persp._world_to_view == wtv);
}

TEST_CASE("Perspective camera can set it's NDC projection matrix",
          "[cameras][matrices]") {
    persp.set_persp(1.0f, 8000.0f, 1280.0f, 720.0f,
                    std::numbers::pi_v<float> / 4.0f, 1.0f);
    Mat4 persp_ndc(1.358f, 0.0f,      0.0f,      0.0f,
                   0.0f,   2.414214f, 0.0f,      0.0f,
                   0.0f,   0.0f,     -1.00025f, -2.00025f,
                   0.0f,   0.0f,     -1.0f,      0.0f);

    REQUIRE(persp._persp_ndc == persp_ndc);
}

TEST_CASE("Perspective camera can set it's screen projection matrix",
          "[cameras][matrices]") {
    persp.set_persp(1.0f, 8000.0f, 1280.0f, 720.0f,
                    std::numbers::pi_v<float> / 4.0f, 1.0f);
    Mat4 persp_screen(640.0f,  0.0f,   0.0f, 640.0f,
                      0.0f,   -360.0f, 0.0f, 360.0f,
                      0.0f,    0.0f,   0.5f, 0.5f,
                      0.0f,    0.0f,   0.0f, 1.0f);

    REQUIRE(persp._screen == persp_screen);
}

TEST_CASE("Perspective camera can transform points properly", "[cameras]") {
    persp.set_persp(1.0f, 8000.0f, 1280.0f, 720.0f,
                    std::numbers::pi_v<float> / 4.0f, 1.0f);
    Point4 p1(65.0f, 135.0f, -128.0f, 1.0f);
    Point4 p2(45.0f, 137.0f, -132.0f, 1.0f);
    Point4 p3(64.0f, 147.0f, -112.0f, 1.0f);

    REQUIRE(persp.view(p1) ==
            Point4(3.356437f, -30.346321f, -195.463134f, 1.0f));
    REQUIRE(persp.view(p2) ==
            Point4(-16.623245f, -25.879653f, -194.53511f, 1.0f));
    REQUIRE(persp.view(p3) ==
            Point4(8.663158f, -11.038665f, -195.693893f, 1.0f));

    REQUIRE(persp.persp_ndc(p1) ==
            Point4(0.023319f, -0.374814f, 0.990016f, 1.0f));
    REQUIRE(persp.persp_ndc(p2) ==
            Point4(-0.116042f, -0.32117f, 0.989967f, 1.0f));
    REQUIRE(persp.persp_ndc(p3) ==
            Point4(0.060117f, -0.13618f, 0.990028f, 1.0f));

    REQUIRE(persp.persp_screen(p1) ==
            Point4(458.681274f, 295.005493f, 0.800052f, 1.0f));
    REQUIRE(persp.persp_screen(p2) ==
            Point4(508.619537f, 224.901779f, 0.800067f, 1.0f));
    REQUIRE(persp.persp_screen(p3) ==
            Point4(528.635925f, 244.786895f, 0.80003f, 1.0f));
}