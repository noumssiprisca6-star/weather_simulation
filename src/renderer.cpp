#include "renderer.h"
#include<SDL3/SDL.h>
#include<../libs/stb/stb_image.h>
#include<cstdlib>
#include<cmath>

SDL_Renderer* gRenderer = nullptr;
//elelment
struct element {
    float x , y;
    float speed ;
};
static std::vector<element> rainDrops ;
static std::vector<element> snowFlakes;
bool initRenderer(SDL_Window* window){
    gRenderer = SDL_CreateRenderer(window , nullptr);
    return gRenderer != nullptr;

}
void cleanupRenderer(){
    SDL_DestroyRenderer(gRenderer);
}
//pour dessiner le soleil
void DrawSoleil(int x , int y , int radius){
    SDL_SetRenderDrawColor(gRenderer , 255, 200, 0 ,255);
    for (int w = -radius; w<=radius ; w++){
        for (int h = -radius; w<=radius; h++){
            if (w*w + h*h <=radius*radius){
                SDL_RenderPoint(gRenderer ,x+w , y+h);
            }
        }
    }

}
//pour dessiner les nuages 
void DrawNuages(float x , float y){
    SDL_SetRenderDrawColor(gRenderer ,200,200 ,200 ,255);
    //pour un nuage il faut en faites créer trois cercles superposés 
    for (int i =0 ; i<3 ; i++){
        for(int w =-30 ; w<=30; w++){
            for (int h =-20 ; h<=20 ; h++){
               if(w*w + h*h <=400){;
               SDL_RenderPoint(gRenderer , x + w +i *25 , y+h);
               }
            }

        }
    }
}
//pour dessiner la pluie 
void DrawPluie ( float intentity , float wind , float deltaTime){
    SDL_SetRenderDrawColor(gRenderer,120,120,255,255);
    int maxDrops = static_cast<int>(intentity * 300);
    if(rainDrops.size() < 300){
        // la fonction ci dessous permet de generer aleatoirement differentes vitesse  pour un rendu naturel
        
        for(auto& rain: rainDrops){
            rain.y += rain.speed * 0.016f;
            if(rain .y > 600 ){
                rain.y =0;
                
                SDL_RenderLine(gRenderer , rain.x , rain . y,rain.x + wind *2, rain.y + 10);
                //une goutte sur une  ligne verticale
            }
            
        }
   }
}
void DrawNeige(float density , float wind , float deltaTime ){
    SDL_SetRenderDrawColor(gRenderer , 255,255, 255 ,255);
    int maxFlakes = static_cast<int>(density * 200);
    if (snowFlakes.size() < 200)snowFlakes.push_back({float(rand()%800), 0, float(50+rand()%50)}); 
    //pour dessiner des flocons 
    for (auto& snow : snowFlakes){
        snow.y += snow.speed * 0.016f;
        if(snow.y > 600){
        snow.y = 0 ;
        SDL_RenderPoint(gRenderer , snow.y , snow.y);  
        }              
    }
}
//pour dessiner des orages 
void DrawOrage(float frequency , float deltaTime){
    //les eclairs apparaisent de facon aleatoires
    if ((rand()% 1000 ) < frequency * 1000 * deltaTime){
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderLine(gRenderer , 400,0, 350, 300);
        SDL_RenderLine(gRenderer, 350, 300, 420, 600);
    }
}
      