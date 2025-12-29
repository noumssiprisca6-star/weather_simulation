#include "../include/renderer.h"
#include <stb_image.h>
#include <cmath>
#include <cstdlib>
#include<vector>
#include"../src/SDL3/SDL3_image/SDL_image.h"

#include <SDL3/SDL.h>
#include <cmath>



//elelment
struct element {
    float x , y;

};

// STRUCTURE NUAGE

struct Cloud {
    float x;
    float y;
    float speed;
};



Cloud clouds[6] = {
    { -150.0f, 100, 0.5f },
    { -300.0f, 150, 0.8f },
    { -500.0f, 90,  0.9f },
    {-200.0f , 92 , 1.0f},
    {-150.0f , 120 ,0.7f },
    {-400.0f , 102 , 0.6f}
};

static std::vector<element> rainDrops ;
static std::vector<element> snowFlakes;
bool initRenderer(SDL_Window* window, SDL_Renderer* renderer){
    renderer = SDL_CreateRenderer(window , nullptr);
    return renderer != nullptr;

}
void cleanupRenderer(SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
}

// DESSIN D'UN CERCLE (UTILISÉ POUR LE SOLEIL ET LES NUAGES)
void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}


// DESSIN DU SOLEIL
/* 
*sun(x , y )sont les position du centre 
*radius est le rayon du soleil c'est a dire du cercle dessiner pour reprenter le soleil
*dx*dx + dy*dy est l'equation du cercle 
* numRays est le nombre de rayon 
* l'angl repartit les rayons uniformement autour du cercle  
*/
void DrawSoleil(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255); // xcouleur jaune 

    int sunX = 650;
    int sunY = 120;
    int radius = 50;

    drawFilledCircle(renderer, sunX, sunY, radius);

    // Rayons du soleil
    for (int i = 0; i < 360; i += 15) {
        float angle = i * M_PI / 180.0f;
        int x1 = sunX + std::cos(angle) * radius;
        int y1 = sunY + std::sin(angle) * radius;
        int x2 = sunX + std::cos(angle) * (radius + 20);
        int y2 = sunY + std::sin(angle) * (radius + 20);
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }
}


// DESSIN D'UN NUAGE
/*
*chaque nuage est compose de 3 cercles blancs 
 * on peut ajuster les decalages pour que les nuages paraisse flutty et realistes 
 * speed est la vitesse de deplacement horizontal 
 * quand le nuage se deplace hors de le='ecran , il revient a gauche 
*/
void DrawCloud(SDL_Renderer* renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);

    drawFilledCircle(renderer, x,     y,     25);
    drawFilledCircle(renderer, x + 25,y - 10,30);
    drawFilledCircle(renderer, x + 55,y,     25);
    drawFilledCircle(renderer, x + 25,y + 10,22);
}
    
// la scene d'animation des nuages 


void RenderScene(SDL_Renderer* renderer){
// Création des nuages
//animation
    for (int i = 0; i < 8 ; i++) {
        clouds[i].x += clouds[i].speed;
        if (clouds[i].x > 900) {
            clouds[i].x = -200;
        }

        DrawCloud(renderer, (int)clouds[i].x, clouds[i].y);
    }

    SDL_RenderPresent(renderer);

}
    


   

 
#define NB_PLUIE 400   // Nombre de gouttes de pluie
#define NB_ECLAIR 3    // Nombre d'éclairs
#define NB_NUAGES 5    // Nombre de nuages

// Dessin d'un cercle plein
void drawFilCircle(SDL_Renderer* renderer, int cx, int cy, int r)
{
    for (int y = -r; y <= r; y++) {
        for (int x = -r; x <= r; x++) {
            if (x * x + y * y <= r * r) {
                SDL_RenderPoint(renderer, cx + x, cy + y);
            }
        }
    }
}
// Dessin de nuage au ton gris  lourd
void DrawNuage(SDL_Renderer* renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);//gris foncé
    drawFilCircle(renderer, x, y, 70);
    drawFilCircle(renderer, x + 150, y - 10, 65);
    drawFilCircle(renderer, x + 190, y+30, 60);
    drawFilCircle(renderer, x + 220, y + 10, 55);
    drawFilCircle(renderer , x +280, y+20 ,45);
}
// Création des  gros nuages gris nuages et animation
void RenderNuage(SDL_Renderer* renderer){

    for (int i = 0; i < 8 ; i++) {
        clouds[i].x += clouds[i].speed;
        if (clouds[i].x > 700) {
            clouds[i].x = -40;
        }

        DrawNuage(renderer, (int)clouds[i].x, clouds[i].y);
    }

    SDL_RenderPresent(renderer);

}
    
//pour dessiner l'orage

void DrawOrage(SDL_Renderer* renderer, int width, int height)
{
    // --- Pluie ---
    static int pluieX[NB_PLUIE];
    static float pluieY[NB_PLUIE];  // float pour chute douce
    static int initPluie = 0;

    // --- Éclairs ---
    static int eclairX[NB_ECLAIR];
    static int eclairY[NB_ECLAIR];
    static int eclairTimer[NB_ECLAIR];
    static int initEclair = 0;

    // --- Nuages ---
    static int nuageX[NB_NUAGES];
    static int nuageY[NB_NUAGES];
    static int initNuage = 0;

    // Initialisation pluie
    if (initPluie == 0)
    {
        for (int i = 0; i < NB_PLUIE; i++)
        {
            pluieX[i] = rand() % width;
            pluieY[i] = rand() % height;
        }
        initPluie = 1;
    }

    // Initialisation éclairs
    if (initEclair == 0)
    {
        for (int i = 0; i < NB_ECLAIR; i++)
        {
            eclairX[i] = rand() % width;
            eclairY[i] = rand() % (height / 2);
            eclairTimer[i] = rand() % 60;
        }
        initEclair = 1;
    }


    // --- Fond gris sombre ---
    SDL_SetRenderDrawColor(renderer, 50, 50, 60, 255);
    SDL_RenderClear(renderer);

    // --- Nuages épais gris foncé ---
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
    for (int i = 0; i < NB_NUAGES; i++)
    {
        // Plusieurs ellipses superposées pour épaissir le nuage
        for (int nx = -50; nx <= 50; nx += 20)
        {
            for (int ny = -25; ny <= 25; ny += 15)
            {
                for (int dx = -30; dx <= 30; dx++)
                {
                    for (int dy = -15; dy <= 15; dy++)
                    {
                        if ((dx*dx)/2 + dy*dy <= 225)
                        {
                            SDL_RenderPoint(renderer, nuageX[i]+nx+dx, nuageY[i]+ny+dy);
                        }
                    }
                }
            }
        }
    }

    // --- Pluie douce ---
    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    for (int i = 0; i < NB_PLUIE; i++)
    {
        SDL_RenderLine(renderer, pluieX[i], static_cast<int>(pluieY[i]), pluieX[i], static_cast<int>(pluieY[i])+5);
        pluieY[i] += 1.5f;               // chute lente
        if (pluieY[i] > height) pluieY[i] = 0; // remonter
    }

    // --- Éclairs ---
    SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
    for (int i = 0; i < NB_ECLAIR; i++)
    {
        eclairTimer[i]++;
        if (eclairTimer[i] > 60)
        {
            int startX = eclairX[i];
            int startY = eclairY[i];
            for (int j = 0; j < 10; j++)
            {
                int offsetX = (rand() % 11) - 5;
                int offsetY = 5 + rand() % 5;
                SDL_RenderLine(renderer, startX, startY, startX+offsetX, startY+offsetY);
                startX += offsetX;
                startY += offsetY;
            }
            eclairTimer[i] = 0;
            eclairX[i] = rand() % width;
            eclairY[i] = rand() % (height / 2);
        }
    }
}

//la fonction pour dessiner de la neige 

#define NB_NEIGE 300

void DrawNeige(SDL_Renderer* renderer, int width, int height)
{
    /* Données persistantes */
    static int x[NB_NEIGE];
    static float y[NB_NEIGE];
    static float v[NB_NEIGE];
    static int r[NB_NEIGE];
    static int init = 0;

    /* Initialisation */
    if (init == 0)
    {
        for (int i = 0; i < NB_NEIGE; i++)
        {
            x[i] = rand() % width;
            y[i] = rand() % height;
            v[i] = 0.2f + static_cast<float>(rand() % 5) * 0.1f; // vitesse lente
            r[i] = 2 + rand() % 3; // rayon 2 à 4
        }
        init = 1;
    }

    /* Fond gris */
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
    SDL_RenderClear(renderer);

    /* Neige blanche */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < NB_NEIGE; i++)
    {
        /* Dessin du flocon */
        for (int dx = -r[i]; dx <= r[i]; dx++)
        {
            for (int dy = -r[i]; dy <= r[i]; dy++)
            {
                if (dx*dx + dy*dy <= r[i]*r[i])
                {
                    SDL_RenderPoint(renderer, x[i] + dx, static_cast<int>(y[i]) + dy);
                }
            }
        }

        /* Chute verticale */
        y[i] += v[i];

        /* Légère dérive horizontale (vent) */
        x[i] += (rand() % 3) - 1; // -1, 0, +1

        /* Retour en haut si bas atteint */
        if (y[i] > height)
        {
            y[i] = 0;
            x[i] = rand() % width;
        }

        /* Reste dans l'écran horizontalement */
        if (x[i] < 0) x[i] = 0;
        if (x[i] > width) x[i] = width;
    }
}

// desin de la nuit 
#define NB_ETOILES 200

void DrawNuit(SDL_Renderer* renderer, int width, int height)
{
    /* ================= DONNÉES PERSISTANTES ================= */

    static int etoileX[NB_ETOILES];
    static int etoileY[NB_ETOILES];
    static int etoileR[NB_ETOILES];
    static int etoileBlink[NB_ETOILES];
    static int init = 0;

    /* ================= INITIALISATION ================= */

    if (!init)
    {
        for (int i = 0; i < NB_ETOILES; i++)
        {
            etoileX[i] = rand() % width;     // position X
            etoileY[i] = rand() % height;    // position Y
            etoileR[i] = 1 + rand() % 2;     // taille
            etoileBlink[i] = rand() % 100;   // scintillement
        }
        init = 1;
    }

    /* ================= FOND DE NUIT ================= */

    SDL_SetRenderDrawColor(renderer, 8, 12, 30, 255); // bleu nuit profond
    SDL_RenderClear(renderer);

    /* ================= LUNE ================= */

    int moonX = width - 120;
    int moonY = 100;
    int moonR = 30;

    // Halo léger
    SDL_SetRenderDrawColor(renderer, 200, 200, 220, 40);
    for (int r = moonR + 5; r < moonR + 15; r++)
    {
        for (int dx = -r; dx <= r; dx++)
        {
            for (int dy = -r; dy <= r; dy++)
            {
                if (dx*dx + dy*dy <= r*r)
                    SDL_RenderPoint(renderer, moonX + dx, moonY + dy);
            }
        }
    }

    // Corps de la lune
    SDL_SetRenderDrawColor(renderer, 220, 220, 210, 255);
    for (int dx = -moonR; dx <= moonR; dx++)
    {
        for (int dy = -moonR; dy <= moonR; dy++)
        {
            if (dx*dx + dy*dy <= moonR*moonR)
                SDL_RenderPoint(renderer, moonX + dx, moonY + dy);
        }
    }

    /* ================= ÉTOILES ================= */

    for (int i = 0; i < NB_ETOILES; i++)
    {
        etoileBlink[i] = (etoileBlink[i] + 1) % 120;
        int lum = 180 + (etoileBlink[i] % 50);

        SDL_SetRenderDrawColor(renderer, lum, lum, lum, 255);

        for (int dx = -etoileR[i]; dx <= etoileR[i]; dx++)
        {
            for (int dy = -etoileR[i]; dy <= etoileR[i]; dy++)
            {
                if (dx*dx + dy*dy <= etoileR[i]*etoileR[i])
                    SDL_RenderPoint(renderer,
                        etoileX[i] + dx,
                        etoileY[i] + dy);
            }
        }
    } 
}

// dessin de l'etoile fillante la nuit 
/*  ici , chaque etoile a un booleen "active " et un respawntime 
 * chaque etoile designe une ligne blanche qui simule la trainée 
 * lorsqu'elle sorte de l'ecran , elle deviennent inactive et 
 * son respawntime est defini pour un temps d'apparition bien specifique 
 *  la fonction verifie de temps avant de la reactivé 
*/
void DrawEtoile (SDL_Renderer* renderer, int screenWidth, int screenHeight) {
    int count = 3;
    struct ShootingStar {
        float x, y;
        float speedX, speedY;
        int length;
        Uint32 respawnTime; // moment où l'étoile peut réapparaître
        bool active;
    };
    static std::vector<ShootingStar> stars;
    static bool initialized = false;

    if (!initialized) {
        srand((unsigned int)time(0));
        for (int i = 0; i < count; ++i) {
            ShootingStar s;
            s.x = rand() % screenWidth;
            s.y = rand() % (screenHeight / 2);
            s.speedX = 5.0f + rand() % 5;
            s.speedY = 2.0f + rand() % 3;
            s.length = 10 + rand() % 10;
            s.active = true;
            s.respawnTime = 0;
            stars.push_back(s);
        }
        initialized = true;
    }

    Uint32 currentTime = SDL_GetTicks();

    for (auto& star : stars) {
        if (star.active) {
            // Dessiner la traînée estompée
            for (int i = 0; i < star.length; ++i) {
                int alpha = 255 - (i * (255 / star.length));
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
                SDL_RenderPoint(renderer,
                    (int)(star.x - i * (star.speedX / star.length)),
                    (int)(star.y - i * (star.speedY / star.length))
                );
            }

            // Mettre à jour la position
            star.x += star.speedX;
            star.y += star.speedY;

            // Si elle sort de l'écran, la désactiver et programmer la réapparition
            if (star.x > screenWidth || star.y > screenHeight) {
                star.active = false;
                star.respawnTime = currentTime + 3000; //  3 secondes plus tard
            }
        } else {
            // Vérifier  si le délai est passé pour réactiver
            if (currentTime >= star.respawnTime) {
                star.x = 0;
                star.y = rand() % (screenHeight / 2);
                star.speedX = 5.0f + rand() % 5;
                star.speedY = 2.0f + rand() % 3;
                star.length = 10 + rand() % 10;
                star.active = true;
            }
        }
    }
}

// fonction pour simuler un tourbillon
/*ici centerx et centery sont les centre du tourbillon 
* turns est le nombre de tours de spirales 
* spcing est la distance entre les spirales 
* pointsperturn est plus grand , plus la spirale est lisse  
* la fonction dessine simplement des points le long d'une spirale

*/
void DrawTour (SDL_Renderer* renderer, int Width, int Height){
int turns = 5;
 float spacing = 5.0f ;
    static float rotation = 0.0f; // rotation du tourbillon

    // Fond gris
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // gris moyen
    SDL_RenderClear(renderer);

    // Couleur du tourbillon (blanc)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    const int pointsPerTurn = 100;
    const float twoPi = 6.28318530718f;

    int centerX = Width / 2;
    int centerY = Height / 2;

    for (int t = 0; t < turns * pointsPerTurn; ++t) {
        float angle = (twoPi * t) / pointsPerTurn + rotation;
        float radius = spacing * angle;
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY + (int)(radius * sin(angle));
        SDL_RenderPoint(renderer, x, y);
    }

    // Mettre à jour la rotation
    rotation += 0.02f;
    if (rotation > twoPi) rotation -= twoPi;

    // Afficher le rendu
    SDL_RenderPresent(renderer);
}