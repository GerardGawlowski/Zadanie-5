#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <memory>

#include "../inc/Wektor.hh"
#include "../inc/Macierz.hh"
#include "../inc/LZespolona.hh"
#include "../inc/WyrazenieZesp.hh"
#include "../inc/lacze_do_gnuplota.hh"
#include "../inc/lamana.hh"
#include "../inc/Wektor3D.hh"
#include "../inc/Bryla.hh"
#include "../inc/Dron.hh"
#include "../inc/Scena.hh"
#include "../inc/Przeszkody.hh"
using namespace std;


int main()
{
  //Inicjalizacja potrzebnych obiektów
  int a=0;
  PzG::LaczeDoGNUPlota  Lacze;
  char c;
  Dron dronik;
  Brylageometryczna dron;
  Scena scena;
  const char* pliksceny;
  char menu='0';
  Dron dronglobalny;      //dron w pozycji po poruszeniu się
  Dron dronprzedruchem;  //dron przed poruszeniem się
   vector<double> katobrotuosiz;
   vector<double> jednostkiprzemieszczenia;
   vector<double>katobrotuosix;
   vector<char> kolejnosc;
  int inicjalizacja=0;
  //Wprowadzenie ścieżek plików
  pliksceny = "../bryly/scena.dat";
  dron=odczytdrona("../bryly/dron.dat");
  Brylageometryczna wirnik=odczytdrona("../bryly/Wirnik.dat");
  Brylageometryczna scianka=odczytdrona("../bryly/Przeszkodasciana.dat");
  Brylageometryczna precik=odczytdrona("../bryly/przeszkodapret.dat");
  // zaincjalizowanie przeszkody w oparciu o klasę bazową przeszkoda i pochodną sciana
  shared_ptr<Przeszkoda> przeszkoda2= make_shared<pret>();
  shared_ptr<Przeszkoda> przeszkoda1= make_shared<sciana>();
  przeszkoda1->setbryla(scianka);
  przeszkoda2->setbryla(precik);
  scena.addprzeszkoda(przeszkoda1);  //dodanie sciany do wektora przeszkód
  scena.addprzeszkoda(przeszkoda2);
  dronik.addbryla(dron);
  dronik.addbryla(wirnik);
  //stworzenie tafli wody i ziemi
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
  

  while (menu!='q')
  { dronglobalny=Ruchy(dronik,katobrotuosiz,katobrotuosix,jednostkiprzemieszczenia,kolejnosc);
    scena.setdron(dronglobalny);
    if(inicjalizacja==1&&kolejnosc.size()>a)
    {
      a=kolejnosc.size();
      if(Kolizja(scena)==1)
      {
        cout << endl << "KOLIZJA!" << endl << "NIE MOŻNA KONTYNUOWAĆ RUCHU" << endl;
        if(kolejnosc.back()=='o')
        {
          kolejnosc.pop_back();
          katobrotuosiz.pop_back();
        }
        else
        {
          kolejnosc.pop_back();
          katobrotuosix.pop_back();
          jednostkiprzemieszczenia.pop_back();
        }
      }
      else
      {
      for (int i=0;i<1000;i++)
      {
        //zanimowanie drogi drona do pozycji globalnej (tak, to brzydki sposób)
      dronprzedruchem=Animacja(dronglobalny,dronprzedruchem,jednostkiprzemieszczenia,katobrotuosix,katobrotuosiz,pliksceny,kolejnosc,dronik);
      dronprzedruchem=AnimacjaWirniki(dronprzedruchem,katobrotuosiz,dronik,i,kolejnosc);
      scena.setdron(dronprzedruchem);
      zapiszscenedopliku(scena,pliksceny);
      Lacze.Rysuj();
      }
      }
    }
    if (inicjalizacja==0)
    {
    scena.setdron(dronglobalny);
    zapiszscenedopliku(scena,pliksceny);
    Lacze.Rysuj();
    inicjalizacja=1;
    }
    dronprzedruchem=dronglobalny;
    cout << "Sterowanie dronem" << endl;
    cout << "o - obrót drona" << endl;
    cout << "r - ruch do przodu" << endl;
    cout << "l - lista przeszkód" << endl;
    cout << "u - usuń przeszkodę" << endl;
    cout << "q - wyjście z symulacji" << endl;
    cin >> menu;
    // obsługa menu
    switch(menu)
    {
      //obrót drona
      case 'o':
      {
        kolejnosc.push_back('o');
        cout <<"O ile stopni?";
        double temp;
        cin >> temp;
        katobrotuosiz.push_back(temp);
      break;
      }
      //ruch drona
      case 'r':
      {
      kolejnosc.push_back('r');
      cout << "O ile jednostek?" << endl;
      double temporary;
      cin >> temporary;
      jednostkiprzemieszczenia.push_back(temporary);
      cout << "Ile stopni?" << endl;
      cin >> temporary;
      katobrotuosix.push_back(temporary);
      break;
      }
      case 'l':
      {
      vector<shared_ptr<Przeszkoda>> wpetli =scena.getvector();
        for(int i=0;i<wpetli.size();i++)
        {
          cout << i+1 << ':' << wpetli[i]->zwrocnazwe() << endl;
        }
      break;
      }

      case 'u':
      {
        vector<shared_ptr<Przeszkoda>> wpetli =scena.getvector();
        cout << "Którą przeszkodę chcesz usunąć? Wpisz jej cyfrę(zmiany będą widoczne podczas następnego ruchu):";
        int cyfra;
        cin >> cyfra;
        cyfra=cyfra-1;
        wpetli.erase(wpetli.begin()+cyfra);
        scena.setvector(wpetli);
        break;
      }
      //wyjście z programu
      case 'q':
      {
      cout << "Koniec pracy programu";
      break;
      }
    }
    
  }
  return 0;

}