/*
Projekt: 1012
Autor: Jakub Jakobczyk
Prowadzacy: Piotr Witonski
*/

#ifndef ZESPOLONE_H_INCLUDED
#define ZESPOLONE_H_INCLUDED

#include "ulamek.h"

class Zespolone
{

public:

	Ulamek rzecz; //Ulamek - klasa z zdefiniowana w pliku ulamek.h
    Ulamek uroj;
	
	//konstruktory
    Zespolone(int a, int b, int c, int d);
    Zespolone(Ulamek r, Ulamek u);
    Zespolone();

    //przeciazone operatory
    Zespolone operator+ (Zespolone &z);
    void operator+= (Zespolone &z);
    Zespolone operator- (Zespolone &z);
    void operator-= (Zespolone &z);
    Zespolone operator* (Zespolone &z);
    void operator*= (Zespolone &z);
	
	//funkcje
    double mod(); //funkcja zwraca modol liczby zespolonej
	
	//destruktor
    ~Zespolone();
};

//przeciazony operator strumienia
ostream & operator<< (ostream &wyjscie, const Zespolone &z);

#endif // ZESPOLONE_H_INCLUDED
