// Stack - Cursor Based Implementation

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

typedef int Stack;

//function prototypes

// HEAP MANAGEMENT OPERATIONS
void initVH(VirtualHeap *VH); // link all nodes in array and put -1 to indicate end of list
int allocSpace (VirtualHeap *VH); //deleteFirst() - removes first available node in VH and returns index of node; -1 if no space
void deallocSpace (VirtualHeap *VH, int index); //insertFirst() - given index, return the node to list of available nodes; equivalent  to free()

// STACK LIST OPERATIONS
void initStack(Stack *S);
void PUSH(VirtualHeap *VH, Stack *S, char x); //insertFirst()
void POP(VirtualHeap *VH, Stack *S); //deleteFirst()
int FULL(VirtualHeap *VH, Stack S);
int EMPTY(VirtualHeap *VH, Stack S);
char TOP(VirtualHeap *VH, Stack S);
void displayStack(VirtualHeap VH, Stack S); //requires 'dumping' of values

void main () {
	VirtualHeap VH;
	initVH(&VH);
	
	Stack S;
	initStack(&S);
	
	//testing successful initialization
	printf("Initiliazed VH & Stack \n%d %d\n", VH.avail, S);
	displayStack(VH, S);
	
	printf("\n----INSERTING ELEMENTS---- \n");
	
	printf("\n PUSH \n");
	PUSH(&VH, &S, 'a');
	displayStack(VH, S);
	
	printf("\n PUSH \n");
	PUSH(&VH, &S, 'a');
	printf("\n PUSH \n");
	PUSH(&VH, &S, 'b');
	printf("\n PUSH \n");
	PUSH(&VH, &S, 'c');
	printf("\n PUSH \n");
	PUSH(&VH, &S, 'd');
	displayStack(VH, S);

	printf("\n\n----DELETING ELEMENTS---- \n");
	
	printf("\n POP \n");
	POP(&VH, &S);
	displayStack(VH, S);
	
	printf("\n POP \n");
	POP(&VH, &S);
	printf("\n POP \n");
	POP(&VH, &S);
	printf("\n POP \n");
	POP(&VH, &S);
	displayStack(VH, S);
	
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


void initStack(Stack *S) {
	*S = -1;
}
void PUSH(VirtualHeap *VH, Stack *S, char x) {
	Stack temp = VH->avail;
	
	if (temp != -1) {
		VH->avail = VH->Nodes[temp].link;
	
		VH->Nodes[temp].data = x;
		VH->Nodes[temp].link = *S;	
		*S = temp;
	}
	
	/* using management functions
		Stack temp = allocSpace();
	
		if (temp != -1 && *S != MAX-1) {
			VH->Nodes[temp].data = x;
			VH->Nodes[temp].link = *S;	
			*S = temp;
		}
	*/
}
void POP(VirtualHeap *VH, Stack *S) {
	Stack temp = *S;
	
	if (temp != -1) {
		
		*S = VH->Nodes[temp].link;
		
		VH->Nodes[temp].link = VH->avail;
		VH->avail = temp;
	}
	
	/* using management functions
		Stack temp = *S;
		
		if (temp != -1) {
			*S = VH->Nodes[temp].link;
			
			deallocSpace(VH, temp);
		}
	*/
}

int FULL(VirtualHeap *VH, Stack S) {
	return (VH->avail != -1)? 0 : 1;
}
int EMPTY(VirtualHeap *VH, Stack S) {
	return (S != -1)? 0 : 1 ;
}
char TOP(VirtualHeap *VH, Stack S) {
	return (S != -1) ? VH->Nodes[S].data : '\0';
}
void displayStack (VirtualHeap VH, Stack S) {
	Stack temp;
	
	printf("\nAvail: %d", VH.avail);
	printf("\nStack: %d \n\n", S);
	 
	for(temp = S; temp != -1; temp = VH.Nodes[temp].link){
        printf("%c -> ", VH.Nodes[temp].data);
    }
}


