#include "../include/ui.h"
#include "../libs/imgui/imgui.h"

void DrawUI(Meteo& meteo) {
    ImGui::Begin("Controle Meteo");

    if (ImGui::Button("☀ Soleil"))  meteo = Meteo::Soleil;
    if (ImGui::Button("☁ Nuageux")) meteo = Meteo::Nuageux;
    if (ImGui::Button("🌧 Pluie"))   meteo = Meteo::Pluie;
    if (ImGui::Button("⛈ Orage"))   meteo = Meteo::Orage;

    ImGui::Text("Meteo actuelle : %s", MeteoToString(meteo));
    ImGui::End();
}

const char* MeteoToString(Meteo m) {
    switch (m) {
        case Meteo::Soleil:  return "Soleil";
        case Meteo::Nuageux: return "Nuageux";
        case Meteo::Pluie:   return "Pluie";
        case Meteo::Orage:   return "Orage";
        default:             return "Inconnu";
    }
}
