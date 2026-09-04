#include <stdio.h>

void radixExchangeSort(int a[], int left, int right, int bit)
{
    if (left >= right || bit < 0)
    {
        return;
    }

    int i = left;
    int j = right;

    while (i <= j)
    {
        while (i <= right && ((a[i] >> bit) & 1) == 0)
        {
            i++;
        }

        while (j >= left && ((a[j] >> bit) & 1) == 1)
        {
            j--;
        }

        if (i < j)
        {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
            j--;
        }
    }

    radixExchangeSort(a, left, j, bit - 1);
    radixExchangeSort(a, i, right, bit - 1);
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

    radixExchangeSort(a, 0, n - 1, 30);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}