#pragma once 
#ifndef METEO_H
#define METEO_H
#include<vector>
#include<iostream>


enum class Meteo {
    Soleil,
    Pluie,
    Nuageux,
    Neige,
    Orage
};
/**
 * la procedure UpdateMeteo permet de mettre à jour les animation 
 * DrawMeteo permet de dessiner la meteo
 * SetMeteo permet de changer la meteo
 */
void UpdateMeteo(float deltaTime); 
void DrawMeteo();
void SetMeteo(Meteo type);
void DrawUI(Meteo& meteo);
#endif