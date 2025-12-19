#include <SDL3/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Taille de la fenêtre
const int WIDTH = 800;
const int HEIGHT = 600;

// Structure nuage
struct Cloud {
    float x;
    float y;
    float speed;
};

// Structure goutte de pluie
struct RainDrop {
    float x;
    float y;
    float speed;
};

// Dessin d'un cercle plein
void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int r)
{
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            if (x * x + y * y <= r * r) {
                SDL_RenderPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

// Dessin de nuage au ton gris  lourd
void drawCloud(SDL_Renderer* renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);//gris foncé
    drawFilledCircle(renderer, x, y, 55);
    drawFilledCircle(renderer, x + 150, y - 10, 70);
    drawFilledCircle(renderer, x + 90, y+30, 65);
    drawFilledCircle(renderer, x + 220, y + 10, 55);
    drawFilledCircle(renderer , x +280, y+20 ,45);
}

// Dessin de la pluie
void drawRain(SDL_Renderer* renderer, const std::vector<RainDrop>& rain)
{
    SDL_SetRenderDrawColor(renderer, 170, 170, 255, 255) ;//bleue
    for (const auto& drop : rain) {
        SDL_RenderLine(renderer, (int)drop.x, (int)drop.y,
                       (int)(drop.x - 5), (int)(drop.y + 12));
    }
}

// Dessin d'un éclair
void drawLightning(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int x = rand() % WIDTH;
    int y = 0;

    for (int i = 0; i < 6; i++) {
        int nx = x + (rand() % 40 - 20);
        int ny = y + 60;
        SDL_RenderLine(renderer, x, y, nx, ny);
        x = nx;
        y = ny;
    }
}

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));

    // Initialisation SDL
    if (!SDL_Init(SDL_INIT_VIDEO) ) return 1;

    SDL_Window* window = SDL_CreateWindow(
        "Pluie, orage et vent - SDL3",
        WIDTH, HEIGHT, 0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    // Création des nuages
    std::vector<Cloud> clouds;
    for (int i = 0; i < 5; i++) {
        clouds.push_back({ (float)(i * 240), 90.0f + i % 2 * 60.0f, 0.5f + i * 0.1f });
    }
    //deuxieme couche de nuage tres chargé
    for(auto& c : clouds ){
        drawCloud(renderer , (int)c.x - 120, (int)c.y +90);
    }

    // Création de la pluie
    std::vector<RainDrop> rain;
    for (int i = 0; i < 300; i++) {
        rain.push_back({ (float)(rand() % WIDTH), (float)(rand() % HEIGHT), 6.0f + rand() % 4 });
    }

    bool running = true;
    bool lightning = false;
    int lightningTimer = 0;
    SDL_Event event;

    // Boucle principale
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }

        // Fond ciel sombre
        SDL_SetRenderDrawColor(renderer, 70, 70, 90, 255);
        SDL_RenderClear(renderer);

        // Vent + nuages
        for (auto& c : clouds) {
            drawCloud(renderer, (int)c.x, (int)c.y);
            c.x += c.speed;
            if (c.x > WIDTH + 100) c.x = -120;
        }

        // Pluie + vent
        for (auto& drop : rain) {
            drop.y += drop.speed;
            drop.x -= 1.2f;
            if (drop.y > HEIGHT) {
                drop.y = rand() % -100;
                drop.x = rand() % WIDTH;
            }
        }
        drawRain(renderer, rain);

        // Gestion éclairs
        if (rand() % 200 == 0) {
            lightning = true;
            lightningTimer = 5;
        }

        if (lightning) {
            drawLightning(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 40);
            SDL_RenderFillRect(renderer, NULL);
            lightningTimer--;
            if (lightningTimer <= 0) lightning = false;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}