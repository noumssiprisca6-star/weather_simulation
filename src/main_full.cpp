#include "../libs/SDL3/SDL.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h> 
// Active l'implémentation de stb_image (une seule fois dans tout le projet)
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#include <iostream>
#include <string> 
//Fonction pour charger une image avec stb_image
SDL_Texture* LoadImageTexture(SDL_Renderer* renderer, const char* filepath) { 
int width, height, channels; 
// Charge l'image en mémoire 
unsigned char* image_data = stbi_load(filepath, &width, &height, &channels, 
4); // Force RGBA 
if (!image_data) { 
std::cerr << "Erreur stb_image: " << stbi_failure_reason() << 
std::endl; 
return nullptr; 
    } 
std::cout << "Image chargée: " << width << "x" << height  
              << 
" (" << channels << " canaux)" << std::endl; 
// Crée une texture SDL 
    SDL_Texture* texture = SDL_CreateTexture( 
        renderer, 
        SDL_PIXELFORMAT_RGBA32, 
        SDL_TEXTUREACCESS_STATIC, 
        width, height 
    ); 
if (!texture) { 
std::cerr << "Erreur création texture: " << SDL_GetError() << std::endl;
        stbi_image_free(image_data); 
return nullptr; 
    } 
// Copie les pixels dans la texture 
    SDL_UpdateTexture(texture, nullptr, image_data, width * 4); 
// Libère la mémoire de stb_image 
    stbi_image_free(image_data); 
return texture; 
} 
int main(int argc, char* argv[]) { 
    // Init SDL3 
    if (!SDL_Init(SDL_INIT_VIDEO)) { 
    std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl; 
    return 1; 
        } 
        SDL_Window* window = SDL_CreateWindow( 
    "SDL3 + ImGui + stb_image 🎨", 
    1280, 720, 
            SDL_WINDOW_RESIZABLE 
        ); 
    if (!window) { 
    std::cerr << "Erreur fenêtre: " << SDL_GetError() << std::endl; 
            SDL_Quit(); 
    return 1; 
        } 
        SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr); 
    if (!renderer) { 
    std::cerr << "Erreur renderer: " << SDL_GetError() << std::endl; 
            SDL_DestroyWindow(window); 
            SDL_Quit(); 
    return 1; 
        } 
    // Setup ImGui 
        IMGUI_CHECKVERSION(); 
        ImGui::CreateContext(); 
        ImGuiIO& io = ImGui::GetIO(); 
        ImGui::StyleColorsDark(); 
        ImGui_ImplSDL3_InitForSDLRenderer(window, renderer); 
        ImGui_ImplSDLRenderer3_Init(renderer); 
    // Charge une image test 
        SDL_Texture* test_texture = LoadImageTexture(renderer, 
    "../assets/test_image.png"); 
    float tex_width = 0, tex_height = 0;
    if (test_texture) { 
            SDL_GetTextureSize(test_texture, &tex_width, &tex_height); 
    std::cout << "Texture créée: " << tex_width << "x" << tex_height << 
    std::endl; 
        } 
    // Variables d'interface 
    bool show_image = true; 
    float image_scale = 1.0f; 
    float clear_color[3] = {0.1f, 0.1f, 0.15f}; 
    char image_path[256] = "assets/test_image.png"; 
    bool show_info_window = true; 
    // Boucle principale 
    bool running = true; 
        SDL_Event event; 
    while (running) { 
    while (SDL_PollEvent(&event)) { 
                ImGui_ImplSDL3_ProcessEvent(&event); 
    if (event.type == SDL_EVENT_QUIT) { 
        running = false; 
    } 
    } 
    // Nouvelle frame ImGui 
    ImGui_ImplSDLRenderer3_NewFrame(); 
    ImGui_ImplSDL3_NewFrame(); 
    ImGui::NewFrame(); 
    // Interface ImGui 
    if (show_info_window) { 
                ImGui::Begin("Contrôles 🎛", &show_info_window); 
                ImGui::Text("Bienvenue dans l'app ultime !"); 
                ImGui::Separator(); 
    // Contrôles de l'image 
                ImGui::Checkbox("Afficher l'image", &show_image); 
    if (test_texture) { 
                    ImGui::SliderFloat("Échelle", &image_scale, 0.1f, 3.0f); 
                    ImGui::Text("Dimensions: %fx%f pixels", tex_width, tex_height); 
                } 
                ImGui::Separator(); 
    // Chargement d'image 
                ImGui::InputText("Chemin image", image_path, 
    IM_ARRAYSIZE(image_path)); 
    if (ImGui::Button("Charger nouvelle image")) { 
    if (test_texture) { 
            SDL_DestroyTexture(test_texture); 
                    } 
                    test_texture = LoadImageTexture(renderer, image_path); 
    if (test_texture) { 
                    SDL_GetTextureSize(test_texture, &tex_width, &tex_height); 
                    } 
                } 
                ImGui::Separator(); 
    // Couleur de fond 
                ImGui::ColorEdit3("Couleur de fond", clear_color); 
                ImGui::Text("FPS: %.1f", io.Framerate); 
                ImGui::End(); 
            } 
    // Fenêtre pour afficher l'image dans ImGui 
    if (show_image && test_texture) { 
                ImGui::Begin("Aperçu Image 🖼"); 
    ImVec2 size(tex_width * image_scale, tex_height * image_scale); 
                ImGui::Image((ImTextureID)(intptr_t)test_texture, size); 
                ImGui::End(); 
            } 
    // Rendu 
            ImGui::Render(); 
            SDL_SetRenderDrawColor(renderer, 
                (Uint8)(clear_color[0] * 255), 
                (Uint8)(clear_color[1] * 255), 
                (Uint8)(clear_color[2] * 255), 
    255 
            ); 
            SDL_RenderClear(renderer); 
    // Dessine l'image en arrière-plan (optionnel) 
    if (test_texture && show_image) { 
                SDL_FRect dest = { 
    100, 100,  
                    ( float)tex_width * image_scale,  
                    ( float)tex_height * image_scale 
                }; 
    // SDL_RenderTexture(renderer, test_texture, nullptr, &dest); 
            } 
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer); 
            SDL_RenderPresent(renderer); 
        }
        // Nettoyage 
    if (test_texture) SDL_DestroyTexture(test_texture); 
        ImGui_ImplSDLRenderer3_Shutdown(); 
        ImGui_ImplSDL3_Shutdown(); 
        ImGui::DestroyContext(); 
        SDL_DestroyRenderer(renderer); 
        SDL_DestroyWindow(window); 
        SDL_Quit(); 
    return 0; 
} 