/*
Projekt: 1012
Autor: Jakub Jakobczyk
Prowadzacy: Piotr Witonski
*/


#include <iostream>

#include "ulamek.h"

using namespace std;


//Funkcje prywatne
int Ulamek::NWD(int a, int b) //funkcja zwraca najwiekszy wspolny dzielnik 2 liczb
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

int Ulamek::NWW(int a, int b) //funkcja zwraca najmniejsza wspolna wielokrotnosc 2 liczb
{
    return a/NWD(a,b)*b;
}

Ulamek Ulamek::dodaj(Ulamek &u) //funckja dodajaca 2 ulamki - przekazany oraz obietk na rzecz ktorego zostala wywolana, zwraca ulamek wynikowy (w najprostszej postaci)
{
    int pom, wMianownik, wLicznik;
	//dodawanie
    wMianownik = NWW(mianownik, u.mianownik);
    wLicznik = ((wMianownik/mianownik)*licznik)+((wMianownik/u.mianownik)*u.licznik);
	//skracanie
    pom = NWD(wLicznik, wMianownik);
    wLicznik /= pom;
    wMianownik /= pom;
	
	return Ulamek(wLicznik, wMianownik);
}

Ulamek Ulamek::odejmij(Ulamek &u) //funkcja odejmujaca ulamki, analogiczna do powyzszej
{
    int pom, wMianownik, wLicznik;
	//odejmowanie
    wMianownik = NWW(mianownik, u.mianownik);
    wLicznik = ((wMianownik/mianownik)*licznik)-((wMianownik/u.mianownik)*u.licznik);
	//skracanie
    pom = NWD(wLicznik, wMianownik);
    wLicznik /= pom;
    wMianownik /= pom;
	
	return Ulamek(wLicznik, wMianownik);
}

Ulamek Ulamek::pomnoz(Ulamek &u) //funkcja mnozaca, analogiczna do powyzszej
{
    int pom, wMianownik, wLicznik;
	//mnozenie
    wLicznik = licznik*u.licznik;
    wMianownik = mianownik * u.mianownik;
	//skracanie
    pom = NWD(wLicznik, wMianownik);
    wLicznik /= pom;
    wMianownik /= pom;
	
	return Ulamek(wLicznik, wMianownik);
}


//Konstruktory

Ulamek::Ulamek()
{
    #ifdef _DEBUG
    cout<<"Konstruktor ulamka 0"<<endl;
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

//Przeciazanie operatorow

Ulamek Ulamek::operator+ (Ulamek &u)
{
    return dodaj(u);
}

Ulamek Ulamek::operator- (Ulamek &u)
{
    return odejmij(u);
}

Ulamek Ulamek::operator* (Ulamek &u)
{
    return pomnoz(u);
}

ostream & operator<< (ostream &wyjscie, const Ulamek &u)
{
    return wyjscie<<u.licznik<<"/"<<u.mianownik;
}

//Funkcje

void Ulamek::set(int licz, int mian)
{
    licznik = licz;
    mianownik = mian;
}

double Ulamek::getDouble()//Funkcja zwraca ulamek w postaci liczby typu double
{
    return (double)licznik/(double)mianownik;
}

int Ulamek::getLicznik() const
{
	return licznik;
}

int Ulamek::getMianownik() const
{
	return mianownik;
}

//Destruktor

Ulamek::~Ulamek()
{
    #ifdef _DEBUG
    cout<<"Destruktor ulamka"<<licznik<<"/"<<mianownik<<endl;
    #endif
}
