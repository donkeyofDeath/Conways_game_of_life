//
// Created by tobias on 04.05.21.
//

#include "../game_of_life/game_of_life.h"
#include "gtest/gtest.h"
#include <array>
#include <vector>

#define NUMBER_OF_ROWS 5
#define NUMBER_OF_COLUMNS 5
#define NUMBER_OF_TIME_STEPS 3

/**
 * This function uses the EXPECT_EQ() function from gtest to compare two 2D boolean arrays of the same length.
 * @param grid1 First grid
 * @param grid2 Second grid.
 */
void compare_grids(std::array<std::array<bool, NUMBER_OF_COLUMNS>, NUMBER_OF_ROWS> grid1,
                  std::array<std::array<bool, NUMBER_OF_COLUMNS>, NUMBER_OF_ROWS> grid2){
    for(int i = 0; i < NUMBER_OF_ROWS; i++){
        for(int j = 0; j < NUMBER_OF_COLUMNS; j++){
            EXPECT_EQ(grid1[i][j], grid2[i][j]);
        }
    }
}

// strcut used as setup before the tests.
struct GameOfLifeTest : testing::Test{

    std::array<std::array<bool, NUMBER_OF_COLUMNS>, NUMBER_OF_ROWS> starting_grid{};
    GameOfLife<NUMBER_OF_ROWS, NUMBER_OF_COLUMNS> gameOfLife;
    GameOfLife<NUMBER_OF_ROWS, NUMBER_OF_COLUMNS> gameOfLife_run;

    explicit GameOfLifeTest(){
        // std::array<std::array<bool, 10>, 10> starting_grid;
        gameOfLife = GameOfLife<NUMBER_OF_ROWS, NUMBER_OF_COLUMNS>(starting_grid);
        gameOfLife_run = GameOfLife<NUMBER_OF_ROWS, NUMBER_OF_COLUMNS>(NUMBER_OF_TIME_STEPS, starting_grid);
    }
    // ~GameOfLifeTest() override = default;
};


/**
 * This function checks if the number of time steps were initialized correctly.
 */
TEST_F(GameOfLifeTest, constructor_test){ //NOLINT
    EXPECT_EQ(gameOfLife_run.number_of_time_steps, NUMBER_OF_TIME_STEPS);
    EXPECT_EQ(gameOfLife.number_of_time_steps, 0);
}


/**
 * This function checks if the grids are initialized correctly.
 */
TEST_F(GameOfLifeTest, grid_initializer_test){ //NOLINT

    std::array<std::array<bool, NUMBER_OF_COLUMNS>, NUMBER_OF_COLUMNS> grid{};

    compare_grids(gameOfLife.current_grid, grid);
    compare_grids(gameOfLife_run.current_grid, grid);
}


/**
 * This test updates the game of life two times and checks whether the returned arrays are correct for each time step.
 */
TEST_F(GameOfLifeTest, update_two_times_test){ //NOLINT

    // Starting_grid.
    std::array<std::array<bool, NUMBER_OF_COLUMNS>, NUMBER_OF_ROWS>
            start_grid = {{{false, true, false, true, false},
                           {false, true, false, true, false},
                           {false, true, false, true, false},
                           {false, true, false, true, false},
                           {false, true, false, true, false}}};

    // Grid after first update.
    std::array<std::array<bool, NUMBER_OF_COLUMNS>, NUMBER_OF_ROWS>
            first_update_grid = {{{false, false, false, false, false},
                                  {true, true, false, true, true},
                                  {true, true, false, true, true},
                                  {true, true, false, true, true},
                                  {false, false, false, false, false}}};

    // Grid after second update.
    std::array<std::array<bool, NUMBER_OF_COLUMNS>, NUMBER_OF_ROWS>
            second_update_grid = {{{false, false, false, false, false},
                                   {true, true, false, true, true},
                                   {false, false, false, false, false},
                                   {true, true, false, true, true},
                                   {false, false, false, false, false}}};


    gameOfLife.current_grid = start_grid;
    gameOfLife.update(); // First update.

    compare_grids(gameOfLife.current_grid, first_update_grid);

    gameOfLife.update(); // Second update.

    compare_grids(gameOfLife.current_grid, second_update_grid);
}


/**
 * This test checks if the vector containing the ratio of living cells for each time step is returned correctly by the
 * run() method.
 */
TEST_F(GameOfLifeTest, run_test){ //NOLINT

    // Starting grid.
    gameOfLife_run.current_grid  = {{{false, true, false, true, false},
                                     {false, true, false, true, false},
                                     {false, true, false, true, false},
                                     {false, true, false, true, false},
                                     {false, true, false, true, false}}};

    std::vector<double> vec = gameOfLife_run.run(); // Run the game of life and save the result.

    EXPECT_DOUBLE_EQ(vec[0], 0.4);
    EXPECT_DOUBLE_EQ(vec[1], 0.48);
    EXPECT_DOUBLE_EQ(vec[2], 0.32);
}


// Run the tests.
int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}