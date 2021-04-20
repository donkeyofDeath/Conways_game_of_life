#include "game_of_life//game_of_life.h"

int main() {

    GameOfLife<10, 10> my_game_of_life(10);

    my_game_of_life.initialize_random_grid();

    my_game_of_life.print_grid();

    return 0;
}
