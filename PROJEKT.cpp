// PROJEKT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;
class FiguraGeometryczna
{
public:
    double wysokosc, szerokosc;
    double Obliczpolepowierzchni()
    {
        return wysokosc * szerokosc;
    }
    void zwrocnazwe();
};

class Prostokat : public FiguraGeometryczna 
{
public:

    double Obliczpolewpowierzchni()
    {
        return a * b;
    }
    void zwrocnazwe()
    {
        cout << " prostokat ";
    }
    double a, b;
    int cotojest = 1;
};

class kolo : public FiguraGeometryczna
{
public:
    double Obliczpolewpowierzchni()
    {
        return 3.14 * promien * promien;
    }
    void zwrocnazwe()
    {
        cout << "kolo";
    }

    double promien;
    int cotojest = 0;
};

int main()
{
    vector<kolo> kola;
    vector<Prostokat> prostokaty;
    kolo jeden;
    kolo dwa;
    jeden.promien = 5;
    dwa.promien = 10;
    kola.push_back(jeden);
    kola.push_back(dwa);
    Prostokat trzy;
    Prostokat cztery;
    trzy.a = 5;
    trzy.b = 10;
    cztery.a = 10;
    cztery.b = 20;
    prostokaty.push_back(trzy);
    prostokaty.push_back(cztery);
    for (int i = 0; i < kola.size(); i++)
    {
        kolo robocze = kola[i];
        cout << "pole : " << robocze.Obliczpolewpowierzchni() << "Nazwa: "; 
        robocze.zwrocnazwe();
        cout<< endl;
    }
    for (int i = 0; i < prostokaty.size(); i++)
    {
        Prostokat robocze = prostokaty[i];
        cout << "pole : " << robocze.Obliczpolewpowierzchni() << "Nazwa: ";
        robocze.zwrocnazwe();
        cout << endl;
    }
    vector<FiguraGeometryczna> Rozne;
    Rozne.push_back(jeden);
    Rozne.push_back(dwa);
    
}


