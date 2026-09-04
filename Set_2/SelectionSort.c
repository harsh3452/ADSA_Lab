#include <stdio.h>

void selectionSort(int arr[], int n);
void swap(int arr[], int j, int k);

int main() {
    int arr[] = {29, 10, 14, 37, 13, 10, 25, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    selectionSort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}

void selectionSort(int arr[], int n) {

    for (int i = 0; i < n; i++) {
        int minElementIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minElementIndex]) {
                minElementIndex = j;
            }
        }

        if (minElementIndex != i) {
            swap(arr, i, minElementIndex);
        }
    }
}

void swap(int arr[], int j, int k) {
    int temp = arr[j];
    arr[j] = arr[k];
    arr[k] = temp;
}