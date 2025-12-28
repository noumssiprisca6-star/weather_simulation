#pragma once 
#ifndef METEO_H
#define METEO_H
#include<vector>
#include<SDL3/SDL.h>
#include<iostream>

extern SDL_Renderer* renderer;

enum class Meteo {
    Soleil,
    Pluie,
    Nuage,
    Neige,
    Orage, 
    nuit
};
/**
 * la procedure UpdateMeteo permet de mettre à jour les animation 
 * DrawMeteo permet de dessiner la meteo
 * SetMeteo permet de changer la meteo
 */
void UpdateMeteo(float deltaTime); 
void DrawMeteo(SDL_Renderer* renderer);
void SetMeteo(Meteo type);
void DrawUI(Meteo& meteo);
#endif