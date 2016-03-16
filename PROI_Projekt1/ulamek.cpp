
#include <iostream>

#include "ulamek.h"

using namespace std;

int licznik, mianownik;

int Ulamek::NWD(int a, int b)
{
    int pom;
    while(b!=0)
    {
        pom = b;
        b = a%b;
        a = pom;
    }
    return a;
}

int Ulamek::NWW(int a, int b)
{
    return a/NWD(a,b)*b;
}

void Ulamek::dodaj(Ulamek &u, int &wLicznik, int &wMianownik)
{
    int pom;
    wMianownik = NWW(mianownik, u.mianownik);
    wLicznik = ((wMianownik/mianownik)*licznik)+((wMianownik/u.mianownik)*u.licznik);
    pom = NWD(wLicznik, wMianownik);
    wLicznik /= pom;
    wMianownik /= pom;
}

void Ulamek::odejmij(Ulamek &u, int &wLicznik, int &wMianownik)
{
    int pom;
    wMianownik = NWW(mianownik, u.mianownik);
    wLicznik = ((wMianownik/mianownik)*licznik)-((wMianownik/u.mianownik)*u.licznik);
    pom = NWD(wLicznik, wMianownik);
    wLicznik /= pom;
    wMianownik /= pom;
}

void Ulamek::pomnoz(Ulamek &u, int &wLicznik, int &wMianownik)
{
    int pom;
    wLicznik = licznik*u.licznik;
    wMianownik = mianownik * u.mianownik;

    pom = NWD(wLicznik, wMianownik);
    wLicznik /= pom;
    wMianownik /= pom;
}


Ulamek::Ulamek()
{
    #ifdef _DEBUG
    cout<<"Destruktor ulamka 0"<<endl;
    #endif
    licznik = 0;
    mianownik = 1;
}

Ulamek::Ulamek(int licz, int mian)
{
    #ifdef _DEBUG
    cout<<"Konstruktor ulamka"<<licz<<"/"<<mian<<endl;
    #endif
    licznik = licz;
    mianownik = mian;
}

Ulamek Ulamek::operator+ (Ulamek &u)
{
    int wLicznik = 0, wMianownik = 1;

    dodaj(u, wLicznik, wMianownik);

    return Ulamek(wLicznik, wMianownik);
}

Ulamek Ulamek::operator- (Ulamek &u)
{
    int wLicznik = 0, wMianownik = 1;

    odejmij(u, wLicznik, wMianownik);

    return Ulamek(wLicznik, wMianownik);
}

Ulamek Ulamek::operator* (Ulamek &u)
{
    int wLicznik = 0, wMianownik = 1;

    pomnoz(u, wLicznik, wMianownik);

    return Ulamek(wLicznik, wMianownik);
}

inline ostream & operator<< (ostream &wyjscie, const Ulamek &u)
{
    return wyjscie<<u.licznik<<"/"<<u.mianownik;
}

void Ulamek::set(int licz, int mian)
{
    licznik = licz;
    mianownik = mian;
}

double Ulamek::getDouble()
{
    return (double)licznik/(double)mianownik;
}

Ulamek::~Ulamek()
{
    #ifdef _DEBUG
    cout<<"Destruktor ulamka"<<licznik<<"/"<<mianownik<<endl;
    #endif
}
