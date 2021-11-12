#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Line3.hpp"
#include "pdmath/Plane.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Collinear points test as such", "[points]") {
    Point3 a(-5, -6, 1);
    Point3 b(6, -1, 1);
    Point3 c(-38, -21, 1);
    REQUIRE(a.are_collinear(b, c));

    a = Point3(-1, -1, -5);
    b = Point3(7, -3, -9);
    c = Point3(-3, 8, -3);
    REQUIRE(!a.are_collinear(b, c));

    a = Point3(-9, 7, 7);
    b = Point3(5, 4, -3);
    c = Point3(-37, 13, 27);
    REQUIRE(a.are_collinear(b, c));

    a = Point3(-1, 0, -9);
    b = Point3(-4, -10, -4);
    c = Point3(-3, 2, -4);
    REQUIRE(!a.are_collinear(b, c));
}

TEST_CASE("Point3s can measure their distance to a line", "[Point3s]") {
    Line3 enemy_line(Point3(5, 2, -7), Vec3(-5, -8, 15));
    Point3 player_loc(0, -5, 8);

    REQUIRE(player_loc.distance_to_line(enemy_line) ==
            Catch::Approx(0.892288f).margin(Vec3::epsilon));
}

TEST_CASE("Point3s know if they're on a plane", "[Point3s]") {
    Plane plane(Point3(0, 0, 0), Vec3(0, 1, 0));
    Point3 test_point(5, 0, -5);
    REQUIRE(test_point.is_on_plane(plane));

    test_point  = Point3(5, 2, -5);
    REQUIRE(test_point.is_on_plane(plane) == false);

    test_point  = Point3(5, -2, -5);
    REQUIRE(test_point.is_on_plane(plane) == false);
}

TEST_CASE("Point3s know how far they are from a plane", "[Point3s]") {
    Plane plane(Point3(0, 0, 0), Vec3(0, 1, 0));
    Point3 test_point(5, 0, -5);
    REQUIRE(test_point.distance_to_plane(plane) ==
            Catch::Approx(0.0f).margin(Vec3::epsilon));

    test_point  = Point3(5, 2, -5);
    REQUIRE(test_point.distance_to_plane(plane) ==
            Catch::Approx(2.0f).margin(Vec3::epsilon));

    test_point  = Point3(5, -2, -5);
    REQUIRE(test_point.distance_to_plane(plane) ==
            Catch::Approx(-2.0f).margin(Vec3::epsilon));
}
