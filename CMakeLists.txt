cmake_minimum_required(VERSION 3.17)
project(Conways_game_of_life)

set(CMAKE_CXX_STANDARD 14)

# Added by me
find_package(SDL2 REQUIRED SDL2)

add_executable(Conways_game_of_life main.cpp game_of_life/game_of_life.h)

# Added by me
target_link_libraries(Conways_game_of_life PRIVATE SDL2)

add_executable(statistical_analysis statistical_analysis/statistical_analysis.cpp)