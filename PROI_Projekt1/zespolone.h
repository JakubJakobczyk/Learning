#ifndef ZESPOLONE_H_INCLUDED
#define ZESPOLONE_H_INCLUDED

#include "ulamek.h"

class Zespolone
{

public:

	Ulamek rzecz;
    Ulamek uroj;
	
    Zespolone(int a, int b, int c, int d);
    Zespolone(Ulamek r, Ulamek u);
    Zespolone();

    //friend ostream & operator<< (ostream &wyjscie, const Zespolone &z);
    Zespolone operator+ (Zespolone &z);
    void operator+= (Zespolone &z);
    Zespolone operator- (Zespolone &z);
    void operator-= (Zespolone &z);
    Zespolone operator* (Zespolone &z);
    void operator*= (Zespolone &z);
	

    double mod();

    ~Zespolone();
};

#endif // ZESPOLONE_H_INCLUDED
