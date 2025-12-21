#include <SDL3/SDL.h>
#include <cmath>
#include <vector>

// CONSTANTES

const int WINDOW_WIDTH  = 800;
const int WINDOW_HEIGHT = 600;
// STRUCTURE NUAGE

struct Cloud {
    float x;
    float y;
    float speed;
};

// DESSIN D'UN CERCLE (UTILISÉ POUR LE SOLEIL ET LES NUAGES)
void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}


// DESSIN DU SOLEIL

void DrawSoleil(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);

    int sunX = 650;
    int sunY = 120;
    int radius = 50;

    drawFilledCircle(renderer, sunX, sunY, radius);

    // Rayons du soleil
    for (int i = 0; i < 360; i += 15) {
        float angle = i * M_PI / 180.0f;
        int x1 = sunX + std::cos(angle) * radius;
        int y1 = sunY + std::sin(angle) * radius;
        int x2 = sunX + std::cos(angle) * (radius + 20);
        int y2 = sunY + std::sin(angle) * (radius + 20);
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }
}


// DESSIN D'UN NUAGE

void drawCloud(SDL_Renderer* renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);

    drawFilledCircle(renderer, x,     y,     25);
    drawFilledCircle(renderer, x + 25,y - 10,30);
    drawFilledCircle(renderer, x + 55,y,     25);
    drawFilledCircle(renderer, x + 25,y + 10,22);
}

// PROGRAMME PRINCIPAL

int main(int argc, char* argv[])
{
    // Initialisation SDL
    if (!SDL_Init(SDL_INIT_VIDEO) ) {
        SDL_Log("Erreur SDL_Init : %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Soleil et nuages animés - SDL3",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    if (!window) {
        SDL_Log("Erreur création fenêtre : %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Erreur création renderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Création des nuages
    std::vector<Cloud> clouds;
    for (int i = 0; i < 8; i++) {
        Cloud c;
        c.x = i * 150.0f;
        c.y = 80.0f + (i % 3) * 60.0f;
        c.speed = 0.3f + (i % 3) * 0.2f;
        clouds.push_back(c);
    }

    bool running = true;
    SDL_Event event;


    // BOUCLE PRINCIPALE
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Fond du ciel (bleu clair)
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);

        // Soleil
        DrawSoleil(renderer);

        // Nuages animés
        for (auto& cloud : clouds) {
            drawCloud(renderer, (int)cloud.x, (int)cloud.y);
            cloud.x += cloud.speed;

            if (cloud.x > WINDOW_WIDTH + 100) {
                cloud.x = -100;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}