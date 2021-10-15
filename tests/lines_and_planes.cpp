#include "pdmath/Point3.hpp"
#include "pdmath/Vector.hpp"
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