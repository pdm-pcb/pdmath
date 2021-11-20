#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Matrix3.hpp"

#include "pdmath/Point4.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Matrix4.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

#include <numbers>
#include <cmath>

using namespace pdm;
using namespace Catch;

TEST_CASE("Spaceship 'forward' vector manipulation", "[vectors][matrices]") {
    Vec3 z_vec(-1, -4, -1);          // 'forward' vector
    Vec3 y_vec(-4, 2, -4);           // 'up' vector
    Vec3 x_vec = y_vec.cross(z_vec); // because j-hat cross k-hat is i-hat

    // now we need to rotate left about the 'up' axis by pi/5 radians
    float theta     = std::numbers::pi_v<float> / 5.0f;
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);

    // gather some terms before diving in
    Vec3 k = y_vec;
    k = k.normalized();
    Vec3 k_cross_v = k.cross(z_vec);
    float k_dot_v  = k.dot(z_vec);

    // apply Rodrigues
    Vec3 zrot = z_vec * cos_theta + k_cross_v * sin_theta +
                k * k_dot_v * (1 - cos_theta);

    REQUIRE(zrot == Vec3(-2.572372f, -3.236068f, 0.954338f));

    // back to the original rotation, but tipping the nose down with the
    // previously derived x-axis
    theta     = std::numbers::pi_v<float> / 4.0f;
    cos_theta = std::cos(theta);
    sin_theta = std::sin(theta);

    // gather some terms before diving in
    k = x_vec;
    k = k.normalized();
    k_cross_v = k.cross(z_vec);
    k_dot_v  = k.dot(z_vec);

    // apply Rodrigues
    Vec3 xrot = z_vec * cos_theta + k_cross_v * sin_theta +
                k * k_dot_v * (1 - cos_theta);

    REQUIRE(xrot == Vec3(1.292893f, -3.828427f, 1.292893f));
}

TEST_CASE("Distribute enemies about a player", "[vectors][matrices]") {
    // The player is at position (1, 0, -5) facing the point (3, 0, -2) and we
    // need to spawn in 6 enemies. Specifically, we want these enemies to appear
    // on the ground (y = 0) and evenly distributed around in a circle of radius
    // 10 centered on the player with the first enemy straight in front of the
    // player.
    
    // establish the player and their 'gaze'
    Point3 player_pos(1, 0, -5);
    Vec3 player_gaze(Point3(3, 0, -2) - player_pos);

    // normalize the vector, make it 10 units long, and translate it to the
    // player's location. this is the first enemy
    player_gaze = player_gaze.normalized();
    Vec3 enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(6.547001f, 0.0f, 3.320503f));

    // rotation terms: the full circle is 2pi, so we need 2pi/6 radians per
    // enemy, or just pi/3
    float theta     = std::numbers::pi_v<float> / 3.0f;
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);

    // trusty rotate-about-the-y-axis matrix
    Mat3 y_rot(cos_theta,  0.0f, sin_theta,
               0.0f,       1.0f,      0.0f,
               -sin_theta, 0.0f, cos_theta);

    // rotate the player gaze, then scale, then point it where it needs to be
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(10.979268f, 0.0f, -5.643593f));

    // again for enemy 3
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(5.432265f, 0.0f, -13.964097f));

    // enemy 4
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(-4.547003f, 0.0f, -13.320503f));

    // enemy 5
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(-8.979269f, 0.0f, -4.356404f));

    // last but not least, enemy 6
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(-3.432264f, 0.0f, 3.964098f));   
}

TEST_CASE("Triangular game object transformations", "[vectors][matrices]") {
    Point3 p1(-1.0f, 0.0f, -1.0f);
    Point3 p2( 0.0f, 0.0f,  2.0f);
    Point3 p3( 1.0f, 0.0f, -1.0f);

    // Move forward by 7 followed by a rotation about the y axis of 1π/4
    Vec3 translation(0.0f, 0.0f, 7.0f);
    float theta = std::numbers::pi_v<float> / 4.0f;
    Vec3 prev_translation;
    Mat3 prev_rotation;

    Point3 new_p1 = Mat4::transform(p1, translation, 1, theta, 1, Vec3::one,
                                    prev_translation, prev_rotation);
    Point3 new_p2 = Mat4::transform(p2, translation, 1, theta, 1, Vec3::one,
                                    prev_translation, prev_rotation);
    Point3 new_p3 = Mat4::transform(p3, translation, 1, theta, 1, Vec3::one,
                                    prev_translation, prev_rotation);

    REQUIRE(new_p1 == Point3(-1.414213f, 0.0f, 7.0f));
    REQUIRE(new_p2 == Point3(1.414213f, 0.0f, 8.414213f));
    REQUIRE(new_p3 == Point3(0.0f, 0.0f, 5.585786f));

    // Move forward by 10 followed by a rotation about the y axis of 2π/4
    translation = Vec3(0.0f, 0.0f, 10.0f);
    theta = std::numbers::pi_v<float> / 2.0f;

    new_p1 = Mat4::transform(p1, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);
    new_p2 = Mat4::transform(p2, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);
    new_p3 = Mat4::transform(p3, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);

    REQUIRE(new_p1 == Point3(7.071067f, 0.0f, 15.485281f));
    REQUIRE(new_p2 == Point3(8.485281f, 0.0f, 12.656854f));
    REQUIRE(new_p3 == Point3(5.656854f, 0.0f, 14.071067f));

    // Move forward by 7 followed by a rotation about the y axis of -2π/4
    translation = Vec3(0.0f, 0.0f, 7.0f);
    theta = std::numbers::pi_v<float> / -2.0f;


    new_p1 = Mat4::transform(p1, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);
    new_p2 = Mat4::transform(p2, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);
    new_p3 = Mat4::transform(p3, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);

    REQUIRE(new_p1 == Point3(10.606601f, 0.0f, 9.121319f));
    REQUIRE(new_p2 == Point3(13.435028f, 0.0f, 10.535533f));
    REQUIRE(new_p3 == Point3(12.020814f, 0.0f, 7.707106f));

    // Move forward by 6 followed by a rotation about the y axis of -3π/4
    translation = Vec3(0, 0, 6);
    theta = (-3 * std::numbers::pi_v<float>) / 4.0f;

    new_p1 = Mat4::transform(p1, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);
    new_p2 = Mat4::transform(p2, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);
    new_p3 = Mat4::transform(p3, translation, 1, theta, 1, Vec3::one,
                             prev_translation, prev_rotation);

    REQUIRE(new_p1 == Point3(17.263454f, 0.0f, 12.36396f));
    REQUIRE(new_p2 == Point3(14.263454f, 0.0f, 13.36396f));
    REQUIRE(new_p3 == Point3(17.263454f, 0.0f, 14.36396f));
}

TEST_CASE("Alternative TGO transformations", "[vectors][matrices]") {
    Point3 p1(-1.0f, 0.0f, -1.0f);
    Point3 p2( 0.0f, 0.0f,  2.0f);
    Point3 p3( 1.0f, 0.0f, -1.0f);

    // Move forward by 7 followed by a rotation about the y axis of 1π/4
    Mat4 prev_transform1 = Mat4::identity;
    Mat4 prev_transform2 = Mat4::identity;
    Mat4 prev_transform3 = Mat4::identity;
    
    Vec3 translation(0.0f, 0.0f, 7.0f);
    float theta = std::numbers::pi_v<float> / 4.0f;

    Point3 new_p1 = Mat4::transform(p1, translation, 1, theta, 1, Vec3::one,
                                    prev_transform1);
    Point3 new_p2 = Mat4::transform(p2, translation, 1, theta, 1, Vec3::one,
                                    prev_transform2);
    Point3 new_p3 = Mat4::transform(p3, translation, 1, theta, 1, Vec3::one,
                                    prev_transform3);

    REQUIRE(new_p1 == Point3(-1.414213f, 0.0f, 7.0f));
    REQUIRE(new_p2 == Point3(1.414213f, 0.0f, 8.414213f));
    REQUIRE(new_p3 == Point3(0.0f, 0.0f, 5.585786f));

    // Move forward by 10 followed by a rotation about the y axis of 2π/4
    translation = Vec3(0.0f, 0.0f, 10.0f);
    theta = std::numbers::pi_v<float> / 2.0f;

    new_p1 = Mat4::transform(p1, translation, 1, theta, 1, Vec3::one,
                             prev_transform1);
    new_p2 = Mat4::transform(p2, translation, 1, theta, 1, Vec3::one,
                             prev_transform2);
    new_p3 = Mat4::transform(p3, translation, 1, theta, 1, Vec3::one,
                             prev_transform3);

    REQUIRE(new_p1 == Point3(7.071067f, 0.0f, 15.485281f));
    REQUIRE(new_p2 == Point3(8.485281f, 0.0f, 12.656854f));
    REQUIRE(new_p3 == Point3(5.656854f, 0.0f, 14.071067f));

    // Move forward by 7 followed by a rotation about the y axis of -2π/4
    translation = Vec3(0.0f, 0.0f, 7.0f);
    theta = std::numbers::pi_v<float> / -2.0f;

    new_p1 = Mat4::transform(p1, translation, 1, theta, 1, Vec3::one,
                             prev_transform1);
    new_p2 = Mat4::transform(p2, translation, 1, theta, 1, Vec3::one,
                             prev_transform2);
    new_p3 = Mat4::transform(p3, translation, 1, theta, 1, Vec3::one,
                             prev_transform3);

    REQUIRE(new_p1 == Point3(10.606601f, 0.0f, 9.121319f));
    REQUIRE(new_p2 == Point3(13.435028f, 0.0f, 10.535533f));
    REQUIRE(new_p3 == Point3(12.020814f, 0.0f, 7.707106f));

    // Move forward by 6 followed by a rotation about the y axis of -3π/4
    translation = Vec3(0.0f, 0.0f, 6.0f);
    theta = (-3 * std::numbers::pi_v<float>) / 4.0f;

    new_p1 = Mat4::transform(p1, translation, 1, theta, 1, Vec3::one,
                             prev_transform1);
    new_p2 = Mat4::transform(p2, translation, 1, theta, 1, Vec3::one,
                             prev_transform2);
    new_p3 = Mat4::transform(p3, translation, 1, theta, 1, Vec3::one,
                             prev_transform3);

    REQUIRE(new_p1 == Point3(17.263454f, 0.0f, 12.36396f));
    REQUIRE(new_p2 == Point3(14.263454f, 0.0f, 13.36396f));
    REQUIRE(new_p3 == Point3(17.263454f, 0.0f, 14.36396f));
}

//TEST_CASE("TRS Deductions", "[matrices]") {
//    Mat4 w( 3.578f, -0.872f, 0.557f, -4.0f,
//            0.0f,    2.907f, 0.836f, -1.0f,
//           -1.789f, -1.744f, 1.114f,  1.0f,
//            0.0f,    0.0f,   0.0f,    1.0f);
//
//    REQUIRE(w.get_world_position() == Vec3(-4.0f, -1.0f, 1.0f));
//
//    // limitations of working with three decimal places above
//    REQUIRE(w.get_x_scale() == Catch::Approx(4.0f).margin(1.0e-3f));
//    REQUIRE(w.get_y_scale() == Catch::Approx(3.5f).margin(1.0e-3f));
//    REQUIRE(w.get_z_scale() == Catch::Approx(1.5f).margin(1.0e-3f));
//
//    REQUIRE(w.get_x_unit_vector() == Vec3(0.894427f, 0.0f, -0.4472136f));
//    REQUIRE(w.get_y_unit_vector() == Vec3(-0.249117f, 0.830484f, -0.498233f));
//    REQUIRE(w.get_z_unit_vector() == Vec3(0.371321f, 0.557315f, 0.742643f));
//
//    // further precision limitations
//    REQUIRE(w.determinant() == Catch::Approx(21.0f).margin(1.0e-2f));
//
//    Vec3 new_obj(-5.0f, 0.0f, -5.0f);
//    REQUIRE((w.inverted() * new_obj) == Vec3(0.447177f, 1.162852f, -2.847383f));
//
//    Mat4 new_obj_mat(1, 0, -3, -5,
//                     0, 1,  0,  0,
//                     0, 0, -1, -5,
//                     0, 0,  0,  1);
//
//    REQUIRE((w.inverted() * new_obj_mat) ==
//        Mat4( 0.223588f, 0.0f,      -0.558971f,  0.447177f,
//             -0.071203f, 0.237203f,  0.356018f,  1.162852f,
//              0.247594f, 0.371349f, -1.237974f, -2.847383f,
//              0.0f,      0.0f,       0.0f,       1.0f));
//}