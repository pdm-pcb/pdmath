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

    Mat3 solution (26, -16, -36,
                   -5,   8,   3,
                   18,  -2,  12);
    
    REQUIRE((m * n)  == solution);    
    REQUIRE((m *= n) == solution);

    m = Mat3(-2,  4,  4,
             -1, -4,  4,
              2,  3,  0);

    n = Mat3( 4,  4,  1,
             -4, -5,  2,
             -1, -1, -5);

    solution = Mat3(-28, -32, -14,
                      8,  12, -29,
                     -4,  -7,  8);
    
    REQUIRE((m * n)  == solution);    
    REQUIRE((m *= n) == solution);
}

TEST_CASE("Matrices can add", "[matrices]") {
    Mat3 m(-4, -2, -2,
           -4,  2, -3,
            2, -3,  2);

    Mat3 n(-1, -1,  1,
            1,  3, -3,
           -3, -5,  2);

    Mat3 solution(-5, -3, -1,
                  -3,  5, -6,
                  -1, -8,  4);
    
    REQUIRE((m + n)  == solution);    
    REQUIRE((m += n) == solution);
}

TEST_CASE("Matrices can subtract", "[matrices]") {
    Mat3 m(-2, -4,  4,
            0,  0, -5,
           -4,  0, -5);

    Mat3 n(-1, -3,  4,
            4,  4, -2,
           -3,  3, -4);

    Mat3 solution(-1, -1,  0,
                  -4, -4, -3,
                  -1, -3, -1);

    REQUIRE((m - n)  == solution);
    REQUIRE((m -= n) == solution);
}