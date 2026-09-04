#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 10

struct Node
{
    int data;
    struct Node *next;
};

void insertSorted(struct Node **head, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= value)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node *current = *head;

    while (current->next != NULL && current->next->data < value)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void addressCalculationSort(int a[], int n)
{
    int min = a[0];
    int max = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] < min)
        {
            min = a[i];
        }

        if (a[i] > max)
        {
            max = a[i];
        }
    }

    if (min == max)
    {
        return;
    }

    struct Node *bucket[BUCKETS] = {NULL};

    for (int i = 0; i < n; i++)
    {
        int index = (int)((long long)(a[i] - min) *
                          (BUCKETS - 1) / (max - min));

        insertSorted(&bucket[index], a[i]);
    }

    int k = 0;

    for (int i = 0; i < BUCKETS; i++)
    {
        struct Node *current = bucket[i];

        while (current != NULL)
        {
            a[k] = current->data;
            k++;

            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main()
{
    int a[100];
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    addressCalculationSort(a, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}