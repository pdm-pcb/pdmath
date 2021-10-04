#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <limits>

#include "pdmath/Vector.hpp"

void vec_projection();
void vec_cross_prod();
void point_colinear();
void enemy_player_hit_test();
void plane_bisection();
void plane_line_test();

std::vector<std::pair<std::string, std::function<void()>>>
menu_choices = {
    std::make_pair("1. Vector projection", vec_projection),
    std::make_pair("2. Vector cross product", vec_cross_prod),
    std::make_pair("3. Colinear points", point_colinear),
    std::make_pair("4. Enemy-player hit testing", enemy_player_hit_test),
    std::make_pair("5. Planar bisection left-right testing", plane_bisection),
    std::make_pair("6. Plane-line testing", plane_line_test),
};

int main() {
    int user_choice;

    while(true) {
        for(const auto &entry : menu_choices) {
            std::cout << entry.first << "\n";
        }

        do {
            std::cout << ">>";
            scanf("%d", &user_choice);
        } while(user_choice <= 0 ||
                user_choice > static_cast<int>(menu_choices.size()));

        auto chosen_function = menu_choices.begin() + (user_choice - 1);
        (chosen_function->second)();

        std::cout << std::endl;
    }
    return 0;
}

void vec_projection() {
    float x, y, z;
    std::cout << "Define v(x, y, z):" << std::endl;
    std::cout << ">>";
    scanf("%f, %f, %f", &x, &y, &z);
    pdm::vec3 v(x, y, z);

    std::cout << "Define w(x, y, z):" << std::endl;
    std::cout << ">>";
    scanf("%f, %f, %f", &x, &y, &z);
    pdm::vec3 w(x, y, z);

    std::cout << v.project_onto(w) << std::endl;
}

void vec_cross_prod() {
    float x, y, z;
    std::cout << "Define v(x, y, z):" << std::endl;
    std::cout << ">>";
    scanf("%f, %f, %f", &x, &y, &z);
    pdm::vec3 v(x, y, z);

    std::cout << "Define w(x, y, z):" << std::endl;
    std::cout << ">>";
    scanf("%f, %f, %f", &x, &y, &z);
    pdm::vec3 w(x, y, z);

    std::cout << v.cross(w) << std::endl;
}

void point_colinear() {
    float x, y, z;
    std::cout << "Define a(x, y, z):" << std::endl;
    std::cout << ">>";
    scanf("%f, %f, %f", &x, &y, &z);
    pdm::point a(x, y, z);

    std::cout << "Define b(x, y, z):" << std::endl;
    std::cout << ">>";
    scanf("%f, %f, %f", &x, &y, &z);
    pdm::point b(x, y, z);

    std::cout << "Define c(x, y, z):" << std::endl;
    std::cout << ">>";
    scanf("%f, %f, %f", &x, &y, &z);
    pdm::point c(x, y, z);

    std::cout << a.are_collinear(b, c) << std::endl;
}

void enemy_player_hit_test() {

}

void plane_bisection() {

}

void plane_line_test() {

}

