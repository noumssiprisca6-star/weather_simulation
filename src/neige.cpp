#include <SDL3/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Taille de la fenêtre
const int WIDTH = 800;
const int HEIGHT = 600;

// Structure flocon de neige
struct SnowFlake {
    float x;
    float y;
    float speedY;
    float driftX;
    int size;
};

// Dessin d'un cercle plein
void DrawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int r)
{
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            if (x * x + y * y <= r * r) {
                SDL_RenderPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

// Dessin de la neige
void DrawNeige(SDL_Renderer* renderer, const std::vector<SnowFlake>& snow)
{
    SDL_SetRenderDrawColor(renderer, 240, 240, 245, 200);
    for (const auto& f : snow) {
        DrawFilledCircle(renderer, (int)f.x, (int)f.y, f.size);
    }
}

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));

    // Initialisation SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) return 1;

    SDL_Window* window = SDL_CreateWindow(
        "Neige réaliste - SDL3",
        WIDTH,
        HEIGHT,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    // Création des flocons
    std::vector<SnowFlake> snow;
    for (int i = 0; i < 200; i++) {
        snow.push_back({
            (float)(rand() % WIDTH),
            (float)(rand() % HEIGHT),
            0.5f + (rand() % 100) / 120.0f,
            ((rand() % 100) / 100.0f - 0.5f) * 0.6f,
            2 + rand() % 3
        });
    }

    bool running = true;
    SDL_Event event;

    // Boucle principale
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        // Fond ciel d'hiver
        SDL_SetRenderDrawColor(renderer, 90, 100, 110, 255);
        SDL_RenderClear(renderer);

        // Animation des flocons
        for (auto& f : snow) {
            f.y += f.speedY;
            f.x += f.driftX + std::sin(f.y * 0.04f) * 0.3f;

            if (f.y > HEIGHT) {
                f.y = rand() % -50;
                f.x = rand() % WIDTH;
            }

            if (f.x < 0) f.x = WIDTH;
            if (f.x > WIDTH) f.x = 0;
        }

        // Dessin de la neige
        DrawNeige(renderer, snow);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}