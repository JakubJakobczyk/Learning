#ifndef ULAMEK_H_INCLUDED
#define ULAMEK_H_INCLUDED

//#include "ulamek.cpp"

using namespace std;

class Ulamek
{
private:

    int NWD(int a, int b);
    int NWW(int a, int b);
    void dodaj(Ulamek &u, int &wLicznik, int &wMianownik);
    void odejmij(Ulamek &u, int &wLicznik, int &wMianownik);
    void pomnoz(Ulamek &u, int &wLicznik, int &wMianownik);

public:

    int licznik, mianownik;
    Ulamek();
    Ulamek(int licz, int mian);

    Ulamek operator+ (Ulamek &u);
    Ulamek operator- (Ulamek &u);
    Ulamek operator* (Ulamek &u);

    //ostream & operator<< (ostream &wyjscie, const Ulamek &u);

    void set(int licz, int mian);
    double getDouble();

    ~Ulamek();
};

#endif // ULAMEK_H_INCLUDED
