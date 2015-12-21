#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dane.h"

#define MAX_DLUGOSC_POLECEN 128

static int czyTest(char*); /*Sprawdza czy polecenie test, zwraca 0 jesli tak, -1 jesli blad*/
static int czyDefinicja(int*, int*, char*, int*, int); /*sprawdza czy jest definicja nowego elementu lub elementu NOT, zwraca 0 jesli tak, -1 jesli blad, 4 jesli NOT*/
static int ktoraDefinicja(int*, char*, int*, int); /*sprawdza czy jest to AND lub OR, zwraca -1 jesli blad, 2 jesli AND, 2 jesli OR*/
static int czyNOT(int*, char*, int*, int); /*sprawdza czy jest to bramka NOT, zwraca 4 jesli tak, -1 jesli blad*/
static int czyOR(int*, char*, int*, int); /*sprawdza czy jest to bramka OR, zwraca 3 jesli tak, -1 jesli blad*/
static int czyAND(int*, char*, int*, int); /*sprawdza czy jest to bramka AND, zwraca 2 jesli tak, -1 jesli blad*/

int wczytajPolecenie(int* wyjscie, int* wezel1, int* wezel2)
{
    char polecenie[MAX_DLUGOSC_POLECEN];
    int i = 0;
	int wynik;

    printf("\n<symulator>: ");
    fgets(polecenie, MAX_DLUGOSC_POLECEN, stdin);
    if (strlen(polecenie)-1 == 0) return -2;
    polecenie[strlen(polecenie)-1] = '\0';

    if (strcmp(polecenie, "exit") == 0) return 0;
    if (strcmp(polecenie, "show") == 0) return 1;

	if(czyTest(polecenie) == 0) return 5;
	wynik = czyDefinicja(wyjscie, wezel1, polecenie, &i, rozmiar);
    if (wynik != 0) return wynik;
    return ktoraDefinicja(wezel2, polecenie, &i, rozmiar);
}

static int czyTest(char *polecenie)
{
	int i = 5;
	if(polecenie[0] == 't' && polecenie[1] == 'e' && polecenie[2] == 's' && polecenie[3] == 't' && polecenie[4] == ' ')
	{
		if((strlen(polecenie)!=rozmiarWejsc+5 && rozmiarWejsc != 0)||(rozmiarWejsc == 0 && strlen(polecenie) != 6))
		{
			return -1;
		}
		for(;i<strlen(polecenie); i++)
		{
			if (polecenie[i]!='0' && polecenie[i]!='1')
			{
				return -1;
			}
		}
		if(rozmiarWejsc == 0)
		{
			bityWejsciowe = calloc(1, sizeof(unsigned int));
			bityWejsciowe[0] = (polecenie[5] - '0');
			return 0;
		}
		bityWejsciowe = calloc(rozmiarWejsc, sizeof(unsigned int));
		for(i = 0; i<rozmiarWejsc; i++)
		{
			bityWejsciowe[i] = (polecenie[i+5] - '0');
		}
		return 0;
	}
	return -1;
}

static int czyDefinicja(int *wyjscie, int *wezel1, char *polecenie, int *i, int rozmiar)
{
    char temporary[MAX_DLUGOSC_POLECEN];
    int temporaryIndex = 0;
	
    if (!isdigit(polecenie[*i])) return -1;
    while (isdigit(polecenie[*i]))
    {
        temporary[temporaryIndex++] = polecenie[*i];
        *i+=1;
        if (*i >= strlen(polecenie)) return -1;
    }
    temporary[temporaryIndex] = '\0';

    *wyjscie = atoi(temporary);
    memset(temporary,0,strlen(temporary));
    temporaryIndex = 0;

    if (polecenie[*i]!='=' || *i+1 >= strlen(polecenie)) return -1;
    *i+=1;
	if (polecenie[*i] == '0') return -1;

    while (isdigit(polecenie[*i]))
    {
        temporary[temporaryIndex++] = polecenie[*i];
        *i+=1;
        if (*i >= strlen(polecenie))
		{
			memset(temporary,0,strlen(temporary));
			temporaryIndex = 0;
			return -1;
		}
    }
	if(!isdigit(polecenie[*i-1]))
	{
		return czyNOT(wezel1, polecenie, i, rozmiar);
	}

    temporary[temporaryIndex] = '\0';
    *wezel1 = atoi(temporary);
    memset(temporary,0,strlen(temporary));
    return 0;
}

static int ktoraDefinicja(int *wezel2, char *polecenie, int *i, int rozmiar)
{
    if (*i+2 >= strlen(polecenie)) return -1;
    if (polecenie[*i] == 'o' && polecenie[*i+1] == 'r')
    {
        return czyOR(wezel2, polecenie, i, rozmiar);
    }

	if (*i+3 >= strlen(polecenie)) return -1;
    if (polecenie[*i] == 'a' && polecenie[*i+1] == 'n' && polecenie[*i+2] == 'd')
    {
        return czyAND(wezel2, polecenie, i, rozmiar);
    }
	
	printf("Blad\n");
    return 0;
}


static int czyNOT(int *wezel1, char *polecenie, int *i, int rozmiar)
{
	char temporary[MAX_DLUGOSC_POLECEN];
    int temporaryIndex = 0;
	if (*i+3>=strlen(polecenie) || (polecenie[*i]!='n') || (polecenie[*i+1]!='o')||(polecenie[*i+2]!='t')  || polecenie[*i+3] == '0')
	{
		
		return -1;
	}
	*i+=3;
	while (isdigit(polecenie[*i]) && *i < strlen(polecenie))
	{
		temporary[temporaryIndex++] = polecenie[*i];
		*i+=1;
	}
	if (*i != strlen(polecenie))
	{
		memset(temporary,0,strlen(temporary));
		return -1;
	}
	temporary[temporaryIndex] = '\0';
	*wezel1 = atoi(temporary);
	memset(temporary,0,strlen(temporary));
	return 4;
}

static int czyOR(int *wezel2, char *polecenie, int *i, int rozmiar)
{
	char temporary[MAX_DLUGOSC_POLECEN];
    int temporaryIndex = 0;
	*i+=2;
	if(polecenie[*i] == '0') return -1;
    while (isdigit(polecenie[*i]) && *i < strlen(polecenie))
    {
        temporary[temporaryIndex++] = polecenie[*i];
        *i+=1;
    }
    temporary[temporaryIndex] = '\0';

    if (*i == strlen(polecenie))
    {
        *wezel2 = atoi(temporary);
        memset(temporary,0,strlen(temporary));
        return 3;
    }
    memset(temporary,0,strlen(temporary));
    return -1;
}

static int czyAND(int *wezel2, char *polecenie, int *i, int rozmiar)
{
	char temporary[MAX_DLUGOSC_POLECEN];
    int temporaryIndex = 0;
	*i+=3;
	if(polecenie[*i] == '0') return -1;
    while (isdigit(polecenie[*i]) && *i < strlen(polecenie))
    {
        temporary[temporaryIndex++] = polecenie[*i];
        *i+=1;
    }
    temporary[temporaryIndex] = '\0';

    if (*i == strlen(polecenie))
    {
        *wezel2 = atoi(temporary);
        memset(temporary,0,strlen(temporary));
        return 2;
    }
    memset(temporary,0,strlen(temporary));
    return -1;
}

