// Queue - Cursor Based Implementation

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
	int data;
	int link;
}Nodetype;

typedef struct heap{
	Nodetype Nodes[MAX];
	int avail;
}VirtualHeap;

typedef struct queue {
	int front;
	int rear;
}QUEUE;

// HEAP MANAGEMENT OPERATIONS
void initVH(VirtualHeap *VH); // link all nodes in array and put -1 to indicate end of list
int allocSpace (VirtualHeap *VH); //deleteFirst() - removes first available node in VH and returns index of node; -1 if no space
void deallocSpace (VirtualHeap *VH, int index); //insertFirst() - given index, return the node to list of available nodes; equivalent  to free()

//function prototypes
void initQueue(QUEUE* Q);
void ENQUEUE(VirtualHeap *VH, QUEUE *Q, int x); //insertLast()
void DEQUEUE(VirtualHeap *VH, QUEUE *Q); //deleteFirst()
int FRONT(VirtualHeap VH, QUEUE Q);
int FULL(VirtualHeap VH);
int EMPTY(QUEUE Q);  
void displayQueue(VirtualHeap VH, QUEUE Q);

void main () {
	VirtualHeap VH;
	initVH(&VH);
	
	QUEUE Q;
	initQueue(&Q);
	
	//testing successful initialization
	printf("Initiliazed VH & List \n\nAvail: %d \nFront: %d \nRear: %d\n", VH.avail, Q.front, Q.rear);
	
	ENQUEUE(&VH, &Q, 10);
	ENQUEUE(&VH, &Q, 5);
	ENQUEUE(&VH, &Q, 7);
	ENQUEUE(&VH, &Q, 18);
	
	printf("\n------ ENQUEUE ------ \n"); displayQueue(VH, Q);
	
	DEQUEUE(&VH, &Q);
	DEQUEUE(&VH, &Q);
	
	printf("\n\n----- DEQUEUE ------ \n"); displayQueue(VH, Q);
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


void initQueue(QUEUE* Q) {
	Q->front = -1;   //sentinel value
	Q->rear = -1;
}

void ENQUEUE(VirtualHeap *VH, QUEUE *Q, int x) { //insertLast()
	int temp = VH->avail;
	
	if (temp != -1) {
		VH->avail = VH->Nodes[temp].link;
		
		VH->Nodes[temp].data = x;
		VH->Nodes[temp].link = -1;
		
		if (Q->front == -1) { //check if queue is empty
			Q->front = temp;
		} else {
			VH->Nodes[Q->rear].link = temp;
		}
		
		Q->rear = temp;
	}
}
void DEQUEUE(VirtualHeap *VH, QUEUE *Q){ //deleteFirst()
	int temp = Q->front;
	
	if (Q->front != -1) {
		Q->front = VH->Nodes[temp].link;
		
		VH->Nodes[temp].link = VH->avail;
		VH->avail = temp;
	}
}
int FRONT(VirtualHeap VH, QUEUE Q) {
	return (Q.front != -1) ? VH.Nodes[Q.front].data : -1;
}
int FULL(VirtualHeap VH) {
	return (VH.avail != -1) ? 0 : 1;
}
int EMPTY(QUEUE Q){
	return (Q.front != -1)? 0 : 1;
}

void displayQueue(VirtualHeap VH, QUEUE Q) {
	printf("\nFront -> %d", Q.front);
	printf("\nRear -> %d \n\n", Q.rear);
	printf("\nQUEUE \n\n");
	
	for (; Q.front != -1; DEQUEUE(&VH, &Q)) {
		printf("%d ", FRONT(VH, Q));
	}
}



