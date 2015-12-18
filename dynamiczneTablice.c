#include <stdio.h>
#include <stdlib.h>

int* tablicaLiczb;
int rozmiarTablicy = 0; /*Zamiast rozmiaru mo¿na u¿ywaæ sizeof(tablicaLiczb)/sizeOf(int)*/

void dodajElement(int);
void wyswietlWszystko();

int main()
{
    int doDodania = 2;
    for (;doDodania<10; doDodania+=2)
    {
        dodajElement(doDodania);
    }
    
    wyswietlWszystko();

/*WAZNE!!!
  Zwolnienie pamieci po zakonczeniu uzywania*/
    free(tablicaLiczb);
    return 0;
}

void dodajElement(int doDodania)
{
    if (rozmiarTablicy == 0)
    {
        rozmiarTablicy++;
        tablicaLiczb = calloc(rozmiarTablicy, sizeof(int));
        tablicaLiczb[0] = doDodania;
    }
    else
    {
        rozmiarTablicy++;
        tablicaLiczb = realloc(tablicaLiczb, rozmiarTablicy*sizeof(int));
        tablicaLiczb[rozmiarTablicy-1] = doDodania;
    }
}

void wyswietlWszystko()
{
    int i = 0;
    for (; i<rozmiarTablicy; i++)
    {
        printf("Element nr: %d = %d\n", i+1, tablicaLiczb[i]);
    }
}




