// ADT List - Cursor Based Implementation

#include <stdio.h>

#define MAX 10

typedef struct node {
	char data;
	int link;
}Nodetype;

typedef struct heap {
	Nodetype Nodes[MAX];
	int avail;
}VirtualHeap;

typedef int List;

//function prototypees

// HEAP MANAGEMENT OPERATIONS
void initVH(VirtualHeap *VH); // link all nodes in array and put -1 to indicate end of list
int allocSpace (VirtualHeap *VH); //deleteFirst() - removes first available node in VH and returns index of node; -1 if no space
void deallocSpace (VirtualHeap *VH, int index); //insertFirst() - given index, return the node to list of available nodes; equivalent  to free()

// CURSOR BASED LIST OPERATIONS
void initList(List *L);
void insertFirst(VirtualHeap *VH, List *L, char x);
void insertLast(VirtualHeap *VH, List *L, char x);
void insertSorted(VirtualHeap *VH, List *L, char x);
void deleteFirst(VirtualHeap *VH, List *L);
void deleteLast(VirtualHeap *VH, List *L);
void deleteAllOccur(VirtualHeap *VH, List *L, char x);
int isMember(VirtualHeap *VH, List L, char x);
void displayList(VirtualHeap *VH, List L;);


void main () {
	VirtualHeap VH;
	initVH(&VH);
	
	List L;
	initList(&L);
	
	//testing successful initialization
	printf("Initiliazed VH & List \n%d %d\n", VH.avail, L);
	displayList(&VH, L);
	
	printf("\n----INSERTING ELEMENTS---- \n");
	
	insertFirst(&VH, &L, 'a');
	printf("\nInsert First \n"); displayList(&VH, L);
	
	insertLast(&VH, &L, 'b');
	printf("\n\nInsert Last \n"); displayList(&VH, L);
	
	insertSorted(&VH, &L, 'b');
	insertSorted(&VH, &L, 'c');
	insertSorted(&VH, &L, 'b');
	insertSorted(&VH, &L, 'd');
	
	printf("\n\nInsert Sorted \n"); displayList(&VH, L);
	


	printf("\n\n----DELETING ELEMENTS---- \n");
	
	deleteFirst(&VH, &L);
	printf("\n\nDelete First \n"); displayList(&VH, L);
	
	deleteLast(&VH, &L);
	printf("\n\nDelete Last \n"); displayList(&VH, L);
	
	deleteAllOccur(&VH, &L, 'b');
	printf("\n\nDelete All Occurences \n"); displayList(&VH, L);
	
	
	
	printf("\n\n---- CHECKING MEMBERSHIP---- \n");
	
	char elem = 'c';
	printf("\nIs ' %c ' a member of List? ", elem);
	(isMember(&VH, L, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 'b';
	printf("\nIs ' %c ' a member of List? ", elem);
	(isMember(&VH, L, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
}

void initVH(VirtualHeap *VH) {
	VH->avail = MAX-1;
	int index;
	
	for (index = 0; index < MAX; index++){
		VH->Nodes[index].link = index - 1;
	}
}

int allocSpace(VirtualHeap *VH) {
	int temp = -1;
	
	if (VH->avail != -1) { //always check if there are nodes available
		temp = VH->avail;
		VH->avail = VH->Nodes[temp].link;
	}
}
void deallocSpace(VirtualHeap *VH, int index) {
	VH->Nodes[index].link = VH->avail;
	VH->avail = index;
}



void initList(List *L) {
	(*L) = -1;
}
void insertFirst(VirtualHeap *VH, List *L, char x){
	List temp = VH->avail;
	
	if (temp != -1) {
		VH->avail = VH->Nodes[temp].link;
		
		VH->Nodes[temp].data = x;
		VH->Nodes[temp].link = *L;
		*L = temp;
	}
	
	/* using management functions
		int temp = allocSpace(VH);
		
		if (temp != -1) {
			VH->Nodes[temp].data = x;
			VH->Nodes[temp].link = *L;
			*L = temp;
		}
	*/
}
void insertLast(VirtualHeap *VH, List *L, char x){
	List *trav, temp = VH->avail;
	
	if (temp != -1) {
		for (trav = L; (*trav) != -1; trav = &VH->Nodes[*trav].link){}
		
		VH->avail = VH->Nodes[temp].link;
		
		VH->Nodes[temp].data = x;
		VH->Nodes[temp].link = *trav;
		*trav = temp;
	}
	
	/* using management functions
		List *trav, temp = allocSpace(VH);
		
		if (temp != -1) {
			for (trav = L; (*trav) != -1; trav = &(*trav)->link){}

			VH->Nodes[temp].data = x;
			VH->Nodes[temp].link = *trav;
			*trav = temp;
		}
	*/
}
void insertSorted(VirtualHeap *VH, List *L, char x) {
	List *trav, temp = VH->avail;
	
	if (temp != -1) {
		for (trav = L; (*trav) != -1 && VH->Nodes[*trav].data < x; trav = &VH->Nodes[*trav].link) {}
		
		VH->avail = VH->Nodes[temp].link;
		
		VH->Nodes[temp].data = x;
		VH->Nodes[temp].link = *trav;
		*trav = temp;
	}
	
	/* using management functions
		List *trav, temp = allocSpace(VH);
		
		if (temp != -1) {
			for (trav = L; (*trav) != -1 && VH->Nodes[*trav].data < x; trav = &VH->Nodes[*trav].link) {}

			VH->Nodes[temp].data = x;
			VH->Nodes[temp].link = *trav;
			*trav = temp;
		}
	*/
}
void deleteFirst(VirtualHeap *VH, List *L) {
	
	if (*L != -1) {
		List temp = *L;
		
		*L = VH->Nodes[temp].link;
		
		VH->Nodes[temp].link = VH->avail;
		VH->avail = temp;
	}
	
	/* using management functions
		if (*L != -1) {
			List temp = *L;
			*L = VH->Nodes[temp].link;
			deallocSpace(VH, L);
		}
	*/
}
void deleteLast(VirtualHeap *VH, List *L) {
	List *trav, temp;
	
	if (*L != -1) {
		for(trav = L; VH->Nodes[(*trav)].link != -1; trav = &VH->Nodes[*trav].link){}
		
		temp = *trav;
		*trav = VH->Nodes[temp].link;
		
		VH->Nodes[temp].link = VH->avail;
		VH->avail = temp;
	}
	
	/* using management functions
			List *trav, temp;
	
			if (*L != -1) {
				for(trav = L; VH->Nodes[(*trav)].link != -1; trav = &VH->Nodes[*trav].link){}
				
				temp = *trav;
				*trav = VH->Nodes[temp].link;
				
				deallocSpace(VH, temp);
			}
	*/
}
void deleteAllOccur(VirtualHeap *VH, List *L, char x) {
	List *trav, temp;
	
	if (*L != -1) {
		for (trav = L; (*trav) != -1; ) {
			if(VH->Nodes[*trav].data == x) {
				temp = *trav;
				*trav = VH->Nodes[temp].link;
				
				VH->Nodes[temp].link = VH->avail;
				VH->avail = temp;
			}else  {
				trav = &VH->Nodes[*trav].link;
			}
		}
	}
}
int isMember(VirtualHeap *VH, List L, char x) {
	List trav;
	
	for (trav = L; trav != -1 && VH->Nodes[trav].data != x; trav = VH->Nodes[trav].link) {}

	return (trav != -1) ? 0 : 1;
}
void displayList(VirtualHeap *VH, List L){
	List trav;
	
	printf("\nAvail: %d", VH->avail);
	printf("\nList: %d \n\n", L);
	for (trav = L; trav != -1; trav = VH->Nodes[trav].link) {
		printf("[%d] %c  %d | ", trav, VH->Nodes[trav].data, VH->Nodes[trav].link);
	}

}













