#include <stdio.h>
#include <stdlib.h>
#include "QueueCB.h"

void initQueue(Queue * Q);
void initVheap(Vheap *VH);
void enqueue(Queue *Q, Vheap *VH, char x);
void dequeue(Queue *Q, Vheap *VH);
char front(Queue *Q, Vheap *VH);
int isEmpty(Queue *Q);
void displayQueue(Queue *Q, Vheap *VH);

void main(){
	Queue Q;
	Vheap VH;
	
	initVheap(&VH);
	initQueue(&Q);
	
	enqueue(&Q,&VH, 'B');
	enqueue(&Q,&VH, 'E');
	enqueue(&Q,&VH, 'S');
	display(&Q,&VH);
	
}
