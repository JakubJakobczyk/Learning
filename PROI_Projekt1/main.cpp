//#define _DEBUG
#include <iostream>
#include <cstdio>

#include "zespolone.h"

using namespace std;

Zespolone pobierzZespolona();
int pobierzLiczbe();
void pobierz2(Zespolone &, Zespolone &);
void pokazOpcje();

int main()
{
    Zespolone *pamiec1 = new Zespolone(), *pamiec2 = new Zespolone();
    int ster = 1;
    while(ster!=0)
    {
        pokazOpcje();
        ster = pobierzLiczbe();
        if (ster == 0) break;
        else if (ster == 1)
        {
            pobierz2(*pamiec1, *pamiec2);
            cout<<&pamiec1<<"+"<<&pamiec2<<"=";
            *pamiec1=*pamiec1+*pamiec2;
            cout<<pamiec1<<endl;
        }
        else if (ster == 2)
        {
            cout<<"Wprowadzanie liczby:"<<endl;
            *pamiec2 = pobierzZespolona();

            cout<<pamiec1<<"+="<<pamiec2<<"=";
            *pamiec1+=*pamiec2;
            cout<<pamiec1<<endl;
        }
        else if (ster == 3)
        {
            pobierz2(*pamiec1, *pamiec2);
            cout<<pamiec1<<"-"<<pamiec2<<"=";
            *pamiec1=*pamiec1-*pamiec2;
            cout<<pamiec1<<endl;
        }
        else if (ster == 4)
        {
            cout<<"Wprowadzanie liczby:"<<endl;
            *pamiec2 = pobierzZespolona();

            cout<<pamiec1<<"-="<<pamiec2<<"=";
            *pamiec1-=*pamiec2;
            cout<<pamiec1<<endl;
        }
        else if (ster == 5)
        {
            pobierz2(*pamiec1, *pamiec2);
            cout<<pamiec1<<"*"<<pamiec2<<"=";
            *pamiec1=*pamiec1*(*pamiec2);
            cout<<pamiec1<<endl;
        }
        else if (ster == 6)
        {
            cout<<"Wprowadzanie liczby:"<<endl;
            *pamiec2 = pobierzZespolona();

            cout<<pamiec1<<"*="<<pamiec2<<"=";
            *pamiec1*=*pamiec2;
            cout<<pamiec1<<endl;
        }
        else if (ster == 7)
        {
            cout<<"|"<<pamiec1<<"|="<<(*pamiec1).mod()<<endl;
        }
        else if (ster == 8)
        {
            cout<<"Pamiec: "<<pamiec1<<endl;
        }
        cout<<"Wcisnij dowolny klawisz aby kontynuowac"<<endl;
        getchar();
        cout<<endl;
    }
    return 0;
}

int pobierzLiczbe()
{
	string s;
	int liczba;
    while(1)
	{
		cin>>s;
		int n = s.length();
		int i=1;
		if (s[0]!='-' && !isdigit(s[0]))
		{
			cout <<"Blad. Wprowadzany ciag nie jest liczba"<<endl;
			continue;
		}
		for ( ; i<n; i++)
		{
			if (!isdigit(s[i])) break;
		}
		if (i==n)
		{
			liczba = stoi(s);
			return liczba;
		}
		else cout <<"Niepoprawny format danych, wpisz dane jeszcze raz"<<endl;
	}
}

void pobierz2(Zespolone &z1, Zespolone &z2)
{
    cout<<"Wprowadzanie pierwszej liczby"<<endl;
    z1 = pobierzZespolona();

    cout<<"Wprowadzanie drugiej liczby"<<endl;
    z2 = pobierzZespolona();
}

Zespolone pobierzZespolona()
{
    int l1, m1, l2, m2;

    cout<<"Podaj licznik cz. rzeczywistej"<<endl;
    l1 = pobierzLiczbe();
    cout<<"Podaj mianownik cz. rzeczywistej"<<endl;
    m1 = pobierzLiczbe();
    cout<<"Podaj licznik cz. urojonej"<<endl;
    l2 = pobierzLiczbe();
    cout<<"Podaj mianownik cz. urojonej"<<endl;
    m2 = pobierzLiczbe();

    return Zespolone(l1, m1, l2, m2);
}

void pokazOpcje()
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
