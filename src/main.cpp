#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "../include/meteo.h"
#include "../include/ui.h"
#include "../include/renderer.h"

// main.cpp
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <windows.h>
#include<cstdlib>

  
  int SDL_main(int argc, char* argv[]) {
    bool drawsun = false;
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
    char text_buffer[256] = "Écris quelque chose ici !";
    Meteo meteo;

    //boucle de jeu
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
        

            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
 //  Fond ciel
        

        // METEO
    

        //  IMGUI
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("Controle Meteo");
        if (ImGui::Button("Soleil"))  {
            SetMeteo( Meteo::Soleil);
            DrawSoleil(renderer);
            
            
        }
        if (ImGui::Button("Nuageux")){
          SetMeteo(Meteo::Nuageux);
          SDL_RenderClear(renderer);
        }
        if (ImGui::Button("Pluie"))  {
        SetMeteo (Meteo::Pluie);
        DrawPluie(renderer);
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
  
    
         
        switch (meteo)
        {
        case Meteo::Soleil:
        std::cout<<"la meteo actuelle est ensoleillée"<<std::endl;
        break;

        case Meteo::Pluie:
        std::cout<<"la meteo actuelle est la pluie " <<std::endl; 
        break;

        case Meteo::Orage:
        std::cout<<"la meteo actuelle est orageuse "<<std::endl;
        break;

        case Meteo::Neige:
        std::cout<<"la meteo actuelle est  celle de l'hyver "<<std::endl;
        break;

        case Meteo::Nuageux:
        std::cout<<"la meteo actuelle est celle de l'automne"<<std::endl;
        default:
            break;
        }
      
        ImGui::Separator();
        ImGui::End();
         ImGui::Render();
        
        
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
        
    

        //effacage de l'ecran avec la couleur choisie
        
        //dessin de ImGui
    }
    
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Good bye " << std::endl;
    return 0;


}