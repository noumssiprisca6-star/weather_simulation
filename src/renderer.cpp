#include "renderer.h"
#include<SDL3/SDL.h>
#include<../libs/stb/stb_image.h>
#include<cstdlib>
#include<cmath>

SDL_Renderer* renderer = nullptr;
//elelment
struct element {
    float x , y;
    float speed ;
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
//pour dessiner le soleil
void DrawSoleil(SDL_Renderer* renderer){
    int cx = 400; 
    int cy = 150;
    int r =50 ;
    SDL_SetRenderDrawColor(renderer , 255, 212, 0 ,255);
    for (int i = 0; i < 360 ; i++){
        float rad =i * M_PI / 180.0f ;
        int x = cx + cos(rad) * r;
        int y = cy + sin(rad) * r ;
        SDL_RenderPoint(renderer , x , y );
             
            }
        }
   
//pour dessiner les nuages 
void DrawNuages(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer ,200,200 ,200 ,255);
    //pour un nuage il faut en faites créer trois cercles superposés 
    int basex = 200;
    int basey = 120;
    for (int i =0 ; i<3 ; i++){
        int cx = basex +  i * 60;
        int cy = basey  + (i % 2) * 10 ;
        int r  = 30 ;
    
            for (int a = 0 ; a < 360; a++){
                float rad = a * M_PI/180.0f;
                int x = cx + cos(rad) * r ;
                int y = cy + sin(rad)  * r ;
               SDL_RenderPoint(renderer , x ,y);
               }
            }

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
      //dessin selon le choix de la video 
      void DrawScene(SDL_Renderer* renderer, Meteo meteo){
        switch (meteo)
        {
        case Meteo::Soleil:
        DrawSoleil(renderer);
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
        DrawNuages(renderer) ;
        default:
            break;
        }
      }