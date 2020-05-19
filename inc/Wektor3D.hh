#ifndef WEKTOR3D_HH
#define WEKTOR3D_HH
#include "Wektor.hh"
#include <iostream>

class Wektor3D
{
    public:
    Wektor<double,3> getWektor()
    {
        return wektor;
    }
    void setWektor(Wektor<double,3> nowywektor)
    {
        wektor=nowywektor;
    }

    private:
    Wektor<double,3> wektor;
};



#endif