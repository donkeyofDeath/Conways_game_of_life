#include "game_of_life//game_of_life.h"
#include <iostream>
#include <unistd.h> // for sleep()

int main() {

    int number_of_time_steps = 100;

    GameOfLife<5, 5> my_game_of_life(number_of_time_steps);

    my_game_of_life.print_current_grid();

    for(int i = 0; i < number_of_time_steps; i++){
        my_game_of_life.update();

        my_game_of_life.print_current_grid();
        sleep(1);
        for(int i = 0; i < 100; i++){
            std::cout << "\b" << std::flush;
        }
    }

    return 0;
}
