#include "game_of_life//game_of_life.h"
#include <iostream>

int main() {

    GameOfLife<5, 5> my_game_of_life(10);

    my_game_of_life.update();

    std::cout << "\n";

    std::cout << "Last grid:\n";

    my_game_of_life.print_last_grid();

    std::cout << "\n";

    std::cout << "Current grid:\n";

    my_game_of_life.print_current_grid();

    return 0;
}
