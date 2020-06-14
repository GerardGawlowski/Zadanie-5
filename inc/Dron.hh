#ifndef DRON_HH
#define DRON_HH

#include "lamana.hh"
#include "Wektor3D.hh"
#include <string>
#include <vector>
#include <iostream>
#include "Bryla.hh"

class Dron

{
private:
    std::vector<Brylageometryczna> Dronik;
public:
    Brylageometryczna getbrylaindeks(unsigned int indeks)
    {
        return Dronik[indeks];
    }
    std::vector<Brylageometryczna> getvektor()
    {
        return Dronik;
    }
    void addbryla(Brylageometryczna a)
    {
        Dronik.push_back(a);
    }
    void removebryla()
    {
        Dronik.pop_back();
    }
    void setvector(std::vector<Brylageometryczna> nowydronik)
    {
        Dronik=nowydronik;
    }

};
Dron Ruchy(Dron dronik, std::vector<double> WartosciobrotuZ, std::vector<double> WartosciobrotuX, std::vector<double> Przemieszczenie, std::vector<char> kolejnosc);
void zapiszdopliku (Dron dronik,const char* plik);                  //zapisanie do pliku
Wektor3D Znajdzwektorprzemieszczenia(Wektor3D wektor, double ileprzemieszczen, double ileobrotow, std::vector<double>WartosciobrotuX, std::vector<double> WartosciobrotuZ);
Dron Animacja(Dron dronporuchu,Dron dronprzedruchem,std::vector<double> jednostkiprzemieszczenia,std::vector<double> katobrotuosix,std::vector<double>katobrotuosiz,const char* plik,std::vector<char> kolejnosc,Dron Dronik);
Dron AnimacjaWirniki(Dron dronprzedruchem,std::vector<double> katobrotuosiz, Dron dronik,double krok,std::vector<char>kolejnosc);
#endif
