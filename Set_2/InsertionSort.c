#include <stdio.h>

void insertionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int j = i + 1;
        int key = arr[j];

        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            j--;
        }

        arr[j] = key;
    }
}

int main() {
    int arr[] = {8, 58, 5, 2, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}