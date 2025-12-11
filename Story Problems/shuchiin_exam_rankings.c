/*
 * Shuchiin Academy Exam Rankings Crisis
 * Story Flavor: Anime (Kaguya-sama: Love is War)
 *
 * The Student Council needs to sort exam scores efficiently using HeapSort.
 * Implement both ascending (remedial) and descending (scholarship) sorting.
 *
 * Key Concepts:
 * - MinHeap → Descending Order (extract min, place at end)
 * - MaxHeap → Ascending Order (extract max, place at end)
 * - Heapify operations from bottom-up
 * - In-place sorting with O(n log n) time complexity
 */

#include <stdio.h>
#define MAX 50

typedef struct
{
    int scores[MAX];
    int lastNdx;
} Heap;

// Core Heap Operations
void initializeHeap(Heap *H);
void populateUnsorted(Heap *H, int arr[], int size);
void displayHeap(Heap H, const char *label);

// MinHeap Operations (for Descending Sort)
void insertMinHeap(Heap *H, int score);
int deleteMin(Heap *H);
void minHeapify(Heap *H);
void heapSortDescending(Heap *H);

// MaxHeap Operations (for Ascending Sort)
void insertMaxHeap(Heap *H, int score);
int deleteMax(Heap *H);
void maxHeapify(Heap *H);
void heapSortAscending(Heap *H);

// Utility
void testSorting(int arr[], int size, char mode);

int main()
{
    printf("+========================================+\n");
    printf("|   Shuchiin Academy Exam Rankings System v1.0          |\n");
    printf("|   Student Council Tech Committee                       |\n");
    printf("+========================================+\n\n");

    // Test 1: Scholarship Rankings (Descending)
    printf("==================================================\n");
    printf("Test 1: Scholarship Rankings (Descending Order)\n");
    printf("==================================================\n");
    int batch1[] = {85, 92, 78, 95, 88, 90};
    testSorting(batch1, 6, 'D');
    printf("Expected: 95 92 90 88 85 78\n\n"); // Expected: 95 92 90 88 85 78

    // Test 2: Remedial Classes (Ascending)
    printf("==================================================\n");
    printf("Test 2: Remedial Classes (Ascending Order)\n");
    printf("==================================================\n");
    int batch2[] = {45, 30, 55, 40, 50};
    testSorting(batch2, 5, 'A');
    printf("Expected: 30 40 45 50 55\n\n"); // Expected: 30 40 45 50 55

    // Test 3: Duplicate Scores
    printf("==================================================\n");
    printf("Test 3: Duplicate Scores (Descending)\n");
    printf("==================================================\n");
    int batch3[] = {70, 85, 70, 90, 85};
    testSorting(batch3, 5, 'D');
    printf("Expected: 90 85 85 70 70\n\n"); // Expected: 90 85 85 70 70

    // Test 4: Single Student
    printf("==================================================\n");
    printf("Test 4: Single Student (Edge Case)\n");
    printf("==================================================\n");
    int batch4[] = {88};
    testSorting(batch4, 1, 'A');
    printf("Expected: 88\n\n"); // Expected: 88

    // Test 5: Already Sorted (Ascending)
    printf("==================================================\n");
    printf("Test 5: Already Sorted Array (Ascending)\n");
    printf("==================================================\n");
    int batch5[] = {10, 20, 30, 40, 50};
    testSorting(batch5, 5, 'A');
    printf("Expected: 10 20 30 40 50\n\n"); // Expected: 10 20 30 40 50

    printf("==================================================\n");
    printf("All tests complete. Shirogane approves! ✓\n");
    printf("==================================================\n");

    return 0;
}

void initializeHeap(Heap *H)
{
    // TODO: Initialize lastNdx to -1 (empty heap)
    H->lastNdx = -1;
}

void populateUnsorted(Heap *H, int arr[], int size)
{
    // TODO: Copy array elements into heap without maintaining heap property
    // Just sequential insertion into scores array
    int i;
    for (i = 0; i < size; i++)
        H->scores[i] = arr[i];

    H->lastNdx = size - 1;
}

void displayHeap(Heap H, const char *label)
{
    printf("%s: ", label);
    for (int i = 0; i <= H.lastNdx; i++)
    {
        printf("%d ", H.scores[i]);
    }
    printf("\n");
}

void testSorting(int arr[], int size, char mode)
{
    // TODO: Create heap, populate with unsorted data, display before/after sorting
    // Call heapSortDescending() if mode == 'D'
    // Call heapSortAscending() if mode == 'A'
    Heap newHeap;
    initializeHeap(&newHeap);
    populateUnsorted(&newHeap, arr, size);
    
    displayHeap(newHeap, "Before Sorting: ");

    if (mode == 'D')
    heapSortDescending(&newHeap);
    else if (mode == 'A')
    heapSortAscending(&newHeap);

    displayHeap(newHeap, "After Sorting: ");
}

// ============================================================================
// MinHeap Operations (for Descending Sort)
// ============================================================================

void insertMinHeap(Heap *H, int score)
{
    // TODO: Insert score and sift-up to maintain min-heap property
    // Parent must be ≤ children
    // Formula: parent = (child - 1) / 2

    H->scores[++H->lastNdx] = score;
    int curr = H->lastNdx;

    while (1)
    {
        int parent = (curr - 1) / 2;
        if (H->scores[parent] > H->scores[curr])
        {
            int temp = H->scores[curr];
            H->scores[curr] = H->scores[parent];
            H->scores[parent] = temp;
            curr = parent;

        }
        else
        {
            break;
        }
    }
}

int deleteMin(Heap *H)
{
    // TODO: Remove root (minimum), replace with last element, sift-down
    // Choose smaller child to swap with
    // Return the deleted minimum value

    int min = H->scores[0];
    H->scores[0] = H->scores[(H->lastNdx)--];
    int currentNdx = 0;

    while ((currentNdx * 2 + 1) <= H->lastNdx)
    {
        int smallest = currentNdx;
        int LC = (currentNdx * 2) + 1;
        int RC = (currentNdx * 2) + 2;

        if (LC <= H->lastNdx && H->scores[LC] < H->scores[smallest])
            smallest = LC;
        if (RC <= H->lastNdx && H->scores[RC] < H->scores[smallest])
            smallest = RC;

        if (currentNdx != smallest)
        {
            int temp = H->scores[currentNdx];
            H->scores[currentNdx] = H->scores[smallest];
            H->scores[smallest] = temp;
            currentNdx = smallest;
        }
        else
        {
            break;
        }
    }

    return min;
}

void minHeapify(Heap *H)
{
    // TODO: Convert unsorted array into min-heap
    // Start from last parent: (lastNdx - 1) / 2
    // Sift-down each parent node to correct position

    for (int parent = (H->lastNdx - 1) / 2; parent >= 0; parent--)
    {
        int currentNdx = parent;

        while ((currentNdx * 2 + 1) <= H->lastNdx)
        {
            int smallest = currentNdx;
            int LC = (currentNdx * 2) + 1;
            int RC = (currentNdx * 2) + 2;

            if (LC <= H->lastNdx && H->scores[LC] < H->scores[smallest])
                smallest = LC;
            if (RC <= H->lastNdx && H->scores[RC] < H->scores[smallest])
                smallest = RC;

            if (currentNdx != smallest)
            {
                int temp = H->scores[currentNdx];
                H->scores[currentNdx] = H->scores[smallest];
                H->scores[smallest] = temp;
                currentNdx = smallest;
            }
            else
            {
                break;
            }
        }
    }
}

void heapSortDescending(Heap *H)
{
    // TODO: Sort in descending order using MinHeap
    // Step 1: Heapify the array
    // Step 2: Repeatedly deleteMin and place at end of array
    // Result: Smallest elements extracted first → placed at end → descending order
    minHeapify(H);

    int oldNdx = H->lastNdx;

    while (H->lastNdx >= 0)
    {
         
        int temp = deleteMin(H);
        H->scores[H->lastNdx + 1] = temp;
    }

    H->lastNdx = oldNdx;
}

// ============================================================================
// MaxHeap Operations (for Ascending Sort)
// ============================================================================

void insertMaxHeap(Heap *H, int score)
{
    H->scores[++H->lastNdx] = score;
    int curr = H->lastNdx;

    while (1)
    {
        int parent = (curr - 1) / 2;
        if (H->scores[parent] < H->scores[curr])
        {
            int temp = H->scores[curr];
            H->scores[curr] = H->scores[parent];
            H->scores[parent] = temp;
        }
        else
        {
            break;
        }
    }
}

int deleteMax(Heap *H)
{
    // TODO: Remove root (maximum), replace with last element, sift-down
    // Choose larger child to swap with
    // Return the deleted maximum value

    int max = H->scores[0]; 
    H->scores[0] = H->scores[H->lastNdx--];
    int currNdx = 0;

    while ((currNdx * 2) + 1 <= H->lastNdx)
    {
        int largest = currNdx;
        int LC = (currNdx * 2) + 1;
        int RC = (currNdx * 2) + 2;
        
        if (LC <= H->lastNdx && H->scores[LC] > H->scores[largest]) largest = LC; 
        if (RC <= H->lastNdx && H->scores[RC] > H->scores[largest]) largest = RC; 

        if (currNdx != largest)
        {

            int temp = H->scores[currNdx];
            H->scores[currNdx] = H->scores[largest];
            H->scores[largest] = temp;
            currNdx = largest;
            
            
        } else break;

    }
    
    return max;
}   

void maxHeapify(Heap *H)
{
    // TODO: Convert unsorted array into max-heap
    // Start from last parent: (lastNdx - 1) / 2
    // Sift-down each parent node to correct position

    for (int parent = (H->lastNdx - 1)/2; parent >= 0; parent--)
    {
        int currNdx = parent;
        while ((currNdx * 2) + 1 <= H->lastNdx)
    {
        int largest = currNdx;
        int LC = (currNdx * 2) + 1;
        int RC = (currNdx * 2) + 2;
        
        if (LC <= H->lastNdx && H->scores[LC] > H->scores[largest]) largest = LC; 
        if (RC <= H->lastNdx && H->scores[RC] > H->scores[largest]) largest = RC; 
        
        if (currNdx != largest)
        {
            
            int temp = H->scores[currNdx];
            H->scores[currNdx] = H->scores[largest];
            H->scores[largest] = temp;
            currNdx = largest;

        } else break;

    }

    }        
}

void heapSortAscending(Heap *H)
{
    // TODO: Sort in ascending order using MaxHeap
    // Step 1: Heapify the array
    // Step 2: Repeatedly deleteMax and place at end of array
    // Result: Largest elements extracted first → placed at end → ascending order

    maxHeapify(H);
    int oldNdx = H->lastNdx;

    while (H->lastNdx >= 0)
    {   
        int temp = deleteMax(H);
        H->scores[H->lastNdx + 1] = temp;
    }

    H->lastNdx = oldNdx;
}
