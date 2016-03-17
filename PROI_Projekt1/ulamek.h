/*
Projekt: 1012
Autor: Jakub Jakobczyk
Prowadzacy: Piotr Witonski
*/


#ifndef ULAMEK_H_INCLUDED
#define ULAMEK_H_INCLUDED


using namespace std;

class Ulamek
{
	
private:

    int NWD(int a, int b); //funkcja zwraca najwiekszy wspolny dzielnik 2 liczb
    int NWW(int a, int b); //funkcja zwraca najmniejsza wspolna wielokrotnosc 2 liczb
    Ulamek dodaj(Ulamek &u); //funckja dodajaca 2 ulamki - przekazany oraz obietk na rzecz ktorego zostala wywolana, zwraca ulamek wynikowy (w najprostszej postaci)
    Ulamek odejmij(Ulamek &u); //funkcja odejmujaca ulamki, analogiczna do powyzszej
    Ulamek pomnoz(Ulamek &u); //funkcja mnozaca, analogiczna do powyzszej

public:
	
	int licznik, mianownik;
	//konstruktory
    Ulamek();
    Ulamek(int licz, int mian);
	
	//przeciazanie operatorow
    Ulamek operator+ (Ulamek &u);
    Ulamek operator- (Ulamek &u);
    Ulamek operator* (Ulamek &u);

	//funkcje
    void set(int licz, int mian); //funkcja zmieniajaca wartosci
    double getDouble(); //Funkcja zwraca ulamek w postaci liczby typu double
	int getLicznik() const; 
	int getMianownik() const;
	
	//destruktor
    ~Ulamek();
};

ostream & operator<< (ostream &wyjscie, const Ulamek &u);

#endif // ULAMEK_H_INCLUDED
