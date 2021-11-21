#include "pdmath/BSphere.hpp"
#include "pdmath/AABBox.hpp"
#include "pdmath/OBBox.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Point3.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"

#include "pdmath/util.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Line - line collision", "[lines][collisions]") {
    Line line1(Point3(4.0f, 2.0f, 4.0f), Vec3(5.0f, 2.0f, 3.0f));
    Line line2(Point3(-6.0f, -2.0f, -2.0f), Vec3(10.0f, 4.0f, 6.0f));

    float a = line1.vec().dot(line1.vec());
    float b = line1.vec().dot(line2.vec());
    float c = line2.vec().dot(line2.vec());
    float d = (line1.point_a() - line2.point_a()).dot(line1.vec());
    float e = (line1.point_a() - line2.point_a()).dot(line2.vec());

    REQUIRE(a == 38.0f);
    REQUIRE(b == 76.0f);
    REQUIRE(c == 152.0f);
    REQUIRE(d == 76.0f);
    REQUIRE(e == 152.0f);

    REQUIRE(line1.parallel_to(line2));
    REQUIRE(line2.parallel_to(line1));
    REQUIRE(line1.collides(line2) == true);
    REQUIRE(line2.collides(line1) == true);

    line1 = Line(Point3(-4.0f, 5.0f, 1.0f), Vec3(2.0f, -4.0f, -3.0f));
    line2 = Line(Point3(4.0f, 0.0f, 1.0f), Vec3(2.0f, -4.0f, -3.0f));

    a = line1.vec().dot(line1.vec());
    b = line1.vec().dot(line2.vec());
    c = line2.vec().dot(line2.vec());
    d = (line1.point_a() - line2.point_a()).dot(line1.vec());
    e = (line1.point_a() - line2.point_a()).dot(line2.vec());

    REQUIRE(a == 29.0f);
    REQUIRE(b == 29.0f);
    REQUIRE(c == 29.0f);
    REQUIRE(d == -36.0f);
    REQUIRE(e == -36.0f);

    REQUIRE(line1.parallel_to(line2));
    REQUIRE(line2.parallel_to(line1));
    REQUIRE(line1.collides(line2) == false);
    REQUIRE(line2.collides(line1) == false);

    line1 = Line(Point3(0.0f, -2.0f, 3.0f), Vec3(5.0f, 0.0f, 5.0f));
    line2 = Line(Point3(2.0f, -2.0f, 5.0f), Vec3(0.0f, 5.0f, -1.0f));

    a = line1.vec().dot(line1.vec());
    b = line1.vec().dot(line2.vec());
    c = line2.vec().dot(line2.vec());
    d = (line1.point_a() - line2.point_a()).dot(line1.vec());
    e = (line1.point_a() - line2.point_a()).dot(line2.vec());

    REQUIRE(a == 50.0f);
    REQUIRE(b == -5.0f);
    REQUIRE(c == 26.0f);
    REQUIRE(d == -20.0f);
    REQUIRE(e == 2.0f);

    REQUIRE(line1.parallel_to(line2) == false);
    REQUIRE(line2.parallel_to(line1) == false);
    REQUIRE(line1.collides(line2) == true);
    REQUIRE(line2.collides(line1) == true);
}

TEST_CASE("Line - plane" "[lines][planes][collisions]") {
    Plane plane(Point3(-6.0f, -15.0f, -6.0f), Vec3(-5.0f, -2.0f, -2.0f));

    Line line1(Point3(14.0f, -12.0f, -54.0f), Point3(13.0f, -8.0f, -56.0f));
    Line line2(Point3(11.0f, -8.0f, -56.0f), Point3(15.0f, -10.0f, -58.0f));

    REQUIRE(line1.collides(plane) == false);
    REQUIRE(line2.collides(plane) == true);

    REQUIRE(line1.collides_depth(plane) == 10.0f);
    REQUIRE(line2.collides_depth(plane) == Catch::Approx(0.0833333f));
}

TEST_CASE("Bounding sphere - bounding sphere collision",
          "[bounding spheres][collisions]") {
    BSphere sphere1(Point3(-0.2f, 0.8f, -0.6f), 6.0f,
                    Mat4(0.6708f, -0.3062f, -0.137f,  3.0f,
                         0.0f,     0.3062f, -0.685f, -5.0f,
                         0.3354f,  0.6124f,  0.2739f, 0.0f,
                         0.0f,     0.0f,     0.0f,    1.0f));

    BSphere sphere2(Point3(0.4f, -1.0f, -0.6f), 3.0f,
                    Mat4( 1.2203f, 1.4847f,  1.0707f, -1.0f,
                          0.0f,    1.2868f, -1.784f,  -9.0f,
                         -1.831f,  0.9898f,  0.7138f, -4.0f,
                          0.0f,    0.0f,     0.0f,     1.0f));

    Vec3 centers = sphere2.center_world() - sphere1.center_world();
    float scaled_radii_sum = sphere1.scaled_radius() + sphere2.scaled_radius();

    REQUIRE(sphere1.center_world() == Point3(2.70308f, -4.34404f, 0.2585f));
    REQUIRE(sphere2.center_world() == Point3(-2.639f, -9.2164f, -6.15048f));
    REQUIRE(centers == Vec3(-5.34208f, -4.87236f, -6.40898f));
    REQUIRE(centers.length() == Catch::Approx(9.66192f));

    REQUIRE(sphere1.scale() == Catch::Approx(0.74998f));
    REQUIRE(sphere2.scale() == Catch::Approx(2.20038f));
    REQUIRE(sphere1.scaled_radius() == Catch::Approx(4.49986f));
    REQUIRE(sphere2.scaled_radius() == Catch::Approx(6.60115f));

    REQUIRE(scaled_radii_sum == Catch::Approx(11.10102f));

    REQUIRE(sphere1.collides(sphere2) == true);
    REQUIRE(sphere2.collides(sphere1) == true);
        
    sphere1 = BSphere(Point3(0.6f, 0.6f, 0.6f), 2.0f,
                      Mat4(-0.402f,  0.6454f,  0.4811f, 1.0f,
                            0.0f,    0.5379f, -0.722f,  4.0f,
                           -0.805f, -0.323f,  -0.241f,  4.0f,
                            0.0f,    0.0f,     0.0f,    1.0f));

    sphere2 = BSphere(Point3(-0.2f, 0.8f, 0.6f), 5.0f,
                      Mat4(-0.257f, -0.05f,    0.146f,  4.0f,
                            0.0f,    0.2838f,  0.0973f, 2.0f,
                           -0.154f,  0.0835f, -0.243f,  8.0f,
                            0.0f,    0.0f,     0.0f,    1.0f));

    centers = sphere2.center_world() - sphere1.center_world();
    scaled_radii_sum = sphere1.scaled_radius() + sphere2.scaled_radius();

    REQUIRE(sphere1.center_world() == Point3(1.4347f, 3.88954f, 3.178599f));
    REQUIRE(sphere2.center_world() == Point3(4.099f, 2.28542f, 7.9518f));
    REQUIRE(centers == Vec3(2.6643f, -1.60412f, 4.7732f));
    REQUIRE(centers.length() == Catch::Approx(5.69694f));

    REQUIRE(sphere1.scale() == Catch::Approx(0.8997939f));
    REQUIRE(sphere2.scale() == Catch::Approx(0.2996081f));
    REQUIRE(sphere1.scaled_radius() == Catch::Approx(1.799587f));
    REQUIRE(sphere2.scaled_radius() == Catch::Approx(1.498040f));

    REQUIRE(scaled_radii_sum == Catch::Approx(3.29763f));

    REQUIRE(sphere1.collides(sphere2) == false);
    REQUIRE(sphere2.collides(sphere1) == false);
}

TEST_CASE("Bounding sphere - point collision",
          "[bounding spheres][points][collisions]") {
    BSphere sphere(Point3(-7.0f, 0.0f, 9.518f), 5.0f, Mat4::identity);
    Point3 point(6.0f, 0.0f, 10.0f);

    REQUIRE(sphere.collides(point) == false);

    sphere = BSphere(Point3(5.118f, 0.0f, -6.02f), 10.0f, Mat4::identity);
    point = Point3(10.0f, 0.0f, -4.0f);

    REQUIRE(sphere.collides(point) == true);
}

TEST_CASE("Bounding sphere - axis aligned bounding box collision",
          "[bounding spheres][axis aligned bounding boxes][collisions]") {
    BSphere sphere(Point3(43.0f, -60.0f, -3.0f), 4.0f, Mat4::identity);
    AABBox  box(Point3(45.0f, -60.0f, 0.0f),
                Point3(49.0f, -56.0f, 2.0f));

    Point3 C_clamped = sphere.center_clamped(box);
    Vec3   C_diff    = sphere.center_clamped(box) - sphere.center();

    REQUIRE(C_clamped == Point3(45.0f, -60.0f, 0.0f));
    REQUIRE(C_diff    == Vec3(2.0f, 0.0f, 3.0f));
    REQUIRE(C_diff.length() == Catch::Approx(3.60555f));

    REQUIRE(sphere.collides(box) == true);
    REQUIRE(box.collides(sphere) == true);

    
    sphere = BSphere(Point3(-102.0f, -22.0f, 62.0f), 3.0f, Mat4::identity);
    box    = AABBox(Point3(-100.0f, -20.0f, 60.0f),
                    Point3(-98.0f, -14.0f, 65.0f));

    C_clamped = sphere.center_clamped(box);
    C_diff    = sphere.center_clamped(box) - sphere.center();

    REQUIRE(C_clamped == Point3(-100.0f, -20.0f, 62.0f));
    REQUIRE(C_diff    == Vec3(2.0f, 2.0f, 0.0f));
    REQUIRE(C_diff.length() == Catch::Approx(2.82843f));

    REQUIRE(sphere.collides(box) == true);
    REQUIRE(box.collides(sphere) == true);
}

TEST_CASE("Bounding sphere - line collision",
          "[bounding spheres][lines][collisions]") {
    BSphere sphere(Point3(-7.0f, -11.0f, 10.0f), 2.0f, Mat4::identity);
    Line line(Point3(3.0f, 4.0f, 5.0f), Vec3(-1.0f, -1.0f, -5.0f));

    Vec3 c_minus_p = sphere.center_world() - line.point_a();
    float t = (line.vec().dot(c_minus_p)) / line.vec().dot(line.vec());
    Point3 q = line.point_a() + t * line.vec();
    Vec3 c_minus_q = sphere.center_world() - q;


    REQUIRE(c_minus_p == Vec3(-10.0f, -15.0f, 5.0f));
    REQUIRE(t == 0.0f);
    REQUIRE(q == Point3(3.0f, 4.0f, 5.0f));
    REQUIRE(c_minus_q == Vec3(-10.0f, -15.0f, 5.0f));

    REQUIRE(sphere.collides(line) == false);

    sphere = BSphere(Point3(-7.0f, 11.0f, -3.0f), 5.0f, Mat4::identity);
    line = Line(Point3(-3.0f, -4.0f, -5.0f), Vec3(0.0f, 1.0f, 0.0f));

    c_minus_p = sphere.center_world() - line.point_a();
    t = (line.vec().dot(c_minus_p)) / line.vec().dot(line.vec());
    q = line.point_a() + t * line.vec();
    c_minus_q = sphere.center_world() - q;


    REQUIRE(c_minus_p == Vec3(-4.0f, 15.0f, 2.0f));
    REQUIRE(t == 15.0f);
    REQUIRE(q == Point3(-3.0f, 11.0f, -5.0f));
    REQUIRE(c_minus_q == Vec3(-4.0f, 0.0f, 2.0f));

    REQUIRE(sphere.collides(line) == true);
}

TEST_CASE("Bounding sphere - plane collision"
          "[bounding spheres][planes][collisions") {
    Plane plane(Point3(6.0f, 6.0f, 12.0f), Vec3(2.0f, 1.0f, -3.0f));

    BSphere sphere1(Point3(-16.0f, -14.0f, 0.0f), 6.0f, Mat4::identity);
    BSphere sphere2(Point3(-8.0f, -10.0f, -12.0f), 8.0f, Mat4::identity);

    Vec3  c_minus_p = sphere1.center() - plane.point();
    float c_minus_p_dot_n = c_minus_p.dot(plane.normal());
    float d = std::abs(c_minus_p_dot_n / plane.normal().length());

    REQUIRE(c_minus_p == Vec3(-22.0f, -20.0f, -12.0f));
    REQUIRE(c_minus_p_dot_n == Catch::Approx(-28.0f));
    REQUIRE(d == Catch::Approx(7.48331f));
    REQUIRE(d > sphere1.scaled_radius());

    REQUIRE(sphere1.collides(plane) == false);
    REQUIRE(sphere1.above_plane(plane) == false);

    c_minus_p = sphere2.center() - plane.point();
    c_minus_p_dot_n = c_minus_p.dot(plane.normal());
    d = std::abs(c_minus_p_dot_n / plane.normal().length());

    REQUIRE(c_minus_p == Vec3(-14.0f, -16.0f, -24.0f));
    REQUIRE(c_minus_p_dot_n == Catch::Approx(28.0f));
    REQUIRE(d == Catch::Approx(7.48331f));
    REQUIRE(d < sphere2.scaled_radius());

    REQUIRE(sphere2.collides(plane) == true);
    REQUIRE(sphere2.above_plane(plane) == true);
}

TEST_CASE("Axis aligned bounding box - axis aligned bounding box collision",
          "[axis aligned bounding boxes][collisions]") {
    AABBox box1(Point3(-3.0f, -1.0f, 1.5f), Point3(3.0f, 1.0f, 6.5f));
    AABBox box2(Point3(2.5f, -1.0f, -3.0f), Point3(9.5f, 1.0f, 3.0f));

    REQUIRE(overlap(box1.x_interval(), box2.x_interval()) == true);
    REQUIRE(overlap(box1.y_interval(), box2.y_interval()) == true);
    REQUIRE(overlap(box1.z_interval(), box2.z_interval()) == true);

    REQUIRE(box1.collides(box2) == true);
    REQUIRE(box2.collides(box1) == true);

    box1 = AABBox(Point3(-1.0f, -1.0f, 4.0f), Point3(1.0f, 1.0f, 8.0f));
    box2 = AABBox(Point3(-5.5f, -1.0f, 1.5f), Point3(-2.5f, 1.0f, 2.5f));

    REQUIRE(overlap(box1.x_interval(), box2.x_interval()) == false);
    REQUIRE(overlap(box1.y_interval(), box2.y_interval()) == true);
    REQUIRE(overlap(box1.z_interval(), box2.z_interval()) == false);

    REQUIRE(box1.collides(box2) == false);
    REQUIRE(box2.collides(box1) == false);
}

TEST_CASE("Axis aligned bounding box - point collision",
          "[axis aligned bounding boxes][points][collisions]") {
    AABBox box(Point3(-2.5f, -1.0f, 0.5f), Point3(2.5f, 1.0f, 5.5f));
    Point3 point(7.0f, 2.0f, 5.0f);

    REQUIRE(box.collides(point) == false);

    box = AABBox(Point3(-8.5f, -1.0f, 1.5f),Point3(-1.5f, 1.0f, 4.5f));    
    point = Point3(-8.0f, 0.5f, 3.0f);

    REQUIRE(box.collides(point) == true);
}

TEST_CASE("Axis aligned bounding box - line collision",
          "[axis aligned bounding boxes][lines][collisions]") {
    AABBox box(Point3(-21.0f, -7.0f, 10.0f), Point3(-9.0f, -3.0f, 30.0f));

    Line line1(Point3(-39.0f, -6.0f, -21.0f), Vec3(7.0f, 0.0f, 12.0f));

    float ax = (box.min()._x - line1.point_a()._x) / line1.vec()._x;
    float bx = (box.max()._x - line1.point_a()._x) / line1.vec()._x;

    float sx = (ax < bx ? ax : bx);
    float tx = (ax > bx ? ax : bx);

    REQUIRE(sx == Catch::Approx(2.57143f));
    REQUIRE(tx == Catch::Approx(4.28571f));

    float ay = (box.min()._y - line1.point_a()._y) / line1.vec()._y;
    float by = (box.max()._y - line1.point_a()._y) / line1.vec()._y;

    float sy = (ay < by ? ay : by);
    float ty = (ay > by ? ay : by);

    REQUIRE(sy == -std::numeric_limits<float>::infinity());
    REQUIRE(ty ==  std::numeric_limits<float>::infinity());

    float az = (box.min()._z - line1.point_a()._z) / line1.vec()._z;
    float bz = (box.max()._z - line1.point_a()._z) / line1.vec()._z;

    float sz = (az < bz ? az : bz);
    float tz = (az > bz ? az : bz);

    REQUIRE(sz == Catch::Approx(2.58333f));
    REQUIRE(tz == Catch::Approx(4.25f));

    REQUIRE(overlap(sx, tx, sy, ty) == true);
    REQUIRE(overlap(sy, ty, sz, tz) == true);
    REQUIRE(overlap(sz, tz, sx, tx) == true);

    Line line2(Point3(-26.0f, -27.0f, -20.0f), Vec3(-4.0f, -5.0f, -11.0f));

    ax = (box.min()._x - line2.point_a()._x) / line2.vec()._x;
    bx = (box.max()._x - line2.point_a()._x) / line2.vec()._x;

    sx = (ax < bx ? ax : bx);
    tx = (ax > bx ? ax : bx);

    REQUIRE(sx == Catch::Approx(-4.25f));
    REQUIRE(tx == Catch::Approx(-1.25f));

    ay = (box.min()._y - line2.point_a()._y) / line2.vec()._y;
    by = (box.max()._y - line2.point_a()._y) / line2.vec()._y;

    sy = (ay < by ? ay : by);
    ty = (ay > by ? ay : by);

    REQUIRE(sy == Catch::Approx(-4.8f));
    REQUIRE(ty == Catch::Approx(-4.0f));

    az = (box.min()._z - line2.point_a()._z) / line2.vec()._z;
    bz = (box.max()._z - line2.point_a()._z) / line2.vec()._z;

    sz = (az < bz ? az : bz);
    tz = (az > bz ? az : bz);

    REQUIRE(sz == Catch::Approx(-4.54545f));
    REQUIRE(tz == Catch::Approx(-2.72727f));

    REQUIRE(box.collides(line1) == true);
    REQUIRE(box.collides(line2) == true);

    REQUIRE(overlap(sx, tx, sy, ty) == true);
    REQUIRE(overlap(sy, ty, sz, tz) == true);
    REQUIRE(overlap(sz, tz, sx, tx) == true);

    box   = AABBox(Point3(3.0f, 9.0f, -18.0f), Point3(7.0f, 21.0f, -2.0f));
    line2 = Line(Point3(28.0f, -36.0f, -18.0f), Vec3(4.0f, -12.0f, -4.0f));

    ax = (box.min()._x - line2.point_a()._x) / line2.vec()._x;
    bx = (box.max()._x - line2.point_a()._x) / line2.vec()._x;

    sx = (ax < bx ? ax : bx);
    tx = (ax > bx ? ax : bx);

    REQUIRE(sx == Catch::Approx(-6.25f));
    REQUIRE(tx == Catch::Approx(-5.25f));

    ay = (box.min()._y - line2.point_a()._y) / line2.vec()._y;
    by = (box.max()._y - line2.point_a()._y) / line2.vec()._y;

    sy = (ay < by ? ay : by);
    ty = (ay > by ? ay : by);

    REQUIRE(sy == Catch::Approx(-4.75f));
    REQUIRE(ty == Catch::Approx(-3.75f));

    az = (box.min()._z - line2.point_a()._z) / line2.vec()._z;
    bz = (box.max()._z - line2.point_a()._z) / line2.vec()._z;

    sz = (az < bz ? az : bz);
    tz = (az > bz ? az : bz);

    REQUIRE(sz == Catch::Approx(-4.0f));
    REQUIRE(tz == Catch::Approx(0.0f));

    REQUIRE(overlap(sx, tx, sy, ty) == false);
    REQUIRE(overlap(sy, ty, sz, tz) == true);
    REQUIRE(overlap(sz, tz, sx, tx) == false);

    REQUIRE(box.collides(line1) == false);
}


TEST_CASE("Object bounding box - object bounding box collision",
          "[object bounding boxes][collisions]") {
    OBBox box1(Point3(-3.75f, -0.75f, -5.0f),
               Point3(4.25f, 1.25f, 5.0f),
               Mat4(-0.279,   0.0388f, -0.1044f, 3.0f,
                     0.0f,    0.2812f,  0.1044f, 0.0f,
                     0.1114f, 0.097f,  -0.261f, -5.0f,
                     0.0f,    0.0f,     0.0f,    1.0f));

    OBBox box2(Point3(-2.5f, -6.0f, -0.5f),
               Point3(3.5f, 6.0f, 1.5f),
               Mat4( 0.707f,  0.4082f,  0.5774f,   3.0f,
                     0.0f,    0.8165f, -0.577f,    4.0f,
                    -0.707f, -0.408f,  -0.577f,  -11.0f,
                     0.0f,    0.0f,     0.0f,      1.0f));

    Vec3 box1_side = box1.side();
    Vec3 box1_up   = box1.up();
    Vec3 box1_fwd  = box1.forward();
    Vec3 box2_side = box2.side();
    Vec3 box2_up   = box2.up();
    Vec3 box2_fwd  = box2.forward();

    Vec3 ss_cross  = box1.side().cross(box2.side());
    Vec3 us_cross  = box1.up().cross(box2.side());
    Vec3 fs_cross  = box1.forward().cross(box2.side());

    Vec3 su_cross  = box1.side().cross(box2.up());
    Vec3 uu_cross  = box1.up().cross(box2.up());
    Vec3 fu_cross  = box1.forward().cross(box2.up());

    Vec3 sf_cross  = box1.side().cross(box2.forward());
    Vec3 uf_cross  = box1.up().cross(box2.forward());
    Vec3 ff_cross  = box1.forward().cross(box2.forward());

    REQUIRE(box1_side == Vec3(-0.279f, 0.0f, 0.1114f));
    REQUIRE(box1_up   == Vec3(0.0388f, 0.2812f, 0.097f));
    REQUIRE(box1_fwd  == Vec3(-0.1044f, 0.1044f, -0.261f));
    REQUIRE(box2_side == Vec3(0.707f, 0.0f, -0.707f));
    REQUIRE(box2_up   == Vec3(0.4082f, 0.8165f, -0.408f));
    REQUIRE(box2_fwd  == Vec3(0.5774f, -0.5774f, -0.5774f));
    REQUIRE(ss_cross  == Vec3(0.0f, -0.118493f, 0.0f));
    REQUIRE(us_cross  == Vec3(-0.198808f, 0.09601f, -0.198808f));
    REQUIRE(fs_cross  == Vec3(-0.07381f, -0.258337f, -0.07381f));
    REQUIRE(su_cross  == Vec3(-0.090958f, -0.068358f, -0.227803f));
    REQUIRE(uu_cross  == Vec3(-0.19393f, 0.055425f, -0.083105f));
    REQUIRE(fu_cross  == Vec3(0.170511f, -0.149135f, -0.127858f));
    REQUIRE(sf_cross  == Vec3(0.064322f, -0.096772f, 0.161094f));
    REQUIRE(uf_cross  == Vec3(-0.106357f, 0.07841f, -0.184768f));
    REQUIRE(ff_cross  == Vec3(-0.210836f, -0.21094f, -0.000041f));

    Vec3 box1_side_local1 = box1.to_local(box1_side);
    Vec3 box1_up_local1   = box1.to_local(box1_up);
    Vec3 box1_fwd_local1  = box1.to_local(box1_fwd);
    Vec3 box2_side_local1 = box1.to_local(box2_side);
    Vec3 box2_up_local1   = box1.to_local(box2_up);
    Vec3 box2_fwd_local1  = box1.to_local(box2_fwd);

    Vec3 ss_cross_local1  = box1.to_local(ss_cross);
    Vec3 us_cross_local1  = box1.to_local(us_cross);
    Vec3 fs_cross_local1  = box1.to_local(fs_cross);

    Vec3 su_cross_local1  = box1.to_local(su_cross);
    Vec3 uu_cross_local1  = box1.to_local(uu_cross);
    Vec3 fu_cross_local1  = box1.to_local(fu_cross);

    Vec3 sf_cross_local1  = box1.to_local(sf_cross);
    Vec3 uf_cross_local1  = box1.to_local(uf_cross);
    Vec3 ff_corss_local1  = box1.to_local(ff_cross);

    Vec3 box1_side_local2 = box2.to_local(box1_side);
    Vec3 box1_up_local2   = box2.to_local(box1_up);
    Vec3 box1_fwd_local2  = box2.to_local(box1_fwd);
    Vec3 box2_side_local2 = box2.to_local(box2_side);
    Vec3 box2_up_local2   = box2.to_local(box2_up);
    Vec3 box2_fwd_local2  = box2.to_local(box2_fwd);

    Vec3 ss_cross_local2  = box2.to_local(ss_cross);
    Vec3 us_cross_local2  = box2.to_local(us_cross);
    Vec3 fs_cross_local2  = box2.to_local(fs_cross);

    Vec3 su_cross_local2  = box2.to_local(su_cross);
    Vec3 uu_cross_local2  = box2.to_local(uu_cross);
    Vec3 fu_cross_local2  = box2.to_local(fu_cross);

    Vec3 sf_cross_local2  = box2.to_local(sf_cross);
    Vec3 uf_cross_local2  = box2.to_local(uf_cross);
    Vec3 ff_corss_local2  = box2.to_local(ff_cross);

    REQUIRE(box1.max_projection(box1_side) == Catch::Approx(13.32516f));

    REQUIRE(box1_side_local1 == Vec3(1.0f, -0.000215f, 0.00058f));
    REQUIRE(box1_up_local1   == Vec3(-0.000215f, 0.999999f, -0.000116f));
    REQUIRE(box1_fwd_local1  == Vec3(0.000578f, -0.000116f, 1.0f));
    //REQUIRE(box2_side_local1 == Vec3(1.313f, -1.067f, 2.872f));
    //REQUIRE(box2_up_local1   == Vec3(-1.796f, 2.287f, 1.658f));
    //REQUIRE(box2_fwd_local1  == Vec3(-2.502f, -2.177f, 0.335f));

    //REQUIRE(ss_cross_local1  == Vec3());
    //REQUIRE(us_cross_local1  == Vec3());
    //REQUIRE(fs_cross_local1  == Vec3());

    //REQUIRE(su_cross_local1  == Vec3());
    //REQUIRE(uu_cross_local1  == Vec3());
    //REQUIRE(fu_cross_local1  == Vec3());

    //REQUIRE(sf_cross_local1  == Vec3());
    //REQUIRE(uf_cross_local1  == Vec3());
    //REQUIRE(ff_corss_local1  == Vec3());

    //REQUIRE(box1_side_local2 == Vec3());
    //REQUIRE(box1_up_local2   == Vec3());
    //REQUIRE(box1_fwd_local2  == Vec3());
    //REQUIRE(box2_side_local2 == Vec3());
    //REQUIRE(box2_up_local2   == Vec3());
    //REQUIRE(box2_fwd_local2  == Vec3());

    //REQUIRE(ss_cross_local2  == Vec3());
    //REQUIRE(us_cross_local2  == Vec3());
    //REQUIRE(fs_cross_local2  == Vec3());

    //REQUIRE(su_cross_local2  == Vec3());
    //REQUIRE(uu_cross_local2  == Vec3());
    //REQUIRE(fu_cross_local2  == Vec3());

    //REQUIRE(sf_cross_local2  == Vec3());
    //REQUIRE(uf_cross_local2  == Vec3());
    //REQUIRE(ff_corss_local2  == Vec3());

    REQUIRE(box1.collides(box2) == false);

    box1 = OBBox(Point3(-2.625f, -1.0f, -1.625f),
                 Point3(2.375f, 1.0f, 2.375f),
                 Mat4(-0.632f, 0.0f, -1.897f, -7.0f,
                       0.0f,   2.0f,  0.0f,    0.0f,
                       1.897f, 0.0f, -0.632f,  4.0f,
                       0.0f,   0.0f,  0.0f,    1.0f));

    box2 = OBBox(Point3(-1.25f, 0.0f, 0.75f),
                 Point3(0.75f, 1.0f, 1.125f),
                 Mat4(-1.6f, 0.0f,  1.2f, -10.0f,
                       0.0f, 2.0f,  0.0f,   0.0f,
                      -1.2f, 0.0f, -1.6f,   9.0f,
                       0.0f, 0.0f,  0.0f,   1.0f));

    REQUIRE(box1.collides(box2) == true); 
}

TEST_CASE("Object bounding box - sphere collision", 
          "[object bounding boxes][spheres][collisions]") {
    OBBox box(Point3(-2.0f, -1.0f, -2.0f),
              Point3(2.0f, 5.0f, 3.0f),
              Mat4(1.414213f, 0.0f, -1.414213f,  45.0f,
                   0.0f,      2.0f,  0.0f,       45.0f,
                   1.414213f, 0.0f,  1.414213f, -75.0f,
                   0.0f,      0.0f,  0.0f,       1.0f));

    BSphere sphere(Point3(39.0f, 45.0f, -70.5f), 3.0f, Mat4::identity);

    Point3 C_local(-0.53033f, -0.000001f, 3.712315f);
    Point3 C_clamped_local(-0.53033f, -0.000001f, 3.712315f);
    Point3 C_clamped_world(40.007362f, 45.0f, -71.507362f);
    Vec3   Q_minus_C(1.007362f, -0.000004f, -1.007362f);

    REQUIRE(box.to_local(sphere.center()) == C_local);
    REQUIRE(sphere.center_clamped(box)    == C_clamped_local);
    REQUIRE(box.to_world(sphere.center_clamped(box)) == C_clamped_world);
    REQUIRE(C_clamped_world - sphere.center() == Q_minus_C);

    REQUIRE(box.collides(sphere) == true);
    REQUIRE(sphere.collides(box) == true);

    box = OBBox(Point3(4.0f, 0.0f, -5.0f),
                Point3(6.0f, 4.0f, 1.0f),
                Mat4(1.4142f, 0.0f, 1.4142f, 60.0f,
                      0.0f,   2.0f,  0.0f,  -60.0f,
                     -1.414f, 0.0f, 1.4142f, -45.0f,
                      0.0f,   0.0f,  0.0f,  1.0f));

    sphere = BSphere(Point3(72.0f, -63.0f, -42.0f), 6, Mat4::identity);

    C_local = Point3(3.182609f, -1.5f, 5.303352f);
    C_clamped_local = Point3(4.0f, 0.0f, 1.0f);
    C_clamped_world = Point3(67.070999f, -60.0f, -49.241798f);
    Q_minus_C = Vec3(-4.929f, 3.0f, -7.243f);

    REQUIRE(box.to_local(sphere.center()) == C_local);
    REQUIRE(sphere.center_clamped(box) == C_clamped_local);
    REQUIRE(box.to_world(sphere.center_clamped(box)) == C_clamped_world);
    REQUIRE(C_clamped_world - sphere.center() == Q_minus_C);

    REQUIRE(box.collides(sphere) == false);
    REQUIRE(sphere.collides(box) == false);
}

TEST_CASE("Object bounding box - point collision", 
          "[object bounding boxes][points][collisions]") {
    OBBox box(Point3(-1.75f, -1.0f, -1.13f),
              Point3(2.25f, 1.0f, 0.875f),
              Mat4(-0.83f, 0.0f,  0.555f, -10.0f,
                    0.0f,  1.0f,  0.0f,     0.0f,
                   -0.55f, 0.0f, -0.83f,    4.0f,
                    0.0f,  0.0f,  0.0f,     1.0f));

    Point3 point(-5.28f, 0.0f, 9.965f);

    REQUIRE(box.collides(point) == false);
}

TEST_CASE("Object bounding box - plane intersection",
          "[object bounding boxes][planes][collisions]") {
    OBBox box(Point3(-5.75f, -5.625f, -1.75f),
              Point3(6.25f, 6.375f, 2.25f),
              Mat4(-1.4142f, 1.1547f, 0.8165f, -17.0f,
                    0.0f, 1.1547f, -1.633f,  -8.0f,
                   -1.4142f, -1.1547f, -0.8165, 5.0f,
                    0.0f,       0.0f,       0.0f,       1.0f));

    Plane plane(Point3(9.0f, -9.0f, 9.0f), Vec3(2.0f, 4.0f, -3.0f));

    Point3 box_local_center = box.center();
    Vec3   half_diag        = box.best_diag();
    float  scale            = box.get_proj_scale();
    Point3 box_world_center = box.center_world();

    REQUIRE(box_local_center == Point3(0.25f, 0.375f, 0.25f));
    REQUIRE(half_diag == Vec3(6.0f, 6.0f, 2.0f));
    REQUIRE(scale == Catch::Approx(3.99992f));
    REQUIRE(box_world_center == Point3(-16.72f, -7.98f, 4.01f));

    float normal_length = plane.normal().length();
    Vec3 local_normal = box.to_local(plane.normal());
    float projection = box.scaled_projection(plane.normal());

    REQUIRE(normal_length == Catch::Approx(5.38516f));
    REQUIRE(local_normal == Vec3(0.353556f, 2.598077f, -0.612369f));
    REQUIRE(projection == Catch::Approx(14.064f));

    Point3 s1(box.center_world() - projection * plane.normal().normalized());
    Point3 s2(box.center_world() + projection * plane.normal().normalized());

    Vec3 s1_minus_p0 = s1 - plane.point();
    Vec3 s2_minus_p0 = s2 - plane.point();

    REQUIRE(s1 == Point3(-21.939632f, -18.42168f, 11.844144f));
    REQUIRE(s2 == Point3(-11.49319f, 2.471205f, -3.82552f));
    REQUIRE(s1_minus_p0 == Vec3(-30.939632f, -9.42168f, 2.844145f));
    REQUIRE(s2_minus_p0 == Vec3(-20.49319f, 11.471205f, -12.82552f));

    float d1 = s1_minus_p0.dot(plane.normal());
    float d2 = s2_minus_p0.dot(plane.normal());

    REQUIRE(d1 == Catch::Approx(-108.09842f));
    REQUIRE(d2 == Catch::Approx(43.375f));

    REQUIRE(box.collides(plane) == true);
}
