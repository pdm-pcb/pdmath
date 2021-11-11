#include "pdmath/BSphere.hpp"
#include "pdmath/AABBox.hpp"
#include "pdmath/OBBox.hpp"
#include "pdmath/Vector4.hpp"

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
                     0.0f,   0.0f,  0.0f,  1.0f
                ));

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