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

/**
 *
 */
const unsigned int FPS = 24;
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

template<size_t T1, size_t T2>
void render_grid(SDL_Renderer *renderer_ptr, std::array<std::array<double, T2>, T1> grid){

    if(WINDOW_WIDTH % T2 != 0 || WINDOW_HEIGHT % T1 != 0){
        std::cout << "T1 must divide the window height and T2 has to divide the window width.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            SDL_Rect r;
            r.x = i * (WINDOW_WIDTH / 10);
            r.y = j * (WINDOW_HEIGHT / 10);
            r.w = WINDOW_WIDTH / 10;
            r.h = WINDOW_HEIGHT / 10;

            // Set render color to blue ( rect will be rendered in this color )
            SDL_SetRenderDrawColor(renderer_ptr, dist(mt), dist(mt), dist(mt), 255);

            // Render rect
            SDL_RenderFillRect(renderer_ptr, &r);

        }
    }
}


int main(int argc, char *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window_ptr = SDL_CreateWindow("SDL2 Window",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    if(!window_ptr)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface *surface_ptr = SDL_GetWindowSurface(window_ptr);

    Uint32 white = SDL_MapRGB(surface_ptr->format, 255, 255, 255);

    SDL_FillRect(surface_ptr, nullptr, white);

    SDL_UpdateWindowSurface(window_ptr);

    SDL_Renderer *renderer_ptr = SDL_CreateRenderer( window_ptr, -1, SDL_RENDERER_ACCELERATED);

    render_rand_rects(renderer_ptr);

    // Render the rect to the screen
    SDL_RenderPresent(renderer_ptr);

    SDL_Event event;
    bool running = true;

    // Main game loop
    while(running){

        Uint32 starting_tick = SDL_GetTicks();

        render_rand_rects(renderer_ptr);
        // Render the rect to the screen
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