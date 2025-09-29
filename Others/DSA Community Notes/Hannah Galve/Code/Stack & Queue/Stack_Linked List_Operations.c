// Stack Linked List Operations

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
	char data;
	struct node* link;
}*STACK;

//function prototypes
void initStack(STACK *S);
void PUSH(STACK *S, char x);
void POP(STACK *S);
int EMPTY(STACK S);
char TOP(STACK S);
void displayStack (STACK S);

void main () {
	
	STACK S;
	
	initStack(&S);
		
	//pop
	PUSH(&S, 'a');
	printf("PUSH \n%c", TOP(S));
	PUSH(&S, 'b');
	printf("\n%c", TOP(S));
	PUSH(&S, 'c');
	printf("\n%c \n", TOP(S));
	
	displayStack (S);
	
	//pop
	POP(&S);
	printf("\n\nPOP \n%c \n", TOP(S));
	
	displayStack (S);
}

void initStack(STACK *S) {
	(*S) = NULL;
}
void PUSH(STACK *S, char x){
	//insertFirst()
	STACK temp = (STACK) malloc (sizeof (struct node));
	
	if (temp != NULL) {
		temp->data = x;
		temp->link = *S;
		*S = temp;
	}
}

void POP(STACK *S) {
	//deleteFirst()
	STACK temp;
	
	if (S != NULL) {
		temp = *S;
		*S = temp->link;
		free(temp);
	}
}

int EMPTY(STACK S) {
	return (S != NULL)? 0: 1;
}
char TOP(STACK S) {
	return (EMPTY(S) == 0)? S->data : '\0';
}

void displayStack(STACK S){
	STACK trav;
	
	printf("\nWHOLE STACK \n");
	printf("\nS --> ");
	for (trav = S; trav != NULL; trav = trav->link) {
		printf("%c -> ", trav->data);
	}
	
}

