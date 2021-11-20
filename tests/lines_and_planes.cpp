#include "pdmath/Point3.hpp"
#include "pdmath/Vector3.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Lines understand their relationship to planes", "[lines][planes]") {
    Plane plane(Point3(-1, -3, -8), Vec3(-18, -35, -50));
    Line line(Point3(-9, -9, 0), Vec3(-3, 8, 2));
    REQUIRE(line.parallel_to_plane(plane) == false);
    REQUIRE(line.intersects_at(plane) ==
        Point3(-8.5766869f, -10.1288347f, -0.2822086f));

    line = Line(Point3(4, 3, -14), Vec3(5, -14, 8));
    REQUIRE(line.parallel_to_plane(plane) == true);
    REQUIRE(line.within_plane(plane) == true);

    line = Line(Point3(8, -3, 2), Vec3(-5, -6, 6));
    REQUIRE(line.parallel_to_plane(plane) == true);
    REQUIRE(line.within_plane(plane) == false);
}

TEST_CASE("We can tell if a point on a plane is to the left or right"
          " of a line on that same plane.", "[lines][planes]") {
    Plane plane(Point3(-8, -5, -6), Vec3(-16, 12, -8));
    Line bisect(Point3(-8, -5, -6), Vec3(-2, 0, 4));
    Point3 point(-6, -1, -4);
    REQUIRE(plane.direction_test(bisect, point) > 0.0f);

    point = Point3(-4, 3, -2);
    REQUIRE(plane.direction_test(bisect, point) > 0.0f);

    point = Point3(-10, -9, -8);
    REQUIRE(plane.direction_test(bisect, point) < 0.0f);
}

TEST_CASE("Point of nearest approach on a segment", "[points][lines]") {
    Line l(Point3(198.0f, 98.0f, 199.0f),
           Point3(202.0f, 102.0f, 201.0f));

    Point3 p(214.0f, 90.0f, 186.0f);
    Point3 q(196.0f, 108.0f, 207.0f);
    Point3 r(193.0f, 90.0f, 201.0f);
    Point3 s(196.0f, 114.0f, 192.0f);

    REQUIRE(p.nearest_approach_segment(l) == Point3(198.666671f, 98.666664f, 199.333328f));
    REQUIRE(q.nearest_approach_segment(l) == Point3(202.0f, 102.0f, 201.0f));
    REQUIRE(r.nearest_approach_segment(l) == Point3(198.0f, 98.0f, 199.0f));
    REQUIRE(s.nearest_approach_segment(l) == Point3(202.0f, 102.0f, 201.0f));
}

TEST_CASE("Distance between lines", "[lines]") {
    Line l1(Point3(-73.0f, -5.0f, -4.0f), Vec3(14.0f, 7.0f, 4.0f));
    Line l2(Point3(-47.0f, -13.0f, 16.0f), Vec3(-8.0f, -9.0f, 0.0f));

    REQUIRE(l1.distance_to(l2) == l2.distance_to(l1));
}