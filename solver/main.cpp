#include <iostream>
#include <map>
#include <functional>
#include <limits>

void vec_projection();
void vec_cross_prod();
void point_colinear();
void enemy_player_hit_test();
void plane_bisection();
void plane_line_test();

std::map<std::string, std::function<void()>> menu_choices = {
    {"1. Vector projection", vec_projection},
    {"2. Vector cross product", vec_cross_prod},
    {"3. Colinear points", point_colinear},
    {"4. Enemy-player hit testing", enemy_player_hit_test},
    {"5. Planar bisection left-right testing", plane_bisection},
    {"6. Plane-line testing", plane_line_test}
};

int main() {
    for(const auto &entry : menu_choices) {
        std::cout << entry.first << "\n";
    }
    std::cout << std::endl;

    size_t user_choice;

    do {
        std::cout << ">>";
        std::cin >> user_choice;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    } while(user_choice <= 0 || user_choice > menu_choices.size());

    return 0;
}

void vec_projection() {

}

void vec_cross_prod() {

}

void point_colinear() {

}

void enemy_player_hit_test() {

}

void plane_bisection() {

}

void plane_line_test() {

}

