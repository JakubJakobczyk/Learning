/*
autor: Jakub Jakobczyk

Zadanie 1.17
program szacujacy wartosc funkcji erf(x) dla zadanej dokladnosci n
dodatkowo program wykorzystuje wartosc pi wyliczana z wzoru na szacunkowa jej wartosc z dokladnoscia k
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pi(int k);               /*wylicza wartosc pi dla zadanej dokladnosci k*/
double silnia(int n);           /*wylicza wartosc n!*/
double sumy(int n, double x);   /*wylicza sume z wzoru na szacunkowa wartosc erf(x)*/

int main()
{
        /*
        zmienne przechowujace dane wprowadzane przez uzytkownika:
        dokladnosc_k - dokladnosc k dla pi
        dokladnosc_n - dokladnosc n dla funkcji y = erf(x)
        x- argument dla funkcji x

        pozostale zmienne:
        index - licznik dla petli
        pi_k - wartosc pi od zadanej dokladnosci k
        */
    int dokladnosc_k = 1, dokladnosc_n = 0, index = 0;
    double x = 0.0, wynik = 0.0, pi_k = 0.0;

        /*pobieranie danych*/
    printf("Podaj naturalna dokladnosc k dla liczby pi:\n");
    scanf("%d", &dokladnosc_k);
    printf("Podaj naturalna dokladnosc n dla funkcji erf(x):\n");
    scanf("%d", &dokladnosc_n);
    printf("Podaj argument x z przedzialu (-2, 2):\n");
    scanf("%lf", &x);

        /*obliczanie sumy:*/
    wynik += sumy(dokladnosc_n, x);
        /*obliczanie pi*/
    pi_k = pi(dokladnosc_k);

        /*mnozenie sumy przez 2/pierwiastek z pi*/
    wynik*=(2/sqrt(pi_k));

        /*wyswietlanie wyniku obu szeregow (pi oraz erf)*/
    printf("\n");
    printf("Pi dla dokladnosci k=%d wynosi %lf\n", dokladnosc_k, pi_k);
    printf("erf(%lf)=%lf\n", x, wynik);

    return 0;
}

double pi(int k)
{
    /*wartosc pi jest szacowana z wzoru w zaleznosci od dokladnosci k*/
    double wynik = 0.0;
    int i;
    for (i = 1; i <= k; i++)
    {
        double licznik = pow(-1.0, (double)(i+1));
        double mianownik = ((2.0*(double)i)-1.0);
        wynik += licznik/mianownik;
    }
    wynik*=4;
    return wynik;
}

double silnia(int n)
{
    /*wartosc silni dla argumentu wyliczana ze wzoru rekurencyjnego*/
    if (n==0 || n==1) return 1.0;
    else return n*silnia(n-1);
}

double sumy(int n, double x)
{
    /*Oblicznie sumy z wzoru na szacowanie erf(x) przy dokladnosci n*/
    int index = 0;
    double wynik = 0.0;
    for (index = 0; index <= n; index++)
    {
        double licznik = pow(-1.0, (double)index);
        double mianownik = (double)((2*index+1)*silnia(index));
        wynik += (licznik/mianownik) * pow(x, 2.0*(double)index+1.0);
    }
    return wynik;
}

