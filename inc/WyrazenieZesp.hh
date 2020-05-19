#ifndef WYRAZENIEZESP_HH
#define WYRAZENIEZESP_HH



#include "../inc/LZespolona.hh"

/*!
 * Modeluje zbior operatorow arytmetycznych.
 */
enum Operator { Op_Dodaj, Op_Odejmij, Op_Mnoz, Op_Dziel };



/*
 * Modeluje pojecie dwuargumentowego wyrazenia zespolonego
 */
struct WyrazenieZesp {
  LZespolona   Arg1;   // Pierwszy argument wyrazenia arytmetycznego
  char     Op;     // Opertor wyrazenia arytmetycznego
  LZespolona   Arg2;   // Drugi argument wyrazenia arytmetycznego
  friend std::ostream& operator << (std::ostream& os, const WyrazenieZesp& skl1);
  friend std::istream& operator >> (std::istream& os, WyrazenieZesp& skl1);
};


/*
 * Funkcje ponizej nalezy zdefiniowac w module.
 *
 */


void WyswietlW(WyrazenieZesp  WyrZ);
void WczytajW(WyrazenieZesp WyrZ);
LZespolona Oblicz(WyrazenieZesp  WyrZ);

#endif
