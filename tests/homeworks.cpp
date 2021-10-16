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
    k.normalize();
    Vec3 k_cross_v = k.cross(z_vec);
    float k_dot_v  = k.dot(z_vec);

    // apply Rodrigues
    Vec3 zrot = z_vec * cos_theta + k_cross_v * sin_theta +
                k * k_dot_v * (1 - cos_theta);

    REQUIRE(zrot == Vec3(-2.5723727, -3.2360680, 0.9543387));

    // back to the original rotation, but tipping the nose down with the
    // previously derived x-axis
    theta     = std::numbers::pi_v<float> / 4.0f;
    cos_theta = std::cos(theta);
    sin_theta = std::sin(theta);

    // gather some terms before diving in
    k = x_vec;
    k.normalize();
    k_cross_v = k.cross(z_vec);
    k_dot_v  = k.dot(z_vec);

    // apply Rodrigues
    Vec3 xrot = z_vec * cos_theta + k_cross_v * sin_theta +
                k * k_dot_v * (1 - cos_theta);

    REQUIRE(xrot == Vec3(1.2928932, -3.8284271, 1.2928932));
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
    player_gaze.normalize();
    Vec3 enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(6.5470018, 0.0f, 3.3205032));

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
    REQUIRE(enemy_pos == Vec3(10.9792681, 0.0f, -5.6435938));

    // again for enemy 3
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(5.4322653, 0.0f, -13.9640970));

    // enemy 4
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(-4.5470037, 0.0f, -13.3205032));

    // enemy 5
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(-8.9792690, 0.0f, -4.3564048));

    // last but not least, enemy 6
    player_gaze *= y_rot;
    enemy_pos = player_gaze * 10 + player_pos;
    REQUIRE(enemy_pos == Vec3(-3.4322643, 0.0f, 3.9640989));   
}

TEST_CASE("Triangular game object", "[vectors][matrices]") {
    Point4 p1(-1, 0, -1, 1);
    Point4 p2( 0, 0,  2, 1);
    Point4 p3( 1, 0, -1, 1);

    // Move forward by 7 followed by a rotation about the y axis of 1π/4
    Vec4 translation(0, 0, 7, 1);
    float theta = std::numbers::pi_v<float> / 4.0f;
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);
    Mat4 y_rot(cos_theta,  0.0f, sin_theta, 0.0f,
               0.0f,       1.0f,      0.0f, 0.0f,
               -sin_theta, 0.0f, cos_theta, 0.0f,
               0.0f,       0.0f,      0.0f, 1.0f);

    Mat4 transform = y_rot;
    transform.set_translate(translation);

    Point4 new_p1 = transform * p1;
    Point4 new_p2 = transform * p2;
    Point4 new_p3 = transform * p3;

    REQUIRE(new_p1 == Point4(-1.4142135f, 0.0f, 7.0f, 1.0f));
    REQUIRE(new_p2 == Point4(1.4142135f, 0.0f, 8.4142132f, 1.0f));
    REQUIRE(new_p3 == Point4(0.0f, 0.0f, 5.5857863f, 1.0f));

    // Move forward by 10 followed by a rotation about the y axis of 2π/4
    Vec4 prev_trans = translation;
    Mat4 prev_rot   = y_rot;

    translation = Vec4(0, 0, 10, 0);
    translation = prev_trans + (prev_rot * translation);

    theta = std::numbers::pi_v<float> / 2.0f;
    cos_theta = std::cos(theta);
    sin_theta = std::sin(theta);
    y_rot = Mat4(cos_theta,  0.0f, sin_theta, 0.0f,
                 0.0f,       1.0f,      0.0f, 0.0f,
                 -sin_theta, 0.0f, cos_theta, 0.0f,
                 0.0f,       0.0f,      0.0f, 1.0f);

    y_rot = prev_rot * y_rot;

    transform = y_rot;
    transform.set_translate(translation);

    new_p1 = transform * p1;
    new_p2 = transform * p2;
    new_p3 = transform * p3;

    REQUIRE(new_p1 == Vec4(7.0710678f, 0.0f, 15.4852810f, 1.0f));
    REQUIRE(new_p2 == Vec4(8.4852810f, 0.0f, 12.6568546f, 1.0f));
    REQUIRE(new_p3 == Vec4(5.6568542f, 0.0f, 14.0710678f, 1.0f));

    // Move forward by 7 followed by a rotation about the y axis of -2π/4
    prev_trans = translation;
    prev_rot   = y_rot;

    translation = Vec4(0, 0, 7, 0);
    translation = prev_trans + (prev_rot * translation);

    theta = std::numbers::pi_v<float> / -2.0f;
    cos_theta = std::cos(theta);
    sin_theta = std::sin(theta);
    y_rot = Mat4(cos_theta,  0.0f, sin_theta, 0.0f,
                 0.0f,       1.0f,      0.0f, 0.0f,
                 -sin_theta, 0.0f, cos_theta, 0.0f,
                 0.0f,       0.0f,      0.0f, 1.0f);

    y_rot = prev_rot * y_rot;
    transform = y_rot;
    transform.set_translate(translation);

    new_p1 = transform * p1;
    new_p2 = transform * p2;
    new_p3 = transform * p3;

    REQUIRE(new_p1 == Vec4(10.6066017f, 0.0f, 9.1213198f, 1.0f));
    REQUIRE(new_p2 == Vec4(13.4350281f, 0.0f, 10.5355330f, 1.0f));
    REQUIRE(new_p3 == Vec4(12.0208149f, 0.0f, 7.7071061f, 1.0f));

    // Move forward by 6 followed by a rotation about the y axis of -3π/4
    prev_trans = translation;
    prev_rot   = y_rot;

    translation = Vec4(0, 0, 6, 0);
    translation = prev_trans + (prev_rot * translation);

    theta = (-3 * std::numbers::pi_v<float>) / 4.0f;
    cos_theta = std::cos(theta);
    sin_theta = std::sin(theta);
    y_rot = Mat4(cos_theta,  0.0f, sin_theta, 0.0f,
                 0.0f,       1.0f,      0.0f, 0.0f,
                 -sin_theta, 0.0f, cos_theta, 0.0f,
                 0.0f,       0.0f,      0.0f, 1.0f);

    y_rot = prev_rot * y_rot;
    transform = y_rot;
    transform.set_translate(translation);

    new_p1 = transform * p1;
    new_p2 = transform * p2;
    new_p3 = transform * p3;

    REQUIRE(new_p1 == Vec4(17.2634544f, 0.0f, 12.3639603f, 1.0f));
    REQUIRE(new_p2 == Vec4(14.2634544f, 0.0f, 13.3639603f, 1.0f));
    REQUIRE(new_p3 == Vec4(17.2634544f, 0.0f, 14.3639603f, 1.0f));
}