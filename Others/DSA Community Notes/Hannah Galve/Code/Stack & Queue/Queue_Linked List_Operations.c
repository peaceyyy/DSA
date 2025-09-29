// Queue - Linked List Implementation

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char data;
	struct node* link;
}Node;

typedef struct queue {
	Node *front, *rear;
}QUEUE;

//function prototypes
void initQueue(QUEUE *Q);
void ENQUEUE(QUEUE *Q, char x); //insertLast()
void DEQUEUE(QUEUE *Q); //deleteFirst()
int EMPTY(QUEUE Q);  


void main () {
	QUEUE Q;
	initQueue(&Q);
	
	//ENQUEUE
	ENQUEUE(&Q, 'a');
	ENQUEUE(&Q, 'b');
	ENQUEUE(&Q, 'c');
	ENQUEUE(&Q, 'a');
	
	//DEQUEUE
	DEQUEUE(&Q);
	DEQUEUE(&Q);
	DEQUEUE(&Q);
}

void initQueue(QUEUE *Q) {
	Q->front = NULL;
	Q->rear = NULL;
}
void ENQUEUE(QUEUE *Q, char x) {
	Node* temp = (Node *) malloc(sizeof(struct node));
	
	if (temp != NULL) {
		temp->data = x;
		temp->link = NULL;
		
		if (Q->front == NULL) ?	Q->front = temp : Q->rear->link = temp;
		
		Q->rear = temp;
	}
}

void DEQUEUE(QUEUE *Q) {
	Node* temp;
	
	if (Q->front != NULL) {
		temp = Q->front;
		
		if (Q->front == Q->rear) {
			Q->rear = temp->link;
		}
		
		Q->front = temp->link;
		free(temp);
	}
}
int EMPTY(QUEUE Q){
	return (Q.front != NULL)? 0 : 1;
}
