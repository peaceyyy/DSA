#include <stdio.h>
#define MAX 6

typedef struct
{

    char data;
    int link;

} node_t;

typedef struct
{

    node_t Nodes[MAX];
    int avail;

} VirtualHeap;

typedef int L;

void initializeVirtualHeap(VirtualHeap *VH)
{

    VH->avail = MAX - 1;

    for (int i = MAX - 1; i >= 0; i--)
    {

        VH->Nodes[i].link = i - 1;
    }
}

int allocSpace(VirtualHeap *VH)
{ // deleteFirst`

    int temp = VH->avail;

    if (temp != -1)
    {
        VH->avail = VH->Nodes[temp].link;
    }
    else
    {
        printf("\nMemory Allocation Failed!");
    }

    return temp;
}

void deallocSpace(VirtualHeap *VH, int p)
{ 

    if (p >= 0 && p < MAX)
    {

        VH->Nodes[p].link = VH->avail;
        VH->avail = p;
    }
}

void displayVH(VirtualHeap VH, L L)
{

     for (int i = L; i != -1; i = VH.Nodes[i].link) {
        printf("%d | Data: %c | Link: %d\n", i, VH.Nodes[i].data, VH.Nodes[i].link);
    }
}

void insertFirst(VirtualHeap *VH, L *L, char data)
{

    int availNdx = allocSpace(VH);

    if (availNdx != -1)
    {  
        VH->Nodes[availNdx].data = data; // newNode -> data = data
    }
    
    if (*L == -1) { // *head == NULL
        VH->Nodes[*L].link = VH->Nodes[availNdx].link;   
    } else {
        VH->Nodes[availNdx].link = *L;   // newNode -> link = head;

    } 
    *L = availNdx;         // *head = newNode
}

void insertLast(VirtualHeap *VH, L *ListHead, char data)
{
        int availNdx = allocSpace(VH);
       if (*ListHead == -1) {
        *ListHead = availNdx;
        VH->Nodes[availNdx].data = data;
        VH->Nodes[availNdx].link = -1;
    } else {
        L *trav = ListHead;
        for (; *trav != -1; trav = &VH->Nodes[*trav].link) {}
        VH->Nodes[*trav].link = availNdx;
        VH->Nodes[availNdx].data = data;
        VH->Nodes[availNdx].link = -1;
    }
}


void delete (VirtualHeap* VH, L *ListHead, char data){

    L *trav = ListHead;

    if (VH->Nodes[*trav].data == data){
         L temp = *ListHead;
         *ListHead = VH->Nodes[temp].link;
    }
    
    for (; *trav != -1; trav = &VH->Nodes[*trav].link){}

    if (*trav != -1){
        L temp = *trav;
        *trav = VH->Nodes[temp].link;
        deallocSpace(VH, temp); //4
        
    }

}


int main()
{
    VirtualHeap VH;
    initializeVirtualHeap(&VH);
    L L = -1;

    insertFirst(&VH, &L, 'a');
    insertFirst(&VH, &L, 'b');
    insertFirst(&VH, &L, 'c');
    insertFirst(&VH, &L, 'c');
    insertFirst(&VH, &L, 'd');
    // insertLast(&VH, &L, 'f');
    
    displayVH(VH, L);
    delete(&VH, &L, 'f');
    printf("\n\n");
   
}