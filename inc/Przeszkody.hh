#ifndef PRZESZKODY_HH
#define PRZESZKODY_HH

#include "lamana.hh"
#include "Wektor3D.hh"
#include "Bryla.hh"
#include <string>
#include <vector>
#include <iostream>

class Przeszkoda {
    protected:
    Brylageometryczna przeszkoda;
    public:
    void setbryla (Brylageometryczna bryla)
    {przeszkoda=bryla;}
    virtual std::string zwrocnazwe(){
        return "0";
    }
    Wektor3D srodek()
    {
        return srodekbryly(przeszkoda);
    }
    Wektor3D maksimum()
    {
        return Maxxyz(przeszkoda);
    }
    Wektor3D minimum()
    {
        return Minxyz(przeszkoda);
    }
    Brylageometryczna getprzeszkoda()
    {
        return przeszkoda;
    }
};

class pret: public Przeszkoda {
    public:
    std::string zwrocnazwe()
    {
        return "pret";
    }

};

class sciana: public Przeszkoda{
    public:
    std::string zwrocnazwe()
    {
        return "sciana";
    }
};

class bryla: public Przeszkoda{
    public:
    std::string zwrocnazwe()
    {
        return "bryla";
    }
};

#endif