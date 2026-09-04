#include <stdio.h>

void bubbleSort(int arr[], int n);
void swap(int arr[], int j, int k);

int main() {
    int arr[] = {29, 10, 14, 37, 13, 10, 25, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);

    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}

void bubbleSort(int arr[], int n){  

    for(int i = 0; i < n; i++){ 
        int swapped = 0;

        for(int j = 0; j < n-i-1; j++){ 
            if(arr[j] > arr[j+1]){
                swap(arr, j+1, j);
                swapped = 1;
            }
        }

        if(!swapped) break;
    }
}

void swap(int arr[], int j, int k){
    int temp = arr[j];
    arr[j] = arr[k];
    arr[k] = temp;
}