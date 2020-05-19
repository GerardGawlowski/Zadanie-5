#ifndef MACIERZ_HH
#define MACIERZ_HH


#include "Wektor.hh"
#include <iostream>


/*
 * Klasa modeluje Macierz w postaci tablicy wektor�w reprezentuj�cych kolumny
 */
template<typename xD, int ROZMIAR>
class Macierz {
public:
    Wektor<xD,ROZMIAR> getWektor(unsigned int index)
    {
        return kolumny[index];
    }

    void setWektor(unsigned int index, Wektor<xD,ROZMIAR> wektor) 
    {
        kolumny[index] = wektor; 
    }
  
private:
    Wektor<xD,ROZMIAR> kolumny[ROZMIAR];
};


/*
 Zapisuje Macierz za pomoc� operatora >>
 */
template<typename xD, int ROZMIAR >
std::istream& operator >> (std::istream& Strm, Macierz<xD, ROZMIAR>& Mac)
{
    for (int i = 0; i < ROZMIAR; i++)
    {
        Wektor<xD,ROZMIAR> kek;
        Strm >> kek;
        Mac.setWektor(i, kek);
    }
    return Strm;
}

/*
 Wy�wietla Macierz za pomoc� operatora <<
 */
template<typename xD,int ROZMIAR >
std::ostream& operator << (std::ostream& Strm, const Macierz<xD, ROZMIAR>& Mac)
{
    for (int i = 0; i < ROZMIAR; i++)
    {
        Macierz<xD,ROZMIAR> Cam;
        Cam = Mac;
        Strm << Cam.getWektor(i) << std::endl;

    }
    return Strm;
}

template<typename xD,int ROZMIAR>
Macierz<xD,ROZMIAR> Gauss(Macierz<xD,ROZMIAR> Mac)                              /*Zmienia macierz za pomoc� algorytmu gaussa do macierzy tr�jk�tnej */
{
    Wektor<xD,ROZMIAR> Wynik;                           /*wektor pomocniczny*/
    Macierz<xD,ROZMIAR> Kac = Mac;                      /* Macierz pomocnicza taka sama jak Kac*/
    for (int i = 0; i < ROZMIAR; i++)
    {
        Wektor<xD,ROZMIAR> temp = Kac.getWektor(i);     /*Pobranie wektora do zmiennej pomocniczej temp*/
        xD a = temp.getSkladowa(i);       /*Pobranie odpowiedniej skladowej wektora do eliminacji*/

        if (a == 0)                         /* petla sprawdzajaca czy a jest zerem i zamieniajaca odpowiednio wiersze zeby moc kontynuowac obliczanie*/
        {

            for (int y = i + 1; a == 0; y++)
            {
                if (y < ROZMIAR)
                {
                    Wynik = Kac.getWektor(y);
                    a = Wynik.getSkladowa(i);
                    if (a != 0)
                    {
                        Kac.setWektor(y, (temp * -1));
                        Kac.setWektor(i, Wynik);
                    }
                }
            }
            temp = Kac.getWektor(i);
            a = temp.getSkladowa(i);
        }
        for (int j = i + 1; j < ROZMIAR; j++)     /*petla wykonujaca eliminacje gaussa*/
        {
            Wektor<xD,ROZMIAR> temp2 = Kac.getWektor(j);
            xD b = temp2.getSkladowa(i);
            xD c;
            if (a != 0) {
                c = b / a;
            }
            else
            {
                c = 0;
            }
            Wynik = temp * c;
            temp2 = temp2 - Wynik;
            Kac.setWektor(j, temp2);
        }
    }
    return Kac;
}                                                                           

template <typename xD,int ROZMIAR>
xD Wyznacznik(Macierz<xD, ROZMIAR> Mac)                                              /*Oblicza wyznacznik macierzy tr�jk�tnej*/
{
    Macierz<xD,ROZMIAR> kek = Gauss(Mac);
    xD elem;
    xD wynik;
    wynik = 1;
    for (int i = 0; i < ROZMIAR; i++)
    {
        Wektor<xD,ROZMIAR> temp = kek.getWektor(i);
        wynik = wynik * temp.getSkladowa(i);
    }
    return wynik;
}
                                                                            
template <typename xD,int ROZMIAR>
Macierz<xD,ROZMIAR> root(Macierz<xD, ROZMIAR> Mac)                               /*Podnosi macierz do kwadratu*/
{
    Macierz<xD,ROZMIAR> Wynik;
    for (int i = 0; i < ROZMIAR; i++)
    {
        Wektor<xD,ROZMIAR> temp = Mac.getWektor(i);
        for (int j = 0; j < ROZMIAR; j++)
        {
            double a = temp.getSkladowa(j);
            double b = a * a;
            temp.setSkladowa(j, b);
        }
        Wynik.setWektor(i, temp);
    }
    return Wynik;
}                

template <typename xD,int ROZMIAR>
Wektor<xD,ROZMIAR> operator * (Macierz<xD,ROZMIAR> Mac,Wektor<xD,ROZMIAR> wk1)                  /*Mno�enie Macierzy przez wektor*/
{
    Wektor<xD,ROZMIAR> Wynik;
    Wektor<xD,ROZMIAR> doMnozenia;
    for (int i = 0; i < ROZMIAR; i++)
    {
        for (int j = 0; j < ROZMIAR; j++)
        {
            Wektor<xD,ROZMIAR> petla = Mac.getWektor(j);
            doMnozenia.setSkladowa(j, petla.getSkladowa(i));
        }
        Wynik.setSkladowa(i, doMnozenia * wk1);
    }
    return Wynik;
}   
template <typename xD,int ROZMIAR>
Macierz<xD,ROZMIAR> operator - (Macierz<xD,ROZMIAR> Mac1, Macierz<xD,ROZMIAR> Mac2)
{
    Macierz<xD,ROZMIAR> Wynik;
    for (int i = 0; i < ROZMIAR; i++)
    {
        Wektor<xD,ROZMIAR> Obrobka = Mac1.getWektor(i) - Mac2.getWektor(i);
        Wynik.setWektor(i, Obrobka);
    }
    return Wynik;
}

template <typename xD,int ROZMIAR>
Macierz<xD,ROZMIAR> operator * (Macierz<xD,ROZMIAR> Mac1, Macierz<xD,ROZMIAR> Mac2)
{
    Macierz<xD,ROZMIAR> Wynik;
    Wektor<xD,ROZMIAR> doMnozenia;
    Wektor<xD,ROZMIAR> malywynik;
    for (int i = 0; i < ROZMIAR; i++)
    {
        for (int j = 0; j < ROZMIAR; j++)
        {
            Wektor<xD,ROZMIAR> petla = Mac1.getWektor(j);
            doMnozenia.setSkladowa(j, petla.getSkladowa(i));
            for (int x = 0; x < ROZMIAR; x++)
            {
                malywynik.setSkladowa(x, doMnozenia * Mac2.getWektor(x));
            }
        }
        Wynik.setWektor(i, malywynik);
    }
    return Wynik;
}
#endif
