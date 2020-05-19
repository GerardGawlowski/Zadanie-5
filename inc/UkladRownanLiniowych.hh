#ifndef UKLADROWNANLINIOWYCH_HH
#define UKLADROWNANLINIOWYCH_HH

#include <iostream>
#include "Macierz.hh"
#include "Wektor.hh"
/*
 *  Tutaj trzeba opisac klase. Jakie pojecie modeluje ta klasa
 *  i jakie ma glowne cechy.
 */
template <typename xD>
class UkladRownanLiniowych {
public:
    Wektor<xD> getWektor()
    {
        return Wek1;
  }
    Macierz<xD> getMacierz()
    {
        return Ma1;
    }
    void setWektor(Wektor<xD> wektor)
    {
        Wek1 = wektor;
    }
    void setMacierz(Macierz<xD> macierz)
    {
        Ma1 = macierz;
    }
private:
    Macierz<xD> Ma1;
    Wektor<xD> Wek1;
};


/*
 Zapisywanie uk³adu równañ za pomoc¹ operatora >> 
 */
template <typename xD>
std::istream& operator >> (std::istream& Strm, UkladRownanLiniowych<xD>& UklRown)
{
    Macierz<xD> tempm;
    Strm >> tempm;
    UklRown.setMacierz(tempm);
    Wektor<xD> temp;
    Strm >> temp;
    UklRown.setWektor(temp);
    return Strm;
}

/*
 Wyœwietlanie uk³adu równañ za pomoc¹ operatora << 
 */
template <typename xD>
std::ostream& operator << (std::ostream& Strm, const UkladRownanLiniowych<xD>& UklRown)
{
    UkladRownanLiniowych<xD> temp;
    temp = UklRown;
    Strm << temp.getMacierz() << temp.getWektor();
    return Strm;
}

template <typename xD>
Wektor<xD> rozwiazcramer(UkladRownanLiniowych<xD> Ukl) {
    UkladRownanLiniowych<xD> wyniki;
    Macierz<xD> Mac = Ukl.getMacierz();
    Wektor<xD> Wek = Ukl.getWektor();
    Wektor<xD> Wynik{};
    xD wyznacznikglowny = Wyznacznik(Mac);
    xD wyznacznikzmiennych;
    if (wyznacznikglowny == 0)
    {
        std::cout << "Wyznacznik glowny jest rowny 0, Uklad nie ma rozwi¹zañ";
        return Wynik;
    }
    for (int i = 0; i < ROZMIAR; i++)
    {
        Mac.setWektor(i, Wek);
        wyznacznikzmiennych = Wyznacznik(Mac);
        Wynik.setSkladowa(i, (wyznacznikzmiennych / wyznacznikglowny));
        Mac = Ukl.getMacierz();
    }
    return Wynik;
}
/*Rozwiazuje uklad rownan za pomoca algorytmu cramera*/

template <typename xD>
Wektor<xD> WektorBledu(UkladRownanLiniowych<xD> Ukl1)
{
    Macierz<xD> Mac = Ukl1.getMacierz();
    Wektor<xD> B = Ukl1.getWektor();
    Wektor<xD> bledu;
    Wektor<xD> WynikCramera = rozwiazcramer(Ukl1);
    bledu = Mac * WynikCramera;
    bledu = bledu - B;
    return bledu;
}                                          /*Oblicza wektor bledu*/
#endif
