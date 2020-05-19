#ifndef WEKTOR_HH
#define WEKTOR_HH


#include <iostream>



template <typename xD,int ROZMIAR>
class Wektor {
 
  public:
      xD getSkladowa(unsigned int index) 
      {
          return skladowa[index];
      }
      void setSkladowa(unsigned int index, xD wartosc) 
      {
          skladowa[index] = wartosc;
      }
      
private:
    xD skladowa[ROZMIAR];
};

template <typename xD,int ROZMIAR>
std::istream& operator >> (std::istream& Strm, Wektor<xD,ROZMIAR>& Wek)
{
    for (int i = 0; i < ROZMIAR; i++)
    {
        xD a;
        Strm >> a;
        Wek.setSkladowa(i, a);
    }

    return Strm;
}

template <typename xD,int ROZMIAR>
std::ostream& operator << (std::ostream& Strm, const Wektor<xD,ROZMIAR>& Wek)
{
    for (int i = 0; i < ROZMIAR; i++)
    {
        Wektor<xD,ROZMIAR> kek;
        kek = Wek;
        xD a;
        a = kek.getSkladowa(i);
        Strm << a << ' ';
    }
    return Strm;
}

template <typename xD,int ROZMIAR>
Wektor<xD,ROZMIAR> operator - (Wektor<xD,ROZMIAR> wk1, Wektor<xD,ROZMIAR> wk2)                   /*R�nica wektor�w*/
{
    Wektor<xD,ROZMIAR> Wynik;
    for (int i = 0; i < ROZMIAR; i++)
    {
        xD a, b, c;
        a = wk1.getSkladowa(i);
        b = wk2.getSkladowa(i);
        c = a - b;
        Wynik.setSkladowa(i, c);
    }
    return Wynik;
}      

template <typename xD,int ROZMIAR>
Wektor<xD,ROZMIAR> operator + (Wektor<xD,ROZMIAR> wk1, Wektor<xD,ROZMIAR> wk2)
{
    Wektor<xD,ROZMIAR> Wynik;
    for (int i = 0; i < ROZMIAR; i++)
    {
        xD a, b, c;
        a = wk1.getSkladowa(i);
        b = wk2.getSkladowa(i);
        c = a + b;
        Wynik.setSkladowa(i, c);
    }
    return Wynik;
}                 /*Suma wektor�w*/

template <typename xD,int ROZMIAR>
xD operator * (Wektor<xD,ROZMIAR> wk1, Wektor<xD,ROZMIAR> wk2)
{
    xD wynik{};
    wynik = wynik * 0;
    for (int i = 0; i < ROZMIAR; i++)
    {
        xD a, b, c;
        a = wk1.getSkladowa(i);
        b = wk2.getSkladowa(i);
        c = a * b;
        wynik = c + wynik;
    }
    return wynik;
}                 /*iloczyn skalarny wektor�w*/

template <typename xD, int ROZMIAR, typename T>
Wektor<xD, ROZMIAR> operator * (Wektor<xD,ROZMIAR> wk1, T wk2)
{
    Wektor<xD,ROZMIAR> wynik;
    for (int i = 0; i < ROZMIAR; i++)
    {
        xD a;
        a = wk1.getSkladowa(i);
        wynik.setSkladowa(i, a * wk2);
    }
    return wynik;
}                /*Mno�enie wektora przez liczb�*/

template <typename xD, int ROZMIAR>
Wektor<xD,ROZMIAR> IloczynWR3(Wektor<xD,ROZMIAR> wk1, Wektor<xD,ROZMIAR> wk2)
{
    Wektor<xD,ROZMIAR> Wynik;
    xD a = (wk1.getSkladowa(1) * wk2.getSkladowa(2)) - (wk1.getSkladowa(2) * wk2.getSkladowa(1));
    xD b = (((wk1.getSkladowa(0) * wk2.getSkladowa(2)) - (wk1.getSkladowa(2) * wk2.getSkladowa(0))) * (-1));
    xD c = (wk1.getSkladowa(0) * wk2.getSkladowa(1)) - (wk1.getSkladowa(1) * wk2.getSkladowa(0));
    Wynik.setSkladowa(0, a);
    Wynik.setSkladowa(1, b);
    Wynik.setSkladowa(2, c);
    return Wynik;
}







#endif
