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



Cloud clouds[3] = {
    { -150.0f, 100, 0.5f },
    { -300.0f, 150, 0.8f },
    { -500.0f, 90,  1.2f }
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
    std::vector<Cloud> clouds;
    for (int i = 0; i < 8; i++) {
        Cloud c;
        c.x = i * 150.0f;
        c.y = 80.0f + (i % 3) * 60.0f;
        c.speed = 0.3f + (i % 3) * 0.2f;
        clouds.push_back(c);
    }
    
        // Nuages animés
        for (auto& cloud : clouds) {
            DrawCloud(renderer, (int)cloud.x, (int)cloud.y);
            cloud.x += cloud.speed;

            if (cloud.x > 800) {
                cloud.x = -100;
            }
        }
     
       
    // Dessin + animation
    for (int i = 0; i < 3; i++) {
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
   //pour dessiner les orages 
void DrawOrage(SDL_Renderer* renderer ){
    //ciel sombre 
    SDL_SetRenderDrawColor(renderer , 50,50, 255 ,255);
    SDL_RenderClear(renderer);
    // les eclairs 
    SDL_SetRenderDrawColor(renderer , 255, 255 ,0,255);
    int x = 400;
    int y = 0;
    for(int i = 0 ; i < 5 ; i++){
        int nx = x + (rand()% 40 - 20);
        int ny = y + 100 ;
        SDL_RenderLine(renderer , x , y , nx , ny );
        x = nx ;
        y = ny ;
    }
}
//pour dessiner de la neige
void DrawNeige(SDL_Renderer* renderer){
   
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //couleur blanche 
        for (int i = 0 ; i< 150; i++){
            int x = rand()% 800;
            int y = rand()% 600 ;
    
        SDL_RenderPoint(renderer, x , y );
    }
}