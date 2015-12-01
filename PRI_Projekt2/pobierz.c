#include "dane.h"

/*Funkcja sprawdza poprawnosc przekazanego wielomianu, zwraca ktory znak jest bledny lub '0' jesli poprawny*/
int sprawdzPoprawnosc(char*, int);

void pobierzDane(char* napis)/*funkcja pobierajaca dane od uzytkownika i sprawdzajaca ich poprawnosc*/
{
/*flaga - zmienna pomocnicza ktora zapisuje czy format danych jest poprawny
  rzltt - zmienna do ktorej przypisywana jest wartosc wynikowa funkcji sprawdzPoprawnosc
  dlgsc - dlugosc wprowadzonych danych
  i - licznik*/
    int flaga = 0, rzltt = 0, dlgsc = 0, i = 0;
    char ciag[MAX_LENGTH];

    do
    {
        printf("Podaj wielomian lub 0 aby zakonczyc dzialanie programu\n");
        printf("Wprowadzono: ");
        fgets(ciag, MAX_LENGTH, stdin);

        if (ciag[0] == '0')exit(0);
        dlgsc = strlen(ciag)-1;
/*jesli wprowadzono tylko 2symbole lub mniej - blad*/
        if (dlgsc < 3)
        {
            printf("Blad danych: ilosc znakow zbyt mala\n");
            printf("-----------\n");
            flaga = 1;
        }
/*sprawdzanie czy dane sa poprawne, jesli nie, zaznaczanie miejsca wystapienia bledu*/
        else
        {
            rzltt = sprawdzPoprawnosc(ciag, dlgsc);
            if (rzltt)
            {
                printf("Blad!  ->   ");
                for (i = 0; i<rzltt; i++) printf(" ");
                printf("^\n");
                printf("-----------\n");
                flaga = 1;
            }
            else flaga = 0;
        }
    }while(flaga);
    strcpy(napis, ciag);
}

int sprawdzPoprawnosc (char* napis, int dlgsc) /*Funkcja sprawdza poprawnosc przekazanego wielomianu, zwraca ktory znak jest bledny lub '0' jesli poprawny*/
{
/*i - licznik - okresla ktory znak jest sprawdzany*/
    int i = 2;
/*sprawdzanie poczatku wprowadzonego wielomianu*/
    if (napis[0] != 'y') return 1;
    if (napis[1] != '=') return 2;
    if (napis[2] != 'x' && napis[2] != '-' && !isdigit(napis[2])) return 3;
    if (napis[2] == '-' && dlgsc == 3) return 3;
    if (napis[2] == '-') i = 3;
    if (!isdigit(napis[dlgsc-1]) && napis[dlgsc-1] != 'x') return dlgsc;
/*dalsza czesc sprawdzania wprowadzonego wielomianu
  petla sprawdza czy kolejny ciag poprzedzony jest znakiem '+' lub '-'
  spelnie format - wspolczynnik*x^potega*/
    for (; i <= dlgsc; i++)
    {
/*sprawdzenie wspolczynnika:*/
        while(isdigit(napis[i]) && i<dlgsc) i++;
        if (i==dlgsc) return 0;
        if (napis[i]!='x') return i+1;
        if (++i == dlgsc) return 0;

        switch(napis[i])
        {
        case '+':
            continue;
            break;
        case '-':
            continue;
            break;
        case '^':
/*sprawdzenie wykladnika potegi*/
            if (++i == dlgsc) return i;
            if (!isdigit(napis[i])) return ++i;
            while(isdigit(napis[i]) && i<dlgsc)
            {
                i++;
            }
            if (i==dlgsc) return 0;
            if (napis[i]!='+' && napis[i]!='-') return i+1;
            break;
        default:
            return i+1;
        }
    }
    return 0;
}

