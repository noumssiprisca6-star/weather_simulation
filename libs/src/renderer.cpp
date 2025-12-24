#include "renderer.h"
#include <stb_image.h>
#include <cmath>
#include <cstdlib>
#include"../libs/SDL3/SDL3_image/SDL_image.h"

#include <SDL3/SDL.h>
#include <cmath>

SDL_Texture* soleiltexture = nullptr;
//la fonction permettant l'ajout de l'image aui represente mon soleil
void loadsoleilTexture(SDL_Renderer*renderer){
    SDL_Surface* surface = IMG_Load("assets/imo.jpg");
    if(!surface){
        std::cerr << "Erreur chargement soleil : " <<std::endl;
    }
    soleiltexture = SDL_CreateTextureFromSurface(renderer , surface );
    SDL_DestroySurface(surface);
}
//dessin de mon soleil en fonction de mon image
void DrawSoleil(SDL_Renderer* renderer)
{
    if(!soleiltexture){
        return;
    }
    SDL_FRect dst;
    dst.x = 300;
    dst.y = 150;
    dst.w = 200;
    dst.h = 200;
    SDL_RenderTexture(renderer , soleiltexture, nullptr, &dst );
}

//  ORAGE (NUAGES + PLUIE)
void DrawOrage(SDL_Renderer* renderer)
{
    // Ciel sombre
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderClear(renderer);

    // Nuages gris
    SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);

    for (int c = 0; c < 3; c++) {
        int baseX = 150 + c * 200;
        int baseY = 120;

        for (int i = 0; i < 3; i++) {
            int cx = baseX + i * 40;
            int cy = baseY + (i % 2) * 10;
            int r  = 30;

            for (int a = 0; a < 360; a++) {
                float rad = a * M_PI / 180.0f;
                int x = cx + cos(rad) * r;
                int y = cy + sin(rad) * r;
                SDL_RenderPoint(renderer, x, y);
            }
        }
    }

}