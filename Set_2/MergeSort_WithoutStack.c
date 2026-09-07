#include <stdio.h>

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
    for (int size = 1; size < n; size *= 2) {

        for (int left = 0; left < n; left += 2 * size) {

            int mid = left + size - 1;
            int right = left + 2 * size - 1;

            if (mid >= n)
                break;

            if (right >= n)
                right = n - 1;

            merge(a, left, mid, right);
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