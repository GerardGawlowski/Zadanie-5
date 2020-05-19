#ifndef LAMANA_HH
#define LAMANA_HH

#include "Wektor.hh"
#include "Wektor3D.hh"
#include <iostream>
#include <vector>

class Lamana 
{
    public:
    Wektor3D getwektorindeks(unsigned int indeks)
    {
        return wektory[indeks];
    }
    std::vector<Wektor3D> getvektor()
    {
        return wektory;
    }
    void addwektor(Wektor3D wektor)
    {
        wektory.push_back(wektor);
    }
    void setvector(std::vector<Wektor3D> nowywektor)
    {
        wektory=nowywektor;
    }
    private:
    std::vector<Wektor3D> wektory;
};

#endif