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
 * Game of life object. More information to Conway's game of life can be found at:
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 * @tparam number_of_rows number of rows in the game of life.
 * @tparam number_of_columns number of columns in the game of life.
 */
template<size_t number_of_rows, size_t number_of_columns>
class GameOfLife {

    /**
     *Initializes the grid randomly and uniformly with 0s and with a probability of 1/2.
     */
    void initialize_random_grid() {

        // Create random number generator.
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, 1);

        // Loop through the grid and initialize it.
        for (int i = 0; i < number_of_rows; i++) {
            for (int j = 0; j < number_of_columns; j++) {

                bool random_bool = dist(mt);

                current_grid[i][j] = random_bool;
            }
        }
    }


public:

    // Underlying grids representing the game of life in the current and last time step.
    std::array<std::array<bool, number_of_columns>, number_of_rows> current_grid{};
    std::array<std::array<bool, number_of_columns>, number_of_rows> last_grid{};


    /**
     *Constructor for the game of life objects. In this constructor the grid is initialized randomly.
     */
    explicit GameOfLife() {
        initialize_random_grid();
    }


    /**
    *Checks the number of living neighbours of a grid point given by the indices i and j. The grid point is taken from
    *the last grid and is used to update the current grid.
    * @param i row index in the last grid.
    * @param j column index in the last grid.
    * @return Returns the status of the cell with the indices i and j in the nest time step.
    */
    bool check_grid_point(const int i, const int j) {

        bool grid_point_status = this->last_grid[i][j]; // Save the grid status.
        int number_of_living_neighbors = 0; // Sum representing the number of living cells surrounding the given cell.

        // Loop through all the row neighbors.
        for (int ii = -1; ii <= 1; ii++) {

            // If the row index is out of bounds, ignore it.
            if (i + ii < 0 || i + ii > number_of_rows - 1) {
                continue;
            }
            // Loop through all the column indices.
            for (int jj = -1; jj <= 1; jj++) {

                // If the column index is out bounds, ignore it.
                if (j + jj < 0 || j + jj > number_of_columns - 1) {
                    continue;
                }
                // Ignore the cell itself.
                else if (!(ii == 0 && jj == 0) && this->last_grid[i + ii][j + jj]) {
                    number_of_living_neighbors++; // Increase the number of living neighbors if a neighbor is alive.
                }
            }
        }
        // Check if a cell is alive.
        if (grid_point_status) {
            // If a living cell has 2 or 3 neighbors it stays alive.
            return (number_of_living_neighbors == 2 || number_of_living_neighbors == 3);
        }
        else {
            // If a cell is dead it gets born if it has 3 living neighbors.
            return (number_of_living_neighbors == 3);
        }
    }


    /*
     *Print the current grid to the console.
     */
    void print_current_grid() {
        for (std::array<bool, number_of_columns> arr: this->current_grid) {
            for (bool i: arr) {
                std::cout << i << "\t";
            }
            std::cout << "\n";
        }
    }


    /**
     *Print the last grid to the console.
     */
    void print_last_grid() {
        for (std::array<bool, number_of_columns> arr: this->last_grid) {
            for (bool i: arr) {
                std::cout << i << "\t";
            }
            std::cout << "\n";
        }
    }


    /**
     *Update the current grid using the rules of Conway's game of life.
     */
    void update() {

        last_grid = current_grid;

        // Loop through the current grid and update the current grid.
        for (int i = 0; i < number_of_rows; i++) {
            for (int j = 0; j < number_of_columns; j++) {
                current_grid[i][j] = check_grid_point(i, j);
            }
        }
    }


    /**
     * This function checks checks where the last and current grid differ and renders the new rectangles. The size of
     * the rectangles is determined by the number of rows and columns relative to window height and width. After the
     * grid is rendered the SDL_RendererPresent method has to be called.
     * @param renderer_ptr An SDL_Renderer object pointer, which is used to render the grid.
     * @param window_width Window width in pixels.
     * @param window_height Window height in pixels.
     */
    void render_grid(SDL_Renderer *renderer_ptr, const int window_width, const int window_height) {

        // Check if the window height and width are divided by the number of columns and rows.
        if (window_width % number_of_columns != 0 || window_height % number_of_rows != 0) {
            std::cout << "The number of columns must divide the window height and the number of rows has to divide the"
                         "window width.\n";
            std::cout << "window_width % number_of_columns: " << window_width % number_of_columns << "\n";
            std::cout << "window_height % number_of_rows: " << window_height % number_of_rows << "\n";
            return;
        }

        SDL_Rect r; // defines a rect which is then drawn on the screen.

        // Define the RGBA colors.
        uint8_t green = 0;
        const uint8_t red = 0;
        const uint8_t blue = 0;
        const uint8_t opacity = 255;

        // Define rectangle height and width relative to the window height and width.
        const int rect_width = window_width / number_of_columns;
        const int rect_height = window_height / number_of_rows;

        for (int i = 0; i < number_of_rows; i++) {
            for (int j = 0; j < number_of_columns; j++) {

                /* The != operator serves as an EXOR here to check if a grid value has changed. Only if the value has
                a new rect will be rendered. */
                if (current_grid[i][j] != last_grid[i][j]) {

                    // Define the rectangle parameters.
                    r.x = j * rect_width;
                    r.y = i * rect_height;
                    r.w = rect_width;
                    r.h = rect_height;

                    // Set the rectangle color to green if the cell is alive, if not set it to black.
                    green = current_grid[i][j]? 255 : 0;

                    // Render the colors and do some error handling.
                    if(SDL_SetRenderDrawColor(renderer_ptr, red, green, blue, opacity)) { //Render drawing color.
                        std::cout << "Error while rendering the rectangle color: " << SDL_GetError() << "\n";
                    }

                    // Render the rectangle.
                    if(SDL_RenderFillRect(renderer_ptr, &r)) {
                        std::cout << "Error while rendering the rectangle: " << SDL_GetError() << "\n";
                    }
                }
                // If the grid point didn't change do nothing
                else {
                    continue;
                }
            }
        }
    }
};

#endif //MAIN_CPP_GAME_OF_LIFE_H