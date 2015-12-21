/*
autor: Jakub Jakobczyk

Projekt 3.2
Symulator kombinacyjnego ukladu logicznego
*/

#include <stdio.h>

#include "polecenia.h"
#include "dane.h"

int main()
{
    int polecenie = 0, wyjscie, wezel1, wezel2;
    usun();
	printf("\"Symulator kombinacyjnego ukladu logicznego\"\n");
/*glowna petla programu*/
    do
    {
        polecenie = wczytajPolecenie(&wyjscie, &wezel1, &wezel2);
        switch(polecenie)
        {
            case -2:
                printf("Nic nie wprowadzono\n");
                break;
            case -1:
                printf("Nieprawidlowa komenda\n");
                break;
            case 1:
                wyswietl(rozmiar);
                break;
            case 2:
				dodajBramke(&wyjscie, &wezel1, &wezel2, AND);
                break;
            case 3:
                dodajBramke(&wyjscie, &wezel1, &wezel2, OR);
                break;
            case 4:
				wezel2 = 0;
				dodajBramke(&wyjscie, &wezel1, &wezel2, NOT);
                break;
            case 5:
                test();
                break;
        }
    }while (polecenie!=0);

    usun();
    return 0;
}

