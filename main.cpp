#include "game_of_life//game_of_life.h"
#include <iostream>
// #include <unistd.h> // for sleep()
#include <chrono>

using namespace std::chrono;

int main() {

    int number_of_time_steps = 100;

    GameOfLife<500, 500> my_game_of_life(number_of_time_steps);

    auto start = high_resolution_clock::now();

    my_game_of_life.update();

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    // To get the value of duration use the count()
    // member function on the duration object
    std::cout << duration.count() << std::endl;

    return 0;
}
