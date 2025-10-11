#include <stdio.h>

#define MAX 10
typedef struct
{
    int elem[MAX];
    int lastNdx; // index of last element
} minHeap;

void displayHeap(minHeap H)
{
    printf("Heap Elements: { ");
    for (int i = 0; i <= H.lastNdx; i++)
    {
        printf("%d%s", H.elem[i], (i < H.lastNdx) ? ", " : " ");
    }
    printf("}\n");
}

void heapifySubtreeRecursive(minHeap *H, int index)

{
    if (index <= H->lastNdx / 2)
    {
        int leftChildNdx = (index * 2) + 1;
        int rightChildNdx = (index * 2) + 2;
        int smallestChilNdx;

        if (leftChildNdx <= H->lastNdx && rightChildNdx <= H->lastNdx)
        {
            smallestChilNdx = (H->elem[leftChildNdx] < H->elem[rightChildNdx]) ? leftChildNdx : rightChildNdx;
        }
        else if (rightChildNdx > H->lastNdx)
        {

            smallestChilNdx = leftChildNdx;
        }
        else
        {
            smallestChilNdx = rightChildNdx;
        }

        int temp;

        if (H->elem[index] > H->elem[smallestChilNdx])
        {
            temp = H->elem[index];
            H->elem[index] = H->elem[smallestChilNdx];
            H->elem[smallestChilNdx] = temp;

            heapifySubtreeRecursive(H, smallestChilNdx);
        }
    }
}

void heapifySubtree(minHeap *H, int index)
{
    int parentNdx = index;  // Start from given index
    int i = 0;              // Pass counter for debugging
    int flag = 1;
    // Continue while current node has children AND we need to keep swapping
    while (flag != 0 && (parentNdx * 2 + 2)  <= H->lastNdx) // check for the right most child
    {
        printf("\nParent is now %d\n", parentNdx);
        
        // Calculate child indices using heap formula
        int leftChildNdx = (parentNdx * 2) + 1;
        int rightChildNdx = (parentNdx * 2) + 2;
        int smallestChildNdx;

        // Find the smaller child (handles both children exist)
        if (leftChildNdx <= H->lastNdx && rightChildNdx <= H->lastNdx)
        {
            smallestChildNdx = (H->elem[leftChildNdx] < H->elem[rightChildNdx]) ? leftChildNdx : rightChildNdx;
        }
        // Only left child exists (right child out of bounds)
        else if (rightChildNdx > H->lastNdx)
        {
            smallestChildNdx = leftChildNdx;
        }
        // Only right child exists (edge case, shouldn't happen in proper heap)
        else
        {
            smallestChildNdx = rightChildNdx;
        }

        // Check if parent violates min-heap property
        if (H->elem[parentNdx] > H->elem[smallestChildNdx])
        {
            // Swap parent with smaller child
            int temp = H->elem[parentNdx];
            H->elem[parentNdx] = H->elem[smallestChildNdx];
            H->elem[smallestChildNdx] = temp;
            
            // Move to the position where we placed the larger element
            parentNdx = smallestChildNdx;

            printf("Pass: %d\n", i++);
            displayHeap(*H);
        }
        else
        {
            // Heap property satisfied, exit loop
            flag = 0;
        }
    }
}

int main()
{
    minHeap myHeap;

    printf("========================================\n");
    printf("Test 1: Right child is smaller, parent is larger\n");
    // Setup: Parent (100) is larger than its smallest child (30)
    myHeap.elem[0] = 100; // Parent
    myHeap.elem[1] = 40;  // Left Child
    myHeap.elem[2] = 30;  // Right Child
    myHeap.elem[3] = 40;
    myHeap.lastNdx = 3;
    printf("Initial State:\n");
    displayHeap(myHeap);
    // Expected Initial State: { 100, 40, 30, 40 }

    heapifySubtree(&myHeap, 0);
    printf("\nState after calling heapifySubtree(&myHeap, 0):\n");
    displayHeap(myHeap);
    // Expected Final State: { 100, 40, 30, 40 }
    // A swap does not occur because the condition `100 < 30` is false.

    printf("========================================\n");
    printf("Test 2: Left child is smaller, parent is larger\n");
    myHeap.elem[0] = 100; // Parent
    myHeap.elem[1] = 20;  // Left Child
    myHeap.elem[2] = 30;  // Right Child
    myHeap.lastNdx = 2;
    printf("Initial State:\n");
    displayHeap(myHeap);
    // Expected Initial State: { 100, 20, 30 }

    heapifySubtree(&myHeap, 0);
    printf("\nState after calling heapifySubtree(&myHeap, 0):\n");
    displayHeap(myHeap);
    // Expected Final State: { 100, 20, 30 }
    // A swap does not occur because the condition `100 < 20` is false.

    printf("========================================\n");
    printf("Test 3: Parent is smaller than its children (incorrect swap)\n");
    // Setup: Parent (10) is already smaller than its children.
    myHeap.elem[0] = 10; // Parent
    myHeap.elem[1] = 50; // Left Child
    myHeap.elem[2] = 60; // Right Child
    myHeap.lastNdx = 2;
    printf("Initial State:\n");
    displayHeap(myHeap);
    // Expected Initial State: { 10, 50, 60 }

    heapifySubtree(&myHeap, 0);
    printf("\nState after calling heapifySubtree(&myHeap, 0):\n");
    displayHeap(myHeap);
    // Expected Final State: { 50, 10, 60 }
    // An incorrect swap occurs because the condition `10 < 50` is true.

    printf("========================================\n");
    printf("Test 4: Multi-level heapify (recursive case)\n");
    // Setup: Root violates heap property at multiple levels
    myHeap.elem[0] = 100; // Root (largest)
    myHeap.elem[1] = 50;  // Left child
    myHeap.elem[2] = 30;  // Right child
    myHeap.elem[3] = 10;  // Left-left grandchild (smallest)
    myHeap.elem[4] = 40;  // Left-right grandchild
    myHeap.lastNdx = 4;
    printf("Initial State:\n");
    displayHeap(myHeap);
    // Expected Initial State: { 100, 50, 30, 10, 40 }

    heapifySubtree(&myHeap, 0);
    printf("\nState after calling heapifySubtree(&myHeap, 0):\n");
    displayHeap(myHeap);
    // Expected Final State: { 10, 40, 30, 100, 50 }
    // Multi-level swaps: 100->30, then 100->10 to properly heapify

    printf("========================================\n");
    printf("Test 5: Out-of-bounds child access (leaf node)\n");
    // Setup: Parent at index 1 has no children.
    myHeap.elem[0] = 10;
    myHeap.elem[1] = 50;
    myHeap.lastNdx = 1;
    printf("Initial State:\n");
    displayHeap(myHeap);
    // Expected Initial State: { 10, 50 }

    heapifySubtree(&myHeap, 1);
    printf("\nState after calling heapifySubtree(&myHeap, 1):\n");
    displayHeap(myHeap);
    // Expected Final State: { 10, 50 } (no change - index 1 is a leaf)
    printf("========================================\n");

    return 0;
}