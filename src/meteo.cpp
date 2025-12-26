#include"../include/meteo.h"
#include"../include/renderer.h"
#include<SDL3/SDL.h>
static Meteo currentMeteo = Meteo::Soleil;
float cloudX = 0 ;
void SetMeteo (Meteo type){
    currentMeteo = type;

}


void DrawMeteo (SDL_Renderer* renderer){
    if (currentMeteo == Meteo::Soleil){
        std::cout<<"soleil"<<std::endl;
        
        if ( currentMeteo == Meteo::Nuage || currentMeteo == Meteo::Pluie || currentMeteo == Meteo::Orage){
        std::cout<<"nuages"<<std::endl;

        }
        
        if (currentMeteo == Meteo::Orage){
            std::cout<<" orage "<<std::endl;
        }
          if (currentMeteo == Meteo::Neige){
            std::cout<<"neige"<<std::endl;
          }
    }
}
