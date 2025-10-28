
#include <stdio.h>
#include <stdlib.h>
#define MAX 18

typedef struct
{

    int *elems;
    int lastNdx;
} maxHeap;

maxHeap *initMaxHeap();
void displayHeap(maxHeap H);
void insert(maxHeap *H, int val);
void delete(maxHeap *H);
void maxHeapify(maxHeap *H);

int main()
{

    maxHeap *MH;

    printf("========================================\n");
    printf("Test 1: Initialize and Insert elements\n");
    MH = initMaxHeap();
    insert(MH, 25);
    insert(MH, 30);
    insert(MH, 15);
    insert(MH, 50);
    insert(MH, 40);

    printf("Heap after inserts [25, 30, 15, 50, 40]:\n");
    displayHeap(*MH);
    printf("\nExpected Output: 50 40 15 25 30 \n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("Test 2: Delete max element\n");
    printf("Heap before delete:\n");
    displayHeap(*MH);

    delete(MH);
    printf("\nHeap after deleting max (50):\n");
    displayHeap(*MH);
    printf("\nExpected Output: 40 25 15 30 \n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("Test 3: Delete max element again\n");
    printf("Heap before delete:\n");
    displayHeap(*MH);

    delete(MH);
    printf("\nHeap after deleting max (40):\n");
    displayHeap(*MH);
    printf("\nExpected Output: 30 25 15 \n");
    printf("========================================\n\n");

    printf("========================================\n");
    printf("Test 4: maxHeapify on an unsorted array\n");
    // Manually populate the heap with unsorted data
    int unsortedData[] = {10, 50, 20, 5, 90, 30};
    int dataSize = sizeof(unsortedData) / sizeof(unsortedData[0]);
    MH->lastNdx = -1; // Reset heap
    for (int i = 0; i < dataSize; i++)
    {
        MH->elems[++MH->lastNdx] = unsortedData[i];
    }

    printf("Heap before maxHeapify:\n");
    displayHeap(*MH);
    maxHeapify(MH);
    printf("\nHeap after maxHeapify:\n");
    displayHeap(*MH);
    printf("\nExpected Output (for a correct implementation): 90 50 30 5 10 20 \n");
    printf("========================================\n\n");

    free(MH->elems);
    free(MH);

    return 0;
}

maxHeap *initMaxHeap()
{
    maxHeap *MH = malloc(sizeof(maxHeap));
    MH->elems = (int *)malloc(sizeof(int) * MAX);
    MH->lastNdx = -1;
    return MH;
}

void displayHeap(maxHeap H)
{
    for (int i = 0; i <= H.lastNdx; i++)
    {
        printf("%d ", H.elems[i]);
    }
}

void insert(maxHeap *H, int val)

{
    if (H->lastNdx != MAX - 1)
    {
        H->elems[++H->lastNdx] = val;
        int currentNdx = H->lastNdx;
        // Sift-up: Loop as long as the node is not the root and is greater than its parent.
        while (currentNdx > 0 && H->elems[currentNdx] > H->elems[(currentNdx - 1) / 2])
        {
            int parentNdx = (currentNdx - 1) / 2;
            int temp = H->elems[parentNdx];
            H->elems[parentNdx] = H->elems[currentNdx];
            H->elems[currentNdx] = temp;

            currentNdx = parentNdx;
        }
    }
}

void delete(maxHeap *H)
{
    // Only proceed if the heap is not empty
    if (H->lastNdx > -1)
    {
        // Replace the root with the last element and decrease the heap size
        int max = H->elems[0]; // Not strictly needed for this implementation, but good practice
        H->elems[0] = H->elems[H->lastNdx--];

        int currentNdx = 0;
        int flag = 1;

        // Sift-down: loop as long as the flag is set and the current node has at least a left child
        while (flag == 1)
        {
            int leftChild = currentNdx * 2 + 1;
            int rightChild = currentNdx * 2 + 2;
            int largerNdx = currentNdx; // Assume parent is the largest initially

            // Find the actual largest among parent, left child, and right child
            if (leftChild <= H->lastNdx && H->elems[leftChild] > H->elems[largerNdx])
            {
                largerNdx = leftChild;
            }
            if (rightChild <= H->lastNdx && H->elems[rightChild] > H->elems[largerNdx])
            {
                largerNdx = rightChild;
            }

            // If the largest is not the parent, swap and continue sifting down
            if (largerNdx != currentNdx)
            {
                int temp = H->elems[currentNdx];
                H->elems[currentNdx] = H->elems[largerNdx];
                H->elems[largerNdx] = temp;
                currentNdx = largerNdx; // Move down to continue sifting from the new position
            }
            else
            {
                // Parent is the largest, heap property is satisfied for this subtree.
                flag = 0; // Set flag to exit the loop
            }
        }
    }
}

void maxHeapify(maxHeap *H)
{
    if (H->lastNdx != -1)
    {
        for (int parentNdx = (H->lastNdx - 1) / 2; parentNdx >=  0; parentNdx--)
        {
            int flag = 1;
            int currentNdx = parentNdx;

            while (flag)
            {
                int largerNdx = currentNdx;
                int LC = (currentNdx * 2 + 1);
                int RC = (currentNdx * 2 + 2);

                if (LC <= H->lastNdx && H->elems[LC] > H->elems[largerNdx])
                {
                    largerNdx = LC;
                }

                if (RC <= H->lastNdx && H->elems[RC] > H->elems[largerNdx])
                {
                    largerNdx = RC;
                }

                if (largerNdx != currentNdx)
                {
                    int temp = H->elems[currentNdx];
                    H->elems[currentNdx] = H->elems[largerNdx];
                    H->elems[largerNdx] = temp;
                    currentNdx = largerNdx;
                }
                else
                {
                    flag = 0;
                }
            }
        }
    }
}