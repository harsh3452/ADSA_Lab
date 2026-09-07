#include <stdio.h>

typedef struct {
    int left, right, state;
} Node;

void merge(int a[], int l, int m, int r) {
    int L[100], R[100];
    int n1 = m - l + 1, n2 = r - m;
    int i = 0, j = 0, k = l;

    for (int x = 0; x < n1; x++)
        L[x] = a[l + x];

    for (int x = 0; x < n2; x++)
        R[x] = a[m + 1 + x];

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];
}

void mergeSort(int a[], int n) {
    Node stack[100];
    int top = -1;

    stack[++top] = (Node){0, n - 1, 0};

    while (top >= 0) {
        Node x = stack[top--];

        if (x.left >= x.right)
            continue;

        int mid = (x.left + x.right) / 2;

        if (x.state == 0) {
            // After both halves are sorted, merge
            stack[++top] = (Node){x.left, x.right, 1};

            // Sort right half
            stack[++top] = (Node){mid + 1, x.right, 0};

            // Sort left half
            stack[++top] = (Node){x.left, mid, 0};
        }
        else {
            merge(a, x.left, mid, x.right);
        }
    }
}

int main() {
    int a[100], n;

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    mergeSort(a, n);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}