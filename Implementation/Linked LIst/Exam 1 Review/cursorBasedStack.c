#include <stdio.h>
#include <stdlib.h>

#define VHSIZE 50

typedef struct {
    int data;
} Element;

typedef struct {
    Element elem;
    int next;
} Node;

typedef struct {
    Node VHNode[VHSIZE];
    int avail;
} VHeap;

typedef int Stack;  // index of top element


/*************************************/
/*           YOUR TASKS              */
/*************************************/
// --- CB functions --- //
void initVHeap(VHeap *VH);
int allocSpace(VHeap *VH);
void freeSpace(VHeap *VH, int idx);

// --- Stack functions ---
void initStack(Stack *S);
void insertSorted(VHeap *VH, Stack *S, int data);
void printStack(VHeap VH, Stack S);



void initVHeap(VHeap *VH) {
    for (int i = VHSIZE - 1; i >= 0 ; i--){
        VH->VHNode[i].next = i - 1;
    }

    VH->avail = VHSIZE - 1; 
}

int allocSpace(VHeap *VH) {
    int temp = VH->avail;

    if (temp != -1){
        VH->avail = VH->VHNode[VH->avail].next;
    }

    return temp;
}

void freeSpace(VHeap *VH, int idx) {
    if (idx >= 0 && idx < VHSIZE){
        VH->VHNode[idx].next = VH->avail;
        VH->avail = idx;
    }
}

// --- Stack functions ---
void initStack(Stack *S) {

    *S = -1; //head set to NULL
}

void insertSorted(VHeap *VH, Stack *S, int data) {
    

    int avail = allocSpace(VH);
    VH->VHNode[avail].elem.data = data;


    // head is empty
    if (*S == -1 || data < VH->VHNode[*S].elem.data){

        
        VH->VHNode[avail].next = *S;
        (*S) = avail; 
        
    } else {

        int trav;

        for (trav = *S; VH->VHNode[trav].next == -1 && data < VH->VHNode[VH->VHNode[trav].next].elem.data; trav = VH->VHNode[trav].next){}
        // insert in between

        if (trav != -1){
          
            VH->VHNode[avail].next = VH->VHNode[trav].next;
            VH->VHNode[trav].next = avail; 
        } else {
            
            VH->VHNode[trav].next = avail; 
            VH->VHNode[avail].next = -1;
            
        }

    }

}

void printStack(VHeap VH, Stack S) {
    for (int idx = S; VH.VHNode[VH.VHNode[idx].next].next != -1; idx = VH.VHNode[idx].next){
        printf("%d ",VH.VHNode[idx].elem.data);
    }
}


// --- Main program ---
int main() {
    VHeap VH;
    Stack S;
    int N, val;
    

    initVHeap(&VH);
    initStack(&S);

    printf("Enter size: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &val);
        insertSorted(&VH, &S, val);
    }

    printStack(VH, S);

    return 0;
}