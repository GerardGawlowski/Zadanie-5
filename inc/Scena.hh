#ifndef SCENA_HH
#define SCENA_HH

#include "lamana.hh"
#include "Wektor3D.hh"
#include "Bryla.hh"
#include "Dron.hh"
#include "Przeszkody.hh"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Scena
{
    private:
    Dron Dronik;
    std::vector<std::shared_ptr<Przeszkoda>> przeszkody;
    public:
    Dron getdron()
    {
        return Dronik;
    }
    std::vector<std::shared_ptr<Przeszkoda>> getvector()
        {
            return przeszkody;
        }
    void setvector(std::vector<std::shared_ptr<Przeszkoda>> nowe)
    {
        przeszkody=nowe;
    }
    void setdron(Dron nowy)
    {
        Dronik=nowy;
    }
    void addprzeszkoda(std::shared_ptr<Przeszkoda> nowa)
    {
        przeszkody.push_back(nowa);
    }
    
};



double Kolizja (Scena scena);
void zapiszscenedopliku (Scena scenka,const char* plik);
#endif