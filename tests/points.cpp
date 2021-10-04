#include "pdmath/Point.hpp"
#include "pdmath/Vector.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Collinear points test as such", "[points]") {
    point a(-5, -6, 1);
    point b(6, -1, 1);
    point c(-38, -21, 1);
    REQUIRE(a.are_collinear(b, c));

    a = point(-1, -1, -5);
    b = point(7, -3, -9);
    c = point(-3, 8, -3);
    REQUIRE(!a.are_collinear(b, c));

    a = point(-9, 7, 7);
    b = point(5, 4, -3);
    c = point(-37, 13, 27);
    REQUIRE(a.are_collinear(b, c));

    a = point(-1, 0, -9);
    b = point(-4, -10, -4);
    c = point(-3, 2, -4);
    REQUIRE(!a.are_collinear(b, c));
}

