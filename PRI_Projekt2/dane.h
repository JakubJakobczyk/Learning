#define DANE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 128

void pobierzDane(char*); /*funkcja pobierajaca dane od uzytkownika i sprawdzajaca ich poprawnosc*/
void wczytajDane(char*, int*, int*, int*); /*funkcja wczytujaca wspolczynniki wielomianu do tablic*/

