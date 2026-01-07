#include"../src/SDL3/SDL3_image/SDL_image.h"
#include <SDL.h>
#include <iostream>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erreur de SDL_init: "<<SDL_GetError()<<std::endl;
        return 1;
    }

    //creation de la fenetre SDL
    SDL_Window* window = SDL_CreateWindow("app_image", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Erreur de creation de la fenetre: "<<SDL_GetError()<<std::endl;
        return 1;
    }

    //creation du moteur de rendu
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Erreur de creation du renderer: "<<SDL_GetError()<<std::endl;
        return 1;
    }

    //creation de la surface
    SDL_Surface* surface = IMG_Load("assets/imo.jpg");
    //creation de la texture a partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    //destruction de la surface. car on en a plus besoin
    SDL_DestroySurface(surface);

    //variables de la boucles principale
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running =false;
            }
        }
        //chargement de la texture dans le renderer
        SDL_RenderTexture(renderer, texture,nullptr , nullptr);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
