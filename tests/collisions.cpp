#include "pdmath/BSphere.hpp"
#include "pdmath/AABBox.hpp"
#include "pdmath/OBBox.hpp"
#include "pdmath/Vector4.hpp"
#include "pdmath/Point4.hpp"
#include "pdmath/Point3.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Bounding sphere - bounding sphere collision",
          "[axis aligned bounding boxes][collisions]") {
    BSphere object1(Point3(-6.77f, 0.0f, -6.7f), 5, Mat4::identity);
    BSphere object2(Point3(9.0f, 0.0f, 5.0f), 2.5, Mat4::identity);

    REQUIRE(object1.collides(object2) == false);
    REQUIRE(object2.collides(object1) == false);

    object1 = BSphere(Point3(7.844f, 0.0f, 5.774f), 3, Mat4::identity);
    object2 = BSphere(Point3(6.0f, 0.0f, 4.0f), 2.5, Mat4::identity);
    
    REQUIRE(object1.collides(object2) == true);
    REQUIRE(object2.collides(object1) == true);
}

TEST_CASE("Bounding sphere - axis aligned bounding box collision",
          "[bounding spheres][axis aligned bounding boxes][collisions]") {
    BSphere object1(Point3(10.0f, 0.0f, 8.0f), 2.5, Mat4::identity);
    AABBox object2(Point3(-6.0f, -1.0f, -5.0f),
                   Point3(-4.0f, 1.0f, 8.0f));

    REQUIRE(object1.collides(object2) == false);
    REQUIRE(object2.collides(object1) == false);

    object1 = BSphere(Point3(-9.0f, 0.0f, -5.0f), 2.5, Mat4::identity);
    object2 = AABBox(Point3(-9.5f, -1.0f, -4.5f),
                     Point3(-4.5f, 1.0f, 2.5f));
    
    REQUIRE(object1.collides(object2) == true);
    REQUIRE(object2.collides(object1) == true);
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

TEST_CASE("Axis aligned bounding box - axis aligned bounding box collision",
          "[axis aligned bounding boxes][collisions]") {
    AABBox object1(Point3(-3.0f, -1.0f, 1.5f),
                   Point3(3.0f, 1.0f, 6.5f));

    AABBox object2(Point3(2.5f, -1.0f, -3.0f),
                   Point3(9.5f, 1.0f, 3.0f));

    REQUIRE(object1.collides(object2) == true);
    REQUIRE(object2.collides(object1) == true);

    object1 = AABBox(Point3(-1.0f, -1.0f, 4.0f),
                     Point3(1.0f, 1.0f, 8.0f));

    object2 = AABBox(Point3(-5.5f, -1.0f, 1.5f),
                     Point3(-2.5f, 1.0f, 2.5f));

    REQUIRE(object1.collides(object2) == false);
    REQUIRE(object2.collides(object1) == false);
}

TEST_CASE("Axis aligned bounding box - bounding sphere collision",
          "[axis aligned bounding boxes][bounding spheres][collisions]") {
    AABBox box(Point3(-3.5f, -1.0f, -6.5f),
               Point3(3.5f, 1.0f, -1.5f));

    BSphere sphere(Point3(5.0f, 0.0f, 9.0f), 1.5f, Mat4::identity);

    REQUIRE(box.collides(sphere) == false);
    REQUIRE(sphere.collides(box) == false);

    box = AABBox(Point3(3.0f, -1.0f, 5.0f),
                 Point3(7.0f, 1.0f, 7.0f));
    sphere = BSphere(Point3(8.0f, 0.0f, 9.0f), 2.5f, Mat4::identity);

    REQUIRE(box.collides(sphere) == true);
    REQUIRE(sphere.collides(box) == true);
}

TEST_CASE("Axis aligned bounding box - point collision",
          "[axis aligned bounding boxes][points][collisions]") {
    AABBox box(Point3(-2.5f, -1.0f, 0.5f),
               Point3(2.5f, 1.0f, 5.5f));

    Point3 point(7.0f, 2.0f, 5.0f);

    REQUIRE(box.collides(point) == false);

    box = AABBox(Point3(-8.5f, -1.0f, 1.5f),
                 Point3(-1.5f, 1.0f, 4.5f));
    
    point = Point3(-8.0f, 0.5f, 3.0f);

    REQUIRE(box.collides(point) == true);
}

TEST_CASE("Object bounding box - object bounding box collision",
          "[object bounding boxes][collisions]") {
    OBBox object1(Point3(-4.5f, -4.5f, -5.0f),
                  Point3(5.5f, 5.5f, 5.0f),
                  Mat4(0.3f, 0.0f,    0.0f,    4.0f,
                       0.0f, 0.2846f,-0.095f, -3.0f,
                       0.0f, 0.0949f, 0.2846f, 3.0f,
                       0.0f, 0.0f,    0.0f,    1.0f));

    OBBox object2(Point3(-4.0f, -4.75f, -4.5f),
                  Point3(4.0f, 5.25f, 5.5f),
                  Mat4(0.2425f,  0.2287f, -0.943f,  6.0f,
                       0.0f,     0.9718f,  0.2357f, 4.0f,
                       0.9701f, -0.057f,   0.2357f, 8.0f,
                       0.0f,     0.0f,     0.0f,    1.0f));

    REQUIRE(object1.collides(object2) == false);

    object1 = OBBox(Point3(-2.625f, -1.0f, -1.625f),
                    Point3(2.375f, 1.0f, 2.375f),
                    Mat4(-0.632f, 0.0f, -1.897f, -7.0f,
                          0.0f, 2.0f, 0.0f, 0.0f,
                          1.897f, 0.0f, -0.632f, 4.0f,
                          0.0f,     0.0f,     0.0f,    1.0f));

    object2 = OBBox(Point3(-1.25f, 0.0f, 0.75f),
                    Point3(0.75f, 1.0f, 1.125f),
                    Mat4(-1.6f, 0.0f, 1.2f, -10.0f,
                          0.0f, 2.0f, 0.0f, 0.0f,
                         -1.2f, 0.0f, -1.6f, 9.0f,
                         0.0f, 0.0f,     0.0f,    1.0f));

    REQUIRE(object1.collides(object2) == true); 
}

TEST_CASE("Object bounding box - sphere collision", 
          "[object bounding boxes][spheres][collisions]") {
    OBBox box(Point3(-0.875f, - 1.0f, - 2.75f),
              Point3(1.125f, 1.0f, 2.25f),
              Mat4(-1.414213f, 0.0f, -1.414213f,  4.0f,
                    0.0f,      2.0f,  0.0f,       0.0f,
                    1.414213f, 0.0f, -1.414213f, -4.0f,
                    0.0f,      0.0f,  0.0f,       1.0f));

    BSphere sphere(Point3(9.176776f, 0.0f, -2.469669f), 1.5f, Mat4::identity);

    Point3 C_local(-1.289213f, 0.0f, -2.371321f);
    Point3 C_clamped_local(-0.875f, 0.0f, -2.371321f);
    Point3 C_clamped_world(8.590990f, 0.0f, -1.883882f);
    Vec3   Q_minus_C(-0.59f, 0.0f, 0.586f);

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

    C_local = Point3(3.182235f, -1.499998f, 5.303127f);
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

TEST_CASE("Axis aligned bounding box - line collision",
          "[axis aligned bounding boxes][lines][collisions]") {
    AABBox box(Point3(-21.0f, -7.0f, 10.0f),
               Point3(-9.0f, -3.0f, 30.0f));

    Line l1(Point3(-39.0f, -6.0f, -21.0f),
             Vec3(7.0f, 0.0f, 12.0f));

    Line l2(Point3(-26.0f, -27.0f, -20.0f),
             Vec3(-4.0f, -5.0f, -11.0f));

    REQUIRE(box.collides(l1) == true);
    REQUIRE(box.collides(l2) == true);
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

    Line l1(Point3(14.0f, -12.0f, -54.0f),
             Point3(13.0f, -8.0f, -56.0f));

    Line l2(Point3(11.0f, -8.0f, -56.0f),
             Point3(15.0f, -10.0f, -58.0f));

    REQUIRE(l1.intersects(plane) == false);
    REQUIRE(l2.intersects(plane) == true);

    REQUIRE(l1.intersects_depth(plane) == 10.0f);
    REQUIRE(l2.intersects_depth(plane) == Catch::Approx(0.0833333f));
}

TEST_CASE("Object bounding box - plane intersection",
          "[object bounding boxes][planes][collisions]") {
    OBBox box(Point3(-4.0f, -2.75f, -3.75f),
              Point3(4.0f, 3.25f, 4.25f),
              Mat4( 0.486664f,  1.377596f, -0.339683f, 13.0f,
                   -0.729996f,  0.551038f,  1.188890f,  0.0f,
                    1.216660f, -0.220415f,  0.849207f, -4.0f,
                    0.0f,       0.0f,       0.0f,       1.0f));

    Plane plane(Point3(7.0f, -9.0f, -6.0f), Vec3(0.0f, -2.0f, -8.0f));

    Vec3   local_normal = box.to_local(plane.normal());
    Point3 world_center = box.center_world();
    float  scale        = box.get_proj_scale();
    float  proj_max     = box.max_projection(plane.normal());
    float  proj_scaled  = box.scaled_projection(plane.normal());

    Vec3 s1(box.center_world() - proj_scaled * plane.normal().normalized());
    Vec3 s2(box.center_world() + proj_scaled * plane.normal().normalized());

    Vec3 s1_minus_p0(s1 - plane.point());
    Vec3 s2_minus_p0(s2 - plane.point());

    float d1 = s1_minus_p0.dot(plane.normal());
    float d2 = s2_minus_p0.dot(plane.normal());

    REQUIRE(local_normal == Vec3(-3.68f, 0.294f, -4.08f));
    REQUIRE(world_center == Point3(13.259478f, 0.434982f, -3.842802f));
    REQUIRE(scale        == Catch::Approx(2.25f));
    REQUIRE(proj_max     == Catch::Approx(3.86778f));
    REQUIRE(proj_scaled  == Catch::Approx(8.7025f));

    REQUIRE(s1 == Vec3(13.26f, 2.546f, 4.6f));
    REQUIRE(s2 == Vec3(13.26f, -1.68f, -12.3f));

    REQUIRE(s1_minus_p0 == Vec3(6.259478f, 11.545648f, 10.599864f));
    REQUIRE(s2_minus_p0 == Vec3(6.259478f, 7.324315f, -6.285468f));

    REQUIRE(d1 == Catch::Approx(-107.89021f));
    REQUIRE(d2 == Catch::Approx(35.63511f));

    REQUIRE(box.collides(plane) == true);
}
