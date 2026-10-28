#include <stdio.h>
#include <string.h>

#define SIZE 256

void badCharacterTable(char pattern[], int badChar[])
{
    int i;
    int m = strlen(pattern);

    for(i = 0; i < SIZE; i++)
        badChar[i] = -1;

    for(i = 0; i < m; i++)
        badChar[(unsigned char)pattern[i]] = i;
}

void boyerMoore(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    int badChar[SIZE];
    int shift, j;

    if(m > n)
    {
        printf("Pattern not found\n");
        return;
    }

    badCharacterTable(pattern, badChar);

    shift = 0;

    while(shift <= n - m)
    {
        j = m - 1;

        while(j >= 0 &&
              pattern[j] == text[shift + j])
            j--;

        if(j < 0)
        {
            printf("Pattern found at position %d\n", shift);

            if(shift + m < n)
                shift += m - badChar[(unsigned char)text[shift + m]];
            else
                shift++;
        }
        else
        {
            int move = j - badChar[(unsigned char)text[shift + j]];

            if(move < 1)
                move = 1;

            shift += move;
        }
    }
}

int main()
{
    char text[100];
    char pattern[50];

    printf("Enter text: ");
    scanf("%99s", text);

    printf("Enter pattern: ");
    scanf("%49s", pattern);

    boyerMoore(text, pattern);

    return 0;
}