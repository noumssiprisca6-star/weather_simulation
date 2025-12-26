#include"../include/meteo.h"
#include"../include/renderer.h"
static Meteo currentMeteo = Meteo::Soleil;
float cloudX = 0 ;
void SetMeteo (Meteo type){
    currentMeteo = type;

}
void UpdateMeteo(float deldaTime ){
    cloudX += 40* deldaTime;
 if (cloudX > 800){
cloudX = -200 ;
}
}
void DrawMeteo (){
    if (currentMeteo == Meteo::Soleil){
        DrawSoleil(renderer);
        
        if ( currentMeteo == Meteo::Nuage || currentMeteo == Meteo::Pluie || currentMeteo == Meteo::Orage){
        std::cout<<"nuages"<<std::endl;

        }
        if (currentMeteo == Meteo::Pluie || currentMeteo == Meteo::Orage){
            DrawOrage(renderer);
    
        }
        if (currentMeteo == Meteo::Orage){
            DrawOrage(renderer);
        }
          if (currentMeteo == Meteo::Neige){
            DrawNeige(renderer);
          }
    }
}
