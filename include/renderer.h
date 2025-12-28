#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "../include/meteo.h"
#include<iostream>
#include<vector>


bool initRenderer(SDL_Window* window, SDL_Renderer* renderer);
void cleanupRenderer(SDL_Renderer* renderer);
extern bool showSoleil;

//pour les dessin

void drawFilledCircle(SDL_Renderer* renderer , int cx , int cy , int radius );
void DrawSoleil( SDL_Renderer* renderer);
void RenderScene(SDL_Renderer* renderer);
void DrawNuit(SDL_Renderer* renderer, int width, int height);
void DrawEtoile(SDL_Renderer* renderer, int width, int height);
void RenderNuage(SDL_Renderer* renderer);
void DrawNuage(SDL_Renderer* renderer , int x , int y);
void DrawCloud(SDL_Renderer* renderer ,int x , int y);
void DrawNeige(SDL_Renderer* renderer , int width , int height);
void DrawOrage(SDL_Renderer* renderer, int width, int height);


#endif


