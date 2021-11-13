#include "pdmath/Camera.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Point4.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

#include <numbers>
#include <cmath>

using namespace pdm;
using namespace Catch;

Camera ortho(Vec3(2.0f, -1.0f, -4.0f),      // position
             Vec3(-569.0f, 399.0f, -61.0f), // target
             Vec3(0.0f, 1.0f, 0.0f));       // up vector

Camera persp(Vec3(6.0f, -1.0f, 3.0f),       // position
             Vec3(187.0f, 633.0f, -449.0f), // target
             Vec3(0.0f, 1.0f, 0.0f));       // up vector

TEST_CASE("Orthographic camera gives correct View-to-World matrix",
          "[cameras][matrices]") {
    Mat4 vtw(0.099331f, 0.569014f,  0.816305f,  2.0f,
             0.0f,      0.820363f, -0.571843f, -1.0f,
            -0.995054f, 0.056801f,  0.081487f, -4.0f,
             0.0f,       0.0f,        0.0f,     1.0f);

    REQUIRE(ortho.view_to_world() == vtw);
}

TEST_CASE("Orthographic camera gives correct World-to-View matrix",
          "[cameras][matrices]") {
    Mat4 wtv(0.099331f,  0.000000f, -0.995054f, -4.178880f,
             0.569015f,  0.820363f,  0.056801f, -0.090459f,
             0.816305f, -0.571843f,  0.081487f, -1.878504f,
             0.0f,       0.0f,       0.0f,       1.0f);

    REQUIRE(ortho.world_to_view() == wtv);
}

TEST_CASE("Orthographic camera can set it's NDC projection matrix",
          "[cameras][matrices]") {
    ortho.set_ortho(-700, 700, 394, -394, 1, 7000, 1280, 720, 1);
    Mat4 ortho_ndc(0.001429f,    0.0f,          0.0f,       0.0f,
                   0.0f,         0.0025381f,    0.0f,       0.0f,
                   0.0f,         0.0f,         -0.000286f, -1.000286f,
                   0.0f,         0.0f,          0.0f,       1.0f);

    REQUIRE(ortho.ortho_ndc() == ortho_ndc);
}

TEST_CASE("Orthographic camera can set it's screen projection matrix",
          "[cameras][matrices]") {
    Mat4 ortho_screen(640.0f,  0.0f,   0.0f, 640.0f,
                      0.0f,   -360.0f, 0.0f, 360.0f,
                      0.0f,    0.0f,   0.5f, 0.5f,
                      0.0f,    0.0f,   0.0f, 1.0f);

    REQUIRE(ortho.screen() == ortho_screen);
}

TEST_CASE("Orthographic camera can transform points properly", "[cameras]") {
    Point4 p1(-4549.0f, 3260.0f, -259.0f);
    Point4 p2(-4500.0f, 3323.0f, -309.0f);
    Point4 p3(-4510.0f, 3305.0f, -332.0f);

    REQUIRE(ortho.view(p1) == Point4(-198.317306f, 71.132675f, -5600.567382f));
    REQUIRE(ortho.view(p2) == Point4(-143.697372f, 147.857040f, -5600.668457f));
    REQUIRE(ortho.view(p3) == Point4(-122.58858f, 128.12249f, -5600.595f));

    REQUIRE(ortho.ortho_ndc(p1) == Point4(-0.283310f, 0.180539f, 0.600105f));
    REQUIRE(ortho.ortho_ndc(p2) == Point4(-0.205282f, 0.375272f, 0.600134f));
    REQUIRE(ortho.ortho_ndc(p3) == Point4(-0.174006f, 0.320036f, 0.600061f));

    REQUIRE(ortho.ortho_screen(p1) == Point4(458.681335f, 295.005676f, 0.800052f));
    REQUIRE(ortho.ortho_screen(p2) == Point4(508.619567f, 224.902191f, 0.800066f));
    REQUIRE(ortho.ortho_screen(p3) == Point4(528.635925f, 244.787384f, 0.800030f));
}

TEST_CASE("Orthographic camera can pick points in space", "[cameras]") {
    Point4 screen_near(505.0f, 558.0f, 0.0f);
    Point4 screen_far (505.0f, 558.0f, 1.0f);

    REQUIRE((ortho.screen().inverted() * screen_near) == 
            Point4(-0.210937f, -0.55f, -1.0f));
    REQUIRE((ortho.screen().inverted() * screen_far) == 
            Point4(-0.210937f, -0.55f, 1.0f));

    REQUIRE((ortho.ortho_ndc().inverted() * ortho.screen().inverted() *
             screen_near) == 
            Point4(-147.65625f, -216.700012f, -1.0f));
    REQUIRE((ortho.ortho_ndc().inverted() * ortho.screen().inverted() *
             screen_far) == 
            Point4(-147.65625f, -216.7000122f, -7000.0f));

    REQUIRE((ortho.view_to_world() *
             ortho.ortho_ndc().inverted() *
             ortho.screen().inverted() *
             screen_near) == 
            Point4(-136.788665f, -178.200897f, 130.535522f));
    REQUIRE((ortho.view_to_world() *
             ortho.ortho_ndc().inverted() *
             ortho.screen().inverted() *
             screen_far) == 
            Point4(-5850.112793f, 3824.128418f, -439.796386f));
}

TEST_CASE("Perspective camera gives correct View-to-World matrix",
          "[cameras][matrices]") {
    Mat4 vtw(0.928335f, -0.294833f, -0.226423f,  6.0f,
             0.0f,       0.609082f, -0.793106f, -1.0f,
             0.371744f,  0.736268f,  0.565432f,  3.0f,
             0.0f,       0.0f,       0.0f,       1.0f);

    REQUIRE(persp.view_to_world() == vtw);
}


TEST_CASE("Perspective camera gives correct World-to-View matrix",
          "[cameras][matrices]") {
    Mat4 wtv(0.928335f, -0.0f,      0.371744f, -6.685243f,
            -0.294833f,  0.609082f, 0.736268f,  0.169275f,
            -0.226423f, -0.793106f, 0.565432f, -1.130865f,
             0.0f,       0.0f,      0.0f,       1.0f);
         

    REQUIRE(persp.world_to_view() == wtv);
}

TEST_CASE("Perspective camera can set it's NDC projection matrix",
          "[cameras][matrices]") {
    persp.set_persp(1.0f, 8000.0f, 1280.0f, 720.0f,
                    std::numbers::pi_v<float> / 4.0f, 1.0f);
    Mat4 persp_ndc(1.358f, 0.0f,      0.0f,      0.0f,
                   0.0f,   2.414214f, 0.0f,      0.0f,
                   0.0f,   0.0f,     -1.00025f, -2.00025f,
                   0.0f,   0.0f,     -1.0f,      0.0f);

    REQUIRE(persp.persp_ndc() == persp_ndc);
}

TEST_CASE("Perspective camera can set it's screen projection matrix",
          "[cameras][matrices]") {
    Mat4 persp_screen(640.0f,  0.0f,   0.0f, 640.0f,
                      0.0f,   -360.0f, 0.0f, 360.0f,
                      0.0f,    0.0f,   0.5f, 0.5f,
                      0.0f,    0.0f,   0.0f, 1.0f);

    REQUIRE(persp.screen() == persp_screen);
}

TEST_CASE("Perspective camera can transform points properly", "[cameras]") {
    Point4 p1(65.0f, 135.0f, -128.0f);
    Point4 p2(45.0f, 137.0f, -132.0f);
    Point4 p3(64.0f, 147.0f, -112.0f);

    REQUIRE(persp.view(p1) ==
            Point4(6.073198f, -31.011152f, -195.293151f));
    REQUIRE(persp.view(p2) ==
            Point4(-13.980478f, -26.841398f, -194.612640f));
    REQUIRE(persp.view(p3) ==
            Point4(11.092779f, -11.627027f, -195.537109f));

    REQUIRE(persp.persp_ndc(p1) ==
            Point4(0.042230f, -0.383359f, 0.990007f));
    REQUIRE(persp.persp_ndc(p2) ==
            Point4(-0.097554f, -0.332973f, 0.989971f));
    REQUIRE(persp.persp_ndc(p3) ==
            Point4(0.077038f, -0.143554f, 0.990020f));

    REQUIRE(persp.persp_screen(p1) ==
            Point4(667.027648f, 498.009521f, 0.995003f));
    REQUIRE(persp.persp_screen(p2) ==
            Point4(577.564880f, 479.870483f, 0.994985f));
    REQUIRE(persp.persp_screen(p3) ==
            Point4(689.304809f, 411.6794128f, 0.995010f));
}

TEST_CASE("Perspective camera can pick points in space", "[cameras]") {
    Point4 screen_near(383.0f, 5.0f, 0.0f);
    Point4 screen_far (383.0f, 5.0f, 1.0f);

    Point4 ndc_near = persp.screen().inverted() * screen_near;
    Point4 ndc_far  = persp.screen().inverted() * screen_far;

    Point4 persp_near = persp.persp_ndc().inverted() * ndc_near;
    Point4 persp_far  = persp.persp_ndc().inverted() * ndc_far;
    
    Point4 cam_near = persp.view_to_world() * persp_near;
    Point4 cam_far  = persp.view_to_world() * persp_far;

    Point4 world_near = cam_near / cam_near._w;
    Point4 world_far  = cam_far  / cam_far._w;

    REQUIRE(ndc_near   == Point4(-0.401563f, 0.9861111f, -1.0f));
    REQUIRE(ndc_far    == Point4(-0.401563f, 0.9861111f,  1.0f));
    REQUIRE(persp_near == Point4(-0.295702f, 0.4084606f, -1.0f));
    REQUIRE(persp_far  == Point4(-0.295702f, 0.4084606f, -1.0f, 0.000125f));
    REQUIRE(cam_near   == Point4( 5.831484f, 0.041893f,   2.625378f));
    REQUIRE(cam_far    == Point4(-0.167765f, 1.041768f, -0.374246f, 0.000125f));
    REQUIRE(world_near == Point4( 5.831484f, 0.041893f,   2.625378f));
    REQUIRE(world_far  == Point4(-1342.543457f, 8336.737304f, -2994.905029f));
}

TEST_CASE("World space face culling", "[cameras]") {
    Point4 p1( 0.0f, 1.0f,  0.0f);
    Point4 p2( 0.0f, 0.0f,  2.0f);
    Point4 p3(-1.0f, 0.0f, -1.0f);
    Point4 p4( 1.0f, 0.0f, -1.0f);

    Mat4 tgo_w( 0.706124f, 0.120803f, 0.697708f,  2.0f,
               -0.6819f,   0.381532f, 0.624061f, -4.0f,
               -0.19081f, -0.91643f,  0.351784f,  4.0f,
                0.0f,      0.0f,      0.0f,      1.0f);

    Camera tgo_cam(Vec3(-5.0f, -4.0f, -2.0f),
                   Vec3(2.0f, -4.0f, 4.0f),
                   Vec3(0.0f, 1.0f, 0.0f));

    tgo_cam.set_persp(1.0f, 1000.0f, 1280.0f, 720.0f,
                      std::numbers::pi_v<float> / 3.0f, 1.0f);

    Mat4 vtw(-0.650791f, 0.0f, -0.759256f, -5.0f,
              0.0f,      1.0f,  0.0f,      -4.0f,
              0.759256f, 0.0f, -0.650791f, -2.0f,
              0.0f,      0.0f,  0.0f,       1.0f);

    Mat4 wtv(-0.650791f, 0.0f,  0.759256f, -1.735443f,
              0.0f,      1.0f,  0.0f,       4.0f,
             -0.759256f, 0.0f, -0.650791f, -5.097865f,
              0.0f,      0.0f,  0.0f,       1.0f);

    Mat4 proj(0.974278f, 0.0f,       0.0f,       0.0f,
              0.0f,      1.73205f,   0.0f,       0.0f,
              0.0f,      0.0f,      -1.002002f, -2.002002f,
              0.0f,      0.0f,      -1.0f,       0.0f);

    REQUIRE(tgo_cam.view_to_world() == vtw);
    REQUIRE(tgo_cam.world_to_view() == wtv);
    REQUIRE(tgo_cam.persp_ndc()     == proj);

    Point4 p1_prime(2.120803f, -3.61847f, 3.083572f);
    Point4 p2_prime(3.395416f, -2.75188f, 4.703567f);
    Point4 p3_prime(0.596169f, -3.94217f, 3.839025f);
    Point4 p4_prime(2.008416f, -5.30596f, 3.457407f);

    REQUIRE(tgo_cam.persp_ndc(p1) == p1_prime);
    REQUIRE(tgo_cam.persp_ndc(p2) == p2_prime);
    REQUIRE(tgo_cam.persp_ndc(p3) == p3_prime);
    REQUIRE(tgo_cam.persp_ndc(p4) == p4_prime);

    Vec3 r_normal = tgo_cam.face_normal(static_cast<Point3>(p1_prime),
                                        static_cast<Point3>(p2_prime),
                                        static_cast<Point3>(p4_prime));
    Vec3 g_normal = tgo_cam.face_normal(static_cast<Point3>(p1_prime),
                                        static_cast<Point3>(p4_prime),
                                        static_cast<Point3>(p3_prime));
    Vec3 b_normal = tgo_cam.face_normal(static_cast<Point3>(p1_prime),
                                        static_cast<Point3>(p3_prime),
                                        static_cast<Point3>(p2_prime));
    Vec3 w_normal = tgo_cam.face_normal(static_cast<Point3>(p2_prime),
                                        static_cast<Point3>(p3_prime),
                                        static_cast<Point3>(p4_prime));

    REQUIRE(r_normal == Vec3( 3.057687f, -0.658561f, -2.053503f));
    REQUIRE(g_normal == Vec3(-1.153809f, -0.485058f, -2.536425f));
    REQUIRE(b_normal == Vec3(-1.17906f,   3.432811f, -0.90865f));
    REQUIRE(w_normal == Vec3(-0.72482f,  -2.28919f,   5.498568f));

    Vec3 camera_to_p1 = tgo_cam.direction_to_point(p1_prime);
    Vec3 camera_to_p2 = tgo_cam.direction_to_point(p2_prime);

    REQUIRE(camera_to_p1 == Vec3(7.120802f, 0.38153f, 5.083571f));
    REQUIRE(camera_to_p2 == Vec3(8.39542f, 1.248122f, 6.703567f));

    REQUIRE(camera_to_p1.dot(r_normal) == Catch::Approx( 11.0828f));
    REQUIRE(camera_to_p1.dot(g_normal) == Catch::Approx(-21.2952f));
    REQUIRE(camera_to_p1.dot(b_normal) == Catch::Approx(-11.7053f));
    REQUIRE(camera_to_p2.dot(w_normal) == Catch::Approx( 27.91767f));
}