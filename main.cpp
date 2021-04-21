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
const unsigned int FPS = 24;

void cap_frame_rate(const uint32_t starting_tick){
    const double val = 1000./FPS;
    if(val > SDL_GetTicks() - starting_tick){
        SDL_Delay(val - (SDL_GetTicks() - starting_tick));
    }
}


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

    Uint32 white = SDL_MapRGB(surface_ptr->format, 255, 255, 255);

    SDL_FillRect(surface_ptr, nullptr, white);

    SDL_UpdateWindowSurface(window_ptr);

    SDL_Renderer *renderer_ptr = SDL_CreateRenderer( window_ptr, -1, SDL_RENDERER_ACCELERATED);

    //SDL_SetRenderDrawColor(renderer_ptr, 255, 0, 0, 255);

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            SDL_Rect r;
            r.x = i * (width / 10);
            r.y = j * (height / 10);
            r.w = width / 10;
            r.h = height / 10;

            // Set render color to blue ( rect will be rendered in this color )
            SDL_SetRenderDrawColor(renderer_ptr, i * (255 / 10), j * (255 / 10), 255, 255);

            // Render rect
            SDL_RenderFillRect(renderer_ptr, &r);

        }
    }

    /*
    SDL_Rect r2;
    r2.x = 50;
    r2.y = 50;
    r2.w = 50;
    r2.h = 50;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(renderer_ptr, 255, 0, 0, 255);

    // Render rect
    SDL_RenderFillRect(renderer_ptr, &r);

    SDL_SetRenderDrawColor(renderer_ptr, 255, 255, 0, 255);

    SDL_RenderFillRect(renderer_ptr, &r2);
    */

    // Render the rect to the screen
    SDL_RenderPresent(renderer_ptr);

    SDL_Event event;
    bool running = true;

    while(running){

        Uint32 starting_tick = SDL_GetTicks();

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