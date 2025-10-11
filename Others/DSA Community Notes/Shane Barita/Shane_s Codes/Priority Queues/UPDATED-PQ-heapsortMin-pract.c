    /* HeapSort in Descending order*/
#include<stdio.h>

#define SIZE 15

typedef struct{
    int Elem[SIZE];
    int lastNdx;
}HEAP;

void initialize(HEAP *H);
void insertPOT(HEAP *H, int x);
void popuUnsort(HEAP *H, int arr[], int size);
int deleteMin(HEAP *H);
void HeapSortMin(HEAP *H);
void MinHeapify(HEAP *H);
void display(HEAP H);

void main(){
    /* Initialize */
    HEAP H;
    initialize(&H);
    /* Populate */
    int arr[]={16,8,12,4,7,20};
    int size = sizeof(arr)/sizeof(arr[0]);
    popuUnsort(&H,arr,size);
    printf("\n**** UNSORTED LIST ****\n");
    display(H);
    /* Heapsort Min */
    HeapSortMin(&H);
    printf("\n**** HEAP AFTER HEAPSORT ****\n");
    display(H);
}

void initialize(HEAP *H){
    H->lastNdx = -1;
}
void display(HEAP H){
    int index;
    for(index = 0; index < H.lastNdx+1; index++){
        printf("[%d] - %d\n", index, H.Elem[index]);
    }
    printf("\nCurrent LastNdx = %d\n", H.lastNdx);
}
void popuUnsort(HEAP *H, int arr[], int size){
    int     index, childNdx;
    for(index = 0; index < size; index++){
        if(H->lastNdx != SIZE-1){
            H->Elem[childNdx = ++H->lastNdx] = arr[index];
        }
    }
}
void insertPOT(HEAP *H, int x){
    int temp, parentNdx, childNdx;
    
    //check if available space
    if(H->lastNdx != SIZE-1){
        //place new elem x at lowest level to the right of the leaves present or to the next level
         H->Elem[childNdx = ++H->lastNdx] = x;

        //while elem x is not root and POT property is not satisfied (parent > elem x)
         while(H->Elem[0] != x && 
         H->Elem[parentNdx = (childNdx-1)/2] > x){
            //SWAP
            temp = H->Elem[parentNdx];
            H->Elem[parentNdx] = H->Elem[childNdx];
            H->Elem[childNdx] = temp;
            childNdx = parentNdx;
         }
    }
}
int deleteMin(HEAP *H){
    int min = -1, parNdx, childNdx, temp;

    if(H->lastNdx != -1){
        //set the min to the root element
        min = H->Elem[0];
        //let the new root element be the last element
        H->Elem[0] = H->Elem[H->lastNdx];
        //decrement the last index
        --H->lastNdx;
        
        parNdx = 0;
        //we have a child for as long as there is a child then there is a child to check on
        childNdx = 1; 
        //here check if a child does exist, to make sure it is not a leaf
        while(childNdx <= H->lastNdx){
            if(childNdx <= H->lastNdx &&
             H->Elem[childNdx+1] < H->Elem[childNdx]){
                childNdx++;
            }
            //we check if the POT property is unsatisfied.
            //the POT property of max heap is parentndx >= childNdx
            if(H->Elem[parNdx] > H->Elem[childNdx]){
                temp = H->Elem[parNdx];
                H->Elem[parNdx] = H->Elem[childNdx];
                H->Elem[childNdx] = temp;
                parNdx = childNdx;
                childNdx = parNdx*2+1;
            } else{
                break;
            }
        }
    }
    return min;
}
//brute forced this shit
void MinHeapify(HEAP *H) {
    // sThis function converts an array into a min-heap by repeatedly sifting down nodes.
    // It iterates through each parent node and ensures the subtree rooted at that parent satisfies the min-heap property.
    // Note: This is a less efficient, but potentially more intuitive, approach than the standard heapify algorithm.
    
    int parentNdx;
    // We need to check every node that could be a parent.
    for (parentNdx = (H->lastNdx - 1) / 2; parentNdx >= 0; parentNdx--) {
        
        int currentNdx = parentNdx;
        
        // Sift-down the node at currentNdx to its correct position in the subtree.
        while (1) { // Loop until the node is in the correct place.
            int smallestNdx = currentNdx;
            int leftChildNdx = 2 * currentNdx + 1;
            int rightChildNdx = 2 * currentNdx + 2;
            
            // Check if the left child exists and is smaller than the current smallest.
            if (leftChildNdx <= H->lastNdx && H->Elem[leftChildNdx] < H->Elem[smallestNdx]) {
                smallestNdx = leftChildNdx;
            }
            
            // Check if the right child exists and is smaller than the current smallest.
            if (rightChildNdx <= H->lastNdx && H->Elem[rightChildNdx] < H->Elem[smallestNdx]) {
                smallestNdx = rightChildNdx;
            }
            
            // If the current node is already the smallest, it's in the right place.
            if (smallestNdx == currentNdx) {
                break; // Exit the sift-down loop for this parent.
            }
            
            // Swap the current node with its smallest child and continue sifting down.
            int temp = H->Elem[currentNdx];
            H->Elem[currentNdx] = H->Elem[smallestNdx];
            H->Elem[smallestNdx] = temp;
            currentNdx = smallestNdx;
        }
    }
}

//can switch between insert through initially empty POT or heapifyMin
void HeapSortMin(HEAP *H){
    int index, origLastNDX, temp;
    origLastNDX = H->lastNdx;
    
    /*
    //METHOD 1: Insert all elements to be sorted in an initially empty POT
    H->lastNdx = -1; //to make it look logically initially empty
    for(index = 0; index <= origLastNDX; index++){
        insertPOT(H, H->Elem[index]);
    }
    */

    //METHOD2: HEAPIFY
    MinHeapify(H);
    
    //while POT not empty
    while(H->lastNdx != -1){
        //deleteMin and store the deleted min elem in the pos of the element
        //which will replace the root
        temp = deleteMin(H);
        H->Elem[H->lastNdx+1] = temp;
    }
    
    //after while loop is executed, retain the real last index
    H->lastNdx = origLastNDX;
}

//kabuangon ko tabang