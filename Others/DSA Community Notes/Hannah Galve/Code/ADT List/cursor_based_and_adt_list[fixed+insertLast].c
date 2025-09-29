
#include <stdio.h>

#define MAX 20

//Data Structure Definition
typedef struct node {
	char elem;
	int link;
}nodetype;

typedef struct heap {
	nodetype Nodes[MAX];
	int avail;	
}VirtualHeap;

typedef int CBList;

//Function Prototypes

//Virtual Heap Management Routines
VirtualHeap initVH();
int allocSpace (VirtualHeap *VH);
void deallocSpace (VirtualHeap *VH, int index);

//ADT List Functions
void initList(CBList *L);
void insertLast(VirtualHeap *VH, CBList *L, char elem);
void insertFirst(VirtualHeap *VH, CBList *L, char elem);
void deleteElem(VirtualHeap*VH, CBList *L, char elem) ;
void displayList(VirtualHeap VH, CBList L);


//main() Function

void main () {
	
	VirtualHeap VH = initVH();
	CBList L;
	initList(&L);
	
	printf("****Task 1: insertFirst ****\n");
	
	//populate the list
	insertFirst(&VH, &L, 'H');
	insertFirst(&VH, &L, 'E');
	insertFirst(&VH, &L, 'L');
	insertFirst(&VH, &L, 'L');
	insertFirst(&VH, &L, 'O');
	
	displayList(VH, L);
		
	printf("****Task 1: insertLast ****\n");
	
	CBList L2;
	initList(&L2);
	
	//populate the list
	insertLast(&VH, &L2, 'A');
	insertLast(&VH, &L2, 'P');
	insertLast(&VH, &L2, 'P');
	insertLast(&VH, &L2, 'L');
	insertLast(&VH, &L2, 'E');
	
	//display the list
	displayList(VH, L2);
	
	
	
	printf("\n****Task 2 ****\n");
	
	CBList L3;
	initList(&L3);
	
	//populate the list
	insertFirst(&VH, &L3, 'U');
	insertFirst(&VH, &L3, 'S');
	insertFirst(&VH, &L3, 'C');
	
	//display the list
	displayList(VH, L2);
	
	
	printf("\n****Task 3 ****\n");
	
	//delete elem
	deleteElem(&VH, &L, 'H');
	displayList(VH, L);
	
		printf("\n");
	deleteElem(&VH, &L3, 'S');
	displayList(VH, L2);
	
}

//Function Definition - VH Management Functions

VirtualHeap initVH(){
	VirtualHeap VH;
	int index;
	
	VH.avail = MAX-1;
	
	for(index = 0; index < MAX; index++){
		VH.Nodes[index].link = index-1;
	}
	
	return VH;
}

int allocSpace(VirtualHeap *VH) {
	int temp = -1;
	
	if (VH->avail != -1) {
		temp = VH->avail;
		VH->avail = VH->Nodes[VH->avail].link;
	}
	
	return temp;
}

void deallocSpace(VirtualHeap *VH, int index) {
	VH->Nodes[index].link = VH->avail;
	VH->avail = index;
}

//Function Definition -ADT List Functions

void initList (CBList *L) {
	(*L) = -1;
}

void insertLast(VirtualHeap *VH, CBList *L, char elem) {
	int *trav;
	
	for (trav = L; (*trav) != -1; trav = &VH->Nodes[*trav].link) {}
	
	int temp = allocSpace(VH);
	
	if (temp != -1) {
		VH->Nodes[temp].elem = elem;
		VH->Nodes[temp].link = -1;
		*trav = temp;  //fixed this!
	} 
}

void insertFirst(VirtualHeap *VH, CBList *L, char elem) {
	int temp = allocSpace(VH);
	
	if (temp != -1) {
		VH->Nodes[temp].elem = elem;
		VH->Nodes[temp].link = *L;
		*L = temp;
	}

}

void deleteElem(VirtualHeap *VH, CBList *L, char elem) {
	CBList *trav, temp;
	
	for (trav = L; (*trav) != -1;) {
		if (VH->Nodes[*trav].elem == elem) {
			temp = *trav;
			*trav = VH->Nodes[temp].link;
			deallocSpace(VH, temp);
		} else {
			trav = &VH->Nodes[*trav].link;
		}
	}
}

void displayList (VirtualHeap VH, CBList L) {
	int ctr;
	
	for (ctr = L; ctr != -1; ctr = VH.Nodes[ctr].link) {
		printf("%c \n", VH.Nodes[ctr].elem);
	}
}



