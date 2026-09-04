#include <stdio.h>

int getMax(int a[], int n)
{
    int max = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
        }
    }

    return max;
}

void countingSort(int a[], int n, int place)
{
    int output[100];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
    {
        int digit = (a[i] / place) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (a[i] / place) % 10;

        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
    {
        a[i] = output[i];
    }
}

void radixSort(int a[], int n)
{
    int max = getMax(a, n);

    for (int place = 1; max / place > 0; place *= 10)
    {
        countingSort(a, n, place);
    }
}

int main()
{
    int a[100];
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter non-negative elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    radixSort(a, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}