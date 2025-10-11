#include <stdio.h>
#define MAX 10

typedef struct
{

    int elems[MAX];
    int lastNdx;
} minHeap;

void initializeHeap(minHeap *H);
void populateHeap(minHeap *H, int array[], int size);
void insert(minHeap *H, int elem);
void deleteMin(minHeap *H);
void minHeapify(minHeap *H);
void heapSort(minHeap *H);
void displayHeap(minHeap H);

int main()
{
    minHeap H;
    
    printf("========================================\n");
    printf("Test 1: Basic Insert & Display\n");
    initializeHeap(&H);
    insert(&H, 50);
    insert(&H, 30);
    insert(&H, 70);
    insert(&H, 10);
    insert(&H, 40);
    printf("After inserts [50,30,70,10,40]: ");
    displayHeap(H);
    printf("\nExpected: 10 30 70 50 40 (min-heap property)\n");

    printf("========================================\n");
    printf("Test 2: Delete Min Operations\n");
    printf("Before delete: ");
    displayHeap(H);
    printf("\nDeleting min...\n");
    deleteMin(&H);
    printf("After 1st delete: ");
    displayHeap(H);
    printf("\nExpected: 30 40 70 50 (10 removed, heap property maintained)\n");
    
    deleteMin(&H);
    printf("After 2nd delete: ");
    displayHeap(H);
    printf("\nExpected: 40 50 70 (30 removed)\n");

    printf("========================================\n");
    printf("Test 3: Edge Case - Single Element\n");
    initializeHeap(&H);
    insert(&H, 42);
    printf("Single element: ");
    displayHeap(H);
    printf("\nExpected: 42\n");
    deleteMin(&H);
    printf("After delete: ");
    displayHeap(H);
    printf("\nExpected: (empty)\n");

    printf("========================================\n");
    printf("Test 4: Edge Case - Only Left Child\n");
    initializeHeap(&H);
    insert(&H, 20);
    insert(&H, 10);
    insert(&H, 30);
    insert(&H, 5);  // This creates a node with only left child
    printf("Before delete [20,10,30,5 -> 5,10,30,20]: ");
    displayHeap(H);
    deleteMin(&H);
    printf("\nAfter delete: ");
    displayHeap(H);
    printf("\nExpected: Should handle node with only left child correctly\n");
    
    printf("========================================\n");
    printf("Test 5: MinHeapify on an Unsorted Array\n");
    initializeHeap(&H);
    int unsortedData[] = {50, 70, 30, 80, 10, 40};
    int dataSize = sizeof(unsortedData) / sizeof(unsortedData[0]);
    populateHeap(&H, unsortedData, dataSize);
    printf("Before minHeapify: ");
    displayHeap(H);
    printf("\nCalling minHeapify...\n");
    minHeapify(&H);
    printf("After minHeapify: ");
    displayHeap(H);
    printf("\nExpected Output (based on flawed logic): 50 80 40 70 10 30 \n");

    return 0;
}

void initializeHeap(minHeap *H)
{
    H->lastNdx = -1;
}

void populateHeap(minHeap *H, int arr[], int size)
{
    for (int i = 0; i < size; i++){

        H->elems[++H->lastNdx] = arr[i];

    }
}

void insert(minHeap *H, int elem)
{

    // insert at last ndx
    if (H->lastNdx < MAX - 1)
    {

        H->elems[++H->lastNdx] = elem;
        int currentNdx = H->lastNdx;

        while (currentNdx > 0 && H->elems[(currentNdx - 1) / 2] > H->elems[currentNdx])
        {
            int parentNdx = (currentNdx - 1) / 2;
            int temp = H->elems[parentNdx];
            H->elems[parentNdx] = H->elems[currentNdx];
            H->elems[currentNdx] = temp;

            currentNdx = parentNdx;
        }
    }
    else
    {
        printf("Heap is full!");
    }

    // check if it has parent

    // while parent is larger swap or index is not 0
}

void deleteMin(minHeap *H)
{
    if (H->lastNdx != -1)
    {
        // Replace root with last element and shrink heap
        H->elems[0] = H->elems[H->lastNdx--];
        
        int currentNdx = 0;
        int flag = 0;

        // Sift down until node has no children OR heap property is satisfied
        while (flag == 0 && (currentNdx * 2 + 1) <= H->lastNdx)
        {
            int leftChild = currentNdx * 2 + 1;
            int rightChild = currentNdx * 2 + 2;
            int smallerChildNdx;
            
            // Find smaller child          (with bounds checking)
            if (leftChild <= H->lastNdx && rightChild <= H->lastNdx) {
                // Both children exist - choose smaller
                smallerChildNdx = (H->elems[leftChild] < H->elems[rightChild]) ? leftChild : rightChild;
            } else if (rightChild > H->lastNdx) {
                // Only left child exists
                smallerChildNdx = leftChild;
            } else {
                flag = 1;
            }
            
            // Check if heap property is satisfied
            if (flag == 0 && H->elems[currentNdx] > H->elems[smallerChildNdx]) {
                // Swap with smaller child
                int temp = H->elems[currentNdx];
                H->elems[currentNdx] = H->elems[smallerChildNdx];
                H->elems[smallerChildNdx] = temp;
                
                // Move to child position for next iteration
                currentNdx = smallerChildNdx;
            } else {
                // Heap property satisfied - done
                flag = 1;
            }
        }
    }
}

void displayHeap(minHeap H)
{
    for (int i = 0; i <= H.lastNdx; i++)
    {
        printf("%d ", H.elems[i]);
    }
}


void minHeapify (minHeap* H)
{
    /*
    ALGORITHM MinHeapify(H)
    INPUT: Array H with elements but not necessarily heap-ordered
    OUTPUT: Array H converted to min-heap



    BEGIN
        // Start from last parent and work backwards to root
        
        
        FOR parentIndex = (H.lastNdx - 1) / 2 DOWN TO 0 DO
            


            // Sift down this parent to correct position
            currentIndex = parentIndex
            
            WHILE currentIndex has at least one child DO
                leftChild = currentIndex * 2 + 1
                rightChild = currentIndex * 2 + 2
                
                // Find smallest among parent and children
                smallestIndex = currentIndex
                
                IF leftChild exists AND H[leftChild] < H[smallestIndex] THEN
                    smallestIndex = leftChild
                END IF
                
                IF rightChild exists AND H[rightChild] < H[smallestIndex] THEN
                    smallestIndex = rightChild
                END IF
                
                // If parent is already smallest, subtree is heapified
                IF smallestIndex == currentIndex THEN
                    BREAK  // or set flag to exit
                END IF
                
                // Swap parent with smallest child
                SWAP H[currentIndex] with H[smallestIndex]
                
                // Continue sifting from new position
                currentIndex = smallestIndex
                
    */
    int LC, RC, smallerNdx;
    
    for (int parentNdx = (H->lastNdx - 1)/2; parentNdx >= 0; parentNdx--)
    {    
        int flag = 0;
        int currentNdx = parentNdx;


            // keep going from parent down to its children if a swap happened or and if there are children to check (at the very least the LC)
        while (flag == 0 && (currentNdx * 2 + 1) <= H->lastNdx)
        {
            smallerNdx = currentNdx;
            LC = currentNdx * 2 + 1;
            RC = currentNdx * 2 + 2;


            // if left side exists and is smaller (do we prio left side first all the time?)
            if (LC <= H->lastNdx && H->elems[smallerNdx] > H->elems[LC])
            {
                smallerNdx = LC;
            } 
            

            // not using else if because right can also exist and be smaller
            if (RC <= H->lastNdx && H->elems[smallerNdx] > H->elems[RC])
            {
                smallerNdx = RC; 
            }

            // either no children or POT already satisfied for that subtree
            if (smallerNdx == currentNdx) // no swaps too place 
            {
                flag = 1;
            }

            // only swap if POT is not satisfied
            if (flag == 0){
                printf("i fired");
                 int temp = H->elems[currentNdx];
                H->elems[currentNdx] = H->elems[smallerNdx];
                H->elems[smallerNdx] = temp;
                // flag = 1;
            }


            currentNdx = smallerNdx;
            
        }    


    }
}

// Insert only if element satisfies condition (e.g., > threshold)
int insertIf(minHeap *H, int elem, int condition) {
    /*
    PSEUDOCODE:
    IF condition is met THEN
        perform normal insert
        RETURN 1 (success)
    ELSE
        RETURN 0 (rejected)
    */
    
    // Your implementation here
}


// Delete element at specific index (not just root)
int deleteAt(minHeap *H, int index) {
    /*
    PSEUDOCODE:
    IF index is valid THEN
        save element to return
        replace with last element
        shrink heap
        IF new element > original THEN
            sift down
        ELSE IF new element < original THEN  
            sift up
        RETURN saved element
    */
    
    // Your implementation here
}


// Change value at index and restore heap property
void updateValue(minHeap *H, int index, int newValue) {
    /*
    PSEUDOCODE:
    IF index is valid THEN
        oldValue = H->elems[index]
        H->elems[index] = newValue
        IF newValue < oldValue THEN
            sift up from index
        ELSE IF newValue > oldValue THEN
            sift down from index
    */
    
    // Your implementation here
}


// Get K smallest elements without destroying heap
void getKSmallest(minHeap *H, int k, int result[]) {
    /*
    PSEUDOCODE:
    create temporary heap (copy original)
    FOR i = 0 to k-1 DO
        result[i] = deleteMin from temp heap
    */
    
    // Your implementation here
}

// Find the Kth smallest element efficiently
int findKthSmallest(minHeap *H, int k) {
    /*
    PSEUDOCODE:
    create auxiliary max-heap of size k
    traverse original heap:
        IF aux heap not full THEN
            insert current element
        ELSE IF current < top of aux heap THEN
            remove max from aux heap
            insert current element
    RETURN top of aux heap
    */
    
    // Your implementation here
}


// Transform min-heap to max-heap in-place
void minToMaxHeap(minHeap *H) {
    /*
    PSEUDOCODE:
    FOR each parent from last to first DO
        apply max-heapify logic instead of min-heapify
        (compare and swap with LARGER child)
    */
    
    // Your implementation here
}


// Combine two heaps efficiently
minHeap* mergeHeaps(minHeap *H1, minHeap *H2) {
    /*
    PSEUDOCODE:
    create new heap with combined size
    copy all elements from both heaps
    apply heapify to combined array
    RETURN new heap
    */
    
    // Your implementation here
}



