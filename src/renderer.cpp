#include "renderer.h"
#include<SDL3/SDL.h>
#include<../libs/stb/stb_image.h>
#include<cstdlib>
#include<cmath>

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

//NUAGE
struct Cloud {
    float x, y;
    float speed;
};

void DrawNuageux(SDL_Renderer* renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    DrawFilledCircle(renderer, x, y, 25);
    DrawFilledCircle(renderer, x + 30, y - 10, 30);
    DrawFilledCircle(renderer, x + 60, y, 25);
    DrawFilledCircle(renderer, x + 30, y + 10, 28);
}

/* Nuages */
    std::vector<Cloud> clouds = {
        {100, 120, 0.3f},
        {300, 180, 0.4f},
        {500, 150, 0.2f}
    };


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
      //dessin selon le choix de la video 
      void DrawScene(SDL_Renderer* renderer, Meteo meteo){
        switch (meteo)
        {
        case Meteo::Soleil:
        DrawSoleil(renderer );
        break;
        case Meteo::Pluie:
        DrawPluie(renderer);
        break;
        case Meteo::Orage:
        DrawOrage(renderer);
        break;
        case Meteo::Neige:
        DrawNeige(renderer);
        break;
        case Meteo::Nuageux:
        DrawNuageux(renderer) ;
        default:
            break;
        }
      }