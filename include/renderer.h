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
extern SDL_Texture* solieiltexture;
extern bool showSoleil;

//pour les dessin
void loadsoleilTexture(SDL_Renderer* renderer);
void DrawFilledCircle(SDL_Renderer* renderer , int cx , int cy , int radius );
void DrawSoleil( SDL_Renderer* renderer);
void drawCloud(SDL_Renderer* renderer, int x, int y);
void DrawNeige(SDL_Renderer* renderer);
void DrawOrage(SDL_Renderer* renderer );


#endif


