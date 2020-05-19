
#include "../inc/LZespolona.hh"
#include <iostream>
#include <cmath>

/*przeci¹¿enie operatora +, dodawanie*/
LZespolona  operator + (LZespolona  Skl1,  LZespolona  Skl2)
{
  LZespolona  Wynik;

  Wynik.re = Skl1.re + Skl2.re;
  Wynik.im = Skl1.im + Skl2.im;
  return Wynik;
}
/*przeci¹¿enie operatora -, odejmowanie*/
LZespolona  operator - (LZespolona  Skl1, LZespolona  Skl2)
{
    LZespolona  Wynik;

    Wynik.re = Skl1.re - Skl2.re;
    Wynik.im = Skl1.im - Skl2.im;
    return Wynik;
}
/*przeci¹¿enie operatora *, mno¿enie.*/
LZespolona  operator * (LZespolona  Skl1, LZespolona  Skl2)
{
    LZespolona  Wynik;

    Wynik.re = (Skl1.re * Skl2.re)-(Skl1.im * Skl2.im);
    Wynik.im = (Skl1.im *Skl2.re)+(Skl2.im * Skl1.re);
    return Wynik;
}
/*przeci¹¿enie operatora /, dzielenie*/
LZespolona  operator / (LZespolona  Skl1, LZespolona  Skl2)
{
    LZespolona Wynik;
    double temp= ((Skl2.re * Skl2.re) - (Skl2.im * (-Skl2.im)));
    Wynik.re = ((Skl1.re * Skl2.re) - (Skl1.im * (-Skl2.im)))/temp;
    Wynik.im = ((Skl1.im * Skl2.re) + ((-Skl2.im) * Skl1.re))/temp;
    return Wynik;
}
/*przeci¹¿enie operatora <<, s³u¿y do wyœwietlania liczb zespolonych np: cout << lzesp*/
std::ostream& operator << (std::ostream& os, const LZespolona& arg)
{
    os << '(' << arg.re;
    if (arg.im >= 0) {
        os << '+';
        os << arg.im;
        os << "i)";
    }
    else {
        os << arg.im;
        os << "i)";
    }
    return os;
}

  /*przeci¹¿enie operatora >>, s³u¿y do wprowadzania liczb zespolonych np: cin >> lzesp */
    std::istream& operator >> (std::istream& os, LZespolona &arg) {
        char tmp;
        double re, im;
        os >> tmp;
        if (tmp == '(')
        {
            
            os >> re;
            os >> im;
            os >> tmp;
            if (tmp == 'i')
            {
                os >> tmp;
                if (tmp == ')')
                {
                    arg.re = re;
                    arg.im = im;
                   
                }

            }
        }
        if (tmp != ')' || arg.re != re) {
            std::cout << "bledny sposob wprowadzania" << std::endl;
            std::cin.ignore(10000, '\n');
        }
    
        return os;
    }
    /*Funkcja modulo*/
    LZespolona operator % (LZespolona Skl1, LZespolona Skl2) {
      
        LZespolona Wynik;
        Wynik.re = std::fmod(Skl1.re, Skl2.re);
        Wynik.im = std::fmod(Skl1.im, Skl2.im);
        
        return Wynik;
    }
    /*porównanie dwóch liczb zespolonych*/
    int operator == (LZespolona Skl1, LZespolona Skl2) {
        if (Skl1.re == Skl2.re && Skl1.im == Skl2.im)
            return 1;
        else
            return 0;
    }
    int operator == (LZespolona Skl1, double Skl2)
    {
        if (Skl1.re == Skl2 && Skl1.im == Skl2)
            return 1;
        else
            return 0;
    }
   
    LZespolona operator * (LZespolona Skl1, double Skl2)
    {
        Skl1.re = Skl1.re * Skl2;
        Skl1.im = Skl1.im * Skl2;
        return Skl1;

    }
    int operator != (LZespolona Skl1, double Skl2)
    {
        if (Skl1.re != Skl2 && Skl1.im != Skl2)
            return 1;
        else
            return 0;
    }
    LZespolona ustaw(LZespolona Skl1, double Skl2)
    {
        Skl1.re = Skl2;
        Skl1.im = Skl2;
        return Skl1;
    }
    LZespolona operator * (double Skl2, LZespolona Skl1)
    {
        Skl1.re = Skl1.re * Skl2;
        Skl1.im = Skl1.im * Skl2;
        return Skl1;

    }