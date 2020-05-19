#include <iostream>

#include "../inc/LZespolona.hh"
#include "../inc/WyrazenieZesp.hh"
using namespace std;

std::ostream& operator << (std::ostream& os, const WyrazenieZesp& skl1)
{
    os << skl1.Arg1;
    os << skl1.Op;
    os << skl1.Arg2;
    return os;
}
std::istream& operator >> (std::istream& os, WyrazenieZesp& skl1)
{
    WyrazenieZesp temp;
    os >> temp.Arg1;
    os >> temp.Op;
    os >> temp.Arg2;
    if (temp.Op != '+' && temp.Op != '-' && temp.Op != '*' && temp.Op != '/') {
        cout << "Niepoprawna forma" << endl;
    }
    else {
        skl1.Arg1 = temp.Arg1;
        skl1.Op = temp.Op;
        skl1.Arg2 = temp.Arg2;
    }
    return os;
}

/*funkcja interpretuj¹ca i wyliczaj¹ca wynik wyra¿enia zespolonego.*/
LZespolona Oblicz(WyrazenieZesp  WyrZ)
{
    LZespolona Wynik;
    char znak;
    znak = WyrZ.Op;
    switch (znak)
    {
    case '+':
        Wynik = WyrZ.Arg1 + WyrZ.Arg2;
        break;
    case '-':
        Wynik = WyrZ.Arg1 - WyrZ.Arg2;
        break;
    case '*':
        Wynik = WyrZ.Arg1 * WyrZ.Arg2;
        break;
    case '/':
        Wynik = WyrZ.Arg1 / WyrZ.Arg2;
        break;
    case '%':
        Wynik = WyrZ.Arg1 % WyrZ.Arg2;
        break;
    }
    return Wynik;
}



void WyswietlW(WyrazenieZesp  WyrZ)
{
    cout << WyrZ.Arg1;
    cout << WyrZ.Op;
    cout << WyrZ.Arg2;
}
void WczytajW(WyrazenieZesp WyrZ)
{
    WyrazenieZesp temp;
    cin >> temp.Arg1;
    cin >> temp.Op;
    cin >> temp.Arg2;
    if (temp.Op != '+' && temp.Op != '-' && temp.Op != '*' && temp.Op != '/') {
        cout << "Niepoprawna forma" << endl;
    }
    else {
        temp.Arg1 = WyrZ.Arg1;
        temp.Op = WyrZ.Op;
        temp.Arg2 = WyrZ.Arg2;
    }
}
