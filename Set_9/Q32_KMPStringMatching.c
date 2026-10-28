#include <stdio.h>
#include <string.h>

void computeLPS(char pattern[], int lps[])
{
    int m = strlen(pattern);
    int len = 0;
    int i = 1;

    lps[0] = 0;

    while(i < m)
    {
        if(pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if(len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMP(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[50];
    int i = 0, j = 0;

    computeLPS(pattern, lps);

    while(i < n)
    {
        if(text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if(j == m)
        {
            printf("Pattern found at position %d\n",
                   i - j);

            j = lps[j - 1];
        }
        else if(i < n && text[i] != pattern[j])
        {
            if(j != 0)
                j = lps[j - 1];
            else
                i++;
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

    KMP(text, pattern);

    return 0;
}