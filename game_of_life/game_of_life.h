//
// Created by tobias on 19.04.21.
//

#ifndef MAIN_CPP_GAME_OF_LIFE_H
#define MAIN_CPP_GAME_OF_LIFE_H


#include <array>
#include <random>
#include <iostream>

/**
 *
 * @tparam number_of_rows
 * @tparam number_of_columns
 */
template<size_t number_of_rows, size_t number_of_columns>
class GameOfLife {

    /**
     *
     */
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


        /**
        *
        * @param i
        * @param j
        * @return
        */
        bool check_grid_point(int i, int j){

            bool grid_point_status = this->last_grid[i][j];
            // std::cout << grid_point_status << "";
            int sum = 0;

            std::cout << "\n " << i << "," << j << ":" << "\t";

            for(int ii = -1; ii <= 1; ii++){
                if(i + ii < 0 || i + ii > number_of_rows - 1){
                    // std::cout << "aborted_i:" << ii+i << " ";
                    continue;
                }
                for(int jj = -1; jj <= 1; jj++){
                    if(j + jj < 0 || j + jj > number_of_columns - 1){
                        // std::cout << "aborted_j:" << j + jj << " ";
                        continue;
                    }
                    else if(!(ii == 0 && jj == 0)){
                        std::cout << i + ii << "," << j + jj << " ";
                        sum += this->last_grid[i + ii][j + jj];
                    }
                }
            }
            if(grid_point_status){
                // std::cout << i << "," << j << " sum:" << sum << "\t";
                return (sum == 2 || sum == 3);

            }
            else{
                // std::cout << i << "," << j << "\t";
                // std::cout << i << "," << j << " sum:" << sum << "\t";
                return (sum == 3);
            }
        }


        /**
         *
         * @param number_of_time_steps
         */
        explicit GameOfLife(int number_of_time_steps){
            this->number_of_time_steps = number_of_time_steps;
            initialize_random_grid();
        }


        /*
         *
         */
        void print_current_grid(){
            for(std::array<bool, number_of_columns> arr: this->current_grid) {
                for (bool i: arr) {
                    std::cout << i << "\t";
                }
                std::cout << "\n";
            }
        }


        /**
         *
         */
        void print_last_grid(){
            for(std::array<bool, number_of_columns> arr: this->last_grid) {
                for (bool i: arr) {
                    std::cout << i << "\t";
                }
                std::cout << "\n";
            }
        }


        /**
         *
         */
        void update(){

            last_grid = current_grid;

            for(int i = 0; i < number_of_rows; i++){
                for(int j = 0; j < number_of_columns; j++){
                    current_grid[i][j] = check_grid_point(i, j);
                }
            }
        }


        /**
         *
         */
        void run(){
            for(int i = 0; i < number_of_time_steps; i++){
                update();
            }
        }
};

#endif //MAIN_CPP_GAME_OF_LIFE_H