// Open Hashing - Cursor Based Implementation

#include <stdio.h>

#define MAX 10
#define HEAP 20 

typedef struct node {
	int data;
	int link;
}Nodetype;

typedef struct heap {
	Nodetype Nodes[HEAP];
	int avail;
}VirtualHeap;

typedef int Dictionary[MAX];

// HEAP MANAGEMENT OPERATIONS
void initVH(VirtualHeap *VH); // link all nodes in array and put -1 to indicate end of list

//function prototypes
void initDictionary (Dictionary D);
int hash(int x);
void insertDictionary (VirtualHeap *VH, Dictionary D, int x);
void deleteDictionary (VirtualHeap *VH, Dictionary D, int x);
int isMember(VirtualHeap *VH, Dictionary D, int x);
void display (VirtualHeap *VH, Dictionary D);

void main () {
	VirtualHeap VH;
	initVH (&VH);
	
	Dictionary D;
	initDictionary (D);
	
	//testing successful initialization
	printf("Initiliazed VH & Dictionary \n%d %d\n", VH.avail, *D);
	display(&VH, D);
	
	
	printf("\n\n----INSERTING ELEMENTS---- \n");
	
	insertDictionary(&VH, D, 10);
	insertDictionary(&VH, D, 20);
	insertDictionary(&VH, D, 30);
	insertDictionary(&VH, D, 40);
	
	insertDictionary(&VH, D, 11);
	insertDictionary(&VH, D, 14);
	insertDictionary(&VH, D, 17);
	insertDictionary(&VH, D, 54);
	display(&VH, D);
	

	printf("\n\n----DELETING ELEMENTS---- \n");
	
	deleteDictionary(&VH, D, 10);
	deleteDictionary(&VH, D, 17);
	display(&VH, D);
	
}


void initVH(VirtualHeap *VH) { // -1 to MAX - 1
	VH->avail = MAX-1;
	int index;
	
	for (index = 0; index < MAX; index++){
		VH->Nodes[index].link = index - 1;
	}
}

void initDictionary (Dictionary D) {
	int index;
	
	for (index = 0; index < MAX; index++) {
		D[index] = -1;
	}
}


int hash(int x){
	return (x % MAX);  //return digit in ones place
}

void insertDictionary (VirtualHeap *VH, Dictionary D, int x) {
	int hashval = hash(x);
	int *trav, temp = VH->avail;
	
	if (temp != -1) {
	
		for (trav = &D[hashval] ; (*trav) != -1 && VH->Nodes[*trav].data <= x; trav = &VH->Nodes[*trav].link){} //find appropriate position
		
		VH->avail = VH->Nodes[temp].link; //allocSpace()
		
		VH->Nodes[temp].data = x;
		VH->Nodes[temp].link = *trav;
		*trav = temp;
	}
}
void deleteDictionary (VirtualHeap *VH, Dictionary D, int x) {
	int hashval = hash(x);
	int *trav, temp;
	
	if (D[hashval] != -1) {
		for (trav = &D[hashval]; (*trav) != -1 && VH->Nodes[*trav].data != x; trav = &VH->Nodes[*trav].link) {}
		
		if (*trav != -1) {
			temp = *trav;
			*trav = VH->Nodes[temp].link;
			
			VH->Nodes[temp].link = VH->avail; //deallocSpace()
			VH->avail = temp;
		}
	}
}
int isMember(VirtualHeap *VH, Dictionary D, int x) {
	int trav, hashval = hash(x);
	
	for (trav = D[hashval]; trav != -1 && VH->Nodes[trav].data != x; trav = VH->Nodes[trav].link){}
	
	return (trav != -1)? 0 : 1;
}
void display (VirtualHeap *VH, Dictionary D) {
	int index, trav;
	
	printf("\nAvail: %d", VH->avail);
	printf("\nHash Values Indices: \n\n");
	for (index = 0; index < MAX; index++) {
		printf("| [%d] | ", index);
		
			for(trav = D[index]; trav != -1; trav = VH->Nodes[trav].link) {
				printf("| %d %d | -> ", VH->Nodes[trav].data, VH->Nodes[trav].link);
			}
		printf("\n");
	}
}

