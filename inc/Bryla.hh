#ifndef BRYLA_HH
#define BRYLA_HH

#include "lamana.hh"
#include "Wektor3D.hh"
#include <string>
#include <vector>
#include <iostream>

class Brylageometryczna
{
    public:
     Lamana getlamanaindeks(unsigned int indeks)
    {
        return lamane[indeks];
    }
    std::vector<Lamana> getvektor()
    {
        return lamane;
    }
    void addlamana(Lamana a)
    {
        lamane.push_back(a);
    }
    void setvector(std::vector<Lamana> nowelamane)
    {
        lamane=nowelamane;
    }
    private:
    std::vector<Lamana> lamane;
};


Brylageometryczna odczytdrona (const char *plik);
void stworzpowierzchnie(const char* plik, double wysokosc);                         //Tworzenie powierzchni wody i ziemi
Brylageometryczna RotacjadronaZ(Brylageometryczna dron, double katobrotu);             // Rotacja drona o Z
Brylageometryczna RotacjadronaX(Brylageometryczna dron, double katobrotu);          // Rotacja drona o X
Brylageometryczna RotacjadronaY(Brylageometryczna dron, double katobrotu);        //Rotacja drona o Y
Brylageometryczna transformacjaowektor(Brylageometryczna dron, Wektor3D T);      //transformacja o wektor
Wektor3D srodekbryly(Brylageometryczna bryla);                       //znalezienie srodka bryly do poprawek w przemieszczeniu(zeby dron obracal sie wokol wlasnej osi)
Wektor3D znajdzwektor3D(std::vector<char> osie, std::vector<double>wartosci, Wektor3D trzyde,double oile);           //Znalezienie wektora przemieszczenia w oparciu o wczesniejsze obroty
Wektor3D znajdzwektor(std::vector<char> osie, std::vector<double>wartosci, double odleglosc,double oile);           //Znalezienie wektora przemieszczenia w oparciu o wczesniejsze obroty
Wektor3D RotacjawektoraZ(Wektor3D wektor, double katobrotu);     //Rotacja wektora o os Z
Wektor3D RotacjawektoraX(Wektor3D wektor, double katobrotu);    //Rotacja wektora o os X
Wektor3D RotacjawektoraY(Wektor3D wektor, double katobrotu);   //Rotacja wektora o os Y



#endif