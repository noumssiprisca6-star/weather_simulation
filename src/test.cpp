#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "../include/ensoleil.h"
#include "../include/orage.h"
#include "../include/neige.h"
// main.cpp
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <windows.h>
#include<cstdlib>
int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Menu météo",
        600, 400, 0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    bool running = true;
    SDL_Event event;

    while (running) {

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Choix météo");

        if (ImGui::Button("☀ Soleil", ImVec2(200, 40))) {
            DrawSoleil(renderer);
        }

        if (ImGui::Button("🌧 Orage", ImVec2(200, 40))) {
            DrawOrage(renderer);
        }

        if (ImGui::Button("❄ Neige", ImVec2(200, 40))) {
            DrawNeige(renderer);
        }

        ImGui::End();

        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),renderer);
        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}