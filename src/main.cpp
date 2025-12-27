#include <SDL3/SDL.h>
#include"../src/SDL3/SDL3_image/SDL_image.h"
#include <SDL3/SDL_main.h>
#include <iostream>
#include "../include/meteo.h"
#include "../include/ui.h"
#include "../include/renderer.h"
#include<vector>
// main.cpp
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <windows.h>
#include<cstdlib>



  int SDL_main(int argc, char* argv[]) {
    SetConsoleCP(CP_UTF8);
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr <<"Erreur SDL_Init: " << SDL_GetError() << std::endl;
    
    }

    std::cout << "SDL3 initialisé avec succès !!" << std::endl;
 
    SDL_Window* window = SDL_CreateWindow("Meteo VIsuelle", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Erreur de creation fenêtre: " << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

   
    if (!renderer) {
        std::cerr << "Erreur de création renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
// etat de ka meteo 
    bool show_demo_window = false; //pas besoin de la fenetre de demo dans le projet final
    bool show_custom_window = true;
    bool showsoleil =false ;
    bool showneige = false; //dessin de l'evenement orage si vrai
    bool showorage = false;//dessin de la pluie si vrai
    bool shownuage = false; //dessin des nuages si vrai
    float clear_color[4] = {0.1f, 0.1f, 0.15f, 1.0f};
    float slider_value = 0.5f;
    int counter;
    char text_buffer[256] = " hello";
    Meteo meteo;
    
     //variable de la boucle principale
// creation de la surface
SDL_Surface* surface = IMG_Load("assets/im.jpg");
//creation de la texture à partir de la surface 
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer , surface);
//destruction de la surface creer 
SDL_DestroySurface(surface);
    //boucle de jeu
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            //ne place plus le code de ta fenetre ici❌
        }
        /**
         * les frames IMGUI commencent a se faire creer ici sinon il y aura des problemes 
         * lors de l'affichage.
         */
        //  IMGUI
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Controle Meteo");

        /**
         * les boutons devrons gerer des booleens decidant de l'affichage ou non de evenements 
         * metheorologiques. laisser les fonctions de dessin comme DrawOrage dans les instructions
         * lancees par les clics sur les boutons n'empechent pas le dessin de l'orage mais cela se fait
         * de facon tres breve. tes evenement metheorologiques s'affichent mais ne restent pas assez 
         * longtemps pour etre percus.
         * 
         * malheureusement l'enum class Meteo ne sert pas a grand chose vu que les booleens passent mieux
         * mais je laisse qund meme tu verras si tu en as encore besoin ou pas.
         */
        if (ImGui::Button("Soleil"))  {
            SetMeteo( Meteo::Soleil); 
            showsoleil = true ;
            shownuage = true; 
            showorage = false;
            showneige = false;
            //il est important de preciser que l'eevenement metheo precedent
            //(selon le choix de l'utilisateur) doit s'arreter avant de lancer
            //le nouvel evenement
        }
        if (ImGui::Button("Nuageux")){
          SetMeteo(Meteo::Nuage);
          shownuage= true; //pour les nuages
        }
       if (ImGui::Button("Pluie"))  {
        SetMeteo (Meteo::Pluie);
        showorage = true; //pour la pluie
        showneige = false;
        showsoleil= false;
        shownuage =false;
        
        }
        //je te laisse faire le cas de la neige pour t'exercer
        if (ImGui::Button("Orage"))  {
        SetMeteo(Meteo::Orage);
        SDL_SetRenderDrawColor(renderer , 220 ,220,220 ,255);
            showorage = true;
            showsoleil = false;
            shownuage=false;
            showneige = false;
        } 
        if (ImGui::Button("Neige")) {
            SetMeteo(Meteo::Neige);
            showneige= true;
            showsoleil = false;
            shownuage=false;
            showorage = false;
          
        }
  
    
        ImGui::Separator();
        ImGui::End();
         ImGui::Render();
        
        SDL_RenderTexture(renderer, texture,nullptr , nullptr);
        //ici, grace au booleen on peut choisir quel etat de metheo on doit afficher
        /**
         * show_cloud ne devient vraie qu'apres avoir appuye sur le bouton orage de ce fait
         * tantque l'utilisateur ne le fait pas on ne dessine pas d'orage dans la fenetre
         * c'est pareil pour le soleil. son affichage depend de l'etat true ou false de 
         * showsun
         */
        //on dessine l'orage. il ne disparaitra pas tant que le bouton ne renvoie pas
        //show_cloud a false.
        if (showneige){
            DrawNeige(renderer ,800 ,600);
        }
        //on dessine le soleil. il ne disparaitra pas tant que le bouton ne renvoie pas
        //showsun a false.
        if(showsoleil){
            
            SDL_SetRenderDrawColor (renderer ,135, 206, 235, 255);
                SDL_RenderClear(renderer);
                DrawSoleil(renderer); 
                RenderScene(renderer);
                
        }
        //pluie si show_rain est vrai
       
        if(showorage){
        
            SDL_SetRenderDrawColor(renderer , 220 ,220,220 ,255);
            DrawOrage(renderer ,800 ,600);
        }
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        
        
        SDL_RenderPresent(renderer);
    }
        
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    
        
    //effface toutes les fenetres creer
   SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Good bye " << std::endl;
    return 0;


}