#include"../include/meteo.h"
#include"../include/renderer.h"
static Meteo currentMeteo = Meteo::Soleil;
static float cloudX = 0 ;
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
        DrawSoleil(700 , 100 , 50);
        if ( currentMeteo == Meteo::Nuageux || currentMeteo == Meteo::Pluie || currentMeteo == Meteo::Orage){
            DrawNuages(cloudX , 120);

        }
        if (currentMeteo == Meteo::Pluie || currentMeteo == Meteo::Orage){
            DrawPluie(1.0f ,30.0f, 0.016f);
    
        }
        if (currentMeteo == Meteo::Orage){
            DrawOrage(0.8f , 0.016f);
        }
          if (currentMeteo == Meteo::Neige){
            DrawNeige(1.5f , 40.0f , 0.016f);
          }
    }
}
