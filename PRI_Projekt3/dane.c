#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Zmienne*/
unsigned int rozmiar = 0;
struct bramka* dane;
unsigned int *bityWejsciowe;
unsigned int rozmiarWejsc = 0;
unsigned int *wejscia;

/*enumeracje i struktury*/
enum typyBramek {NOT, AND, OR};
enum typyWejscia {UZYTKOWNIK, ELEMENT};

struct bramka
{
    unsigned int wyjscie;
    enum typyBramek typBramki;
    enum typyWejscia typW1;
    unsigned int wejscie1;
    enum typyWejscia typW2;
    unsigned int wejscie2;
};

/*funkcje*/
enum typyBramek dopasowanieTypu(int);/*fuckja zraca typ wejscia dla podanego wezla*/
void zmianaTypu(int);/*zmienia typy wejsc w istniejacych elementach*/
int dodajPierwszaBramke(int*, int*, int*, enum typyBramek); /*dodaje pierwszy element, zwraca 0 jesli sie powiodlo, 1 jesli nie*/

int zmienWejscia(int, int, int); /*funkcja aktualizuje wejscia, zwraca 0 jesli sie powiodlo, 1 jesli nie*/
void usunZdefiniowane(); /*funkcja usuwa nowozdefiniowane wejscia*/
void uporzadkujWejscia(int, int); /*porzadkuje wejscia, zwraca 0 jesli sie powiodlo, 1 jesli nie*/
void usunPowtorzenia1(int); /*usuwa powtarzajacy sie wezel pierwszy z wejsc*/
void usunPowtorzenia2(int); /*usuwa powtarzajacy sie wezel drugi z wejsc*/

int czyMoznaDodac(int *wyjscie, int *wezel1, int *wezel2); /*sprawdza czy mozna dodac element, zwraca 0 jesli tak, 1 jesli nie*/
int sprawdzSprzezenie(int, int, int, int); /*sprawdza czy wystapi sprzezenie zwrotne, zwraca 0 jesli nie, 1 jesli tak*/
int porownanie (const void*, const void*); /*funkcja porownujaca 2 elementy, zwraca 0 jesli rowne, 1 jesli pierwszy wiekszy, -1 jesli drugi wiekszy*/
int obliczWynik(int); /*funkcja oblicza wynik dzialania ukladu i zwraca wartosc*/


/*dodaje nowy element*/
void dodajBramke(int *wyjscie, int *wezel1, int *wezel2, enum typyBramek typ)
{
    if (rozmiar == 0)
    {
        if(dodajPierwszaBramke(wyjscie, wezel1, wezel2, typ)) return;
    }
    else
    {
		if(czyMoznaDodac(wyjscie, wezel1, wezel2)) return;
	/*Dodawnie bramki*/
        dane = realloc (dane, (rozmiar+1)*sizeof(struct bramka));
        dane[rozmiar].wyjscie = *wyjscie;
	/*Znajdowanie wyjscia dodawanego elementu wsrod wejsc i zmiana typu*/
		zmianaTypu(*wyjscie);
		
        dane[rozmiar].wejscie1 = *wezel1;
		dane[rozmiar].typW1 = dopasowanieTypu(*wezel1);
        dane[rozmiar].wejscie2 = *wezel2;
		if(*wezel2 != 0) dane[rozmiar].typW2 = dopasowanieTypu(*wezel1);
        dane[rozmiar].typBramki = typ;
        rozmiar++;
    }
    printf("Dodano element\n");
}

/*fuckja zraca typ wejscia dla podanego wezla*/
enum typyBramek dopasowanieTypu(int wezel1)
{
	int i = 0;
	for (; i<rozmiarWejsc; i++)
	{
		if(wejscia[i] == wezel1)
		{
			return UZYTKOWNIK;
		}
	}
	return ELEMENT;
}

/*zmienia typy wejsc w istniejacych elementach*/
void zmianaTypu(int wyjscie)
{
	int i = 0;
	for (; i<rozmiar; i++)
	{
		if(dane[i].wejscie1 == wyjscie)
		{
			dane[i].typW1 = ELEMENT;
			break;
		}
		if(dane[i].wejscie2!=0 && dane[i].wejscie2 == wyjscie)
		{
			dane[i].typW2 = ELEMENT;
			break;
		}
	}
}

/*dodaje pierwszy element, zwraca 0 jesli sie powiodlo, 1 jesli nie*/
int dodajPierwszaBramke(int *wyjscie, int *wezel1, int *wezel2, enum typyBramek typ)
{
	if (*wyjscie != 1 || *wezel1 == 1 || *wezel2 == 1)
    {
        printf("Blad\n");
        return 1;
    }
    if (typ == NOT)
    {
        wejscia = malloc(sizeof(int));
        wejscia[0] = *wezel1;
        rozmiarWejsc++;
    }
    else
    {
        wejscia = calloc(2, sizeof(int));
        wejscia[0] = *wezel1;
        wejscia[1] = *wezel2;
        rozmiarWejsc+=2;
        uporzadkujWejscia(*wezel1, *wezel2);
    }

    rozmiar++;
    dane = calloc(rozmiar, sizeof(struct bramka));
    dane[0].wyjscie = *wyjscie;
    dane[0].typW1 = UZYTKOWNIK;
    dane[0].wejscie1 = *wezel1;
    dane[0].typW2 = UZYTKOWNIK;
    dane[0].wejscie2 = *wezel2;
	if (typ == NOT) dane[0].wejscie2 = 0;
    dane[0].typBramki = typ;
	return 0;
}

/*funkcja aktualizuje wejscia, zwraca 0 jesli sie powiodlo, 1 jesli nie*/
int zmienWejscia(int wyjscie, int wezel1, int wezel2)
{
    int i = rozmiarWejsc-1;
    int czyIstnieje = 0;

	for (; i>=0; i--)
	{
		if (wyjscie == wejscia[i])
		{
			wejscia[i] = wezel1;
			czyIstnieje = 1;
			break;
		}
	}
	if (!czyIstnieje) return 1;

    if (wezel2 != 0)
    {
		wejscia = realloc(wejscia, ++rozmiarWejsc);
		wejscia[rozmiarWejsc-1] = wezel2;
    }
	usunZdefiniowane();
	uporzadkujWejscia(wezel1, wezel2);
    return 0;
}

/*funkcja usuwa nowozdefiniowane wejscia*/
void usunZdefiniowane()
{
	int i = 0, j;
	for (; i<rozmiarWejsc; i++)
	{
		for(j = 0; j<rozmiar; j++)
		{
			if (wejscia[i] == dane[j].wyjscie) wejscia[i] = 0;
		}
	}
}

/*porzadkuje wejscia, zwraca 0 jesli sie powiodlo, 1 jesli nie*/
void uporzadkujWejscia(int dodany1, int dodany2)
{
	usunPowtorzenia1(dodany1);
	if (dodany2!=0)
	{
		usunPowtorzenia2(dodany2);
	}
	qsort (wejscia, rozmiarWejsc, sizeof(int), porownanie);
}

/*usuwa powtarzajacy sie wezel pierwszy z wejsc*/
void usunPowtorzenia1(int dodany1)
{
	int i = 0, licznik = 0;
	for (;i<rozmiarWejsc; i++)
	{
		if (wejscia[i] == dodany1)
		{
			licznik++;
			if (licznik >= 2)
			{
				wejscia[i] = wejscia[rozmiarWejsc-1];
				rozmiarWejsc--;
			}
		}
		if(wejscia[i] == 0)
		{
			if (i == rozmiarWejsc-1)
			{
				rozmiarWejsc--;
			}
			else
			{
				wejscia[i] = wejscia[rozmiarWejsc-1];
				rozmiarWejsc--;
			}
		}
	}
}

/*usuwa powtarzajacy sie wezel drugi z wejsc*/
void usunPowtorzenia2(int dodany2)
{

	int licznik = 0, i = 0;
	for (i = 0; i<rozmiarWejsc; i++)
	{
		if (wejscia[i] == dodany2)
		{
			licznik++;
			if (licznik >= 2)
			{
				wejscia[i] = wejscia[rozmiarWejsc-1];
				rozmiarWejsc--;
			}
		}
	}
}

/*sprawdza czy mozna dodac element, zwraca 0 jesli tak, 1 jesli nie*/
int czyMoznaDodac(int *wyjscie, int *wezel1, int *wezel2)
{
        if (*wyjscie == *wezel1 || *wyjscie == *wezel2)
        {
            printf("Blad - sprzezenie zwrotne\n");
            return 1;
        }
        if(sprawdzSprzezenie(*wezel1, *wezel2, *wyjscie, *wyjscie))
        {
            printf("Blad - sprzezenie zwrotne\n");
            return 1;
        }
        if(zmienWejscia(*wyjscie, *wezel1, *wezel2))
        {
            printf("Blad, podany wezel wyjsciowy nie jest wejsciem\n");
            return 1;
        }
		return 0;
}

/*sprawdza czy wystapi sprzezenie zwrotne, zwraca 0 jesli nie, 1 jesli tak*/
int sprawdzSprzezenie(int wezel1, int wezel2, int wyjscie, int dodawane)
{
    int i = 0;
    for (;i<rozmiar;i++)
    {
        if (dane[i].wyjscie == wezel1)
        {
            if (dane[i].wejscie1 == dodawane) return 1;
			if (dane[i].wejscie2!=0 && dane[i].wejscie2 == dodawane) return 1;

            if (sprawdzSprzezenie(dane[i].wejscie1, dane[i].wejscie2, dane[i].wyjscie, dodawane)) return 1;
            break;
        }
    }
    if (wezel2 == 0) return 0;
    for (i=0; i<rozmiar; i++)
    {
        if (dane[i].wyjscie == wezel2)
        {
            if (dane[i].wejscie1 == dodawane) return 1;
			if (dane[i].wejscie2!=0 && dane[i].wejscie2 == dodawane) return 1;

            return sprawdzSprzezenie(dane[i].wejscie1, dane[i].wejscie2, dane[i].wyjscie, dodawane);
        }
    }
    return 0;
}

/*wyswietla aktualna topologie ukladu*/
void wyswietl()
{
    int i = 0;
    if (rozmiar == 0) printf("Wejscie: 1\nWyjscie: 1\n");
    else
    {
        for (;i<rozmiar; i++)
        {
            printf("%d=", dane[i].wyjscie);
            switch (dane[i].typBramki)
            {
                case NOT:
                    printf("not%d\n", dane[i].wejscie1);
                    continue;
                case AND:
                    printf("%dand%d\n", dane[i].wejscie1, dane[i].wejscie2);
                    break;
                case OR:
                    printf("%dor%d\n", dane[i].wejscie1, dane[i].wejscie2);
                    break;
            }
        }
        printf("Wejscia: ");
        for (i = 0;i<rozmiarWejsc; i++)

        {
            printf("%d ", wejscia[i]);
        }
        printf("\nWyjscie: 1\n");
    }

}

/*funkcja porownujaca 2 elementy, zwraca 0 jesli rowne, 1 jesli pierwszy wiekszy, -1 jesli drugi wiekszy*/
int porownanie (const void * a, const void * b)
{
    int _a = *(int*)a;
    int _b = *(int*)b;
    if(_a < _b) return -1;
    if(_a > _b) return 1;
    return 0;
}

/*symuluje uklad*/
void test()
{
	int wynik;
	if(rozmiarWejsc == 0)
	{
		printf("Wynik: %d\n", bityWejsciowe[0]);
	}
	else
	{
		wynik = obliczWynik(1);
		printf("Wynik: %d\n", wynik);
	}
	
	if(bityWejsciowe != NULL)
	{
		free(bityWejsciowe);
	}
}

/*funkcja oblicza wynik dzialania ukladu i zwraca wartosc*/
int obliczWynik(int wezel)
{
	int i = 0;
	for (;i<rozmiar; i++)
	{
		if(dane[i].wyjscie == wezel)
		{
			switch(dane[i].typBramki)
			{
				case NOT:
					return !obliczWynik(dane[i].wejscie1);
					break;
				case AND:
					return obliczWynik(dane[i].wejscie1)&&obliczWynik(dane[i].wejscie2);
					break;
				case OR:
					return obliczWynik(dane[i].wejscie1)||obliczWynik(dane[i].wejscie2);
					break;
			}
		}
	}
	for (i = 0; i<rozmiarWejsc; i++)
	{
		if(wejscia[i] == wezel) return bityWejsciowe[i];
	}
	printf("Blad przy obliczaniu - wynik moze nie byc poprawny\n");
	return 0;
}

/*zwalnia pamiec*/
void usun()
{
	/*if(bityWejsciowe != NULL)
	{
		free(bityWejsciowe);
	}*/

	if(wejscia != NULL)
	{
		free(wejscia);
	}

	if(dane!=NULL)
	{
		free(dane);
	}
}
