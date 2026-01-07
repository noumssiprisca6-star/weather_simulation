#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/backends/imgui_impl_sdl3.h"
#include "../libs/imgui/backends/imgui_impl_sdlrenderer3.h"
int SDL_main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr <<"Erreur SDL_Init: " << SDL_GetError() << std::endl;
    }

    std::cout << "SDL3 initialisé avec succès !!" << std::endl;

    SDL_Window* window = SDL_CreateWindow("Ma premiere fenetre sDL", 800, 600, SDL_WINDOW_RESIZABLE);
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
    int counter = 0;
    char text_buffer[256] = "Écris quelque chose ici !";

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

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        if (show_custom_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        if(show_custom_window) {
            ImGui::Begin(" Ma fenêtre magique ✨", &show_custom_window);
            ImGui::Text("Bienvenue dans ImGui !");
            ImGui::Separator();
            if (ImGui::Button("Clique-moi mon petit !")) {
                counter++;
            }
            ImGui::SameLine();
            ImGui::Text("compteur = %d", counter);
            //slider
            ImGui::SliderFloat("valeur", &slider_value, 0.0f, 1.0f);
            //champ de texte
            ImGui::InputText("texte", text_buffer, IM_ARRAYSIZE(text_buffer));
            //selecteur de couleur
            ImGui::Text("Application moyenne %.3f md/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        ImGui::Render();

        //effacage de l'ecran avec la couleur choisie
        SDL_SetRenderDrawColor(renderer,(Uint8)(clear_color[0]) * 255, (Uint8)(clear_color[1]) * 255,
                                (Uint8)(clear_color[2]) * 255, (Uint8)(clear_color[3] * 255));
        SDL_RenderClear(renderer);
        //dessin de ImGui
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),renderer);
        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Good bye nigga!" << std::endl;
    return 0;
}