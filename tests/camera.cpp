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
    Point4 p1(-4549.0f, 3260.0f, -259.0f, 1.0f);
    Point4 p2(-4500.0f, 3323.0f, -309.0f, 1.0f);
    Point4 p3(-4510.0f, 3305.0f, -332.0f, 1.0f);

    REQUIRE(ortho.view(p1) ==
            Point4(-198.317306f, 71.132675f, -5600.567382f, 1.0f));
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
            Point4(458.681304f, 295.005981f, 0.800052f, 1.0f));
    REQUIRE(ortho.ortho_screen(p2) ==
            Point4(508.619537f, 224.902267f, 0.800067f, 1.0f));
    REQUIRE(ortho.ortho_screen(p3) ==
            Point4(528.635986f, 244.787368f, 0.800030f, 1.0f));
}

TEST_CASE("Orthographic camera can pick points in space", "[cameras]") {
    Point4 screen_near(505, 558, 0, 1);
    Point4 screen_far (505, 558, 1, 1);

    REQUIRE((ortho.screen().inverted() * screen_near) == 
            Point4(-0.210937f, -0.55f, -1.0f, 1.0f));
    REQUIRE((ortho.screen().inverted() * screen_far) == 
            Point4(-0.210937f, -0.55f, 1.0f, 1.0f));

    REQUIRE((ortho.ortho_ndc().inverted() * ortho.screen().inverted() *
             screen_near) == 
            Point4(-147.65625f, -216.700012f, -1.0f, 1.0f));
    REQUIRE((ortho.ortho_ndc().inverted() * ortho.screen().inverted() *
             screen_far) == 
            Point4(-147.65625f, -216.7000122f, -7000.0f, 1.0f));

    REQUIRE((ortho.view_to_world() *
             ortho.ortho_ndc().inverted() *
             ortho.screen().inverted() *
             screen_near) == 
            Point4(-136.788665f, -178.200897f, 130.535522f, 1.0f));
    REQUIRE((ortho.view_to_world() *
             ortho.ortho_ndc().inverted() *
             ortho.screen().inverted() *
             screen_far) == 
            Point4(-5850.112793f, 3824.128418f, -439.796386f, 1.0f));
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

    REQUIRE(persp.view_to_world() == vtw);
}


TEST_CASE("Perspective camera gives correct World-to-View matrix",
          "[cameras][matrices]") {
    Mat4 wtv(0.921136f, -0.0f,      0.389241f, -6.694539f,
            -0.307815f,  0.612063f, 0.728442f,  0.273628f,
            -0.238240f, -0.790808f, 0.563794f, -1.052748f,
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
    Point4 p1(65.0f, 135.0f, -128.0f, 1.0f);
    Point4 p2(45.0f, 137.0f, -132.0f, 1.0f);
    Point4 p3(64.0f, 147.0f, -112.0f, 1.0f);

    REQUIRE(persp.view(p1) ==
            Point4(3.356436f, -30.346324f, -195.46315f, 1.0f));
    REQUIRE(persp.view(p2) ==
            Point4(-16.623247f, -25.879653f, -194.535141f, 1.0f));
    REQUIRE(persp.view(p3) ==
            Point4(8.66316f, -11.038673f, -195.693908f, 1.0f));

    REQUIRE(persp.persp_ndc(p1) ==
            Point4(0.023319f, -0.374814f, 0.990016f, 1.0f));
    REQUIRE(persp.persp_ndc(p2) ==
            Point4(-0.116042f, -0.32117f, 0.989967f, 1.0f));
    REQUIRE(persp.persp_ndc(p3) ==
            Point4(0.060117f, -0.13618f, 0.990028f, 1.0f));

    REQUIRE(persp.persp_screen(p1) ==
            Point4(654.924255f, 494.93338f, 0.995008f, 1.0f));
    REQUIRE(persp.persp_screen(p2) ==
            Point4(577.8112f, 479.142f, 0.994987f, 1.0f));
    REQUIRE(persp.persp_screen(p3) ==
            Point4(678.474853f, 409.025024f, 0.995014f, 1.0f));
}

TEST_CASE("Perspective camera can pick points in space", "[cameras]") {
    Point4 screen_near(383, 5, 0, 1);
    Point4 screen_far (383, 5, 1, 1);

    Point4 ndc_near = persp.screen().inverted() * screen_near;
    Point4 ndc_far  = persp.screen().inverted() * screen_far;

    Point4 persp_near = persp.persp_ndc().inverted() * ndc_near;
    Point4 persp_far  = persp.persp_ndc().inverted() * ndc_far;
    
    Point4 cam_near = persp.view_to_world() * persp_near;
    Point4 cam_far  = persp.view_to_world() * persp_far;

    Point4 world_near = cam_near / cam_near._w;
    Point4 world_far  = cam_far  / cam_far._w;

    REQUIRE(ndc_near   == Point4(-0.401563f, 0.9861111f, -1.0f,      1.0f));
    REQUIRE(ndc_far    == Point4(-0.401563f, 0.9861111f,  1.0f,      1.0f));
    REQUIRE(persp_near == Point4(-0.295702f, 0.4084606f, -1.0f,      1.0f));
    REQUIRE(persp_far  == Point4(-0.295702f, 0.4084606f, -1.0f,      0.000125f));
    REQUIRE(cam_near   == Point4( 5.840127f, 0.040812f,   2.618646f, 1.0f));
    REQUIRE(cam_far    == Point4(-0.159122f, 1.040687f,  -0.380978f, 0.000125f));
    REQUIRE(world_near == Point4( 5.840127f, 0.040812f,   2.618646f, 1.0f));
    REQUIRE(world_far  == Point4(-1273.375f, 8328.088867f, -3048.777832f, 1.0f));
}

TEST_CASE("World space face culling", "[cameras]") {
    Point4 p1(0, 1, 0, 1);
    Point4 p2(0, 0, 2, 1);
    Point4 p3(-1, 0, -1, 1);
    Point4 p4(1, 0, -1, 1);

    Mat4 tgo_w( 0.706124f, 0.120803f, 0.697708f,  2.0f,
               -0.6819f,   0.381532f, 0.624061f, -4.0f,
               -0.19081f, -0.91643f,  0.351784f,  4.0f,
                0.0f,      0.0f,      0.0f,      1.0f);

    Camera tgo_cam(Vec3(-5, -4, -2), Vec3(2, -4, 4), Vec3(0, 1, 0));
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

    Point4 p1_prime(2.120803f, -3.61847f, 3.083572f, 1.0f);
    Point4 p2_prime(3.395416f, -2.75188f, 4.703567f, 1.0f);
    Point4 p3_prime(0.596169f, -3.94217f, 3.839025f, 1.0f);
    Point4 p4_prime(2.008416f, -5.30596f, 3.457407f, 1.0f);

    REQUIRE(tgo_cam.persp_ndc(p1) == p1_prime);
    REQUIRE(tgo_cam.persp_ndc(p2) == p2_prime);
    REQUIRE(tgo_cam.persp_ndc(p3) == p3_prime);
    REQUIRE(tgo_cam.persp_ndc(p4) == p4_prime);

    Vec4 r_normal = tgo_cam.face_normal(p1_prime, p2_prime, p4_prime);
    Vec4 g_normal = tgo_cam.face_normal(p1_prime, p4_prime, p3_prime);
    Vec4 b_normal = tgo_cam.face_normal(p1_prime, p3_prime, p2_prime);
    Vec4 w_normal = tgo_cam.face_normal(p2_prime, p3_prime, p4_prime);

    REQUIRE(r_normal == Vec4( 3.057687f, -0.658561f, -2.053503f,   1.0f));
    REQUIRE(g_normal == Vec4(-1.153809f, -0.485058f, -2.536425f,  1.0f));
    REQUIRE(b_normal == Vec4(-1.17906f,   3.432811f, -0.90865f,  1.0f));
    REQUIRE(w_normal == Vec4(-0.72482f,  -2.28919f,   5.498568f, 1.0f));

    Vec4 camera_to_p1 = tgo_cam.direction_to_point(p1_prime);
    Vec4 camera_to_p2 = tgo_cam.direction_to_point(p2_prime);

    REQUIRE(camera_to_p1 == Vec4(7.120802f, 0.38153f, 5.083571f, 1.0f));
    REQUIRE(camera_to_p2 == Vec4(8.39542f, 1.248122f, 6.703567f, 1.0f));

    REQUIRE(camera_to_p1.dot(r_normal) == Catch::Approx( 12.0828f));
    REQUIRE(camera_to_p1.dot(g_normal) == Catch::Approx(-20.2952f));
    REQUIRE(camera_to_p1.dot(b_normal) == Catch::Approx(-10.7053f));
    REQUIRE(camera_to_p2.dot(w_normal) == Catch::Approx( 28.9177f));
}

// TEST_CASE("Lol") {
//     // Homework
//     Mat4 W1(0.2846,  0.0744, -0.059,   0,
//             0,       0.1861,  0.2353, -5,
//             0.0949, -0.223,   0.1765,  4,
//             0,       0,       0,       1);

//     Point4 W1_min(-4.50, -3.75, -3.75, 1.0);
//     Point4 W1_max(5.50, 4.25, 4.25, 1.0);

//     Vec4 W1_fwd(0.2846, 0, 0.0949, 0);

//     Mat4 W2(0.6247,  0.2328, -0.745,  -1,
//             0,       0.9545,  0.2981, -11,
//             0.7809, -0.186,   0.5963,  9,
//             0,       0,       0,       1);

//     Point4 W2_min(-2.75, -5.00, -3.50, 1.0);
//     Point4 W2_max(3.25, 5.00, 4.50, 1.0);

//     Vec4 W2_fwd(-0.745, 0.2981, 0.5963, 0);

//     // Practice
//     // Mat4 W1(0.3, 0,       0,      4,
//     //         0,   0.2846, -0.095, -3,
//     //         0,   0.0949,  0.2846, 3,
//     //         0,   0,       0,      1);

//     // Point4 W1_min(-4.50, -4.50, -5.00, 1.0);
//     // Point4 W1_max(5.50, 5.50, 5.00, 1.0);

//     // Vec4 W1_fwd(0, -0.095, 0.2846, 0);

//     // Mat4 W2(0.2425,  0.2287, -0.943,  6,
//     //         0,       0.9718,  0.2357, 4,
//     //         0.9701, -0.057,   0.2357, 8,
//     //         0,       0,       0,      1);

//     // Point4 W2_min(-4.00, -4.75, -4.50, 1.0);
//     // Point4 W2_max(4.00, 5.25, 5.50, 1.0);

//     // Vec4 W2_fwd(-0.943, 0.2357, 0.2357, 0);

//     Vec4 cross_fwd(Vec3(W1_fwd._x, W1_fwd._y, W1_fwd._z).cross(
//                         Vec3(W2_fwd._x, W2_fwd._y, W2_fwd._z)), 0);

//     std::cout << "W1_fwd    : " << W1_fwd << " / "    << W1_fwd.length()    << "\n"
//               << "W2_fwd    : " << W2_fwd << " / "    << W2_fwd.length()    << "\n"
//               << "cross_fwd : " << cross_fwd << " / " << cross_fwd.length() << "\n"
//               << std::endl;

//     Point4 W1_C((W1_max._x - W1_min._x)/2,
//                 (W1_max._y - W1_min._y)/2,
//                 (W1_max._z - W1_min._z)/2, 1);

//     Point4 W2_C((W2_max._x - W2_min._x)/2,
//                 (W2_max._y - W2_min._y)/2,
//                 (W2_max._z - W2_min._z)/2, 1);

//     std::cout << "W1_C      : " << W1_C << "\n"
//               << "W2_C      : " << W2_C << "\n\n"
//               << "W1inv:\n"  << W1.inverted() << "\n"
//               << "W2inv:\n"  << W2.inverted() << "\n\n"
//               << std::endl;

//     Vec4 W1_fwd_local    = W1.inverted() * W1_fwd;
//     Vec4 W2_fwd_local    = W1.inverted() * W2_fwd;
//     Vec4 cross_fwd_local = W1.inverted() * cross_fwd;
    
//     std::cout << "W1_fwd local    W1 : " << W1_fwd_local    << "\n"
//               << "W2_fwd local    W1 : " << W2_fwd_local    << "\n"
//               << "cross_fwd local W1 : " << cross_fwd_local << "\n"
//               << std::endl;

//     float W1_proj = ((std::abs(W1_fwd_local._x * W1_C._x)) +
//                      (std::abs(W1_fwd_local._y * W1_C._y)) +
//                      (std::abs(W1_fwd_local._z * W1_C._z))) / W1_fwd.length();

//     std::cout << "W1_proj max    : " << W1_proj << "\n"
//               << "W1 scale       : " << std::pow(W1.get_x_scale(), 2)
//               << std::endl;

//     W1_proj *= std::pow(W1.get_x_scale(), 2);

//     float W1_rho1 = W1_proj;

//     std::cout << "W1_proj scaled : " << W1_proj << std::endl;

//     float W2_proj = ((std::abs(W2_fwd_local._x * W1_C._x)) +
//                      (std::abs(W2_fwd_local._y * W1_C._y)) +
//                      (std::abs(W2_fwd_local._z * W1_C._z))) / W2_fwd.length();

//     std::cout << "W2_proj max    : " << W2_proj << std::endl;

//     W2_proj *= std::pow(W1.get_x_scale(), 2);

//     float W2_rho1 = W2_proj;

//     std::cout << "W2_proj scaled : " << W2_proj << std::endl;

//     float cross_proj = ((std::abs(cross_fwd_local._x * W1_C._x)) +
//                         (std::abs(cross_fwd_local._y * W1_C._y)) +
//                         (std::abs(cross_fwd_local._z * W1_C._z))) / cross_fwd.length();

//     std::cout << "cross_proj max    : " << cross_proj << std::endl;

//     cross_proj *= std::pow(W1.get_x_scale(), 2);

//     float cross_rho1 = cross_proj;

//     std::cout << "cross_proj scaled : " << cross_proj << "\n" << std::endl;



//     W1_fwd_local    = W2.inverted() * W1_fwd;
//     W2_fwd_local    = W2.inverted() * W2_fwd;
//     cross_fwd_local = W2.inverted() * cross_fwd;
    
//     std::cout << "W1_fwd local    W2 : " << W1_fwd_local    << "\n"
//               << "W2_fwd local    W2 : " << W2_fwd_local    << "\n"
//               << "cross_fwd local W2 : " << cross_fwd_local << "\n"
//               << std::endl;

//     W1_proj = ((std::abs(W1_fwd_local._x * W2_C._x)) +
//                (std::abs(W1_fwd_local._y * W2_C._y)) +
//                (std::abs(W1_fwd_local._z * W2_C._z))) / W1_fwd.length();

//     std::cout << "W1_proj max    : " << W1_proj << "\n"
//               << "W2 scale       : " << std::pow(W2.get_x_scale(), 2)
//               << std::endl;

//     W1_proj *= std::pow(W2.get_x_scale(), 2);

//     float W1_rho_sum = W1_rho1 + W1_proj;

//     std::cout << "W1_proj scaled : " << W1_proj << std::endl;

//     W2_proj = ((std::abs(W2_fwd_local._x * W2_C._x)) +
//                (std::abs(W2_fwd_local._y * W2_C._y)) +
//                (std::abs(W2_fwd_local._z * W2_C._z))) / W2_fwd.length();

//     std::cout << "W2_proj max    : " << W2_proj << std::endl;

//     W2_proj *= std::pow(W2.get_x_scale(), 2);
//     float W2_rho_sum = W2_rho1 + W2_proj;

//     std::cout << "W2_proj scaled : " << W2_proj << std::endl;

//     cross_proj = ((std::abs(cross_fwd_local._x * W2_C._x)) +
//                   (std::abs(cross_fwd_local._y * W2_C._y)) +
//                   (std::abs(cross_fwd_local._z * W2_C._z))) / cross_fwd.length();

//     std::cout << "cross_proj max    : " << cross_proj << std::endl;

//     cross_proj *= std::pow(W2.get_x_scale(), 2);

//     float cross_rho_sum = cross_rho1 + cross_proj;

//     std::cout << "cross_proj scaled : " << cross_proj << "\n" << std::endl;

//     std::cout << "W1 rho sum    : " << W1_rho_sum << "\n"
//               << "W2 rho sum    : " << W2_rho_sum << "\n"
//               << "cross rho sum : " << cross_rho_sum << "\n"
//               << std::endl;

//     W1_min *= W1;
//     W1_max *= W1;

//     W2_min *= W2;
//     W2_max *= W2;

//     Point4 W1_Clocal((W1_min._x + W1_max._x)/2,
//                      (W1_min._y + W1_max._y)/2,
//                      (W1_min._z + W1_max._z)/2, 1);

//     Point4 W2_Clocal((W2_min._x + W2_max._x)/2,
//                      (W2_min._y + W2_max._y)/2,
//                      (W2_min._z + W2_max._z)/2, 1);

//     Vec4 Cavg     = static_cast<Vec4>(W2_Clocal) - W1_Clocal;
//     float W1_D    = std::abs(Cavg.dot(W1_fwd))    / W1_fwd.length();
//     float W2_D    = std::abs(Cavg.dot(W2_fwd))    / W2_fwd.length();
//     float cross_D = std::abs(Cavg.dot(cross_fwd)) / cross_fwd.length();

//     std::cout << "W1_min local : " << W1_min << "\n"
//               << "W1_max local : " << W1_max << "\n"
//               << "W2_min local : " << W2_min << "\n"
//               << "W2_max local : " << W2_max << "\n\n"
//               << "W1_Clocal    : " << W1_Clocal << "\n"
//               << "W2_Clocal    : " << W2_Clocal << "\n\n"
//               << "Cavg         : " << Cavg << "\n"
//               << "W1_D         : " << W1_D << "\n"
//               << "W2_D         : " << W2_D << "\n"
//               << "cross_D      : " << cross_D << "\n"
//               << std::endl;
// }