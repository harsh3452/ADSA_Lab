#include <stdio.h>

void insertionSort(float bucket[], int n)
{
    for (int i = 1; i < n; i++)
    {
        float key = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j] > key)
        {
            bucket[j + 1] = bucket[j];
            j--;
        }

        bucket[j + 1] = key;
    }
}

void bucketSort(float a[], int n)
{
    float bucket[10][100];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
    {
        int index = (int)(a[i] * 10);

        if (index == 10)
        {
            index = 9;
        }

        bucket[index][count[index]] = a[i];
        count[index]++;
    }

    for (int i = 0; i < 10; i++)
    {
        insertionSort(bucket[i], count[i]);
    }

    int k = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < count[i]; j++)
        {
            a[k] = bucket[i][j];
            k++;
        }
    }
}

int main()
{
    float a[100];
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements between 0 and 1: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &a[i]);
    }

    bucketSort(a, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%.2f ", a[i]);
    }

    return 0;
}