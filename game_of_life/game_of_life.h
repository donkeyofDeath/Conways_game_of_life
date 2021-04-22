//
// Created by tobias on 19.04.21.
//

#ifndef MAIN_CPP_GAME_OF_LIFE_H
#define MAIN_CPP_GAME_OF_LIFE_H


#include <array>
#include <random>
#include <iostream>
#include <SDL2/SDL.h>


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
         * @param number_of_time_steps
         */
        explicit GameOfLife(int number_of_time_steps){
            this->number_of_time_steps = number_of_time_steps;
            initialize_random_grid();
        }


        /**
        *
        * @param i
        * @param j
        * @return
        */
        bool check_grid_point(const int i, const int j){

            bool grid_point_status = this->last_grid[i][j];
            int sum = 0;

            for(int ii = -1; ii <= 1; ii++){
                if(i + ii < 0 || i + ii > number_of_rows - 1){
                    continue;
                }
                for(int jj = -1; jj <= 1; jj++){
                    if(j + jj < 0 || j + jj > number_of_columns - 1){
                        continue;
                    }
                    else if(!(ii == 0 && jj == 0)){
                        sum += this->last_grid[i + ii][j + jj];
                    }
                }
            }
            if(grid_point_status){
                return (sum == 2 || sum == 3);

            }
            else{
                return (sum == 3);
            }
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
         * @param renderer_ptr
         * @param window_width
         * @param window_height
         */
        void render_current_grid(SDL_Renderer *renderer_ptr, const int window_width, const int window_height){

            if(window_width % number_of_columns != 0 || window_height % number_of_rows != 0){
                std::cout << "T1 must divide the window height and T2 has to divide the window width.\n";
                return;
            }

            for(int i = 0; i < number_of_columns; i++){
                for(int j = 0; j < number_of_rows; j++){

                    SDL_Rect r;
                    r.x = i * (window_width / number_of_columns);
                    r.y = j * (window_height / number_of_rows);
                    r.w = window_width / number_of_columns;
                    r.h = window_height / number_of_rows;

                    // Set render color to blue ( rect will be rendered in this color )
                    if (current_grid[i][j]){
                        SDL_SetRenderDrawColor(renderer_ptr, 0, 255, 0, 255);
                    }
                    else{
                        SDL_SetRenderDrawColor(renderer_ptr, 0, 0, 0, 255);
                    }
                    // Render rect
                    SDL_RenderFillRect(renderer_ptr, &r);

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