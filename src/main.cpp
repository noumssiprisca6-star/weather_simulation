#include <SDL3/SDL.h>
#include"../libs/SDL3/SDL3_image/SDL_image.h"
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
    bool showsun = false;
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

    bool show_demo_window = true;
    bool show_custom_window = true;
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
        //  IMGUI
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Controle Meteo");

        if (ImGui::Button("Soleil"))  {
            SetMeteo( Meteo::Soleil);
            showsun = true ;
            if(showsun){
                DrawSoleil(renderer);
            }
          
        }
        if (ImGui::Button("Nuageux")){
          SetMeteo(Meteo::Nuageux);
          SDL_RenderClear(renderer);
        }
       if (ImGui::Button("Pluie"))  {
        SetMeteo (Meteo::Pluie);
        DrawOrage(renderer);
        SDL_RenderClear(renderer);
        }
          
        if (ImGui::Button("Neige"))  {
        SetMeteo(Meteo::Neige);
        DrawNeige(renderer);
        SDL_RenderClear(renderer);
        } 
        if (ImGui::Button("Orage")) {
              SetMeteo( Meteo::Orage);
              DrawOrage(renderer);
              SDL_RenderClear(renderer);
        }
  
    
        ImGui::Separator();
        ImGui::End();
         ImGui::Render();
        
        
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
        SDL_RenderTexture(renderer, texture,nullptr , nullptr);
        SDL_RenderPresent(renderer);
        
        }
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