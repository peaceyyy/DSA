// Queue [4 Array List Versions] Implementation

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

//VERSION 1
// List is structure containing array and count.
typedef struct node {
	char Elem[MAX];
	int front, rear;
}QUEUE_1;

//VERSION 2
// List is a pointer to structure containing array and count.
typedef struct node2 {
	char Elem[MAX];
	int front, rear;
}*QUEUE_2;

//VERSION 3
// List is a structure containing a pointer to dynamically allocated array and count.
typedef struct node3{
	char* Elemptr;
	int front, rear;
}QUEUE_3;

//VERSION 4
// List is a pointer to structure containing a pointer to dynamically allocated array and count.
typedef struct node4 {
	char* Elemptr;
	int front, rear;
}*QUEUE_4;


//function prototypes

//VERSION 1
void initQueue_1(QUEUE_1 *Q);
void ENQUEUE_1(QUEUE_1 *Q, char x);
void DEQUEUE_1(QUEUE_1 *Q);
int FULL_1(QUEUE_1 Q);
int EMPTY_1(QUEUE_1 Q);  

//VERSION 2
void initQueue_2(QUEUE_2 *Q);
void ENQUEUE_2(QUEUE_2 *Q, char x);
void DEQUEUE_2(QUEUE_2 *Q);
int FULL_2(QUEUE_2 Q);
int EMPTY_2(QUEUE_2 Q); 

//VERSION 3
void initQueue_3(QUEUE_3 *Q);
void ENQUEUE_3(QUEUE_3 *Q, char x);
void DEQUEUE_3(QUEUE_3 *Q);
int FULL_3(QUEUE_3 Q);
int EMPTY_3(QUEUE_3 Q); 

//VERSION 4
void initQueue_4(QUEUE_4 *Q);
void ENQUEUE_4(QUEUE_4 *Q, char x);
void DEQUEUE_4(QUEUE_4 *Q);
int FULL_4(QUEUE_4 Q);
int EMPTY_4(QUEUE_4 Q); 

//**************************************************************************************************************
//main function

void main () {
	QUEUE_1 Q1;
	QUEUE_2 Q2;
	QUEUE_3 Q3;
	QUEUE_4 Q4;
	
	initQueue_1(&Q1);
	initQueue_2(&Q2);
	initQueue_3(&Q3);
	initQueue_4(&Q4);
	
	//testing successful initialization
	printf("\nINITIALIZATION \n Q1| %d %d \n Q2| %d %d \n Q3| %d %d \n Q4| %d %d \n", Q1.front, Q1.rear, Q2->front, Q2->rear,Q3.front, Q3.rear,Q4->front, Q4->rear);
	
	//ENQUEUE
	char x = 'a';
	ENQUEUE_1(&Q1, x);
	ENQUEUE_2(&Q2, x);
	ENQUEUE_3(&Q3, x);
	ENQUEUE_4(&Q4, x);
	
	x = 'b';
	ENQUEUE_1(&Q1, x);
	ENQUEUE_2(&Q2, x);
	ENQUEUE_3(&Q3, x);
	ENQUEUE_4(&Q4, x);
	
	x = 'c';
	ENQUEUE_1(&Q1, x);
	ENQUEUE_2(&Q2, x);
	ENQUEUE_3(&Q3, x);
	ENQUEUE_4(&Q4, x);
	
	//DEQUEUE
	DEQUEUE_1(&Q1);
	DEQUEUE_2(&Q2);
	DEQUEUE_3(&Q3);
	DEQUEUE_4(&Q4);
	
	DEQUEUE_1(&Q1);
	DEQUEUE_2(&Q2);
	DEQUEUE_3(&Q3);
	DEQUEUE_4(&Q4);
}

//VERSION 1
void initQueue_1(QUEUE_1 *Q) {
	//empty queue: Front is head of rear by 1 cell
	Q->front = 1;
	Q->rear = 0;
}
void ENQUEUE_1(QUEUE_1 *Q, char x) {
	
	if ((Q->rear + 2) % MAX != Q->front) { //check if full
		Q->rear = (Q->rear + 1) % MAX;
		Q->Elem[Q->rear] = x;
	}
}
void DEQUEUE_1(QUEUE_1 *Q) {
	
	if ((Q->rear + 1) % MAX != Q->front) { //check if empty
		Q->front = (Q->front + 1) % MAX;
	}
}
int FULL_1(QUEUE_1 Q) {
	return ((Q.rear + 2) % MAX != Q.front)? 0: 1;  
}
int EMPTY_1(QUEUE_1 Q) {
	return ((Q.rear + 1) % MAX != Q.front)? 0: 1;  
}

//VERSION 2
void initQueue_2(QUEUE_2 *Q) {
	(*Q) = (QUEUE_2) malloc (sizeof(struct node2));
	
	if (*Q != NULL) {
		(*Q)->front = 1;
		(*Q)->rear = 0;
	}
}
void ENQUEUE_2(QUEUE_2 *Q, char x) {
	
	if (((*Q)->rear + 2) % MAX != (*Q)->front) { //check if full
		(*Q)->rear = ((*Q)->rear + 1) % MAX;
		(*Q)->Elem[(*Q)->rear] = x;
	}
}
void DEQUEUE_2(QUEUE_2 *Q) {
	
	if (((*Q)->rear + 1) % MAX != (*Q)->front) { //check if empty
		(*Q)->front = ((*Q)->front + 1) % MAX;
	}
}
int FULL_2(QUEUE_2 Q) {
	return (((Q)->rear + 2) % MAX != (Q)->front)? 0 : 1;
}
int EMPTY_2(QUEUE_2 Q){
	return (((Q)->rear + 1) % MAX != (Q)->front)? 0 : 1;
}



//VERSION 3
void initQueue_3(QUEUE_3 *Q) {
	Q->Elemptr = (char *) malloc (sizeof (char) * MAX);
	
	if (Q->Elemptr != NULL) {
		Q->front = 1;
		Q->rear = 0;
	}
}
void ENQUEUE_3(QUEUE_3 *Q, char x) {
	
	if ((Q->rear + 2) % MAX != Q->front) {
		Q->rear = (Q->rear + 1) % MAX;
		Q->Elemptr[Q->rear] = x;
	}
}
void DEQUEUE_3(QUEUE_3 *Q) {
	
	if ((Q->rear + 1) % MAX != Q->front) {
		Q->front = (Q->front + 1) % MAX;
	}
}
int FULL_3(QUEUE_3 Q) {
	return ((Q.rear + 2) % MAX != Q.front)? 0 : 1;
}
int EMPTY_3(QUEUE_3 Q) {
	return ((Q.rear + 1) % MAX != Q.front)? 0 : 1;
}


//VERSION 4
void initQueue_4(QUEUE_4 *Q) {
	(*Q) = (QUEUE_4) malloc (sizeof(struct node4));
	
	if (*Q != NULL) {
		(*Q)->Elemptr = (char *) malloc (sizeof(char) * MAX);
		
		if ((*Q)->Elemptr != NULL) {
			(*Q)->front = 1;
			(*Q)->rear = 0;
		}
	}
}
void ENQUEUE_4(QUEUE_4 *Q, char x) {
	
	if (((*Q)->rear + 2) % MAX != (*Q)->front) {
		(*Q)->rear = (*Q)->rear + 1 % MAX;
		(*Q)->Elemptr[(*Q)->rear] = x;
	}
}
void DEQUEUE_4(QUEUE_4 *Q) {
	if (((*Q)->rear + 1) % MAX != (*Q)->front) {
		(*Q)->front = (*Q)->front + 1 % MAX;
	}
}


int FULL_4(QUEUE_4 Q) {
	return (((Q)->rear + 2) % MAX != (Q)->front) ? 0 : 1;
}
int EMPTY_4(QUEUE_4 Q) {
	return (((Q)->rear + 1) % MAX != (Q)->front) ? 0 : 1;
}



