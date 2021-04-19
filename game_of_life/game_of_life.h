//
// Created by tobias on 19.04.21.
//

#ifndef MAIN_CPP_GAME_OF_LIFE_H
#define MAIN_CPP_GAME_OF_LIFE_H


#include <array>
#include <random>


template<size_t dimension_x, size_t dimension_y>
class GameOfLife {

    int number_of_time_steps{};
    std::array<std::array<bool, dimension_x>, dimension_y> grid{};


    explicit GameOfLife(int number_of_time_steps){
        this->number_of_time_steps = number_of_time_steps;
        grid.fill({});
    }


    void initialize_random_grid(){

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, 1);

        for(int i = 0; i < dimension_x; i++){
            for(int j = 0; j < dimension_y; j++){

                bool random_bool = dist(mt);

                grid[i][j] = random_bool;

            }
        }
    }

};


#endif //MAIN_CPP_GAME_OF_LIFE_H
