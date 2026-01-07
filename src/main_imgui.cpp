#include "../src/SDL3/SDL.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/backends/imgui_impl_sdl3.h"
#include "../libs/imgui/backends/imgui_impl_sdlrenderer3.h"
#include <iostream>
int main(int argc, char* argv[]) {
 // � Init SDL3
 if (!SDL_Init(SDL_INIT_VIDEO)) {
 std:: cerr << "Erreur SDL: " << SDL_GetError() << std:: endl;
 return 1;
 }
 // � Crée la fenêtre
 SDL_Window* window = SDL_CreateWindow(
 "SDL3 + ImGui = � ",
 1280, 720,
 SDL_WINDOW_RESIZABLE
 );
 if (!window) {
 std:: cerr << "Erreur fenêtre: "  << SDL_GetError() << std:: endl;
 SDL_Quit();
 return 1;
 }
 // � Crée le renderer
 SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
 if (!renderer) {
 std:: cerr << "Erreur renderer: "  << SDL_GetError() << std:: endl;
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 1;
 }
 ImGui::CreateContext();
 ImGuiIO& io = ImGui::GetIO();
 io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Navigation clavier
 // � Style ImGui (choisis ton thème !)
 ImGui::StyleColorsDark(); // Thème sombre
 // ImGui::StyleColorsLight(); // Thème clair
 // ImGui::StyleColorsClassic(); // Thème classique
 // � Init backends ImGui
 ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
 ImGui_ImplSDLRenderer3_Init(renderer);
 // � Variables pour la démo
 bool show_demo_window = true;
 bool show_custom_window = true;
 float clear_color[ 4] = {0.1f, 0.1f, 0.15f, 1.0f};
 float slider_value = 0.5f;
 int counter = 0;
 char text_buffer[ 256] = "Écris quelque chose ici !" ;
 // � Boucle principale
 bool running = true;
 SDL_Event event;
 while (running) {
 // � Événements
 while (SDL_PollEvent(&event)) {
 ImGui_ImplSDL3_ProcessEvent(&event); // ImGui traite l'événement
 if (event.type == SDL_EVENT_QUIT) {
 running = false;
 }
 }
 // � Nouvelle frame ImGui
 ImGui_ImplSDLRenderer3_NewFrame();
 ImGui_ImplSDL3_NewFrame();
 ImGui::NewFrame();
 // � --- TON CODE IMGUI ICI ---
 // Fenêtre de démo (super utile pour apprendre !)
 if (show_demo_window) {
 ImGui::ShowDemoWindow(&show_demo_window);
 }
 // Ta fenêtre personnalisée
 if (show_custom_window) {
 ImGui::Begin( "Ma Fenêtre Magique ✨ ", &show_custom_window);
 ImGui::Text( "Bienvenue dans ImGui !" );
 ImGui::Separator();

 // Bouton
 if (ImGui::Button( "Clique-moi !")) {
 counter++;
 }
 ImGui::SameLine();
 ImGui::Text( "Compteur = %d", counter);
 // Slider
 ImGui::SliderFloat( "Valeur", &slider_value, 0.0f, 1.0f);
 // Champ de texte
 ImGui::InputText( "Texte", text_buffer, IM_ARRAYSIZE(text_buffer));
 // Sélecteur de couleur
 ImGui::ColorEdit3( "Couleur de fond" , clear_color);
 // Checkbox
 ImGui::Checkbox( "Afficher la démo ImGui" , &show_demo_window);
 ImGui::Text( "Application moyenne %.3f ms/frame (%.1f FPS)" ,
 1000.0f / io.Framerate, io.Framerate);
 ImGui::End();
 }
 // � Rendu
 ImGui::Render();
 // Efface l'écran avec la couleur choisie
 SDL_SetRenderDrawColor(renderer,
 (Uint8)(clear_color[ 0] * 255),
 (Uint8)(clear_color[ 1] * 255),
 (Uint8)(clear_color[ 2] * 255),
 (Uint8)(clear_color[ 3] * 255)
 );
 SDL_RenderClear(renderer);
 // Dessine ImGui
 ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
 SDL_RenderPresent(renderer);
 }
 // � Nettoyage
 ImGui_ImplSDLRenderer3_Shutdown();
 ImGui_ImplSDL3_Shutdown();
 ImGui::DestroyContext();
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}