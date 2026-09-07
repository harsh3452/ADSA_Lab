#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    int data;
    struct Node *next;
};

struct Node *head[SIZE];

int hash(int x) {
    return x / 10;   // for values 0-99
}

void insert(int x) {
    int a = hash(x);
    struct Node *p = malloc(sizeof(struct Node));
    p->data = x;

    if (head[a] == NULL || x < head[a]->data) {
        p->next = head[a];
        head[a] = p;
        return;
    }

    struct Node *q = head[a];
    while (q->next && q->next->data < x)
        q = q->next;

    p->next = q->next;
    q->next = p;
}

void addressSort(int a[], int n) {
    for (int i = 0; i < SIZE; i++)
        head[i] = NULL;

    for (int i = 0; i < n; i++)
        insert(a[i]);

    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        struct Node *p = head[i];

        while (p) {
            a[k++] = p->data;
            struct Node *t = p;
            p = p->next;
            free(t);
        }
    }
}

int main() {
    int a[] = {25, 57, 48, 37, 12, 92, 86, 33, 22, 10};
    int n = sizeof(a) / sizeof(a[0]);

    addressSort(a, n);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
}