#include "dane.h"

/*funkcja przypisujaca wykladniek potegi do odpowiedniego miejsca w tablicy*/
void przypiszPotege(int doZapisu, int* potegi, int* j, int* k, int* i);
/*funkcja wczytujaca kolejny wspolczynnik z wprowadzonego ciagu znakow*/
int wczytajWspol(char* napis, int* i);

void wczytajDane(char* napis, int* wspol, int* potegi, int* ilCznnkw)/*funkcja wczytujaca wspolczynniki wielomianu do tablic*/
{
    int i = 1, j = 0, k = 0;
    char temporary[MAX_LENGTH];

    for (;i<strlen(napis)-1; i++)
    {
/*wczytaj wspolczynnik*/
        wspol[k] = wczytajWspol(napis, &i);
/*sprawdz warunek konca*/
        if (i >= strlen(napis)-1)
        {
            przypiszPotege(0, potegi, &j, &k, &i);
            memset(temporary, 0, MAX_LENGTH);
            break;
        }
/*wczytaj wykladnik potagi*/
        if (napis[i] == 'x')
        {
            if (napis[++i] == '^')
            {
                i++;
                while (isdigit(napis[i]))
                {
                    temporary[j++] = napis[i++];
                }
                przypiszPotege(atoi(temporary), potegi, &j, &k, &i);
            }
            else przypiszPotege(1, potegi, &j, &k, &i);

            memset(temporary, 0, MAX_LENGTH);
        }
    }
    *ilCznnkw = --k;
}

void przypiszPotege(int doZapisu, int* potegi, int* j, int* k, int* i) /*funkcja przypisujaca wykladniek potegi do odpowiedniego miejsca w tablicy*/
{
    potegi[*k] = doZapisu;
    *k+=1;
    *j = 0;
    *i-=1;
}

int wczytajWspol(char* napis, int* i) /*funkcja wczytujaca kolejny wspolczynnik z wprowadzonego ciagu znakow*/
{
/*temporary - tymczasowa tablica do ktorej wczytywane sa koleje znaki znaczace*/
    char temporary[MAX_LENGTH];
/*j - licznik wspol - obliczony wspolczynnik*/
    int j = 0, wspol;
    if (napis[*i] == '+' || napis[*i] == '-' || napis[*i] == '=')
    {
        if (napis[*i] == '+' || napis[*i] == '=') *i+=1;
        if (napis[*i] == '-' && napis[*i+1] == 'x')
        {
            *i+=1;
            return -1;
        }
        if (isdigit(napis[*i]) || (isdigit(napis[*i+1]) && napis[*i]=='-'))
        {
            while (isdigit(napis[*i]) || napis[*i]=='-')
            {
                temporary[j++] = napis[*i];
                *i += 1;
            }
            wspol = atoi(temporary);
            memset(temporary, 0, MAX_LENGTH);
            return wspol;
        }
    }
    return 1;
}
