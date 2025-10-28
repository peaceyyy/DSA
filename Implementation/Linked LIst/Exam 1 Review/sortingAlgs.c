#include <stdio.h>
#include <stdlib.h>
#define ARRSIZE 5

void swap (int* a, int* b){
    
    int temp = *a;
    *a = *b;
    *b = temp;
}


void bubbleSort (int* arr){

    for (int i = 0; i < ARRSIZE - 1; i++){

        for (int j = 0; j < ARRSIZE - 1 - i; j++){

            if (arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }

    }
}

void insertionSort (int* arr){


    for (int i = 1; i < ARRSIZE; i++){

        int key = arr[i];
        int j;

        for (j = i - 1; j >= 0 && arr[j] > key; j--){
            arr[j + 1] = arr[j];
        }


        arr[j + 1] = key;
    }
}


void selectionSort (int* arr){

    for (int i = 0; i < ARRSIZE - 1; i++){

        int minIndex = i;
        int j;
    
        for (j = i + 1; j < ARRSIZE; j++){
            
            if (arr[j] < arr[minIndex]){ //always access minIndex value and not index itself
                minIndex = j;
            }
        }

        if (minIndex != i){
            swap(&arr[i], &arr[minIndex]);
        }
    }
}

void displayArray (int* arr){

    for (int i = 0; i < ARRSIZE; i++) printf("%d ", arr[i]);
}


int main (){

    int arr1[ARRSIZE] = {5, 2, 9, 1, 5};
    int arr2[ARRSIZE] = {5, 2, 9, 1, 5};
    int arr3[ARRSIZE] = {5, 2, 9, 1, 5};

    printf("Original array: ");
    displayArray(arr1);
    printf("\n");

    bubbleSort(arr1);
    printf("Bubble sorted: ");
    displayArray(arr1);
    printf("\n");

    insertionSort(arr2);
    printf("Insertion sorted: ");
    displayArray(arr2);
    printf("\n");

    selectionSort(arr3);
    printf("Selection sorted: ");
    displayArray(arr3);
    printf("\n");
}
