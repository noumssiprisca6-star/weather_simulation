#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "../include/meteo.h"
#include<iostream>
#include<vector>

void RenderScene(SDL_Renderer* renderer);
extern SDL_Renderer* renderer;
bool initRenderer(SDL_Window* window);
void cleanupRenderer();
extern bool showSoleil;

//pour les dessin

void DrawFilledCircle(SDL_Renderer* renderer , int cx , int cy , int radius );
void DrawSoleil( SDL_Renderer* renderer);
void DrawCloud(SDL_Renderer* renderer ,int x , int y);
void DrawNeige(SDL_Renderer* renderer);
void DrawOrage(SDL_Renderer* renderer );
void DrawPluie(SDL_Renderer* renderer);

#endif


