#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'
echo -e "${YELLOW}�  Compilation de l'application complète... ${NC}"
# Chemins
IMGUI_DIR="./libs/imgui"
STB_DIR="./libs/stb"
IMGUI_SOURCES="$IMGUI_DIR/imgui.cpp \
 $IMGUI_DIR/imgui_demo.cpp \
 $IMGUI_DIR/imgui_draw.cpp \
 $IMGUI_DIR/imgui_tables.cpp \
 $IMGUI_DIR/imgui_widgets.cpp \
 $IMGUI_DIR/backends/imgui_impl_sdl3.cpp \
 $IMGUI_DIR/backends/imgui_impl_sdlrenderer3.cpp"
# Compilation
clang++ src/main_full.cpp $IMGUI_SOURCES -o build/app_complete \
 -I$IMGUI_DIR \
 -I$IMGUI_DIR/backends \
 -I$STB_DIR \
 -lSDL3 \
 -std=c++17 \
 -O2 -Wall -Wextra
if [ $? -eq 0 ]; then
void SetupCoolTheme() {
 ImGuiStyle& style = ImGui::GetStyle();
 // Coins arrondis
 style.WindowRounding = 5.0f;
 style.FrameRounding = 4.0f;
 style.GrabRounding = 3.0f;
 // Couleurs personnalisées (exemple cyberpunk)
 ImVec4* colors = style.Colors;
 colors[ImGuiCol_WindowBg] = ImVec4( 0.1f, 0.1f, 0.13f, 0.94f);
 colors[ImGuiCol_Button] = ImVec4( 0.2f, 0.6f, 0.86f, 0.4f);
 colors[ImGuiCol_ButtonHovered] = ImVec4( 0.2f, 0.7f, 1.0f, 1.0f);
 colors[ImGuiCol_ButtonActive] = ImVec4( 0.15f, 0.5f, 0.8f, 1.0f);
}

// Tous ces formats fonctionnent !
LoadImageTexture(renderer, "image.png"); // PNG (avec transparence)
LoadImageTexture(renderer, "photo.jpg"); // JPEG
LoadImageTexture(renderer, "icon.bmp"); // BMP
LoadImageTexture(renderer, "anim.gif"); // GIF (première frame)
LoadImageTexture(renderer, "texture.tga"); // TGA
LoadImageTexture(renderer, "art.psd"); // Photoshop !
LoadImageTexture(renderer, "hdr.hdr"); // HDR
// Utile pour les ressources embarquées
unsigned char* image_data = stbi_load_from_memory(
 data_buffer,
 data_size,
 &width, &height, &channels,
 4 // Force RGBA
);