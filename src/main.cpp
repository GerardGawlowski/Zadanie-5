#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

#include "../inc/Wektor.hh"
#include "../inc/Macierz.hh"
#include "../inc/LZespolona.hh"
#include "../inc/WyrazenieZesp.hh"
#include "../inc/lacze_do_gnuplota.hh"
#include "../inc/lamana.hh"
#include "../inc/Wektor3D.hh"
#include "../inc/Bryla.hh"
using namespace std;


int main()
{
  PzG::LaczeDoGNUPlota  Lacze;
  char c;
  vector<char> osieobrotu;
  vector<double> wartosciobrotu;
  vector<double> przemieszczenie;
  Brylageometryczna dron;
  const char* pliksceny;
  pliksceny = "../bryly/scena.dat";
  dron=odczytdrona();
  zapiszdopliku(dron,pliksceny);
  stworzpowierzchnie("../bryly/Woda.dat",90);
  stworzpowierzchnie("../bryly/Ziemia.dat", -80 );
  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.

  Lacze.UstawZakresX(-90, 90);
  Lacze.UstawZakresY(-90, 90);
  Lacze.UstawZakresZ(-90, 90);

  Lacze.UsunWszystkieNazwyPlikow();
  Lacze.UstawRotacjeXZ(75,55); // Tutaj ustawiany jest widok
  Lacze.DodajNazwePliku("../bryly/Woda.dat");
  Lacze.DodajNazwePliku("../bryly/Ziemia.dat");
  Lacze.DodajNazwePliku("../bryly/scena.dat");
  Lacze.DodajNazwePliku("../bryly/chuj.dat");
  Lacze.Rysuj(); 
  char menu='0';
  Brylageometryczna dronglobalny=dron;    // Teraz powinno pojawic sie okienko gnuplota
  while (menu!='q')
  {
    dronglobalny=Master(dron,osieobrotu,wartosciobrotu,przemieszczenie);
    zapiszdopliku(dronglobalny,pliksceny);
    Lacze.Rysuj();
    cout << "Sterowanie dronem" << endl;
    cout << "o - obrót drona" << endl;
    cout << "r - ruch do przodu" << endl;
    cout << "q - wyjście z symulacji" << endl;
    cin >> menu;
    switch(menu)
    {
      case 'o':
      char obrot;
      double stopnie;
      cout << "W jakiej osi?";
      cin >> obrot;
      if (obrot=='x')
      {
        osieobrotu.push_back(obrot);
        cout << "O ile stopni?";
        cin >>stopnie;
        wartosciobrotu.push_back(stopnie);
        
      }
      if (obrot=='y')
      {
        osieobrotu.push_back(obrot);
        cout << "O ile stopni?";
        cin >>stopnie;
        wartosciobrotu.push_back(stopnie);
      }
      if (obrot=='z')
      {
        osieobrotu.push_back(obrot);
        cout << "O ile stopni?";
        cin >>stopnie;
        wartosciobrotu.push_back(stopnie);
      }
      break;

      case 'r':
      double temp;
      cout << "Podaj odległość:";
      cin >> temp;
      przemieszczenie.push_back(temp);
      break;

      case 'q':
      cout << "Koniec pracy programu";
      break;
    }
    
  }
  return 0;

}