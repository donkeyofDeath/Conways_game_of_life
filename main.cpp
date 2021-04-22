#include "game_of_life//game_of_life.h"
#include <iostream>
// #include <unistd.h> // for sleep()
#include <chrono>
#include <SDL2/SDL.h>


/**
 *
 */
const unsigned int FPS = 10;
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 600;


void cap_frame_rate(const uint32_t starting_tick){
    const double val = 1000./FPS;
    if(val > SDL_GetTicks() - starting_tick){
        SDL_Delay(val - (SDL_GetTicks() - starting_tick));
    }
}

/**
 *
 * @tparam T1
 * @tparam T2
 * @param renderer_ptr
 * @param grid
 */

/*
template<size_t T1, size_t T2>
void render_grid(SDL_Renderer *renderer_ptr, std::array<std::array<bool, T2>, T1> &grid){

    if(WINDOW_WIDTH % T2 != 0 || WINDOW_HEIGHT % T1 != 0){
        std::cout << "T1 must divide the window height and T2 has to divide the window width.\n";
        return;
    }

    for(int i = 0; i < T2; i++){
        for(int j = 0; j < T1; j++){
            SDL_Rect r;
            r.x = i * (WINDOW_WIDTH / T2);
            r.y = j * (WINDOW_HEIGHT / T1);
            r.w = WINDOW_WIDTH / T2;
            r.h = WINDOW_HEIGHT / T1;

            // Set render color to blue ( rect will be rendered in this color )
            if (grid[i][j]) {
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
 */


int main(int argc, char *argv[])
{
    GameOfLife<100, 100> my_game_of_life(100);

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

    SDL_Surface *surface_ptr = SDL_GetWindowSurface(window_ptr);

    // Uint32 white = SDL_MapRGB(surface_ptr->format, 255, 255, 255);

    // SDL_FillRect(surface_ptr, nullptr, white);

    // SDL_UpdateWindowSurface(window_ptr);

    SDL_Renderer *renderer_ptr = SDL_CreateRenderer( window_ptr, -1, SDL_RENDERER_ACCELERATED);

    // render_rand_rects(renderer_ptr);

    std::array<std::array<bool, 10>, 10> test_grid{};

    test_grid[0][0] = true;

    // render_grid(renderer_ptr, test_grid);

    my_game_of_life.render_current_grid(renderer_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Render the rect to the screen
    SDL_RenderPresent(renderer_ptr);

    SDL_Event event;
    bool running = true;

    // Main game loop
    while(running){

        Uint32 starting_tick = SDL_GetTicks();

        // render_rand_rects(renderer_ptr);
        // Render the rect to the screen

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

    SDL_DestroyWindow(window_ptr);
    SDL_Quit();

    return 0;
}