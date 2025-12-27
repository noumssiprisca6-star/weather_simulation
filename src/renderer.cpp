#include "../include/renderer.h"
#include <stb_image.h>
#include <cmath>
#include <cstdlib>
#include<vector>
#include"../src/SDL3/SDL3_image/SDL_image.h"

#include <SDL3/SDL.h>
#include <cmath>



//elelment
struct element {
    float x , y;

};

// STRUCTURE NUAGE

struct Cloud {
    float x;
    float y;
    float speed;
};



Cloud clouds[6] = {
    { -150.0f, 100, 0.6f },
    { -300.0f, 150, 1.0f },
    { -500.0f, 90,  0.9f },
    {-200.0f , 92 , 1.2f},
    {-150.0f , 120 ,0.8f },
    {-400.0f , 102 , 0.7f}
};

static std::vector<element> rainDrops ;
static std::vector<element> snowFlakes;
bool initRenderer(SDL_Window* window, SDL_Renderer* renderer){
    renderer = SDL_CreateRenderer(window , nullptr);
    return renderer != nullptr;

}
void cleanupRenderer(SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
}

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

void DrawCloud(SDL_Renderer* renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);

    drawFilledCircle(renderer, x,     y,     25);
    drawFilledCircle(renderer, x + 25,y - 10,30);
    drawFilledCircle(renderer, x + 55,y,     25);
    drawFilledCircle(renderer, x + 25,y + 10,22);
}
    
// la scene d'animation des nuages 


void RenderScene(SDL_Renderer* renderer){
// Création des nuages
//animation
    for (int i = 0; i < 8 ; i++) {
        clouds[i].x += clouds[i].speed;
        if (clouds[i].x > 900) {
            clouds[i].x = -200;
        }

        DrawCloud(renderer, (int)clouds[i].x, clouds[i].y);
    }

    SDL_RenderPresent(renderer);

}
    

//pour dessiner la pluie 
void DrawPluie ( SDL_Renderer* renderer ){
    SDL_SetRenderDrawColor(renderer,100,100,255,255);
   for (int i = 0; i< 200; i++){
    int x = rand()% 800 ;
    int y = rand() % 600;
    SDL_RenderLine(renderer , x , y , x  , y + 10);
   }    
   }
   

 
#define NB_PLUIE 400   // Nombre de gouttes de pluie
#define NB_ECLAIR 3    // Nombre d'éclairs
#define NB_NUAGES 5    // Nombre de nuages

void DrawOrage(SDL_Renderer* renderer, int width, int height)
{
    // --- Pluie ---
    static int pluieX[NB_PLUIE];
    static float pluieY[NB_PLUIE];  // float pour chute douce
    static int initPluie = 0;

    // --- Éclairs ---
    static int eclairX[NB_ECLAIR];
    static int eclairY[NB_ECLAIR];
    static int eclairTimer[NB_ECLAIR];
    static int initEclair = 0;

    // --- Nuages ---
    static int nuageX[NB_NUAGES];
    static int nuageY[NB_NUAGES];
    static int initNuage = 0;

    // Initialisation pluie
    if (initPluie == 0)
    {
        for (int i = 0; i < NB_PLUIE; i++)
        {
            pluieX[i] = rand() % width;
            pluieY[i] = rand() % height;
        }
        initPluie = 1;
    }

    // Initialisation éclairs
    if (initEclair == 0)
    {
        for (int i = 0; i < NB_ECLAIR; i++)
        {
            eclairX[i] = rand() % width;
            eclairY[i] = rand() % (height / 2);
            eclairTimer[i] = rand() % 60;
        }
        initEclair = 1;
    }

    // Initialisation nuages
    if (initNuage == 0)
    {
        for (int i = 0; i < NB_NUAGES; i++)
        {
            nuageX[i] = rand() % width;
            nuageY[i] = 50 + rand() % 100;
        }
        initNuage = 1;
    }

    // --- Fond gris sombre ---
    SDL_SetRenderDrawColor(renderer, 50, 50, 60, 255);
    SDL_RenderClear(renderer);

    // --- Nuages épais gris foncé ---
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
    for (int i = 0; i < NB_NUAGES; i++)
    {
        // Plusieurs ellipses superposées pour épaissir le nuage
        for (int nx = -50; nx <= 50; nx += 20)
        {
            for (int ny = -25; ny <= 25; ny += 15)
            {
                for (int dx = -30; dx <= 30; dx++)
                {
                    for (int dy = -15; dy <= 15; dy++)
                    {
                        if ((dx*dx)/2 + dy*dy <= 225)
                        {
                            SDL_RenderPoint(renderer, nuageX[i]+nx+dx, nuageY[i]+ny+dy);
                        }
                    }
                }
            }
        }
    }

    // --- Pluie douce ---
    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    for (int i = 0; i < NB_PLUIE; i++)
    {
        SDL_RenderLine(renderer, pluieX[i], static_cast<int>(pluieY[i]), pluieX[i], static_cast<int>(pluieY[i])+5);
        pluieY[i] += 1.5f;               // chute lente
        if (pluieY[i] > height) pluieY[i] = 0; // remonter
    }

    // --- Éclairs ---
    SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
    for (int i = 0; i < NB_ECLAIR; i++)
    {
        eclairTimer[i]++;
        if (eclairTimer[i] > 60)
        {
            int startX = eclairX[i];
            int startY = eclairY[i];
            for (int j = 0; j < 10; j++)
            {
                int offsetX = (rand() % 11) - 5;
                int offsetY = 5 + rand() % 5;
                SDL_RenderLine(renderer, startX, startY, startX+offsetX, startY+offsetY);
                startX += offsetX;
                startY += offsetY;
            }
            eclairTimer[i] = 0;
            eclairX[i] = rand() % width;
            eclairY[i] = rand() % (height / 2);
        }
    }
}

//la fonction pour dessiner de la neige 

#define NB_NEIGE 300

void DrawNeige(SDL_Renderer* renderer, int width, int height)
{
    /* Données persistantes */
    static int x[NB_NEIGE];
    static float y[NB_NEIGE];
    static float v[NB_NEIGE];
    static int r[NB_NEIGE];
    static int init = 0;

    /* Initialisation */
    if (init == 0)
    {
        for (int i = 0; i < NB_NEIGE; i++)
        {
            x[i] = rand() % width;
            y[i] = rand() % height;
            v[i] = 0.2f + static_cast<float>(rand() % 5) * 0.1f; // vitesse lente
            r[i] = 2 + rand() % 3; // rayon 2 à 4
        }
        init = 1;
    }

    /* Fond gris */
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
    SDL_RenderClear(renderer);

    /* Neige blanche */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < NB_NEIGE; i++)
    {
        /* Dessin du flocon */
        for (int dx = -r[i]; dx <= r[i]; dx++)
        {
            for (int dy = -r[i]; dy <= r[i]; dy++)
            {
                if (dx*dx + dy*dy <= r[i]*r[i])
                {
                    SDL_RenderPoint(renderer, x[i] + dx, static_cast<int>(y[i]) + dy);
                }
            }
        }

        /* Chute verticale */
        y[i] += v[i];

        /* Légère dérive horizontale (vent) */
        x[i] += (rand() % 3) - 1; // -1, 0, +1

        /* Retour en haut si bas atteint */
        if (y[i] > height)
        {
            y[i] = 0;
            x[i] = rand() % width;
        }

        /* Reste dans l'écran horizontalement */
        if (x[i] < 0) x[i] = 0;
        if (x[i] > width) x[i] = width;
    }
}