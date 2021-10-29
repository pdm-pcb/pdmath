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
    Mat4 vtw(0.099331f, 0.569014f,  0.816305f,  2.0f,
             0.0f,      0.820363f, -0.571843f, -1.0f,
            -0.995054f, 0.056801f,  0.081487f, -4.0f,
             0.0f,       0.0f,        0.0f,     1.0f);

    REQUIRE(ortho._view_to_world == vtw);
}

TEST_CASE("Orthographic camera gives correct World-to-View matrix",
          "[cameras][matrices]") {
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
    Mat4 ortho_screen(640.0f,  0.0f,   0.0f, 640.0f,
                      0.0f,   -360.0f, 0.0f, 360.0f,
                      0.0f,    0.0f,   0.5f, 0.5f,
                      0.0f,    0.0f,   0.0f, 1.0f);

    REQUIRE(ortho._screen == ortho_screen);
}

TEST_CASE("Orthographic camera can transform points properly", "[cameras]") {
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
    Point4 screen_near(505, 558, 0, 1);
    Point4 screen_far (505, 558, 1, 1);

    REQUIRE((ortho._screen.inverted() * screen_near) == 
            Point4(-0.210937f, -0.55f, -1.0f, 1.0f));
    REQUIRE((ortho._screen.inverted() * screen_far) == 
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
    Mat4 vtw(0.921135f, -0.307815f, -0.238240f,  6.0f,
             0.0f,       0.612063f, -0.790808f, -1.0f,
             0.389241f,  0.728442f,  0.563794f,  3.0f,
             0.0f,       0.0f,       0.0f,       1.0f);

    REQUIRE(persp._view_to_world == vtw);
}


TEST_CASE("Perspective camera gives correct World-to-View matrix",
          "[cameras][matrices]") {
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
    Mat4 persp_screen(640.0f,  0.0f,   0.0f, 640.0f,
                      0.0f,   -360.0f, 0.0f, 360.0f,
                      0.0f,    0.0f,   0.5f, 0.5f,
                      0.0f,    0.0f,   0.0f, 1.0f);

    REQUIRE(persp._screen == persp_screen);
}

TEST_CASE("Perspective camera can transform points properly", "[cameras]") {
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
            Point4(654.924255f, 494.933349f, 0.995008f, 1.0f));
    REQUIRE(persp.persp_screen(p2) ==
            Point4(577.8112f, 479.142f, 0.994987f, 1.0f));
    REQUIRE(persp.persp_screen(p3) ==
            Point4(678.474853f, 409.025024f, 0.995014f, 1.0f));
}

TEST_CASE("Perspective camera can pick points in space", "[cameras]") {
    Point4 screen_near(383, 5, 0, 1);
    Point4 screen_far (383, 5, 1, 1);

    std::cout << "Screen\n"          << persp._screen               << "\n"
              << "Inverted Screen\n" << persp._screen.inverted()    << "\n\n"
              << "NDC\n"             << persp._persp_ndc            << "\n"
              << "Inverted NDC\n"    << persp._persp_ndc.inverted() << "\n\n"
              << "View\n"            << persp._world_to_view        << "\n"
              << "Inverted View\n"   << persp._view_to_world        << "\n"
              << std::endl;

    Point4 ndc_near = persp._screen.inverted() * screen_near;
    Point4 ndc_far  = persp._screen.inverted() * screen_far;

    Point4 persp_near = persp._persp_ndc.inverted() * ndc_near;
    Point4 persp_far  = persp._persp_ndc.inverted() * ndc_far;
    
    Point4 cam_near = persp_near / persp_near._w;
    Point4 cam_far  = persp_far  / persp_far._w;

    Point4 world_near = persp._view_to_world * cam_near;
    Point4 world_far  = persp._view_to_world * cam_far;

    std::cout << "NDC\n"
              << "I near " << ndc_near << "\n"
              << "A near " << Point4(-0.401563f, 0.9861111f, -1.0f, 1.0f) << "\n"
              << "I far  " << ndc_far << "\n"
              << "A far  " << Point4(-0.401563f, 0.9861111f, 1.0f, 1.0f) << "\n"
              << std::endl;

    std::cout << "Perspective Homogeneous\n"
              << "I near " << persp_near << "\n"
              << "A near " << Point4(-0.295702f, 0.4084606f, -1.0f, 1.0f) << "\n"
              << "I far  " << persp_far << "\n"
              << "A far  " << Point4(-0.295702f, 0.4084606f, -1.0f, 0.000125f) << "\n"
              << std::endl;

    std::cout << "Camera\n"
              << "I near " << cam_near << "\n"
              << "A near " << Point4(5.831667f, 0.041653f, 2.624629, 1.0f) << "\n"
              << "I far  " << cam_far << "\n"
              << "A far  " << Point4(-0.167583, 1.0415277, -0.374996, 0.000125) << "\n"
              << std::endl;

    std::cout << "World\n"
              << "I near " << world_near << "\n"
              << "A near " << Point4(5.831667f, 0.041653f, 2.624629, 1.0f) << "\n"
              << "I far  " << world_far << "\n"
              << "A far  " << Point4(-1340.662f, 8332.2217f, -2999.972f, 1.0f) << "\n"
              << std::endl;
}

// TEST_CASE("Homework 5") {
//     Camera camera(Vec3(8, -5, -1), Vec3(-47, 439, -223), Vec3(0, 1, 0));
//     camera.set_ortho(-800, 800, 422, -422, 1, 5000, 2048, 1080, 1);

//     std::cout << "View-to-World:\n" << camera._view_to_world << "\n\n"
//               << "World-to-View:\n" << camera._world_to_view << "\n\n"
//               << "Orthographic:\n"  << camera._ortho_ndc     << "\n\n"
//               << "Viewport:\n"      << camera._screen        << "\n\n"
//               << std::endl;

//     Point4 p1(-1080, 3569, -1581, 1);
//     Point4 p2(-1010, 3605, -1527, 1);
//     Point4 p3(-993, 3594, -1552, 1);

//     std::cout << "p1 wtv:    " << camera.view(p1)         << "\n"
//               << "p1 ortho:  " << camera.ortho_ndc(p1)    << "\n"
//               << "p1 screen: " << camera.ortho_screen(p1) << "\n\n"

//               << "p2 wtv:    " << camera.view(p2)         << "\n"
//               << "p2 ortho:  " << camera.ortho_ndc(p2)    << "\n"
//               << "p2 screen: " << camera.ortho_screen(p2) << "\n\n"

//               << "p3 wtv:    " << camera.view(p3)         << "\n"
//               << "p3 ortho:  " << camera.ortho_ndc(p3)    << "\n"
//               << "p3 screen: " << camera.ortho_screen(p3) << "\n"
//               << std::endl;

//     Point4 screen_near(1269, 596, 0, 1);
//     Point4 screen_far (1269, 596, 1, 1);

//     std::cout << "ndc near: " << ortho._screen.inverted() * screen_near << "\n"
//               << "ndc far:  " << ortho._screen.inverted() * screen_far << "\n\n"
              
//               << "camera near: " << ortho._ortho_ndc.inverted() * ortho._screen.inverted() * screen_near << "\n"
//               << "camera far:  " << ortho._ortho_ndc.inverted() * ortho._screen.inverted() * screen_far << "\n\n"
              
//               << "world near: " << ortho._view_to_world * ortho._ortho_ndc.inverted() * ortho._screen.inverted() * screen_near << "\n"
//               << "world far:  " << ortho._view_to_world * ortho._ortho_ndc.inverted() * ortho._screen.inverted() * screen_far << "\n\n"
//               << std::endl;
// }