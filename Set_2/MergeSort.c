#include <stdio.h>
#include <stdlib.h>

void mergeSort(int array[], int l, int r);
void merge(int array[], int l, int mid, int r);
void printArray(int array[], int n);

int main() {
    int array[] = {1, 4, 5, 6, 3, 66, 777, 543, 87, 54, 23, 65};
    int n = sizeof(array) / sizeof(array[0]);

    mergeSort(array, 0, n - 1);
    printArray(array, n);

    return 0;
}

void mergeSort(int array[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;

        mergeSort(array, l, mid);
        mergeSort(array, mid + 1, r);

        merge(array, l, mid, r);
    }
}

void merge(int array[], int l, int mid, int r) {
    int n1 = mid - l + 1;
    int n2 = r - mid;

    int *lArray = (int *)malloc(n1 * sizeof(int));
    int *rArray = (int *)malloc(n2 * sizeof(int));

    for (int x = 0; x < n1; x++) {
        lArray[x] = array[l + x];
    }

    for (int x = 0; x < n2; x++) {
        rArray[x] = array[mid + x + 1];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (lArray[i] <= rArray[j]) {
            array[k] = lArray[i];
            i++;
        } else {
            array[k] = rArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = lArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = rArray[j];
        j++;
        k++;
    }

    free(lArray);
    free(rArray);
}

void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}