#include "renderer.h"
#include<SDL3/SDL.h>
#include<../libs/stb/stb_image.h>
#include<cstdlib>
#include<cmath>

 
#define STB_IMAGE_IMPLEMENTATION

// Textures globales
static SDL_Texture* sunTex   = nullptr;
static SDL_Texture* cloudTex = nullptr;
static SDL_Texture* rainTex  = nullptr;

// Animation
static float cloudX = 0.0f;
static float rainY  = 0.0f;



//Fonction utilitaire (privée)

static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* path) {
    int w, h, c;
    unsigned char* data = stbi_load(path, &w, &h, &c, 4);
    if (!data) return nullptr;

    SDL_Texture* tex = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STATIC,
        w, h
    );

    SDL_UpdateTexture(tex, nullptr, data, w * 4);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    stbi_image_free(data);

    return tex;
}



// Initialisation

void InitRenderer(SDL_Renderer* renderer) {
    sunTex   = LoadTexture(renderer, "assets/sun.png");
    cloudTex = LoadTexture(renderer, "assets/cloud.png");
    rainTex  = LoadTexture(renderer, "assets/rain.png");
}


// Nettoyage

void CleanupRenderer() {
    SDL_DestroyTexture(sunTex);
    SDL_DestroyTexture(cloudTex);
    SDL_DestroyTexture(rainTex);
}


//Soleil

void DrawSun(SDL_Renderer* renderer) {
    SDL_FRect r = {50, 50, 120, 120};
    SDL_RenderTexture(renderer, sunTex, nullptr, &r);
     static float angle = 0.0f;
    angle += 0.01f;

    int cx = 100 + (int)(sin(angle) * 3);
    int cy = 100 + (int)(cos(angle) * 3);

    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);

    for (int r = 0; r < 40; r++) {
        for (int a = 0; a < 360; a += 10) {
            int x = cx + r * cos(a * 3.14 / 180);
            int y = cy + r * sin(a * 3.14 / 180);
            SDL_RenderPoint(renderer, x, y);
        }
    }
}



//Nuages (animés)

void DrawClouds(SDL_Renderer* renderer) {
    
     cloudX += 0.3f;
    if (cloudX > 800) cloudX= -300;

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    SDL_FRect cloud1 = {200 + cloudX, 100, 150, 60};
    SDL_FRect cloud2 = {240 + cloudX, 70, 150, 60};
    SDL_FRect cloud3 = {280 + cloudX, 100, 150, 60};

    SDL_RenderFillRect(renderer, &cloud1);
    SDL_RenderFillRect(renderer, &cloud2);
    SDL_RenderFillRect(renderer, &cloud3);

    
}


//Pluie

void DrawRain(SDL_Renderer* renderer) {
    
    rainY += 5.0f;
    if (rainY > 600) rainY = 0;

    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);

    for (int i = 0; i < 200; i++) {
        int x = rand() % 800;
        int y = (rand() % 600 + (int)rainY) % 600;
        SDL_RenderLine(renderer, x, y, x, y + 10);
    }

}


// Orage

void DrawStorm(SDL_Renderer* renderer) {
    DrawClouds(renderer);
    DrawRain(renderer);
}


void DrawScene(SDL_Renderer* renderer, Meteo meteo) {
    if (meteo == Meteo::Soleil) {
    
        
        // draw sun
    }
    if (meteo == Meteo::Pluie) {
        // draw rain
    }
    if (meteo == Meteo::Nuageux){
        //draw clouds
    }
    if (meteo == Meteo::Orage){
        //draw
    }
    if (meteo == Meteo::Neige){
        //draw ..
    }
}
 