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

TEST_CASE("Object bounding box - object bounding box collision",
          "[object bounding boxes][collisions]") {
    OBBox object1(Point4(-4.5f, -4.5f, -5.0f, 1.0f),
                  Point4(5.5f, 5.5f, 5.0f, 1.0f),
                  Mat4(0.3f, 0.0f,    0.0f,   4.0f,
                       0.0f, 0.2846f,-0.095, -3.0f,
                       0.0f, 0.0949f, 0.2846, 3.0f,
                       0.0f, 0.0f,    0.0f,   1.0f));

    OBBox object2(Point4(-4.0f, -4.75f, -4.5f, 1.0f),
                  Point4(4.0f, 5.25f, 5.5f, 1.0f),
                  Mat4(0.2425f,  0.2287f, -0.943f,  6.0f,
                       0.0f,     0.9718f,  0.2357f, 4.0f,
                       0.9701f, -0.057f,   0.2357f, 8.0f,
                       0.0f,     0.0f,     0.0f,    1.0f));

    std::cout << (object1.collides(object2) ? "true\n" : "false\n") << std::endl;

    // Vec4 cross_fwd(object1.forward().cross(object2.forward()));

    // std::cout << "W1_fwd    : " << object1.forward() << " / "
    //           << object1.forward().length() << "\n"
    //           << "W2_fwd    : " << object2.forward() << " / "
    //           << object2.forward().length() << "\n"
    //           << "cross_fwd : " << cross_fwd << " / "
    //           << cross_fwd.length() << "\n"
    //           << std::endl;

    // std::cout << "W1_C      : " << object1.center() << "\n"
    //           << "W2_C      : " << object2.center() << "\n\n"
    //           << "W1inv:\n"     << object1.to_local() << "\n"
    //           << "W2inv:\n"     << object2.to_local() << "\n\n"
    //           << std::endl;
    
    // std::cout << "W1_fwd local     W1 : " << object1.forward_local() << "\n"
    //           << "W2_fwd local     W1 : " << object1.to_local(object2.forward()) << "\n"
    //           << "cross_fwd local  W1 : " << object1.to_local(cross_fwd) << "\n\n"
    //           << "W1_proj max      W1 : " << OBBox::max_projection(object1, object1.forward()) << "\n"
    //           << "W1 scale         W1 : " << object1.get_proj_scale() << "\n"
    //           << "W1_proj scaled   W1 : " << OBBox::scaled_projection(object1, object1.forward()) << "\n"
    //           << std::endl;

    // std::cout << "W2_proj max      W1 : " << OBBox::max_projection(object1, object2.forward()) << "\n"
    //           << "W2_proj scaled   W1 : " << OBBox::scaled_projection(object1, object2.forward()) << "\n"
    //           << std::endl;

    // std::cout << "cross_proj max    W1 : " << OBBox::max_projection(object1, cross_fwd) << "\n"
    //           << "cross_proj scaled W1 : " << OBBox::scaled_projection(object1, cross_fwd) << "\n"
    //           << std::endl;

    // std::cout << "W1_fwd local     W2 : " << object2.to_local(object1.forward()) << "\n"
    //           << "W2_fwd local     W2 : " << object2.forward_local() << "\n"
    //           << "cross_fwd local  W2 : " << object2.to_local(cross_fwd) << "\n"
    //           << std::endl;

    // std::cout << "W1_proj max      W2 : " << OBBox::max_projection(object2, object1.forward()) << "\n"
    //           << "W1_proj scaled   W2 : " << OBBox::scaled_projection(object2, object1.forward()) << "\n"
    //           << std::endl;
    
    // std::cout << "W2_proj max      W2 : " << OBBox::max_projection(object2, object1.forward()) << "\n"
    //           << "W2 scale         W2 : " << object2.get_proj_scale() << "\n"
    //           << "W2_proj scaled   W2 : " << OBBox::scaled_projection(object2, object1.forward()) << "\n"
    //           << std::endl;

    // std::cout << "cross_proj max    W2 : " << OBBox::max_projection(object2, cross_fwd) << "\n"
    //           << "cross_proj scaled W2 : " << OBBox::scaled_projection(object2, cross_fwd) << "\n"
    //           << std::endl;


    // std::cout << "W1 rho sum    : " << OBBox::scaled_projection(object1, object1.forward()) + OBBox::scaled_projection(object2, object1.forward()) << "\n"
    //           << "W2 rho sum    : " << OBBox::scaled_projection(object2, object2.forward()) + OBBox::scaled_projection(object1, object2.forward()) << "\n"
    //           << "cross rho sum : " << OBBox::scaled_projection(object1, cross_fwd)         + OBBox::scaled_projection(object2, cross_fwd) << "\n"
    //           << std::endl;

    // Vec4 Cavg     = static_cast<Vec4>(object1.center_world()) - object2.center_world();
    // float W1_D    = std::abs(Cavg.dot(object1.forward())) / object1.forward().length();
    // float W2_D    = std::abs(Cavg.dot(object2.forward())) / object2.forward().length();
    // float cross_D = std::abs(Cavg.dot(cross_fwd)) / cross_fwd.length();

    // std::cout << "W1_Cworld    : " << object1.center_world() << "\n"
    //           << "W2_Cworld    : " << object2.center_world() << "\n\n"
    //           << "Cavg         : " << Cavg << "\n"
    //           << "W1_D         : " << W1_D << "\n"
    //           << "W2_D         : " << W2_D << "\n"
    //           << "cross_D      : " << cross_D << "\n"
    //           << std::endl;
}