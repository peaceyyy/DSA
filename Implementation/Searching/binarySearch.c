#include <stdio.h>

int binarySearch (int arr[], int arrSize, int n)
{

    int LB = 0;
    int UB = arrSize - 1;
    int mid; 


    while (LB <= UB)
    {
        mid = (LB + UB)/2;

        if (arr[mid] < n) LB = mid + 1;
        else if (arr[mid] > n) UB = mid - 1; 

        else return mid;
    }

    return -1;


}

int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 7;
    int result = binarySearch(arr, size, target);
    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found\n", target);
    }
    target = 11;
    result = binarySearch(arr, size, target);
    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found\n", target);
    }
}