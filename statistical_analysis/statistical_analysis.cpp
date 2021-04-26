//
// Created by tobias on 26.04.21.
//


#include <iostream>
#include <fstream>
#include "../game_of_life/game_of_life.h"
#include <vector>


int main(){

    const int number_of_time_steps = 2000; // Number of time steps after which the game terminates.
    const unsigned long width = 100; // Width of the game of life grid in cells.
    const unsigned long height = 100; // Height of the game of life grid in cells.

    GameOfLife<height, width> my_game_of_life(number_of_time_steps); // Initialize a game of life object.

    std::vector<double> number_of_living_cells = my_game_of_life.run(); // Save the number of living cells in a vector.

    // Create an ofstream object to write to a file.
    std::ofstream my_file;
    my_file.open ("../statistical_analysis/data.csv");
    my_file << "Number of time steps: " << number_of_time_steps << "; grid width: " << width << " cells; grid height: "
    << height << ".\n";

    // Write the individual density of living numbers to a csv-file.
    for(double m: number_of_living_cells){
        my_file << m << "\n";
    }

    my_file.close(); // Close the file.

    std::cout << "Finished writing data.\n";

    return 0;
}