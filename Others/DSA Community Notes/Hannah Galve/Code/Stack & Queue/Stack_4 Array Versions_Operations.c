// Stack [4 Array List Versions] Operations

#include <stdio.h>
#include <stdlib.h>

#define MAX 10


//VERSION 1
// List is structure containing array and count.
typedef struct node {
	char Elem[MAX];
	int top;
}STACK_1;

//VERSION 2
// List is a pointer to structure containing array and count.
typedef struct node2 {
	char Elem[MAX];
	int top;
}*STACK_2;

//VERSION 3
// List is a structure containing a pointer to dynamically allocated array and count.
typedef struct node3{
	char* Elemptr;
	int top;
}STACK_3;

//VERSION 4
// List is a pointer to structure containing a pointer to dynamically allocated array and count.
typedef struct node4 {
	char* Elemptr;
	int top;
}*STACK_4;


//function prototypes

//VERSION 1
void initStack_1(STACK_1 *S);
void PUSH_1(STACK_1 *S, char x);
void POP_1(STACK_1 *S);
char TOP_1(STACK_1 S);
int FULL_1(STACK_1 S);
int EMPTY_1(STACK_1 S);  

//VERSION 2
void initStack_2(STACK_2 *S);
void PUSH_2(STACK_2 *S, char x);
void POP_2(STACK_2 *S);
char TOP_2(STACK_2 S);
int FULL_2(STACK_2 S);
int EMPTY_2(STACK_2 S);  

//VERSION 3
void initStack_3(STACK_3 *S);
void PUSH_3(STACK_3 *S, char x);
void POP_3(STACK_3 *S);
char TOP_3(STACK_3 S);
int FULL_3(STACK_3 S);
int EMPTY_3(STACK_3 S);  

//VERSION 4
void initStack_4(STACK_4 *S);
void PUSH_4(STACK_4 *S, char x);
void POP_4(STACK_4 *S);
char TOP_4(STACK_4 S);
int FULL_4(STACK_4 S);
int EMPTY_4(STACK_4 S);  

//**************************************************************************************************************
//main function

void main () {
	STACK_1 S1;
	STACK_2 S2;
	STACK_3 S3;
	STACK_4 S4;
	
	initStack_1(&S1);
	initStack_2(&S2);
	initStack_3(&S3);
	initStack_4(&S4);
	
	//testing successful initialization
	printf("\nINITIALIZATION \n%d %d %d %d", S1.top, S2->top, S3.top, S4->top);
	
	//push
	char x = 'a';
	PUSH_1(&S1, x);
	PUSH_2(&S2, x);
	PUSH_3(&S3, x);
	PUSH_4(&S4, x);
	
	printf("\n\nPOP \n%c %c %c %c", TOP_1(S1), TOP_2(S2), TOP_3(S3), TOP_4(S4));
	
	 x = 'b';
	PUSH_1(&S1, x);
	PUSH_2(&S2, x);
	PUSH_3(&S3, x);
	PUSH_4(&S4, x);
	
	printf("\n%c %c %c %c", TOP_1(S1), TOP_2(S2), TOP_3(S3), TOP_4(S4));
	
	 x = 'c';
	PUSH_1(&S1, x);
	PUSH_2(&S2, x);
	PUSH_3(&S3, x);
	PUSH_4(&S4, x);
	
	printf("\n%c %c %c %c", TOP_1(S1), TOP_2(S2), TOP_3(S3), TOP_4(S4));
	
	//pop
	POP_1(&S1);
	POP_2(&S2);
	POP_3(&S3);
	POP_4(&S4);
	
	printf("\n\nPOP \n%c %c %c %c", TOP_1(S1), TOP_2(S2), TOP_3(S3), TOP_4(S4));
	
	POP_1(&S1);
	POP_2(&S2);
	POP_3(&S3);
	POP_4(&S4);
	
	printf("\n%c %c %c %c", TOP_1(S1), TOP_2(S2), TOP_3(S3), TOP_4(S4));
	
	
}

//VERSION 1
void initStack_1(STACK_1 *S) {
	S->top = MAX;
}
void PUSH_1(STACK_1 *S, char x){
	S->top--;
	S->Elem[S->top] = x;
}
void POP_1(STACK_1 *S) {
	S->top++;
}
int FULL_1(STACK_1 S) {
	return (S.top != 0)? 0: 1;
}

int EMPTY_1(STACK_1 S){
	return (S.top != MAX)? 0: 1;
}

char TOP_1(STACK_1 S){
	return(EMPTY_1(S) == 0)? S.Elem[S.top]: '\0';
}

//VERSION 2
void initStack_2(STACK_2 *S) {
	(*S) = (STACK_2) malloc (sizeof(struct node2));
	
	if ((*S) != NULL) {
		(*S)->top = MAX;
	}
}
void PUSH_2(STACK_2 *S, char x){
	(*S)->top--;
	(*S)->Elem[(*S)->top] = x;
}
void POP_2(STACK_2 *S) {
	(*S)->top++;
}
int FULL_2(STACK_2 S) {
	return (S->top != 0)? 0: 1;
}

int EMPTY_2(STACK_2 S){
	return (S->top != MAX)? 0: 1;
}

char TOP_2(STACK_2 S){
	return(EMPTY_2(S) == 0)? S->Elem[S->top]: '\0';
}


//VERSION 3
void initStack_3(STACK_3 *S) {
	S->Elemptr = (char*) malloc(sizeof(char) * MAX);
	
	if (S->Elemptr != NULL){
		S->top = MAX;
	}
}
void PUSH_3(STACK_3 *S, char x) {
	S->top--;
	S->Elemptr[S->top] = x;
}
void POP_3(STACK_3 *S) {
	S->top++;
}
int FULL_3(STACK_3 S){
	return (S.top != 0)? 0: 1;
}
int EMPTY_3(STACK_3 S) {
	return (S.top != MAX)? 0:1;
}
char TOP_3(STACK_3 S){
	return (EMPTY_3(S) == 0)? S.Elemptr[S.top] : '\0';
} 

//VERSION 4
void initStack_4(STACK_4 *S) {
	(*S) = (STACK_4) malloc (sizeof (struct node4));
	
	if (*S != NULL){
		(*S)->Elemptr = (char *) malloc (sizeof (char) * MAX);
		(*S)->top = MAX;
	}
}
void PUSH_4(STACK_4 *S, char x) {
	(*S)->top--;
	(*S)->Elemptr[(*S)->top] = x;
}
void POP_4(STACK_4 *S) {
	(*S)->top++;
}
int FULL_4(STACK_4 S){
	return (S->top != 0)? 0: 1;
}
int EMPTY_4(STACK_4 S){
	return (S->top != MAX)? 0: 1;
}
char TOP_4(STACK_4 S){
	return(FULL_4(S) == 0)? S->Elemptr[S->top]: '\0';
}
