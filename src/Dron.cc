#include "../inc/Bryla.hh"
#include "../inc/lamana.hh"
#include "../inc/Wektor3D.hh"
#include "../inc/Wektor.hh"
#include "../inc/Macierz.hh"
#include "../inc/Dron.hh"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;


Dron Master(Dron dronik,std::vector<char> kolejnosc,std::vector<char> osie, std::vector<double> wartosci, std::vector<double> przemieszczenie)
{
    Wektor3D p;
    double osx;
    double osy;
    double osz;
    double ileobrotow=0;
    double ileprzemieszczen=0;  
    Dron wynikowy;
    Brylageometryczna dron=dronik.getbrylaindeks(0);  
    Brylageometryczna wirnik=dronik.getbrylaindeks(1);                                                          
    for(int j=0;j<kolejnosc.size();j++)
    {
        if (kolejnosc[j]=='o')
        {
        if(osie[ileobrotow]=='x')
        {
            osx=osx+wartosci[ileobrotow];
            ileobrotow++;
        }
        if(osie[ileobrotow]=='y')
        {
            osy=osy+wartosci[ileobrotow];
            ileobrotow++;
        }
        if(osie[ileobrotow]=='z')
        {
            osz=osz+wartosci[ileobrotow];
            ileobrotow++;
        }
        }
        else if (kolejnosc[j]=='r')
        {
        p=znajdzwektor(osie,wartosci,przemieszczenie[ileprzemieszczen],ileobrotow);
        dron=transformacjaowektor(dron,p);
        wirnik=transformacjaowektor(wirnik,p);
        ileprzemieszczen++;
        }
    }
    dron=RotacjadronaX(dron,osx);
    dron=RotacjadronaY(dron,osy);
    dron=RotacjadronaZ(dron,osz);
    wirnik=RotacjadronaZ(wirnik,90);
    wirnik=RotacjadronaZ(wirnik,osz);
    wirnik=RotacjadronaY(wirnik,osy);
    wirnik=RotacjadronaX(wirnik,osx);
    Wektor<double,3> trans;
    trans.setSkladowa(0,0);
    trans.setSkladowa(1,15);
    trans.setSkladowa(2,0);
    Wektor3D transpo;
    transpo.setWektor(trans);
    Wektor3D droniks=srodekbryly(dron);
    transpo=znajdzwektor3D(osie,wartosci,transpo,ileobrotow);
    droniks.setWektor(droniks.getWektor()-transpo.getWektor());
    wirnik=transformacjaowektor(wirnik,droniks);
    
wynikowy.addbryla(dron);
wynikowy.addbryla(wirnik);
wynikowy.addbryla(wirnik);
    return wynikowy;
}


void zapiszdopliku(Dron dronik,const char* plik)
{
    ofstream scena;
    scena.open (plik);
    for(int i=0; i<3; i++)
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
}