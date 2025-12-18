#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "meteo.h"
#include<iostream>
#include<vector>

extern SDL_Renderer* renderer;
bool initRenderer(SDL_Window* window);
void cleanupRenderer();
//pour les dessin
void DrawSoleil( SDL_Renderer* renderer);
void DrawNuages(SDL_Renderer* renderer );
void DrawPluie(SDL_Renderer* renderer);
void DrawNeige(SDL_Renderer* renderer);
void DrawOrage(SDL_Renderer* renderer );
void DrawScene(SDL_Renderer* renderer);

#endif


