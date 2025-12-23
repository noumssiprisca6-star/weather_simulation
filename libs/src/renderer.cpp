#include "renderer.h"
#include <stb_image.h>
#include <cmath>
#include <cstdlib>

#include <SDL3/SDL.h>
#include <cmath>


void DrawSoleil(SDL_Renderer* renderer)
{
    // ☀ Soleil
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);

    int sunX = 600;
    int sunY = 120;
    int sunR = 60;

    for (int a = 0; a < 360; a++)
    {
        float rad = a * 3.14159f / 180.0f;
        SDL_RenderPoint(renderer,
            sunX + cos(rad) * sunR,
            sunY + sin(rad) * sunR);
    }

    // ☁ Nuages blancs (overlay)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    static int cloudX = 50;
    cloudX += 1;
    if (cloudX > 800) cloudX = -200;

    int cloudY = 200;

    for (int a = 0; a < 360; a++)
    {
        float rad = a * 3.14159f / 180.0f;
        SDL_RenderPoint(renderer,
            cloudX + cos(rad) * 30,
            cloudY + sin(rad) * 30);
        SDL_RenderPoint(renderer,
            cloudX + 40 + cos(rad) * 35,
            cloudY + sin(rad) * 35);
        SDL_RenderPoint(renderer,
            cloudX + 90 + cos(rad) * 30,
            cloudY + sin(rad) * 30);
    }
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