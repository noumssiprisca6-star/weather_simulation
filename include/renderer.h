#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include "meteo.h"
#include<iostream>

SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer);
void DrawScene(SDL_Renderer* renderer, Meteo meteo);
// pour le ciel


void InitRenderer(SDL_Renderer* renderer);
void CleanupRenderer();

void DrawSun(SDL_Renderer* renderer);
void DrawClouds(SDL_Renderer* renderer);
void DrawRain(SDL_Renderer* renderer);
void DrawStorm(SDL_Renderer* renderer);

void DrawScene(SDL_Renderer* renderer, Meteo meteo);

#endif


