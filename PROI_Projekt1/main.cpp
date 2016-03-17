/*
Projekt: 1012
Autor: Jakub Jakobczyk
Prowadzacy: Piotr Witonski
*/



/*Odkomentowac przy debugowaniu, pozwala na sledzenie konstruktorow i destruktorow*/
//#define _DEBUG

#include <iostream>
#include <cstdio>

#include "zespolone.h"

using namespace std;

int pobierzLiczbe(); //funkcja pobiera od uzytkownika l. calkowita do skutko, nastepnie zwraca ja
void pobierz2(Zespolone &, Zespolone &); //funkcja pobiera 2 l. zespolone
Zespolone pobierzZespolona(); //funckja pobiera od uzytkownika dane i zwraca utworzona z nich liczbe zespolona 
void pokazOpcje(); //funkcja wyswietlajaca opcje (pomoc dla uzytkownika)

int main()
{
    Zespolone *pamiec1 = new Zespolone(), *pamiec2 = new Zespolone();
	Zespolone doWysw1, doWysw2;
    int ster = 1;
    while(ster!=0)
    {
        pokazOpcje();
        ster = pobierzLiczbe();
		
		//podejmowanie dzialan na podstawie wprowadzonej zmiennej ster:
		
        if (ster == 0) break; //0 - wyjscie
        else if (ster == 1) //1 - dodawanie 2 liczb, zapis wyniku do pamieci
        {
            pobierz2(*pamiec1, *pamiec2);
			doWysw1 = *pamiec1;
			doWysw2 = *pamiec2;
            cout<<doWysw1<<" + "<<doWysw2<<" = ";
            *pamiec1=*pamiec1+*pamiec2;
			doWysw1 = *pamiec1;
            cout<<doWysw1<<endl;
        }
        else if (ster == 2) //2 - dodanie do istniejacej liczby w pamieci
        {
            cout<<"Wprowadzanie liczby:"<<endl;
            *pamiec2 = pobierzZespolona();
			doWysw1 = *pamiec1;
			doWysw2 = *pamiec2;
            cout<<doWysw1<<" += "<<doWysw2<<" = ";
            *pamiec1+=*pamiec2;
			doWysw1 = *pamiec1;
            cout<<doWysw1<<endl;
        }
        else if (ster == 3) //3 - odejmowanie 2 liczb, zapis wyniku do pamieci
        {
            pobierz2(*pamiec1, *pamiec2);
			doWysw1 = *pamiec1;
			doWysw2 = *pamiec2;
            cout<<doWysw1<<" - "<<doWysw2<<" = ";
            *pamiec1=*pamiec1-*pamiec2;
			doWysw1 = *pamiec1;
            cout<<doWysw1<<endl;
        }
        else if (ster == 4) //4 - odjecie od istniejacej liczby w pamieci
        {
            cout<<"Wprowadzanie liczby:"<<endl;
            *pamiec2 = pobierzZespolona();
			doWysw1 = *pamiec1;
			doWysw2 = *pamiec2;
            cout<<doWysw1<<" -= "<<doWysw2<<" = ";
            *pamiec1-=*pamiec2;
			doWysw1 = *pamiec1;
            cout<<doWysw1<<endl;
        }
        else if (ster == 5) //5 - mnozenie 2 liczb, zapis wyniku do pamieci
        {
            pobierz2(*pamiec1, *pamiec2);
			doWysw1 = *pamiec1;
			doWysw2 = *pamiec2;
            cout<<doWysw1<<" * "<<doWysw2<<" = ";
            *pamiec1=*pamiec1*(*pamiec2);
			doWysw1 = *pamiec1;
            cout<<doWysw1<<endl;
        }
        else if (ster == 6) //6 - wymnazanie istniejacej liczby w pamieci
        {
            cout<<"Wprowadzanie liczby:"<<endl;
            *pamiec2 = pobierzZespolona();
			doWysw1 = *pamiec1;
			doWysw2 = *pamiec2;
            cout<<doWysw1<<" *= "<<doWysw2<<" = ";
            *pamiec1*=*pamiec2;
			doWysw1 = *pamiec1;
            cout<<doWysw1<<endl;
        }
        else if (ster == 7) //7 - wyswietlenie modulu liczby w pamieci
        {
			doWysw1 = *pamiec1;
            cout<<"|"<<doWysw1<<"| = "<<(*pamiec1).mod()<<endl;
        }
        else if (ster == 8) //8 - wyswietlenie liczby z pamieci
        {
			doWysw1 = *pamiec1;
            cout<<"Pamiec: "<<doWysw1<<endl;
        }
        cout<<"Wcisnij klawisz 'enter' aby kontynuowac..."<<endl;
		cin.ignore(1024,'\n');
        getchar();
        cout<<endl<<endl<<endl;
    }
    return 0;
}

int pobierzLiczbe() //funkcja pobiera od uzytkownika l. calkowita do skutku, nastepnie zwraca ja
{
	string s;
	int liczba;
    while(1)
	{
		cin>>s;
		int n = s.length();
		int i=1;
		if (s[0]!='-' && !isdigit(s[0])) //Sprawdzenie pierwszego znaku
		{
			cout <<"Blad, wprowadzany ciag nie jest liczba calkowita. Wprowadz ponownie"<<endl;
			continue;
		}
		if (s[0]=='-' && s.length()==1) //Kolejny krok sprawdzenia pierwszego znaku
		{
			cout <<"Blad, wprowadzany ciag nie jest liczba calkowita. Wprowadz ponownie"<<endl;
			continue;
		}
		for ( ; i<n; i++) //Petla sprawdzajaca po kolei znaki wprowadzonego ciagu
		{
			if (!isdigit(s[i])) break;
		}
		if (i==n) //Mozliwe tylko jesli wystopily same cyfry
		{
			liczba = stoi(s); //zamiana string na int
			return liczba;
		}
		else cout <<"Blad, wprowadzany ciag nie jest liczba calkowita. Wprowadz ponownie"<<endl;
	}
}

void pobierz2(Zespolone &z1, Zespolone &z2) //funkcja pobiera 2 l. zespolone
{
    cout<<"Wprowadzanie pierwszej liczby"<<endl;
    z1 = pobierzZespolona();

    cout<<"Wprowadzanie drugiej liczby"<<endl;
    z2 = pobierzZespolona();
}

Zespolone pobierzZespolona() //funckja pobiera od uzytkownika dane i zwraca utworzona z nich liczbe zespolona 
{
    int l1, m1, l2, m2;

    cout<<"Podaj licznik cz. rzeczywistej"<<endl;
    l1 = pobierzLiczbe();
    cout<<"Podaj mianownik cz. rzeczywistej"<<endl;
    m1 = pobierzLiczbe();
	while(m1 == 0)
	{
		cout<<"Blad, proba dzielenia przez zero"<<endl;
		m1 = pobierzLiczbe();
	}
    cout<<"Podaj licznik cz. urojonej"<<endl;
    l2 = pobierzLiczbe();
    cout<<"Podaj mianownik cz. urojonej"<<endl;
    m2 = pobierzLiczbe();
	while(m2 == 0)
	{
		cout<<"Blad, proba dzielenia przez zero"<<endl;
		m2 = pobierzLiczbe();
	}

    return Zespolone(l1, m1, l2, m2);
}

void pokazOpcje() //funkcja wyswietlajaca opcje (pomoc dla uzytkownika)
{
    cout<<"<Podaj cyfre i zatwierdz klawiszem 'enter'>"<<endl;
    cout<<"[0] - zakoncz"<<endl;
    cout<<"[1] - dodaj 2 liczby zespolone, zapisz wynik"<<endl;
    cout<<"[2] - dodaj liczbe zespolona do liczby w pamieci"<<endl;
    cout<<"[3] - odejmij 2 liczby zespolone, zapisz wynik"<<endl;
    cout<<"[4] - odejmij liczbe zespolona od liczby w pamieci"<<endl;
    cout<<"[5] - pomnoz 2 liczby zespolone, zapisz wynik"<<endl;
    cout<<"[6] - pomnoz liczbe zespolona przez liczbe w pamieci"<<endl;
    cout<<"[7] - wyswietl modul liczby w pamieci"<<endl;
    cout<<"[8] - wyswietl liczbe w pamieci"<<endl;
}
