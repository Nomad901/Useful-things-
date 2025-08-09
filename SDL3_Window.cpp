#include <iostream>
#include <SDL3/SDL.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720


int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("Window", WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    bool active{ true };
    while (active)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT ||
                event.key.key == SDLK_ESCAPE)
            {
                active = false;
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);



        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
