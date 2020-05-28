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
    void setvector(std::vector<Brylageometryczna> nowydronik)
    {
        Dronik=nowydronik;
    }

};

Dron Master(Dron dronik,std::vector<char> kolejnosc, std::vector<char> osie, std::vector<double> wartosci, std::vector<double> przemieszczenie);    //Funkcja laczaca przemieszczenia i obroty,aby poprawnie umiescic drona
void zapiszdopliku (Dron dronik,const char* plik);                  //zapisanie do pliku

#endif
