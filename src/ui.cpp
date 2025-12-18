#include "../include/ui.h"
#include "../libs/imgui/imgui.h"
extern Meteo meteo;

void SetPress(float& intensity,float& density, float& wind, float& frequency){
    ImGui::Separator();

    ImGui::SliderFloat("Intensité pluie", &intensity, 0.0f, 2.0f);
    ImGui::SliderFloat("Densité neige", &density, 0.0f, 2.0f);
    ImGui::SliderFloat("Vent", &wind, -100.0f, 100.0f);
    ImGui::SliderFloat("Fréquence éclairs", &frequency, 0.0f, 0.2f);
} 



void DrawUI(Meteo& meteo) {
    ImGui::Begin("Controle Meteo");
    if (ImGui::Button("Soleil"))
    SetMeteo(Meteo::Soleil);
    if (ImGui::Button("Pluie"))
    SetMeteo(Meteo::Pluie);
    if (ImGui::Button("Nuageux"))
    SetMeteo(Meteo::Nuageux);
    if (ImGui::Button("Orage"))
    SetMeteo(Meteo::Orage);
    if (ImGui::Button("Neige"))
    SetMeteo(Meteo::Neige);
}
