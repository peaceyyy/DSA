#ifndef QUEUE_H
#define QUEUE_H
#define MAX 10

typedef struct{
	int front;
	int rear;
}Queue;

typedef struct{
	char elem;
	int link;
}nodetype;

typedef struct{
	nodetype Nodes[MAX];
	int Avail;
}Vheap;

void initQueue(Queue * Q){
	Q->front = -1;
	Q-> rear = -1;
}

void initVheap(Vheap *VH){
	int c;
	VH->Avail = MAX-1;
	for(c=VH->Avail; c>=0; c--){
		VH->Nodes[c].link = c-1;
	}
}

void enqueue(Queue *Q, Vheap *VH, char x){
	int temp;
	temp = VH->Avail;
	if(temp != -1){
		VH->Avail = VH->Nodes[temp].link;
		VH->Nodes[temp].elem = x;
		VH->Nodes[temp].link = -1;
		if(Q->front == -1 && Q->rear == -1){
			Q->front = temp;
		}
		else{
			VH->Nodes[Q->rear].link = temp;			
		}
		Q->rear = temp;
	}
}

void dequeue(Queue *Q, Vheap *VH){
	int temp;
	if(Q->front != -1){
		temp = Q->front;
		Q->front = VH->Nodes[temp].link;
		VH->Nodes[temp].link = VH->Avail;
		VH->Avail = temp;
	}
	if(Q->front == -1){
		Q->rear = -1;
	}
}

char front(Queue *Q, Vheap *VH){
	return (Q->front != -1)?  VH->Nodes[Q->front].elem: '\0';
}

int isEmpty(Queue *Q){
	return (Q->front == -1 && Q->rear == -1)? 1:0;
}

void display(Queue *Q, Vheap *VH){
	while(isEmpty(Q)!= 1){
		printf(" %c", front(Q, VH));
		dequeue(Q, VH);
	}
}

#endif
