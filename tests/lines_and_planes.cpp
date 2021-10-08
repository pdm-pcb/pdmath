#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"
#include "pdmath/Line.hpp"
#include "pdmath/Plane.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Lines know whether or not they're parallel to a plane", "[lines]") {
    Plane plane(Point(-1, -3, -8), Vec3(-18, -35, -50));
    Line line(Point(-9, -9, 0), Vec3(-3, 8, 2));
    REQUIRE(line.parallel_to_plane(plane) == false);
    REQUIRE(line.intersects_at(plane) ==
        Point(-8.5766869f, -10.1288347f, -0.2822086f));

    line = Line(Point(4, 3, -14), Vec3(5, -14, 8));
    REQUIRE(line.parallel_to_plane(plane) == true);
    REQUIRE(line.within_plane(plane) == true);

    line = Line(Point(8, -3, 2), Vec3(-5, -6, 6));
    REQUIRE(line.parallel_to_plane(plane) == true);
    REQUIRE(line.within_plane(plane) == false);
}