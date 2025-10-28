#include <stdio.h>
#include <stdlib.h>
#define SIZE 0xFF

typedef struct
{
    int elem[SIZE];
    int count;
} maxHeap, minHeap;

// V1

void maxSubHeapify(maxHeap *H, int subTreeRootNdx);
void maxHeapifyTree(maxHeap *H);
void swap(maxHeap *H);
void heapSortV1(maxHeap *H);

// V2
void insertMinHeap(minHeap *H, int x);
minHeap *insertAllMinHeap(minHeap *unsortedHeap);
int deleteMin(minHeap *H);
void heapSortV2(minHeap *H);

void displayHeap(maxHeap H, const char *label)
{
    printf("%s: { ", label);
    for (int i = 0; i < H.count; i++)
    {
        printf("%d%s", H.elem[i], (i < H.count - 1) ? ", " : " ");
    }
    printf("}\n");
}

void displayHeapSortV2(minHeap H, const char *label, int originalCount)
{
    printf("%s: { ", label);
    printf("Original: [");
    for (int i = 0; i < originalCount; i++)
    {
        printf("%d%s", H.elem[i], (i < originalCount - 1) ? ", " : "");
    }
    printf("] | Sorted: [");
    for (int i = originalCount; i < originalCount * 2; i++)
    {
        printf("%d%s", H.elem[i], (i < originalCount * 2 - 1) ? ", " : "");
    }
    printf("] }\n");
}

int main()
{
    minHeap minimumHeap;
    maxHeap maximumHeap;

    printf("========================================\n");
    printf("Test 1: maxSubHeapify on a simple subtree\n");
    int data1[] = {10, 80, 20};
    maximumHeap.count = 3;
    for (int i = 0; i < maximumHeap.count; i++)
        maximumHeap.elem[i] = data1[i];

    displayHeap(maximumHeap, "Initial State");
    printf("Calling maxSubHeapify(&maximumHeap, 0)...\n");
    maxSubHeapify(&maximumHeap, 0);
    displayHeap(maximumHeap, "Final State  ");
    printf("Expected Output: { 80, 10, 20 } (10 and 80 swap)\n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("Test 2: maxHeapifyTree on an unsorted array\n");
    int data2[] = {10, 50, 20, 5, 90, 30};
    maximumHeap.count = 6;
    for (int i = 0; i < maximumHeap.count; i++)
        maximumHeap.elem[i] = data2[i];

    displayHeap(maximumHeap, "Initial State");
    printf("Calling maxHeapifyTree(&maximumHeap)...\n");
    maxHeapifyTree(&maximumHeap);
    displayHeap(maximumHeap, "Final State  ");
    printf("Expected Output: { 90, 50, 30, 5, 10, 20 } (Array is heapified)\n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("Test 3: heapSortV1 to sort the array\n");
    // Using the heapified array from Test 2
    displayHeap(maximumHeap, "Initial State (Heapified)");
    printf("Calling heapSortV1(&maximumHeap)...\n");
    heapSortV1(&maximumHeap);
    // After sorting, the elements are in ascending order, but count is 0.
    // We will display the first 6 elements of the array to see the result.
    maximumHeap.count = 6; // Temporarily set count to display the sorted portion
    displayHeap(maximumHeap, "Final State  ");
    printf("Expected Output: { 5, 10, 20, 30, 50, 90 } (Array is sorted ascending)\n");
    printf("========================================\n\n");

    printf("\n////////////////////////////////////////\n");
    printf("///           V2 TESTS               ///\n");
    printf("////////////////////////////////////////\n\n");

    printf("========================================\n");
    printf("Test 4: insertMinHeap to build proper min-heap\n");
    minimumHeap.count = 0;
    printf("Inserting 50, 30, 70, 10...\n");
    insertMinHeap(&minimumHeap, 50);
    insertMinHeap(&minimumHeap, 30);
    insertMinHeap(&minimumHeap, 70);
    insertMinHeap(&minimumHeap, 10);
    displayHeap(minimumHeap, "Final State  ");
    printf("Expected Output: { 10, 30, 70, 50 } (Proper min-heap with 10 at root)\n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("Test 5: insertAllMinHeap from unsorted data\n");
    minHeap *newMinHeap;
    // Using the 'minimumHeap' from the previous test as the unsorted source
    displayHeap(minimumHeap, "Unsorted Data");
    printf("Calling insertAllMinHeap(&minimumHeap)...\n");
    newMinHeap = insertAllMinHeap(&minimumHeap);
    displayHeap(*newMinHeap, "Final State  ");
    printf("Expected Output: { 10, 30, 70, 50 } (Same min-heap structure)\n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("Test 6: deleteMin from min-heap\n");
    // Using the 'newMinHeap' from the previous test
    displayHeap(*newMinHeap, "Initial State");
    printf("Calling deleteMin(newMinHeap)...\n");
    int deletedValue = deleteMin(newMinHeap);
    printf("Deleted Value: %d\n", deletedValue);
    displayHeap(*newMinHeap, "Final State  ");
    printf("Expected Output: { 30, 50, 70 } (10 deleted, heap reorganized)\n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("Test 7: heapSortV2 for ascending order\n");
    // Reset minimumHeap with fresh data
    int data7[] = {50, 30, 70, 10};
    minimumHeap.count = 4;
    for (int i = 0; i < minimumHeap.count; i++)
        minimumHeap.elem[i] = data7[i];
    displayHeap(minimumHeap, "Initial State");
    printf("Calling heapSortV2(&minimumHeap)...\n");
    heapSortV2(&minimumHeap);
    displayHeapSortV2(minimumHeap, "Final State  ", 4);
    printf("Expected Output: Original: [50, 30, 70, 10] | Sorted: [10, 30, 50, 70] (Descending if read backwards)\n");
    printf("========================================\n\n");

    return 0;
}

// V1

// Given the maxHeap and the index Of the root Of
// function will make the subtree a heap (i.e. it
// supports the POT property)
void maxSubHeapify(maxHeap *H, int subTreeRootNdx)
{
    int currentNdx = subTreeRootNdx, flag = 1;
    int largerNdx;
    while (flag && (currentNdx * 2 + 1) < H->count)
    {
        largerNdx = currentNdx;
        int LC = currentNdx * 2 + 1;
        int RC = currentNdx * 2 + 2;

        if (LC < H->count && H->elem[LC] > H->elem[largerNdx])
            largerNdx = LC;
        if (RC < H->count && H->elem[RC] > H->elem[largerNdx])
            largerNdx = RC;

        if (largerNdx != currentNdx)
        {
            int temp = H->elem[currentNdx];
            H->elem[currentNdx] = H->elem[largerNdx];
            H->elem[largerNdx] = temp;
            currentNdx = largerNdx;
        }
        else
        {
            flag = 0;
        }
    }
}

// Given the maxHeap, the function will make tree a heap. Function will call maxSubheapify().
void maxHeapifyTree(maxHeap *H)
{

    for (int parentNdx = (H->count / 2) - 1; parentNdx >= 0; parentNdx--)
    {
        maxSubHeapify(H, parentNdx);
    }
}

// Given the root node and the lowest level a found at the
// rightmost, the function exchange the values of the
// nodes.
void swap(maxHeap *H)
{
    int temp = H->elem[0];
    H->elem[0] = H->elem[H->count - 1];
    H->elem[H->count - 1] = temp;
}

// Given an unsorted list (with data type maxHeap), the function
// will sort the elements in the given list in ascending order using
// heapsort technique.
// a) Call maxHeapifyTree() //to heapify the unsorted elements
// b) Call swap() and maxSubheapify() while there are still
// elements in the heap.
void heapSortV1(maxHeap *H)
{
    maxHeapifyTree(H);
    int originalCount = H->count;

    for (int i = H->count; i > 1; i--)
    {
        swap(H);
        H->count--;
        maxSubHeapify(H, 0);
    }

    H->count = originalCount;
}

// V2

// Given the minHeap and an element X,  at its proper position in the heap.

void insertMinHeap(minHeap *H, int x)
{
    if (H->count < SIZE)
    {
        H->elem[H->count++] = x;
        int currentNdx = H->count - 1; // Corrected index to last element
        int flag = 1;

        while (flag && currentNdx > 0) // Corrected loop condition to allow sifting to the root
        {
            int parentNdx = (currentNdx - 1) / 2;

            if (H->elem[parentNdx] > H->elem[currentNdx])
            {
                int temp = H->elem[parentNdx];
                H->elem[parentNdx] = H->elem[currentNdx];
                H->elem[currentNdx] = temp;
                currentNdx = parentNdx;
            }
            else
            {
                flag = 0;
            }
        }
    }
}

// Given the unsorted list (with data type minHeap) insert all elements in an initially emp ty. Use function insertMinHeap

minHeap *insertAllMinHeap(minHeap *unsortedHeap)
{

    minHeap *newHeap = malloc(sizeof(minHeap));
    if (newHeap != NULL)
        newHeap->count = 0;

    for (int i = 0; i < unsortedHeap->count; i++)
    {
        insertMinHeap(newHeap, unsortedHeap->elem[i]);
    }

    return newHeap;
}

// Given the minHeap, the function will store the root in
// a temporary variable, delete the root element by replacing it
// with the element at the lowest level far right, and push the
// new root to its proper position in the minHeap. Old root will be
// return to the calling function.

int deleteMin(minHeap *H)
{
    int temp = H->elem[0];
    H->elem[0] = H->elem[--H->count];
    int currentNdx = 0;
    int flag = 1;

    while (flag && (currentNdx * 2 + 1) < H->count)
      {   
        int smallerNdx = currentNdx;
        int LC = currentNdx * 2 + 1;
        int RC = currentNdx * 2 + 2;

        if (LC < H->count)
        {
            smallerNdx = LC;
        }

        if (RC < H->count && H->elem[RC] < H->elem[LC])
        {
            smallerNdx = RC;
        }

        if (H->elem[currentNdx] > H->elem[smallerNdx])
        {
            int temp = H->elem[currentNdx];
            H->elem[currentNdx] = H->elem[smallerNdx];
            H->elem[smallerNdx] = temp;
            currentNdx = smallerNdx;
        }
        else
        {
            flag = 0;
        }
    }

    return temp;
}

// Given an unsorted list (with data type mi*eap), the function
// will sort the elements in the given list in descending order
// using heapsort technique.
// a) Call insertAllMinHeap
// b) Call deleteMin while there are still elements in the heap and put the returned value of deleteMin at the position following the last element of the heap
void heapSortV2(minHeap *H)
{
    minHeap *newHeap = insertAllMinHeap(H);
    // int originalCount = H->count;
    int sortedIndex = H->count; // Start placing after original heap boundary
    
    H->count = 0; // Reset heap count to track original data
    
    while (newHeap->count > 0)
    {
        int deletedMin = deleteMin(newHeap);
        H->elem[sortedIndex++] = deletedMin; // Place after the heap boundary
    }
    
    // H->count = originalCount; // Restore count for display
}
