#define DANE_H_INCLUDED


struct bramka *dane;
unsigned int rozmiar;

unsigned int rozmiarWejsc;

unsigned int *bityWejsciowe;

enum typyBramek {NOT, AND, OR};

void dodajBramke(int*, int*, int*, enum typyBramek); /*dodaje nowy element*/
void wyswietl(); /*wyswietla aktualna topologie ukladu*/
void test(); /*symuluje uklad*/
void usun(); /*zwalnia pamiec*/
