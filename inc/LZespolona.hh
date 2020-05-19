#ifndef LZESPOLONA_HH
#define LZESPOLONA_HH

#include<iostream> 


class LZespolona {
public:
  double   re;    /*! Pole repezentuje czesc rzeczywista. */
  double   im;    /*! Pole repezentuje czesc urojona. */
  friend std::ostream& operator << (std::ostream& os, const LZespolona& skl1);
  friend std::istream& operator >> (std::istream& os, LZespolona& skl1);
  void operator = (const double& Skl2)
  {
      re = Skl2;
      im = Skl2;
 }
  
};

void wyswietl(LZespolona arg);

void wczytaj(LZespolona *arg);

LZespolona  operator + (LZespolona  Skl1,  LZespolona  Skl2);
LZespolona operator - (LZespolona Skl1, LZespolona Skl2);
LZespolona operator * (LZespolona Skl1, LZespolona Skl2);
LZespolona operator / (LZespolona Skl1, LZespolona Skl2);
LZespolona operator % (LZespolona Skl1, LZespolona Skl2);
LZespolona operator * (LZespolona Skl1, double Skl2);
LZespolona operator * (double Skl2, LZespolona Skl1);
int operator == (LZespolona Skl1, LZespolona Skl2);
int operator == (LZespolona Skl1, double SKl2);
int operator != (LZespolona Skl1, double Skl2);
LZespolona ustaw(LZespolona Skl1, double Skl2);
#endif

LZespolona dziel(LZespolona arg, LZespolona mab);
