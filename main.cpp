#include "game_of_life//game_of_life.h"
#include <iostream>
// #include <unistd.h> // for sleep()
#include <chrono>
#include <SDL2/SDL.h>

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
int main(int argc, char *argv[])
{
    const int width = 680;
    const int height = 480;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window_ptr = SDL_CreateWindow("SDL2 Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width
                                          , height,SDL_WINDOW_RESIZABLE);

    if(!window_ptr)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface *surface_ptr = SDL_GetWindowSurface(window_ptr);

    uint32_t white = SDL_MapRGB(surface_ptr->format, 255, 255, 255);

    SDL_FillRect(surface_ptr, nullptr, white);

    SDL_UpdateWindowSurface(window_ptr);

    SDL_Event event;
    bool running = true;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
                break;
            }
        }
    }

    SDL_DestroyWindow(window_ptr);
    SDL_Quit();

    return 0;
}