//
// Created by tobias on 19.04.21.
//

#ifndef MAIN_CPP_GAME_OF_LIFE_H
#define MAIN_CPP_GAME_OF_LIFE_H


#include <array>
#include <random>
#include <iostream>


template<size_t number_of_rows, size_t number_of_columns>
class GameOfLife {

    bool check_grid_point(unsigned long i, unsigned long j){

        bool grid_point_status = current_grid[i][j];
        int sum = 0;
        short start_value_i = -1;
        short start_value_j = -1;
        short end_value_i = 2;
        short end_value_j = 2;

        if(i == 0){
            start_value_i = 0;
        }
        else if(i == number_of_rows - 1){
            end_value_i = 1;
        }
        if(j == 0){
            start_value_j = 0;
        }
        else if(j == number_of_columns - 1){
            end_value_j = 1;
        }

        for(int ii = start_value_i; ii < end_value_i; ii++){
            for(int jj = start_value_j; jj < end_value_j; jj++){
                if(ii != 0 && jj != 0) {
                    sum = sum + (int) current_grid[i + ii][j + jj];
                }
            }
        }
        if(grid_point_status) {
            return (sum == 2 || sum == 3);
        }
        else{
            return (sum == 3);
        }
    }


    void initialize_random_grid(){

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, 1);

        for(int i = 0; i < number_of_columns; i++){
            for(int j = 0; j < number_of_rows; j++){

                bool random_bool = dist(mt);

                current_grid[i][j] = random_bool;
            }
        }
    }


    public:

        int number_of_time_steps{};
        std::array<std::array<bool, number_of_columns>, number_of_rows> current_grid{};
        std::array<std::array<bool, number_of_columns>, number_of_rows> last_grid{};


        explicit GameOfLife(int number_of_time_steps){
            this->number_of_time_steps = number_of_time_steps;
            initialize_random_grid();
        }


        void print_current_grid(){
            for(std::array<bool, number_of_columns> arr: this->current_grid) {
                for (bool i: arr) {
                    std::cout << i << "\t";
                }
                std::cout << "\n";
            }
        }

        void print_last_grid(){
            for(std::array<bool, number_of_columns> arr: this->last_grid) {
                for (bool i: arr) {
                    std::cout << i << "\t";
                }
                std::cout << "\n";
            }
        }


        void update(){

            last_grid = current_grid;

            for(int i = 0; i < number_of_columns; i++){
                for(int j = 0; j < number_of_rows; j++){

                }
            }
        }
};

#endif //MAIN_CPP_GAME_OF_LIFE_H