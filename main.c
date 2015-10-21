#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT 128

int parseInt(char tab[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(tab[i]))
        {
            printf("Not a number\n");
            return 0;
        }
    }
    if (length > 7) //Should be MAX length of int
    {
        printf("Too big number\n");
        return 0;
    }
    int wynik = 0;
    for (int i = 0; i < length; i++)
    {
        printf("%d\n", (tab[i] - '0'));
        int temp = (tab[i] - '0');
        wynik += (tab[i] - '0')*pow(10.0, ((length-i)-1));
    }
    return wynik;
}

int main()
{
    char input[MAX_INPUT];
    scanf("%s", input);
    int length = strlen(input);
    printf("%d\n", parseInt(input, length));
    return 0;
}
