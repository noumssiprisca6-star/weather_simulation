#pragma once 

#include<iostream>
#ifndef METEO_H
#define METEO_H
enum  class Meteo{
    Soleil ,
    Nuageux ,
    Pluie ,
    Orage , 
    Neige
};

const char*MeteoToString(Meteo meteo);
bool IsSunny(Meteo meteo);
bool iscloudy(Meteo meteo);
bool israiny(Meteo meteo);
bool isStormy(Meteo meteo);
#endif