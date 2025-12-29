#pragma once 
#ifndef METEO_H
#define METEO_H
#include<vector>
#include<SDL3/SDL.h>
#include<iostream>

extern SDL_Renderer* renderer;

enum class Meteo {
    Soleil,
    tourbillon,
    Pluie ,
    Nuage,
    Neige,
    Orage, 
    nuit
};
/*
 * DrawMeteo permet de dessiner la meteo
 * SetMeteo permet de changer la meteo
 */

void DrawMeteo(SDL_Renderer* renderer);
void SetMeteo(Meteo type);

#endif