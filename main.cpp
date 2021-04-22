#include "game_of_life//game_of_life.h"
#include <iostream>
// #include <unistd.h> // for sleep()
#include <chrono>
#include <SDL2/SDL.h>

// TODO: Add documentation for main function.
// TODO: Add tests.
// TODO: Add Error handling for the SDL functions.

/**
 *
 */
const unsigned int FPS = 10;
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;


void cap_frame_rate(const uint32_t starting_tick){
    const double val = 1000./FPS;
    if(val > SDL_GetTicks() - starting_tick){
        SDL_Delay(val - (SDL_GetTicks() - starting_tick));
    }
}


int main(int argc, char *argv[])
{
    GameOfLife<900, 900> my_game_of_life(100);

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window_ptr = SDL_CreateWindow("Conway\'s game of life",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    if(!window_ptr)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Renderer *renderer_ptr = SDL_CreateRenderer( window_ptr, -1, SDL_RENDERER_ACCELERATED);

    my_game_of_life.render_current_grid(renderer_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Render the rect to the screen
    SDL_RenderPresent(renderer_ptr);

    SDL_Event event;
    bool running = true;

    // Main game loop
    while(running){

        Uint32 starting_tick = SDL_GetTicks();

        my_game_of_life.update();
        my_game_of_life.render_current_grid(renderer_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_RenderPresent(renderer_ptr);

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
                break;
            }
        }
        cap_frame_rate(starting_tick);
    }

    // Destroy everything and quit the game.
    SDL_DestroyRenderer(renderer_ptr);
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();

    return 0;
}