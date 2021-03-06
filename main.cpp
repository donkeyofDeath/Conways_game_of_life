#include "game_of_life//game_of_life.h"
#include <iostream>
#include <SDL2/SDL.h>


// TODO: Add tests.


const unsigned int FPS = 30; // FPS at which the game is running.
const int WINDOW_WIDTH = 800; // Height of the game window in pixels.
const int WINDOW_HEIGHT = 800; // Width of the game window in pixels.
const unsigned long NUMBER_OF_ROWS = 400;  // Number of rows in the game of life.
const unsigned long NUMBER_OF_COLUMNS = 400; // Number of columns in the game of life.


/**
 * This function caps the frame rate at the rate fps.
 * @param fps frame per second at which the game loop should run.
 * @param starting_tick The starting tick of the game loop.
 */
void cap_frame_rate(const unsigned int fps,const Uint32 starting_tick){

    const double seconds_per_frame = 1000./fps; // How much milliseconds a frame lasts at a given fps.

    // Check if there is still time left in the frame.
    if(seconds_per_frame > SDL_GetTicks() - starting_tick){
        SDL_Delay(seconds_per_frame - (SDL_GetTicks() - starting_tick));  // Sleep the according amount.
    }
}


/**
 * The main game loop.
 * @param argc I don't know what this does. I just read that you need it for SDL.
 * @param argv I don't know what this does. I just read that you need it for SDL
 * @return 0 = EXIT_SUCCESS, everything else is an error code.
 */
int main() {

    // Initializes the SDL library and prints out an error if one occurred.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Failed to initialize the SDL2 library, Error: " << SDL_GetError() << "\n"; // Print out the error.
        return -1;
    }


    // Declare the game window.
    /*SDL_Window *window_ptr = SDL_CreateWindow("Conway\'s game of life",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);*/

    SDL_Window *window_ptr = SDL_CreateWindow("Conway\'s game of life",
                                              200,
                                              200,
                                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    // Check if an error occurred during the creation of the game window.
    if(!window_ptr){
        std::cout << "Failed to create window, Error: " << SDL_GetError() << "\n"; // Print out the error.
        return -1;
    }

    // Create the renderer.
    SDL_Renderer *renderer_ptr = SDL_CreateRenderer( window_ptr, -1, SDL_RENDERER_ACCELERATED);

    // Check if an error occurred during the creation of the renderer.
    if(!renderer_ptr){
        std::cout << "Failed to create the renderer, Error: " << SDL_GetError() << "\n"; // Print out the error.
        return -1;
    }


    // Render a black screen.
    if(SDL_SetRenderDrawColor(renderer_ptr, 0, 0, 0, 255)){
        std::cout << "An error occurred when drawing the color: " << SDL_GetError() << "\n"; // Error handling.
    }
    if(SDL_RenderClear(renderer_ptr)){
        std::cout << "An error occurred when clearing the screen: " << SDL_GetError() << "\n"; // Error handling.
    }
    SDL_RenderPresent(renderer_ptr);

    bool running = true; // Define running variable, which is used for quitting the game.

    GameOfLife<NUMBER_OF_ROWS, NUMBER_OF_COLUMNS> my_game_of_life; // Initialize a game of life object.
    if(my_game_of_life.render_grid(renderer_ptr, WINDOW_WIDTH, WINDOW_HEIGHT)){ // Render grid for the first time.
        std::cout << "An error occurred within the game of life class when rendering the screen.";
        running = false;
    }
    SDL_RenderPresent(renderer_ptr); // Render the rect to the screen.
    SDL_Event event; // Define SDL event, which used for quitting the game.

    // Main game loop
    while(running){

        Uint32 starting_tick = SDL_GetTicks(); // Starting tick is needed for capping the frame rate.

        // Render the updated game.
        my_game_of_life.update();
        if(my_game_of_life.render_grid(renderer_ptr, WINDOW_WIDTH, WINDOW_HEIGHT)){
            std::cout << "An error occurred within the game of life class when rendering the screen.";
            running = false;
            break;
        }
        SDL_RenderPresent(renderer_ptr);

        while(SDL_PollEvent(&event)){ // Loop used for quitting the game.
            if(event.type == SDL_QUIT){
                running = false;
                break;
            }
        }

        cap_frame_rate(FPS, starting_tick); // Cap the frame rate.

    }

    // Destroy everything and quit the game.
    SDL_DestroyRenderer(renderer_ptr);
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();

    return 0;
}