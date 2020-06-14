#include "../inc/Bryla.hh"
#include "../inc/lamana.hh"
#include "../inc/Wektor3D.hh"
#include "../inc/Wektor.hh"
#include "../inc/Macierz.hh"
#include "../inc/Dron.hh"
#include "../inc/Przeszkody.hh"
#include "../inc/Scena.hh"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <memory>
using namespace std;

//kolizja drona oparta o algorytm AABB;
double Kolizja (Scena scena)
{
    int kolizja;
    Dron dronik=scena.getdron();
    vector<shared_ptr<Przeszkoda>> przeszkody=scena.getvector();
    Wektor3D MaksDrona = Maxxyz(dronik.getbrylaindeks(0));
    Wektor3D MinDrona = Minxyz(dronik.getbrylaindeks(0));
    Wektor<double,3> MaksD= MaksDrona.getWektor();
    Wektor<double,3> MinD=MinDrona.getWektor();
    double XMAX=MaksD.getSkladowa(0);
    double YMAX=MaksD.getSkladowa(1);
    double ZMAX=MaksD.getSkladowa(2);
    double XMIN=MinD.getSkladowa(0);
    double YMIN=MinD.getSkladowa(1);
    double ZMIN=MinD.getSkladowa(2);
    for(int i=0;i<przeszkody.size();i++)
    {
        shared_ptr<Przeszkoda> kolizyjna=make_shared<Przeszkoda>();
        kolizyjna=przeszkody[i];
        Wektor3D MaksPrzeszkody =kolizyjna->maksimum();
    Wektor3D MinPrzeszkody = kolizyjna->minimum();
    Wektor<double,3> MaksP= MaksPrzeszkody.getWektor();
    Wektor<double,3> MinP=MinPrzeszkody.getWektor();
    double XMAXP=MaksP.getSkladowa(0);
    double YMAXP=MaksP.getSkladowa(1);
    double ZMAXP=MaksP.getSkladowa(2);
    double XMINP=MinP.getSkladowa(0);
    double YMINP=MinP.getSkladowa(1);
    double ZMINP=MinP.getSkladowa(2);
    //Wszystko wyżej to ustalenie maksymalnych i minimalnych wartości X Y Z dla drona i przeszkody,
    //Poniżej jest logika związana z algorytmem AABB
     kolizja=(XMIN<=XMAXP && XMAX>=XMINP)&&(YMIN<=YMAXP && YMAX>=YMINP) && (ZMIN<=ZMAXP && ZMAX>=ZMINP);
    }
    return kolizja;
}
    
   

void zapiszscenedopliku (Scena scenka,const char* plik)
{
    //to samo co zapiszdopliku z dodatkiem wektora przeszkód
    ofstream scena;
    scena.open (plik);
    Dron dronik=scenka.getdron();
    vector<Brylageometryczna> ilebryl =dronik.getvektor();
    for(int i=0; i<ilebryl.size(); i++)
    { 
    Brylageometryczna bryla =dronik.getbrylaindeks(i);
    vector<Lamana> temp=bryla.getvektor();
    for(int i=0; i < temp.size(); i++)
    {
         Lamana wpetli= temp[i];
        vector<Wektor3D> temporary=wpetli.getvektor();
        for (int j=0; j< temporary.size();j++)
        {
            Wektor3D wektortrzyde=temporary[j];
            scena << wektortrzyde.getWektor();
            scena << endl;
        }
        scena << endl;
    }
    }
    vector<shared_ptr<Przeszkoda>> przeszkody;
    przeszkody=scenka.getvector();
    for(int i=0;i<przeszkody.size();i++)
    {
        scena << endl;
        shared_ptr<Przeszkoda> petla=make_shared<Przeszkoda>();
        petla=przeszkody[i];
        Brylageometryczna bryla=petla->getprzeszkoda();
        vector<Lamana> temp=bryla.getvektor();
    for(int i=0; i < temp.size(); i++)
    {
         Lamana wpetli= temp[i];
        vector<Wektor3D> temporary=wpetli.getvektor();
        for (int j=0; j< temporary.size();j++)
        {
            Wektor3D wektortrzyde=temporary[j];
            scena << wektortrzyde.getWektor();
            scena << endl;
        }
        scena << endl;
    
    }
    }
}
