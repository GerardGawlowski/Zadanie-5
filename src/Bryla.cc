#include "../inc/Bryla.hh"
#include "../inc/lamana.hh"
#include "../inc/Wektor3D.hh"
#include "../inc/Wektor.hh"
#include "../inc/Macierz.hh"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;
Brylageometryczna odczytdrona ()
{
    int i=1;
    Wektor3D wektortrzyde;
    Lamana lamana;
    Brylageometryczna dronik;
    ifstream dron;
    dron.open ("../bryly/dron.dat");
    Wektor<double,3> nowy;
    double a,b,c;
    while(dron >> a >> b >> c)
    {
        
        nowy.setSkladowa(0,a);
        nowy.setSkladowa(1,b);
        nowy.setSkladowa(2,c);
        wektortrzyde.setWektor(nowy);
        lamana.addwektor(wektortrzyde);
        if(i%4==0&&i!=0)
        {
        dronik.addlamana(lamana);
        vector<Wektor3D> czyszczenie=lamana.getvektor();
        czyszczenie.clear();
        lamana.setvector(czyszczenie);
        }
        i++;
    }
    return dronik;
}

void zapiszdopliku(Brylageometryczna bryla,const char* plik)
{
    ofstream scena;
    scena.open (plik);
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

void stworzpowierzchnie(const char* plik, double wysokosc)          
{
    ofstream woda;
    woda.open(plik);
    double y = wysokosc;
    for (int i=0; i<18;i++)
    {
        double x= -30;
        double z=-80 +(i*10);
        Wektor<double,3> wodiczka;
        wodiczka.setSkladowa(0,x);
        wodiczka.setSkladowa(1,z);
        wodiczka.setSkladowa(2,y);
        woda << wodiczka << endl;
        x=90;
        wodiczka.setSkladowa(0,x);
        wodiczka.setSkladowa(1,z);
        wodiczka.setSkladowa(2,y);
        woda << wodiczka;
        woda << endl << endl;
    }
    for (int i =0; i<18; i++)
    {
        double x = -30 + (i*10);
        double z =-80;
        Wektor<double,3> wodiczka;
        wodiczka.setSkladowa(0,x);
        wodiczka.setSkladowa(1,z);
        wodiczka.setSkladowa(2,y);
        woda << wodiczka << endl;
        z=80;
        wodiczka.setSkladowa(0,x);
        wodiczka.setSkladowa(1,z);
        wodiczka.setSkladowa(2,y);
        woda << wodiczka;
        woda << endl << endl;
    }
}

Brylageometryczna RotacjadronaZ(Brylageometryczna bryla, double katobrotu)
{
    katobrotu=katobrotu*M_PI/180;
    Wektor3D poczatek=srodekbryly(bryla);
    Wektor<double,3> pierwszy;                                  //Ustawianie macierzy według wzorów obrotu wokół osi OZ
    pierwszy.setSkladowa(0,cos(katobrotu));
    pierwszy.setSkladowa(1,(-sin(katobrotu)));
    pierwszy.setSkladowa(2,0);
    Wektor<double,3> drugi;
    drugi.setSkladowa(0,sin(katobrotu));
    drugi.setSkladowa(1,cos(katobrotu));
    drugi.setSkladowa(2,0);
    Wektor<double,3> trzeci;
    trzeci.setSkladowa(0,0);
    trzeci.setSkladowa(1,0);
    trzeci.setSkladowa(2,1);
    Macierz<double,3> obrot;
    obrot.setWektor(0,pierwszy);
    obrot.setWektor(1,drugi);
    obrot.setWektor(2,trzeci);
    vector<Lamana> temp=bryla.getvektor();
    for(int i=0; i < temp.size(); i++)
    {
         Lamana wpetli= temp[i];
        vector<Wektor3D> temporary=wpetli.getvektor();
        vector<Wektor3D> doobrotu;

        for (int j=0; j< temporary.size();j++)
        {
            Wektor3D wektortrzyde=temporary[j];
            Wektor<double,3> obrotny=wektortrzyde.getWektor();
            obrotny=obrot*obrotny;
            wektortrzyde.setWektor(obrotny);
            doobrotu.push_back(wektortrzyde);
        }
        Lamana poobrocie;
        poobrocie.setvector(doobrotu);
        temp[i]=poobrocie;
    }
    bryla.setvector(temp);
    Brylageometryczna dron = bryla;
    Wektor3D T;
    T.setWektor(poczatek.getWektor()-(obrot*poczatek.getWektor()));
    cout << T.getWektor();
    dron=transformacjaowektor(dron,T);
return dron;
}

Brylageometryczna RotacjadronaX(Brylageometryczna bryla, double katobrotu)
{
    katobrotu=katobrotu*M_PI/180;
    Wektor3D poczatek=srodekbryly(bryla);
    Wektor<double,3> pierwszy;                      //Ustawianie macierzy według wzorów obrotu wokół osi OX
    pierwszy.setSkladowa(0,1);
    pierwszy.setSkladowa(1,0);
    pierwszy.setSkladowa(2,0);
    Wektor<double,3> drugi;
    drugi.setSkladowa(0,0);
    drugi.setSkladowa(1,cos(katobrotu));
    drugi.setSkladowa(2,(-sin(katobrotu)));
    Wektor<double,3> trzeci;
    trzeci.setSkladowa(0,0);
    trzeci.setSkladowa(1,sin(katobrotu));
    trzeci.setSkladowa(2,cos(katobrotu));
    Macierz<double,3> obrot;
    obrot.setWektor(0,pierwszy);
    obrot.setWektor(1,drugi);
    obrot.setWektor(2,trzeci);
    vector<Lamana> temp=bryla.getvektor();
    for(int i=0; i < temp.size(); i++)
    {
         Lamana wpetli= temp[i];
        vector<Wektor3D> temporary=wpetli.getvektor();
        vector<Wektor3D> doobrotu;

        for (int j=0; j< temporary.size();j++)
        {
            Wektor3D wektortrzyde=temporary[j];
            Wektor<double,3> obrotny=wektortrzyde.getWektor();
            obrotny=obrot*obrotny;
            wektortrzyde.setWektor(obrotny);
            doobrotu.push_back(wektortrzyde);
        }
        Lamana poobrocie;
        poobrocie.setvector(doobrotu);
        temp[i]=poobrocie;
    }
     bryla.setvector(temp);
    Brylageometryczna dron = bryla;
    Wektor3D koniec=srodekbryly(dron);
    Wektor3D T;
    T.setWektor(poczatek.getWektor()-(obrot*poczatek.getWektor()));
    cout << T.getWektor();
    dron=transformacjaowektor(dron,T);
    return dron;
}

Brylageometryczna RotacjadronaY(Brylageometryczna bryla, double katobrotu)
{
    katobrotu=katobrotu*M_PI/180;
    Wektor3D poczatek=srodekbryly(bryla);
    Wektor<double,3> pierwszy;                      //Ustawianie macierzy według wzorów obrotu wokół osi OY
    pierwszy.setSkladowa(0,cos(katobrotu));
    pierwszy.setSkladowa(1,0);
    pierwszy.setSkladowa(2,sin(katobrotu));
    Wektor<double,3> drugi;
    drugi.setSkladowa(0,0);
    drugi.setSkladowa(1,1);
    drugi.setSkladowa(2,0);
    Wektor<double,3> trzeci;
    trzeci.setSkladowa(0,(-sin(katobrotu)));
    trzeci.setSkladowa(1,0);
    trzeci.setSkladowa(2,cos(katobrotu));
    Macierz<double,3> obrot;
    obrot.setWektor(0,pierwszy);
    obrot.setWektor(1,drugi);
    obrot.setWektor(2,trzeci);
    vector<Lamana> temp=bryla.getvektor();
    for(int i=0; i < temp.size(); i++)    //Petla odczytujaca zawartość vectorów z Bryły aż do zwykłego wektora
    {
         Lamana wpetli= temp[i];
        vector<Wektor3D> temporary=wpetli.getvektor();
        vector<Wektor3D> doobrotu;

        for (int j=0; j< temporary.size();j++)
        {
            Wektor3D wektortrzyde=temporary[j];
            Wektor<double,3> obrotny=wektortrzyde.getWektor();
            obrotny=obrot*obrotny;
            wektortrzyde.setWektor(obrotny);
            doobrotu.push_back(wektortrzyde);
        }
        Lamana poobrocie;
        poobrocie.setvector(doobrotu);
        temp[i]=poobrocie;
    }
    bryla.setvector(temp);              
    Brylageometryczna dron = bryla;
    Wektor3D koniec=srodekbryly(dron);
    cout << koniec.getWektor();
    Wektor3D T;
    T.setWektor(poczatek.getWektor()-(obrot*poczatek.getWektor()));
    cout << T.getWektor();
    dron=transformacjaowektor(dron,T);
return dron;
}

Brylageometryczna transformacjaowektor(Brylageometryczna dron, Wektor3D T)
{
    vector<Lamana> temp=dron.getvektor();
    for(int i=0; i < temp.size(); i++)
    {
         Lamana wpetli= temp[i];
        vector<Wektor3D> temporary=wpetli.getvektor();
        vector<Wektor3D> dotransformacji;

        for (int j=0; j< temporary.size();j++)
        {
            Wektor3D wektortrzyde=temporary[j];
            Wektor<double,3> trans=wektortrzyde.getWektor();
            Wektor<double,3> t =T.getWektor();
            trans = trans +t;
            wektortrzyde.setWektor(trans);
            dotransformacji.push_back(wektortrzyde);
        }
        Lamana potransformacji;
        potransformacji.setvector(dotransformacji);
        temp[i]=potransformacji;
    }
    dron.setvector(temp);
    return dron;
}

Wektor3D srodekbryly(Brylageometryczna bryla)
{
     double maksz,maksx,maksy,minz,miny,minx;
        maksx=0;
        maksz=0;
        maksy=0;
        minz=0;
        miny=0;
        minx=0;
    int i=1;
    Wektor3D wektortrzyde;
    Wektor<double,3> nowy;
    double a,b,c;
    vector<Lamana> temp=bryla.getvektor();
    for(int i=0; i < temp.size(); i++)
    {
         Lamana wpetli= temp[i];
        vector<Wektor3D> temporary=wpetli.getvektor();
       
        for (int j=0; j< temporary.size();j++)
        {
            Wektor3D wektortrzyde=temporary[j];
            Wektor<double,3> dosrodka=wektortrzyde.getWektor();
            a=dosrodka.getSkladowa(0);
            b=dosrodka.getSkladowa(1);
            c=dosrodka.getSkladowa(2); 
           if(i==0)
       {
           maksx=a;
           minx=a;
           maksy=b;
           miny=b;
           minz=c;
           maksz=c;
       }
        if(a>maksx)
        {
            maksx=a;
        }
        if(a<minx)
        {
            minx=a;
        }
        if(b>maksy)
        {
            maksy=b;
        }
        if(b<maksy)
        {
            miny=b;
        }
        if(c>maksz)
        {
            maksz=c;
        }
        if(c<minz)
        {
            minz=c;
        } 
        }
       
    }
    nowy.setSkladowa(0,(maksx+minx)/2);
    nowy.setSkladowa(1,(maksy+miny)/2);
    nowy.setSkladowa(2,(maksz+minz)/2);
Wektor3D wynik;
wynik.setWektor(nowy);
    return wynik;
}

Wektor3D znajdzwektor(vector<char> osie, vector<double>wartosci, double odleglosc)
{
    Wektor3D wynik;
    Wektor3D doprzodu;
    Wektor<double,3> przod;
    przod.setSkladowa(0,0);
    przod.setSkladowa(1,odleglosc);
    przod.setSkladowa(2,0);
    doprzodu.setWektor(przod);
    for (int i=0; i<osie.size();i++)
    {
        if(osie[i]=='x')
        {
            wynik=RotacjawektoraX(doprzodu, wartosci[i]);
        }
        if(osie[i]=='y')
        {
            wynik=RotacjawektoraY(doprzodu,wartosci[i]);
        }
        if(osie[i]=='z')
        {
            wynik=RotacjawektoraZ(doprzodu,wartosci[i]);
        }
    }
    if(osie.size()==0)
    {
        return doprzodu;
    }
    return wynik;
}

Wektor3D RotacjawektoraZ(Wektor3D wektor, double katobrotu)
{
    katobrotu=katobrotu*M_PI/180;
    Wektor<double,3> pierwszy;                                  //Ustawianie macierzy według wzorów obrotu wokół osi OZ
    pierwszy.setSkladowa(0,cos(katobrotu));
    pierwszy.setSkladowa(1,(-sin(katobrotu)));
    pierwszy.setSkladowa(2,0);
    Wektor<double,3> drugi;
    drugi.setSkladowa(0,sin(katobrotu));
    drugi.setSkladowa(1,cos(katobrotu));
    drugi.setSkladowa(2,0);
    Wektor<double,3> trzeci;
    trzeci.setSkladowa(0,0);
    trzeci.setSkladowa(1,0);
    trzeci.setSkladowa(2,1);
    Macierz<double,3> obrot;
    obrot.setWektor(0,pierwszy);
    obrot.setWektor(1,drugi);
    obrot.setWektor(2,trzeci);
    Wektor3D wynik;
    Wektor<double,3> wynikowy=wektor.getWektor();
    wynik.setWektor(obrot*wynikowy);    
    return wynik;
}

Wektor3D RotacjawektoraX(Wektor3D wektor, double katobrotu)
{
    katobrotu=katobrotu*M_PI/180;
    Wektor<double,3> pierwszy;                      //Ustawianie macierzy według wzorów obrotu wokół osi OX
    pierwszy.setSkladowa(0,1);
    pierwszy.setSkladowa(1,0);
    pierwszy.setSkladowa(2,0);
    Wektor<double,3> drugi;
    drugi.setSkladowa(0,0);
    drugi.setSkladowa(1,cos(katobrotu));
    drugi.setSkladowa(2,(-sin(katobrotu)));
    Wektor<double,3> trzeci;
    trzeci.setSkladowa(0,0);
    trzeci.setSkladowa(1,sin(katobrotu));
    trzeci.setSkladowa(2,cos(katobrotu));
    Macierz<double,3> obrot;
    obrot.setWektor(0,pierwszy);
    obrot.setWektor(1,drugi);
    obrot.setWektor(2,trzeci);
    Wektor3D wynik;
    Wektor<double,3> wynikowy=wektor.getWektor();
    wynik.setWektor(obrot*wynikowy);    
    return wynik;
}

Wektor3D RotacjawektoraY(Wektor3D wektor, double katobrotu)
{
    katobrotu=katobrotu*M_PI/180;
    Wektor<double,3> pierwszy;                      //Ustawianie macierzy według wzorów obrotu wokół osi OY
    pierwszy.setSkladowa(0,cos(katobrotu));
    pierwszy.setSkladowa(1,0);
    pierwszy.setSkladowa(2,sin(katobrotu));
    Wektor<double,3> drugi;
    drugi.setSkladowa(0,0);
    drugi.setSkladowa(1,1);
    drugi.setSkladowa(2,0);
    Wektor<double,3> trzeci;
    trzeci.setSkladowa(0,(-sin(katobrotu)));
    trzeci.setSkladowa(1,0);
    trzeci.setSkladowa(2,cos(katobrotu));
    Macierz<double,3> obrot;
    obrot.setWektor(0,pierwszy);
    obrot.setWektor(1,drugi);
    obrot.setWektor(2,trzeci);
    Wektor3D wynik;
    Wektor<double,3> wynikowy=wektor.getWektor();
    wynik.setWektor(obrot*wynikowy);
    return wynik;
}

Brylageometryczna Master(Brylageometryczna dron,std::vector<char> osie, std::vector<double> wartosci, std::vector<double> przemieszczenie)
{
    
    for (int i=0; i<osie.size();i++)
    {
        if(osie[i]=='x')
        {
            dron=RotacjadronaX(dron, wartosci[i]);
        }
        if(osie[i]=='y')
        {
            dron=RotacjadronaY(dron,wartosci[i]);
        }
        if(osie[i]=='z')
        {
            dron=RotacjadronaZ(dron,wartosci[i]);
        }
    }
    for (int i=0;i<przemieszczenie.size();i++)
    {
    Wektor3D p;
    p=znajdzwektor(osie,wartosci,przemieszczenie[i]);
    dron=transformacjaowektor(dron,p);
    }
    return dron;
}