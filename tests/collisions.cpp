#include "pdmath/BSphere.hpp"
#include "pdmath/AABBox.hpp"
#include "pdmath/OBBox.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Point3.hpp"
#include "pdmath/Line3.hpp"
#include "pdmath/Line4.hpp"
#include "pdmath/Plane.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Bounding sphere - bounding sphere collision",
          "[axis aligned bounding boxes][collisions]") {
    BSphere object1(Point4(-6.77f, 0.0f, -6.7f, 1.0f), 5, Mat4::identity);
    BSphere object2(Point4(9.0f, 0.0f, 5.0f, 1.0f), 2.5, Mat4::identity);

    REQUIRE(object1.collides(object2) == false);
    REQUIRE(object2.collides(object1) == false);

    object1 = BSphere(Point4(7.844f, 0.0f, 5.774f, 1.0f), 3, Mat4::identity);
    object2 = BSphere(Point4(6.0f, 0.0f, 4.0f, 1.0f), 2.5, Mat4::identity);
    
    REQUIRE(object1.collides(object2) == true);
    REQUIRE(object2.collides(object1) == true);
}

TEST_CASE("Bounding sphere - axis aligned bounding box collision",
          "[bounding spheres][axis aligned bounding boxes][collisions]") {
    BSphere object1(Point4(10.0f, 0.0f, 8.0f, 1.0f), 2.5, Mat4::identity);
    AABBox object2(Point4(-6.0f, -1.0f, -5.0f, 1.0f),
                   Point4(-4.0f, 1.0f, 8.0f, 1.0f));

    REQUIRE(object1.collides(object2) == false);
    REQUIRE(object2.collides(object1) == false);

    object1 = BSphere(Point4(-9.0f, 0.0f, -5.0f, 1.0f), 2.5, Mat4::identity);
    object2 = AABBox(Point4(-9.5f, -1.0f, -4.5f, 1.0f),
                     Point4(-4.5f, 1.0f, 2.5f, 1.0f));
    
    REQUIRE(object1.collides(object2) == true);
    REQUIRE(object2.collides(object1) == true);
}

TEST_CASE("Bounding sphere - point collision",
          "[bounding spheres][points][collisions]") {
    BSphere sphere(Point4(-7.0f, 0.0f, 9.518f, 1.0f), 5.0f, Mat4::identity);
    Point4 point(6.0f, 0.0f, 10.0f, 1.0f);

    REQUIRE(sphere.collides(point) == false);

    sphere = BSphere(Point4(5.118f, 0.0f, -6.02f, 1.0f), 10.0f, Mat4::identity);
    point = Point4(10.0f, 0.0f, -4.0f, 1.0f);

    REQUIRE(sphere.collides(point) == true);
}

TEST_CASE("Axis aligned bounding box - axis aligned bounding box collision",
          "[axis aligned bounding boxes][collisions]") {
    AABBox object1(Point4(-3.0f, -1.0f, 1.5f, 1.0f),
                   Point4(3.0f, 1.0f, 6.5f, 1.0f));

    AABBox object2(Point4(2.5f, -1.0f, -3.0f, 1.0f),
                   Point4(9.5f, 1.0f, 3.0f, 1.0f));

    REQUIRE(object1.collides(object2) == true);
    REQUIRE(object2.collides(object1) == true);

    object1 = AABBox(Point4(-1.0f, -1.0f, 4.0f, 1.0f),
                     Point4(1.0f, 1.0f, 8.0f, 1.0f));

    object2 = AABBox(Point4(-5.5f, -1.0f, 1.5f, 1.0f),
                     Point4(-2.5f, 1.0f, 2.5f, 1.0f));

    REQUIRE(object1.collides(object2) == false);
    REQUIRE(object2.collides(object1) == false);
}

TEST_CASE("Axis aligned bounding box - bounding sphere collision",
          "[axis aligned bounding boxes][bounding spheres][collisions]") {
    AABBox box(Point4(-3.5f, -1.0f, -6.5f, 1.0f),
               Point4(3.5f, 1.0f, -1.5f, 1.0f));

    BSphere sphere(Point4(5.0f, 0.0f, 9.0f, 1.0f), 1.5f, Mat4::identity);

    REQUIRE(box.collides(sphere) == false);
    REQUIRE(sphere.collides(box) == false);

    box = AABBox(Point4(3.0f, -1.0f, 5.0f, 1.0f),
                 Point4(7.0f, 1.0f, 7.0f, 1.0f));
    sphere = BSphere(Point4(8.0f, 0.0f, 9.0f, 1.0f), 2.5f, Mat4::identity);

    REQUIRE(box.collides(sphere) == true);
    REQUIRE(sphere.collides(box) == true);
}

TEST_CASE("Axis aligned bounding box - point collision",
          "[axis aligned bounding boxes][points][collisions]") {
    AABBox box(Point4(-2.5f, -1.0f, 0.5f, 1.0f),
               Point4(2.5f, 1.0f, 5.5f, 1.0f));

    Point4 point(7.0f, 2.0f, 5.0f, 1.0f);

    REQUIRE(box.collides(point) == false);

    box = AABBox(Point4(-8.5f, -1.0f, 1.5f, 1.0f),
                 Point4(-1.5f, 1.0f, 4.5f, 1.0f));
    
    point = Point4(-8.0f, 0.5f, 3.0f, 1.0f);

    REQUIRE(box.collides(point) == true);
}

TEST_CASE("Object bounding box - object bounding box collision",
          "[object bounding boxes][collisions]") {
    OBBox object1(Point4(-4.5f, -4.5f, -5.0f, 1.0f),
                  Point4(5.5f, 5.5f, 5.0f, 1.0f),
                  Mat4(
                      0.3f, 0.0f,    0.0f,     4.0f,
                       0.0f, 0.2846f,-0.095f, -3.0f,
                       0.0f, 0.0949f, 0.2846f, 3.0f,
                       0.0f, 0.0f,    0.0f,    1.0f));

    OBBox object2(Point4(-4.0f, -4.75f, -4.5f, 1.0f),
                  Point4(4.0f, 5.25f, 5.5f, 1.0f),
                  Mat4(
                      0.2425f,  0.2287f, -0.943f,  6.0f,
                      0.0f,     0.9718f,  0.2357f, 4.0f,
                      0.9701f, -0.057f,   0.2357f, 8.0f,
                      0.0f,     0.0f,     0.0f,    1.0f));

    REQUIRE(object1.collides(object2) == false);

    object1 = OBBox(Point4(-1.88f, -1.0f, -3.0f, 1.0f),
                    Point4(2.125f, 1.0f, 2.0f, 1.0f),
                    Mat4(
                         1.961f, 0.0f,  0.392f,  9.0f,
                         0.0f,   2.0f,  0.0f,    0.0f,
                        -0.392f, 0.0f,  1.961f, -7.0f,
                         0.0f,   0.0f,  0.0f,    1.0f));

    object2 = OBBox(Point4(-1.38f, -1.0f, -1.5f, 1.0f),
                    Point4(1.625f, 1.0f, 0.5f, 1.0f),
                    Mat4(
                        -2.0f, 0.0f,  1.2f,  6.0f,
                         0.0f, 2.0f,  0.0f,  0.0f,
                         0.0f, 0.0f, -2.0f, -9.0f,
                         0.0f, 0.0f,  0.0f,  1.0f));

    REQUIRE(object1.collides(object2) == true);
}

TEST_CASE("Object bounding box - sphere collision", 
          "[object bounding boxes][spheres][collisions]") {
    OBBox box(Point4(-1.75f, -1.0f, -1.13f, 1.0f),
              Point4(2.25f, 1.0f, 0.875f, 1.0f),
              Mat4(
                  -0.83f, 0.0f,  0.555f, -10.0f,
                  0.0f,   1.0f,  0.0f,     0.0f,
                  -0.55f, 0.0f, -0.83f,    4.0f,
                  0.0f,   0.0f,  0.0f,     1.0f));

    BSphere sphere(Point4(-5.28f, 0.0f, 9.965f, 1.0f), 2.5f, Mat4::identity);

    REQUIRE(box.collides(sphere) == false);
    REQUIRE(sphere.collides(box) == false);

    box = OBBox(Point4(-2.88f, -1.0f, -1.38f, 1.0f),
                Point4(2.125f, 1.0f, 1.625f, 1.0f),
                Mat4(
                    -1.34f,  0.0f, -0.67f, 8.0f,
                     0.0f,   1.5f,  0.0f,  0.0f,
                     0.671f, 0.0f, -1.34f, 9.0f,
                     0.0f,   0.0f,  0.0f,  1.0f));

    sphere = BSphere(Point4(7.419f, 0.0f, 11.58f, 1.0f), 2, Mat4::identity);

    REQUIRE(box.collides(sphere) == true);
    REQUIRE(sphere.collides(box) == true);
}

TEST_CASE("Object bounding box - point collision", 
          "[object bounding boxes][points][collisions]") {
    OBBox box(Point4(-1.75f, -1.0f, -1.13f, 1.0f),
              Point4(2.25f, 1.0f, 0.875f, 1.0f),
              Mat4(
                  -0.83f, 0.0f,  0.555f, -10.0f,
                  0.0f,   1.0f,  0.0f,     0.0f,
                  -0.55f, 0.0f, -0.83f,    4.0f,
                  0.0f,   0.0f,  0.0f,     1.0f));

    Point4 point(-5.28f, 0.0f, 9.965f, 1.0f);

    REQUIRE(box.collides(point) == false);
}


// HOMEWORK 7 ------------------------------------------------------------------


TEST_CASE("Point of nearest approach on a segment",
          "[points][lines][collisions") {
    Line4 l(Point4(198.0f, 98.0f, 199.0f, 1.0f),
            Point4(202.0f, 102.0f, 201.0f, 0.0f));

    Point4 p(214.0f, 90.0f, 186.0f);
    Point4 q(196.0f, 108.0f, 207.0f);
    Point4 r(193.0f, 90.0f,  201.0f);
    Point4 s(196.0f, 114.0f, 192.0f);

    REQUIRE(p.nearest_approach_segment(l) == Point4(198.67f, 98.67f, 199.33f));
    REQUIRE(q.nearest_approach_segment(l) == Point4(202.0f, 102.0f, 201.0f));
    REQUIRE(r.nearest_approach_segment(l) == Point4(198.0f, 98.0f, 199.0f));
    REQUIRE(s.nearest_approach_segment(l) == Point4(202.0f, 102.0f, 201.0f));
}

TEST_CASE("Axis aligned bounding box - line collision",
          "[axis aligned bounding boxes][lines][collisions]") {
    AABBox box(Point4(-21.0f, -7.0f, 10.0f, 1.0f),
               Point4(-9.0f, -3.0f, 30.0f, 1.0f));

    Line4 l1(Point4(-39.0f, -6.0f, -21.0f, 1.0f),
             Vec4(7.0f, 0.0f, 12.0f, 0.0f));

    Line4 l2(Point4(-26.0f, -27.0f, -20.0f, 1.0f),
             Vec4(-4.0f, -5.0f, -11.0f, 0.0f));

    REQUIRE(box.collides(l1) == true);
    REQUIRE(box.collides(l2) == true);
}

TEST_CASE("Distance between lines", "[lines][collisions]") {
    Line4 l1(Point4(-73.0f, -5.0f, -4.0f), Vec4(14.0f, 7.0f, 4.0f));
    Line4 l2(Point4(-47.0f, -13.0f, 16.0f), Vec4(-8.0f, -9.0f, 0.0f));

    REQUIRE(l1.distance_to(l2) == l2.distance_to(l1));
}

TEST_CASE("Bounding sphere - plane intersection"
          "[bounding spheres][planes][collisions") {
    Plane plane(Point3(6.0f, 6.0f, 12.0f),
                Vec3(2.0f, 1.0f, -3.0f));

    BSphere s1(Point4(-16.0f, -14.0f, 0.0f), 6.0f, Mat4::identity);

    BSphere s2(Point4(-8.0f, -10.0f, -12.0f), 8.0f, Mat4::identity);

    REQUIRE(s1.collides(plane)    == false);
    REQUIRE(s1.above_plane(plane) == false);

    REQUIRE(s2.collides(plane)    == true);
    REQUIRE(s2.above_plane(plane) == true);
}

TEST_CASE("Plane - segment intersection" "[planes][lines][collisions]") {
    Plane plane(Point3(-6.0f, -15.0f, -6.0f),
                Vec3(-5.0f, -2.0f, -2.0f));

    Line3 l1(Point3(14.0f, -12.0f, -54.0f),
             Point3(13.0f, -8.0f, -56.0f));

    Line3 l2(Point3(11.0f, -8.0f, -56.0f),
             Point3(15.0f, -10.0f, -58.0f));

    REQUIRE(l1.intersects(plane) == false);
    REQUIRE(l2.intersects(plane) == true);

    REQUIRE(l1.intersects_depth(plane) == 10.0f);
    REQUIRE(l2.intersects_depth(plane) == Catch::Approx(0.0833333f));
}

TEST_CASE("Object bounding box - plane intersection",
          "[object bounding boxes][planes][collisions]") {
    OBBox box(Point4(-5.75f, -5.625f, -1.75f, 1.0f),
              Point4(6.25f, 6.375f, 2.25f, 1.0f),
              Mat4(
                  -1.4142f,  1.1547f,  0.8165f, -17.0f,
                   0.0f,     1.1547f, -1.633f,   -8.0f,
                  -1.4142f, -1.1547f, -0.8165f,   5.0f,
                   0.0f,     0.0f,     0.0f,      1.0f));

    Plane plane(Point3(9.0f, -9.0f, 9.0f), Vec3(2.0f, 4.0f, -3.0f));

    REQUIRE(box.collides(plane) == true);
}



TEST_CASE("Problem 1") {
    Line4 l(Point4(-43.0f, -42.0f, -44.0f, 1.0f),
            Point4(-37.0, -38.0, -36.0f, 0.0f));

    Point4 p(-37.0f, -53.0f, -27.0f, 1.0f);
    Point4 q(-46.0f, -26.0f, -27.0f, 1.0f);
    Point4 r(-34.0f, -50.0f, -48.0f, 1.0f);
    Point4 s(-34.0f, -44.0f, -45.0f, 1.0f);

    // p.nearest_approach_segment(l);
    // q.nearest_approach_segment(l);
    // r.nearest_approach_segment(l);
    // s.nearest_approach_segment(l);
}

TEST_CASE("Problem 2") {
    AABBox box(Point4(-35.0f, -9.0f, 6.0f, 1.0f),
               Point4(-15.0f, -1.0f, 14.0f, 1.0f));

    Line4 l1(Point4(-60.0f, -19.0f, 8.0f, 1.0f),
             Vec4(10.0f, 4.0f, 0.0f, 0.0f));

    Line4 l2(Point4(-35.0f, -29.0f, 26.0f, 1.0f),
             Vec4(-5.0f, -6.0f, 2.0f, 0.0f));

    // std::cout << box.collides(l1) << std::endl;
    // std::cout << box.collides(l2) << std::endl;
}



TEST_CASE("Problem 3") {
    Line4 l1(Point4(-43.0f, -68.0f, -18.0f), Vec4(11.0f, 14.0f, 5.0f));
    Line4 l2(Point4(-20.0f, -87.0f, 14.0f), Vec4(-6.0f, -17.0f, 1.0f));

    // std::cout << l1.distance_to(l2) << std::endl;
}

TEST_CASE("Problem 4") {
    Plane plane(Point3(-12.0f, -3.0f, -9.0f),
                Vec3(-3.0f, 2.0f, 3.0f));

    BSphere s1(Point4(-11.0f, 10.0f, -4.0f), 10.0f, Mat4::identity);

    BSphere s2(Point4(-3.0f, 4.0f, -12.0f), 4.0f, Mat4::identity);

    // std::cout << s1.collides(plane) << std::endl;
    // std::cout << s1.above_plane(plane) << std::endl;

    // std::cout << s2.collides(plane)    << std::endl;
    // std::cout << s2.above_plane(plane) << std::endl;
}

TEST_CASE("Problem 5") {
    Plane plane(Point3(-3.0f, 12.0f, -12.0f),
                Vec3(-4.0f, -5.0f, 4.0f));

    Line3 l1(Point3(10.0f, 5.0f, 0.0f),
             Point3(16.0f, 13.0f, -4.0f));

    Line3 l2(Point3(12.0f, 9.0f, -1.0f),
             Point3(13.0f, 10.0f, 1.0f));

    // std::cout << l1.intersects(plane) << std::endl;
    // std::cout << l2.intersects(plane) << std::endl;
}

TEST_CASE("Problem 6") {
    OBBox box(Point4(-4.125f, -3.625f, -3.5f, 1.0f),
              Point4(3.875f, 4.375f, 4.5f, 1.0f),
              Mat4(
                  -0.6247f,  0.23281f, -0.7454f,   9.0f,
                   0.0f,     0.95452f,  0.29814f, -4.0f,
                   0.78087f, 0.18625f, -0.5963f,  -4.0f,
                   0.0f,     0.0f,      0.0f,      1.0f));

    Plane plane(Point3(9.0f, -12.0f, -15.0f), Vec3(-5.0f, -4.0f, -2.0f));

    // std::cout << box.collides(plane) << std::endl;
}