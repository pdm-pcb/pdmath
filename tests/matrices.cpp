#include "pdmath/Matrix.hpp"

#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_approx.hpp"

using namespace pdm;
using namespace Catch;

TEST_CASE("Matrices can multiply", "[matrices]") {
    Mat3 m( 3, -5,  4,
           -2,  2,  3,
           -3, -4, -5);

    Mat3 n(-1, -2, -3,
           -5,  2,  3,
            1,  0, -3);
    
    REQUIRE((m *= n) == Mat3(26, -16, -36,
                             -5,   8,   3,
                             18,  -2,  12));

    m = Mat3(-2,  4,  4,
             -1, -4,  4,
              2,  3,  0);

    n = Mat3( 4,  4,  1,
             -4, -5,  2,
             -1, -1, -5);
    
    REQUIRE((m *= n) == Mat3(-28, -32, -14,
                               8,  12, -29,
                              -4,  -7,  8));
}