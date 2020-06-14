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



Dron Ruchy(Dron dronik, vector<double> WartosciobrotuZ, vector<double> WartosciobrotuX, vector<double> Przemieszczenie,vector<char>kolejnosc)
{
    double obrotywirnika=0;
    Brylageometryczna BrylaDrona;
    double ileobrotow=0;
    double ileprzemieszczen=0;
    BrylaDrona=dronik.getbrylaindeks(0);
    //petla korzystajaca z wektora char aby poprawnie przesuwac i obracac drona 
    for(int i=0; i<kolejnosc.size(); i++)
    {
        if(kolejnosc[i]=='o')
        {
            BrylaDrona=RotacjadronaZ(BrylaDrona,WartosciobrotuZ[ileobrotow]);
            obrotywirnika=obrotywirnika+WartosciobrotuZ[ileobrotow];
            ileobrotow++;
        }
        if(kolejnosc[i]=='r')
        {
            Wektor<double,3> ruch;
            ruch.setSkladowa(0,0);
            ruch.setSkladowa(1,Przemieszczenie[ileprzemieszczen]);
            ruch.setSkladowa(2,0);
            Wektor3D doprzodu;
            doprzodu.setWektor(ruch);
            doprzodu=Znajdzwektorprzemieszczenia(doprzodu,ileprzemieszczen,ileobrotow,WartosciobrotuX,WartosciobrotuZ);
            BrylaDrona=transformacjaowektor(BrylaDrona,doprzodu);
            ileprzemieszczen++;
            
        }
    }
    Dron wynikowy;
     //To ustawia wirniki w swoim miejscu i jest brzydkie
    Brylageometryczna Wirnik1=dronik.getbrylaindeks(1);
    Wirnik1=RotacjadronaZ(Wirnik1,90);
    Wirnik1=RotacjadronaZ(Wirnik1,obrotywirnika);
    Wektor<double,3> trans;
    trans.setSkladowa(0,5);
    trans.setSkladowa(1,15);
    trans.setSkladowa(2,0);
    Wektor3D transpo;
    transpo.setWektor(trans);
    transpo=RotacjawektoraZ(transpo,obrotywirnika);
    Wektor3D droniks=srodekbryly(BrylaDrona);
    droniks.setWektor(droniks.getWektor()-transpo.getWektor());
    Wirnik1=transformacjaowektor(Wirnik1,droniks);
    Brylageometryczna Wirnik2=dronik.getbrylaindeks(1);
    Wirnik2=RotacjadronaZ(Wirnik2,90);
    Wirnik2=RotacjadronaZ(Wirnik2,obrotywirnika);
    Wektor<double,3> trans2;
    trans2.setSkladowa(0,-5);
    trans2.setSkladowa(1,15);
    trans2.setSkladowa(2,0);
    Wektor3D transpo2;
    transpo2.setWektor(trans2);
    transpo2=RotacjawektoraZ(transpo2,obrotywirnika);
    Wektor3D droniks2=srodekbryly(BrylaDrona);
    droniks2.setWektor(droniks2.getWektor()-transpo2.getWektor());
    Wirnik2=transformacjaowektor(Wirnik2,droniks2);
    //koniec ustawiania wirników
    wynikowy.addbryla(BrylaDrona);
    wynikowy.addbryla(Wirnik1);
    wynikowy.addbryla(Wirnik2);
    return wynikowy;
}
//to odpowiada za poruszanie sie animacje ruchu bryly
Dron Animacja(Dron dronporuchu,Dron dronprzedruchem,std::vector<double> jednostkiprzemieszczenia,std::vector<double> katobrotuosix,std::vector<double>katobrotuosiz,const char* plik,std::vector<char>kolejnosc,Dron dronik)
{
    Brylageometryczna Bryladronaporuchu=dronporuchu.getbrylaindeks(0);
    Brylageometryczna Bryladronaprzedruchem=dronprzedruchem.getbrylaindeks(0);
    Wektor3D doprzodu;
    Dron Wynikowy;
    
    if(kolejnosc.back()=='o')
    {
    double obrotZ=katobrotuosiz.back();
    obrotZ=obrotZ/1000;
    Bryladronaprzedruchem=RotacjadronaZ(Bryladronaprzedruchem,obrotZ);
    Wynikowy.addbryla(Bryladronaprzedruchem);
    }
    else if(kolejnosc.back()=='r')
    {
        Wektor<double,3> ruch;
        ruch.setSkladowa(0,0);
        ruch.setSkladowa(1,jednostkiprzemieszczenia.back()/1000);
        ruch.setSkladowa(2,0);
        doprzodu.setWektor(ruch);
        doprzodu=RotacjawektoraX(doprzodu,katobrotuosix.back());
            for(int i=0; i<katobrotuosiz.size();i++)
            {
                doprzodu=RotacjawektoraZ(doprzodu,katobrotuosiz[i]);
            }
        Bryladronaprzedruchem=transformacjaowektor(Bryladronaprzedruchem,doprzodu);
        Wynikowy.addbryla(Bryladronaprzedruchem);
    }
    return Wynikowy;
}
//funkcja która po każdym ruchu animacji ustawia wirniki na tyle drona i obraca je wokół własnej osi
Dron AnimacjaWirniki(Dron dronprzedruchem,std::vector<double> katobrotuosiz, Dron dronik,double krok,std::vector<char> kolejnosc)
{
    Brylageometryczna BrylaDrona=dronprzedruchem.getbrylaindeks(0);
    double obrotywirnika=0;
    if(kolejnosc.back()=='o'){
    for (int i=0;i<(katobrotuosiz.size()-1);i++)
    {
        obrotywirnika=obrotywirnika+katobrotuosiz[i];
    }
    for (int i=0;i<krok;i++)
    {
        obrotywirnika=obrotywirnika+(katobrotuosiz.back()/1000);
    }
    }
    else if(kolejnosc.back()=='r')
    {
        for (int i=0;i<(katobrotuosiz.size());i++)
    {
        obrotywirnika=obrotywirnika+katobrotuosiz[i];
    }
    }
 //To ustawia wirniki w swoim miejscu i jest brzydkie
    double obrotY=0;
    double oile=1.080;
    for (int i=0;i<krok;i++)
    {
        obrotY=obrotY+oile;
    }
    Brylageometryczna Wirnik1=dronik.getbrylaindeks(1);
    Wirnik1=RotacjadronaX(Wirnik1,obrotY);
    Wirnik1=RotacjadronaZ(Wirnik1,90);
    Wirnik1=RotacjadronaZ(Wirnik1,obrotywirnika);
    Wektor<double,3> trans;
    trans.setSkladowa(0,5);
    trans.setSkladowa(1,16);
    trans.setSkladowa(2,0);
    Wektor3D transpo;
    transpo.setWektor(trans);
    transpo=RotacjawektoraZ(transpo,obrotywirnika);
    Wektor3D droniks=srodekbryly(BrylaDrona);
    droniks.setWektor(droniks.getWektor()-transpo.getWektor());
    Wirnik1=transformacjaowektor(Wirnik1,droniks);
    Brylageometryczna Wirnik2=dronik.getbrylaindeks(1);
    Wirnik2=RotacjadronaX(Wirnik2,obrotY);
    Wirnik2=RotacjadronaZ(Wirnik2,90);
    Wirnik2=RotacjadronaZ(Wirnik2,obrotywirnika);
    Wektor<double,3> trans2;
    trans2.setSkladowa(0,-5);
    trans2.setSkladowa(1,16);
    trans2.setSkladowa(2,0);
    Wektor3D transpo2;
    transpo2.setWektor(trans2);
    transpo2=RotacjawektoraZ(transpo2,obrotywirnika);
    Wektor3D droniks2=srodekbryly(BrylaDrona);
    droniks2.setWektor(droniks2.getWektor()-transpo2.getWektor());
    Wirnik2=transformacjaowektor(Wirnik2,droniks2);
    //koniec ustawiania wirników    
    Dron wynikowy;
    wynikowy.addbryla(BrylaDrona);
    wynikowy.addbryla(Wirnik1);
    wynikowy.addbryla(Wirnik2);
    return wynikowy;
}
// Funkcja potrzebna aby poprawnie przemieszczać drona
Wektor3D Znajdzwektorprzemieszczenia(Wektor3D wektor, double ileprzemieszczen, double ileobrotow, std::vector<double>WartosciobrotuX, std::vector<double> WartosciobrotuZ)
{       
    wektor=RotacjawektoraX(wektor,WartosciobrotuX[ileprzemieszczen]);
    if(ileobrotow>0)
        {
            for(int i=0; i<ileobrotow;i++)
            {
        wektor=RotacjawektoraZ(wektor,WartosciobrotuZ[i]);
            }
        }
        
    return wektor;
}

//zapisanie drona do pliku
void zapiszdopliku(Dron dronik,const char* plik)
{
    ofstream scena;
    scena.open (plik);
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
}
