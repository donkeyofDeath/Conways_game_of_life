#include "game_of_life//game_of_life.h"
#include <iostream>
// #include <unistd.h> // for sleep()
#include <chrono>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

// using namespace std::chrono;

/*
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
*/
int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480,
                                          0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);
}