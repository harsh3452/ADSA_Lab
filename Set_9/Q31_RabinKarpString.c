#include <stdio.h>
#include <string.h>

#define d 256

void rabinKarp(char text[], char pattern[], int q)
{
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    for(i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for(i = 0; i < m; i++)
    {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for(i = 0; i <= n - m; i++)
    {
        if(p == t)
        {
            for(j = 0; j < m; j++)
            {
                if(text[i + j] != pattern[j])
                    break;
            }

            if(j == m)
                printf("Pattern found at position %d\n", i);
        }

        if(i < n - m)
        {
            t = (d * (t - text[i] * h)
                 + text[i + m]) % q;

            if(t < 0)
                t += q;
        }
    }
}

int main()
{
    char text[100], pattern[50];
    int q;

    printf("Enter text: ");
    scanf("%99s", text);

    printf("Enter pattern: ");
    scanf("%49s", pattern);

    printf("Enter prime number for hashing: ");
    scanf("%d", &q);

    rabinKarp(text, pattern, q);

    return 0;
}