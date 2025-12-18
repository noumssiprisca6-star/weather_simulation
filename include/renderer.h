#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "meteo.h"
#include<iostream>
#include<vector>

extern SDL_Renderer* gRenderer;
bool initRenderer(SDL_Window* window);
void cleanupRenderer();
//pour les dessin
void DrawSoleil(int x , int y , int radius );
void DrawNuages(float x , float y );
void DrawPluie(float intensity , //quantite de pluie 
    float wind,// le vent horizontal
    float deltaTime //fluidite 
);
void DrawNeige(float density ,//nombre de flocons 
    float wind ,// derive laterale 
    float deltaTime );
void DrawOrage(float frequency , // la frequence  des eclairs
    float deltaTime );
void DrawScene(SDL_Renderer* renderer);

#endif


