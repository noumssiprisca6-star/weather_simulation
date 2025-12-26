#include "renderer.h"
#include <stb_image.h>
#include <cmath>
#include <cstdlib>
#include<vector>
#include"../libs/SDL3/SDL3_image/SDL_image.h"

#include <SDL3/SDL.h>
#include <cmath>

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
SDL_Renderer* renderer = nullptr;
//elelment
struct element {
    float x , y;

};
static std::vector<element> rainDrops ;
static std::vector<element> snowFlakes;
bool initRenderer(SDL_Window* window){
    renderer = SDL_CreateRenderer(window , nullptr);
    return renderer != nullptr;

}
void cleanupRenderer(){
    SDL_DestroyRenderer(renderer);
}
//pour dessiner un cercle plein 
void DrawFilledCircle(SDL_Renderer* renderer , int cx , int cy , int radius){
    for (int i = - radius ; i <= radius ; i++){
        for(int a = - radius ; a <= radius ; a ++){
            if (i*i + a*a <= radius*radius){
           SDL_RenderPoint(renderer ,cx + i , cy + a);
            }
        }
    }
}

    //SOLEIL
    void DrawSoleil(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer , 255 ,215 ,0,255) ;//couleur jaune
        DrawFilledCircle(renderer ,650 ,120 ,50);
    }


//pour dessiner les nuages

void DrawCloud(SDL_Renderer* renderer, int x, int y)
{
    // Couleur blanche
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Fonction locale : cercle plein
    auto drawFilledCircle = [&](int cx, int cy, int radius)
    {
        for (int dy = -radius; dy <= radius; dy++)
        {
            for (int dx = -radius; dx <= radius; dx++)
            {
                if (dx * dx + dy * dy <= radius * radius)
                {
                    SDL_RenderPoint(renderer, cx + dx, cy + dy);
                }
            }
        }
    };

    // Composition du nuage (plusieurs cercles)
    drawFilledCircle(x,      y,      20);
    drawFilledCircle(x + 25, y - 10,  25);
    drawFilledCircle(x + 55, y,      20);
    drawFilledCircle(x + 30, y + 10, 18);
}
void RenderScene(SDL_Renderer* renderer){
    int CloudX = -100;
    CloudX += 1;
    if(CloudX > 800){
        CloudX = -100;
    }
 
    //appel de le fonction nuage

    DrawCloud(renderer, 120, 100);
    DrawCloud(renderer, 350, 150);
    DrawCloud(renderer, 600, 90);
    DrawCloud(renderer , CloudX , 120);
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