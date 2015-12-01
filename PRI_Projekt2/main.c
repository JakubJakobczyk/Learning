/*
autor: Jakub Jakobczyk

Zadanie 2.9
Program wyznaczajacy wzor na calke nieoznaczona z wprowadzonego wielomianu
*/

#include"dane.h"

#define MAX_DLUGOSC 128
#define MAX_LICZBA_WSPOL 32

/*funkcja wypisujaca calki*/
void calkuj (int*, int*, int);

int main()
{
/*napis - wprowadzony wielomian
  wspol - tablica wspolczynnikow
  potegi - tablica wykladnikow poteg*/
    char napis[MAX_DLUGOSC];
    int wspol[MAX_LICZBA_WSPOL];
    int potegi[MAX_LICZBA_WSPOL];
/*k - licznik ilosci wspolczynnikow*/
    int k = 0;

    pobierzDane(napis);
    wczytajDane(napis, wspol, potegi, &k);
    calkuj(wspol, potegi, k);

    return 0;
}

void calkuj(int* wspol, int* potegi, int dl) /*funkcja wypisujaca calki*/
{
    int i = 0;
    printf("\nWynik: y=");
    for (; i<=dl; i++)
    {
        if (i>0 && wspol[i]>0) printf("+");
        if ((wspol[i]%(potegi[i]+1)) == 0)
        {
            if (wspol[i]/(potegi[i]+1) == 1)
            {
                printf("x");
            }
            else
            {
                printf("%dx", (wspol[i]/(potegi[i]+1)));
            }
        }
        else
        {
            if (wspol[i]<0)
            {
                printf("-(%d/%d)x", -wspol[i], (potegi[i]+1));
            }
            else printf("(%d/%d)x", wspol[i], (potegi[i]+1));
        }

        if ((potegi[i]+1) != 1 && (potegi[i]+1) != 0) printf("^%d", potegi[i]+1);
    }
    printf("\n");
}
