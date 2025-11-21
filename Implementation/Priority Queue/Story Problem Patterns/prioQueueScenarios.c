#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Minimal heap stub so this file compiles as a scaffold.
// Real heap implementation is left to the user.
typedef struct {
    int *elems;
    int size;
    int capacity;
} minHeap;


// --- Utility functions for testing scaffold ---
// NOTE: A proper heap implementation is required for the scenarios to work.
// The functions below are provided to make this test file runnable.

void swap(int *a, int *b) {

    int temp = *a;
    *a = *b;
    *b = temp;
    
}


minHeap* initHeap(int capacity) {
    
    minHeap* H = (minHeap*) malloc(sizeof(minHeap));  
    H->elems = (int*) malloc(sizeof(int) * capacity);
    H->size = 0;
    H->capacity = capacity;
    return H;
}

void destroyHeap(minHeap* H) {
    if (H == NULL) return;
    free(H->elems);
    free(H);
}

void heapifyDown(minHeap *H, int i) {
    
    int currentNdx = i;
    int noSwap = 0;
 
    while (((currentNdx * 2) + 1 < H->size) && noSwap != 1)
    {
        int smallerNdx = currentNdx;
        int LC = (currentNdx * 2) + 1;
        int RC = (currentNdx * 2) + 2;

        if (LC <  H->elems[LC]) smallerNdx  = LC;
        if (RC < H->size && H->elems[smallerNdx] > H->elems[RC]) smallerNdx = RC;

        if (smallerNdx != currentNdx)
        {   
            swap(&H->elems[currentNdx], &H->elems[smallerNdx]);
            currentNdx = smallerNdx;
        } else {

            noSwap = 1;
        }

    }
}

void heapifyUp(minHeap *H, int i) {

    int currentNdx = i;
    
    while (currentNdx > 0)
    {
        int parentNdx = (currentNdx - 1)/2;

        if (H->elems[parentNdx] >= 0 && H->elems[parentNdx] > H->elems[currentNdx])
        {
            swap(&H->elems[currentNdx], &H->elems[parentNdx]);
            currentNdx = parentNdx;
        } 
        
        else {
            break;
        }

    }
}

void insert (minHeap* H, int n)
{
    
    if (H->size < H->capacity)
    {
        H->elems[H->size++] = n;
        heapifyUp(H, H->size - 1);
    }
}

int deleteMin(minHeap* H) {
    
    int temp = H->elems[0];
    H->elems[0] = H->elems[--H->size];
    heapifyDown(H,0);

    return temp;

}

void printHeap(minHeap *H, const char* title) {
    printf("%s [size=%d]: ", title, H->size);
    for (int i = 0; i < H->size; ++i) {
        printf("%d ", H->elems[i]);
    }
    printf("\n");
}


typedef struct {
    minHeap* maxHeap; // for smaller half (use negative values)
    minHeap*  minHeap; // for larger half
} MedianFinder;

int getMedian(MedianFinder* mf) {
    /*
    PSEUDOCODE:
    IF heap sizes equal THEN
    
    
        return average of both tops
    ELSE
        return top of larger heap
    */
    
    // Your implementation here
    if (mf->minHeap->size == mf->maxHeap->size){
        return (-mf->minHeap->elems[0] + mf->maxHeap->elems[0]) / 2; 
    } else {
        return (mf->minHeap->size > mf->maxHeap->size) ? mf->minHeap->elems[0] : -mf->maxHeap->elems[0];
    }

}

void addNumber(MedianFinder *mf, int num) {

    minHeap* maxHeap = initHeap(10);
    minHeap* minHeap = initHeap(10);

    /*
    PSEUDOCODE:
    IF both heaps empty OR num <= current median THEN
    
        add to max heap (smaller half)
    ELSE
        add to min heap (larger half)
    balance heaps if size difference > 1
    */
    
    if (mf->minHeap->size == 0 && mf->maxHeap->size == 0 || num <= getMedian(mf))
    {
        insert(mf->maxHeap, -num);
    } else {
        
        insert(mf->minHeap, num);
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
    if (condition){
        insert(H, elem);
        return 1;
    }

    else return 0;
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
    
    if (index < H->size)
    {
        int temp = H->elems[index];
        H->elems[index] = H->elems[--H->size];

        if (H->elems[index] > temp){
            heapifyDown(H, index);
        } else {
            
            heapifyUp(H, index);
        }
    }



    return -1;
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
    
    
    if (index < H->size){
        
        int temp = H->elems[index];
        H->elems[index] = newValue; 

        if (H->elems[index] > temp)
        {
            heapifyUp(H, index);

        } else {
            heapifyDown(H, index);
        }
    }
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
    minHeap *heapCopy = initHeap(H->capacity);
    heapCopy->size = H->size;
    memcpy(heapCopy->elems, H->elems, sizeof(int) * H->size);

    for (int i = 0; i < k - 1; i++)
    {
        result[i] = deleteMin(heapCopy);
    }

    
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
    // Placeholder return to allow compilation.
    return -1;
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
    // Placeholder: return NULL until real implementation provided.
    return NULL;
}


// -----------------------------------------------------------------------------
// Boilerplate main() - Test Scaffold
// Uncomment the blocks one by one as you implement the functions.
// -----------------------------------------------------------------------------
int main(void) {
    printf("========== Priority Queue Scenarios — Test Harness ==========\n\n");

    // minHeap* newHeap = initHeap(10);
    // insert(newHeap, 2);
    // insert(newHeap, 3);
    // printf("\n");
    // insert(newHeap, 4);
    // insert(newHeap, 9);
    // printHeap(newHeap, "Our Heap!");
    // deleteMin(newHeap);
    // printHeap(newHeap, "Our New Heap!");
    // printf("\n");


    // --- Test Block 1: MedianFinder (addNumber / getMedian) ---
    // printf("--- 1) Testing MedianFinder ---\n");
    // MedianFinder mf;
    // mf.maxHeap = initHeap(10);
    // mf.minHeap = initHeap(10);
    
    // printf("Adding 1, 3, 2...\n");
    // addNumber(&mf, 1);
    // addNumber(&mf, 3);
    // addNumber(&mf, 2);
    // printf("Median should be 2. GOT: %d\n\n", getMedian(&mf));
    // destroyHeap(mf.maxHeap);
    // destroyHeap(mf.minHeap);

    // // --- Test Block 2: insertIf ---
    // printf("--- 2) Testing insertIf ---\n");
    // minHeap* h_insertIf = initHeap(10);
    // int condition_met = 1; // Simulate condition being true
    // int condition_not_met = 0; // Simulate condition being false
    
    // printf("Attempting to insert 5 (condition true)...\n");
    // int result1 = insertIf(h_insertIf, 5, condition_met);
    // printf("Expected 1, GOT: %d. ", result1);
    // printHeap(h_insertIf, "Heap state:");

    // printf("Attempting to insert 10 (condition false)...\n");
    // int result2 = insertIf(h_insertIf, 10, condition_not_met);
    // printf("Expected 0, GOT: %d. ", result2);
    // printHeap(h_insertIf, "Heap state:");
    // printf("\n");
    // destroyHeap(h_insertIf);
    
    /*
    // --- Test Block 3: deleteAt ---
    printf("--- 3) Testing deleteAt ---\n");
    minHeap* h_deleteAt = initHeap(10);
    insert(h_deleteAt, 3); insert(h_deleteAt, 8); insert(h_deleteAt, 5); insert(h_deleteAt, 10); insert(h_deleteAt, 9);
    printHeap(h_deleteAt, "Initial heap:");
    int index_to_delete = 1; // Element 8
    printf("Deleting element at index %d...\n", index_to_delete);
    int deleted_val = deleteAt(h_deleteAt, index_to_delete);
    printf("Deleted value should be 8. GOT: %d\n", deleted_val);
    printHeap(h_deleteAt, "Heap after deletion:");
    printf("\n");
    destroyHeap(h_deleteAt);
    */

    // --- Test Block 4: updateValue ---
    printf("--- 4) Testing updateValue ---\n");
    minHeap* h_update = initHeap(10);
    insert(h_update, 5); insert(h_update, 10); insert(h_update, 7); insert(h_update, 12); insert(h_update, 15);
    printHeap(h_update, "Initial heap:");
    int index_to_update = 2; // Element 7
    int new_value = 3; // New value is smaller, should sift up
    printf("Updating index %d from 7 to %d...\n", index_to_update, new_value);
    updateValue(h_update, index_to_update, new_value);
    printHeap(h_update, "Heap after update (sift up):");
    
    new_value = 14; // New value is larger, should sift down
    printf("Updating index 0 from 3 to %d...\n", new_value);
    updateValue(h_update, 0, new_value);
    printHeap(h_update, "Heap after update (sift down):");
    printf("\n");
    destroyHeap(h_update);
    

    /*
    // --- Test Block 5: getKSmallest ---
    printf("--- 5) Testing getKSmallest ---\n");
    minHeap* h_getK = initHeap(10);
    insert(h_getK, 5); insert(h_getK, 1); insert(h_getK, 4); insert(h_getK, 2); insert(h_getK, 3);
    printHeap(h_getK, "Initial heap:");
    int k_smallest = 3;
    int* result_k = (int*)malloc(sizeof(int) * k_smallest);
    printf("Getting %d smallest elements...\n", k_smallest);
    getKSmallest(h_getK, k_smallest, result_k);
    printf("Expected [1 2 3]. GOT: [");
    for(int i=0; i<k_smallest; ++i) printf("%d ", result_k[i]);
    printf("]\n\n");
    free(result_k);
    destroyHeap(h_getK);
    */

    /*
    // --- Test Block 6: findKthSmallest ---
    printf("--- 6) Testing findKthSmallest ---\n");
    minHeap* h_findK = initHeap(10);
    insert(h_findK, 5); insert(h_findK, 1); insert(h_findK, 4); insert(h_findK, 2); insert(h_findK, 3);
    printHeap(h_findK, "Initial heap:");
    int k_find = 4;
    printf("Finding %dth smallest element...\n", k_find);
    int kth_val = findKthSmallest(h_findK, k_find);
    printf("Expected 4. GOT: %d\n\n", kth_val);
    destroyHeap(h_findK);
    */

    /*
    // --- Test Block 7: minToMaxHeap ---
    printf("--- 7) Testing minToMaxHeap ---\n");
    minHeap* h_transform = initHeap(10);
    insert(h_transform, 1); insert(h_transform, 2); insert(h_transform, 3); insert(h_transform, 4); insert(h_transform, 5);
    printHeap(h_transform, "Initial min-heap:");
    printf("Transforming to max-heap...\n");
    minToMaxHeap(h_transform);
    // Note: printHeap assumes min-heap. The internal array order is what matters.
    // We expect the largest element (5) to be at the root.
    printf("Heap array after transform (should be max-heap order): ");
    for(int i=0; i<h_transform->size; ++i) printf("%d ", h_transform->elems[i]);
    printf("\n\n");
    destroyHeap(h_transform);
    */

    /*
    // --- Test Block 8: mergeHeaps ---
    printf("--- 8) Testing mergeHeaps ---\n");
    minHeap* h1 = initHeap(10);
    insert(h1, 1); insert(h1, 5); insert(h1, 3);
    printHeap(h1, "Heap 1:");
    
    minHeap* h2 = initHeap(10);
    insert(h2, 2); insert(h2, 6); insert(h2, 4);
    printHeap(h2, "Heap 2:");

    printf("Merging heaps...\n");
    minHeap* merged = mergeHeaps(h1, h2);
    if (merged != NULL) {
        printHeap(merged, "Merged heap:");
        destroyHeap(merged);
    } else {
        printf("mergeHeaps not implemented yet.\n");
    }
    destroyHeap(h1);
    destroyHeap(h2);
    */

    return 0;
}
