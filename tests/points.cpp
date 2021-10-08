#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Collinear points test as such", "[points]") {
    Point a(-5, -6, 1);
    Point b(6, -1, 1);
    Point c(-38, -21, 1);
    REQUIRE(a.are_collinear(b, c));

    a = Point(-1, -1, -5);
    b = Point(7, -3, -9);
    c = Point(-3, 8, -3);
    REQUIRE(!a.are_collinear(b, c));

    a = Point(-9, 7, 7);
    b = Point(5, 4, -3);
    c = Point(-37, 13, 27);
    REQUIRE(a.are_collinear(b, c));

    a = Point(-1, 0, -9);
    b = Point(-4, -10, -4);
    c = Point(-3, 2, -4);
    REQUIRE(!a.are_collinear(b, c));
}

TEST_CASE("Points can measure their distance to a line", "[Points]") {
    Line  enemy_line(Point(5, 2, -7), Vec3(-5, -8, 15));
    Point player_loc(0, -5, 8);

    REQUIRE(player_loc.distance_to_line(enemy_line) ==
            Catch::Approx(0.892288f).margin(Vec3::epsilon));
}

TEST_CASE("Points know if they're on a plane", "[Points]") {
    Plane plane(Point(0, 0, 0), Vec3(0, 1, 0));
    Point test_point(5, 0, -5);
    REQUIRE(test_point.is_on_plane(plane));

    test_point  = Point(5, 2, -5);
    REQUIRE(test_point.is_on_plane(plane) == false);

    test_point  = Point(5, -2, -5);
    REQUIRE(test_point.is_on_plane(plane) == false);
}

TEST_CASE("Points how far they are from a plane", "[Points]") {
    Plane plane(Point(0, 0, 0), Vec3(0, 1, 0));
    Point test_point(5, 0, -5);
    REQUIRE(test_point.distance_to_plane(plane) ==
            Catch::Approx(0.0f).margin(Vec3::epsilon));

    test_point  = Point(5, 2, -5);
    REQUIRE(test_point.distance_to_plane(plane) ==
            Catch::Approx(2.0f).margin(Vec3::epsilon));

    test_point  = Point(5, -2, -5);
    REQUIRE(test_point.distance_to_plane(plane) ==
            Catch::Approx(-2.0f).margin(Vec3::epsilon));
}
