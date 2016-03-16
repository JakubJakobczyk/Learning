#include <iostream>
#include <math.h>

#include "zespolone.h"
#include "ulamek.h"

using namespace std;



//Ulamek rzecz;
//Ulamek uroj;

Zespolone::Zespolone(int a, int b, int c, int d)
{
    #ifdef _DEBUG
    cout<<"Konstruktor l. zespolonej "<<a<<"/"<<b<<"+"<<c<<"/"<<d<<"j"<<endl;
    #endif
    rzecz.set(a, b);
    uroj.set(c, d);
}

Zespolone::Zespolone(Ulamek r, Ulamek u)
{
    #ifdef _DEBUG
    cout<<"Konstruktor l. zespolonej "<<r<<"+"<<u<<"j"<<endl;
    #endif
    rzecz = r;
    uroj = u;
}

Zespolone::Zespolone()
{
    #ifdef _DEBUG
    cout<<"Konstruktor l. zespolonej "<<0<<"+"<<0<<"j"<<endl;
    #endif
    rzecz = Ulamek();
    uroj = Ulamek();
}

ostream & operator<< (ostream &wyjscie, const Zespolone z)
{
	//cout<<"z.rzecz - "<<z.rzecz<<endl;
	//cout<<"z.rzecz.licznik"<<z.rzecz.licznik<<endl;
    return wyjscie<<z.rzecz.licznik<<"/"<<z.rzecz.mianownik<<"+"<<z.uroj.licznik<<"/"<<z.uroj.mianownik<<"j";
}

Zespolone Zespolone::operator+ (Zespolone &z)
{
    Ulamek r, u;

    r = rzecz+z.rzecz;
    u = uroj+z.uroj;

    return Zespolone(r, u);
}

void Zespolone::operator+= (Zespolone &z)
{
    Ulamek r,u;

    r = rzecz+z.rzecz;
    u = uroj+z.uroj;

    rzecz = r;
    uroj = u;
}

Zespolone Zespolone::operator- (Zespolone &z)
{
    Ulamek r, u;

    r = rzecz-z.rzecz;
    u = uroj-z.uroj;

    return Zespolone(r, u);
}

void Zespolone::operator-= (Zespolone &z)
{
    Ulamek r,u;

    r = rzecz-z.rzecz;
    u = uroj-z.uroj;

    rzecz = r;
    uroj = u;
}

Zespolone Zespolone::operator* (Zespolone &z)
{
    Ulamek r,u, pom1, pom2;
    pom1 = (rzecz*z.rzecz);
    pom2 = (uroj*z.uroj);
    r = pom1-pom2;
    pom1 = (rzecz*z.uroj);
    pom2 = (uroj*z.rzecz);
    u = pom1 + pom2;

    return Zespolone(r, u);
}

void Zespolone::operator*= (Zespolone &z)
{
    Ulamek r,u, pom1, pom2;
    pom1 = (rzecz*z.rzecz);
    pom2 = (uroj*z.uroj);
    r = pom1-pom2;
    pom1 = (rzecz*z.uroj);
    pom2 = (uroj*z.rzecz);
    u = pom1 + pom2;

    rzecz = r;
    uroj = u;
}

double Zespolone::mod()
{
    Ulamek a, b;
    a = rzecz;
    a = a*a;
    b = uroj;
    b = b*b;
    a = a+b;
    return sqrt(a.getDouble());
}

Zespolone::~Zespolone()
{
    #ifdef _DEBUG
    cout<<"Destruktor l. zespolonej "<<rzecz<<"+"<<uroj<<"j"<<endl;
    #endif
}
//ostream & operator<< (ostream &wyjscie, const Zespolone &z)

