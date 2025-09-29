// ADT List [4 Versions] Operations

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

//VERSION 1
// List is structure containing array and count.
typedef struct node {
	char Elem[MAX];
	int count;
}VER_1;

//VERSION 2
// List is a pointer to structure containing array and count.
typedef struct node2 {
	char Elem[MAX];
	int count;
}*VER_2;

//VERSION 3
// List is a structure containing a pointer to dynamically allocated array and count.
typedef struct node3{
	char* Elemptr;
	int count;
}VER_3;

//VERSION 4
// List is a pointer to structure containing a pointer to dynamically allocated array and count.
typedef struct node4 {
	char* Elemptr;
	int count;
}*VER_4;

//function prototypes

//VERSION 1
void initList_1(VER_1 *S);
void insertFirst_1(VER_1 *S, char x);
void insertElem_1(VER_1 *S, char x); //insertLast()
void insertSorted_1(VER_1 *S, char x);
void deleteFirst_1(VER_1 *S);
void deleteElem_1(VER_1 *S, char x); //deleteAllOccur()
void deleteLast_1(VER_1 *S);
int isMember_1(VER_1 S, char x);
void displayList_1(VER_1 S);

//VERSION 2
void initList_2(VER_2 *S);
void insertFirst_2(VER_2 *S, char x);
void insertElem_2(VER_2 *S, char x);
void insertSorted_2(VER_2 *S, char x);
void deleteFirst_2(VER_2 *S);
void deleteElem_2(VER_2 *S, char x);
void deleteLast_2(VER_2 *S);
int isMember_2(VER_2 S, char x);
void displayList_2(VER_2 S);

//VERSION 3
void initList_3(VER_3 *S);
void insertFirst_3(VER_3 *S, char x);
void insertElem_3(VER_3 *S, char x);
void insertSorted_3(VER_3 *S, char x);
void deleteFirst_3(VER_3 *S);
void deleteElem_3(VER_3 *S, char x);
void deleteLast_3(VER_3 *S);
int isMember_3(VER_3 S, char x); 
void displayList_3(VER_3 S);

//VERSION 4
void initList_4(VER_4 *S);
void insertFirst_4(VER_4 *S, char x);
void insertElem_4(VER_4 *S, char x);
void insertSorted_4(VER_4 *S, char x);
void deleteFirst_4(VER_4 *S);
void deleteElem_4(VER_4 *S, char x);
void deleteLast_4(VER_4 *S);
int isMember_4(VER_4 S, char x);
void displayList_4(VER_4 S);

void main () {
	VER_1 L1;
	VER_2 L2;
	VER_3 L3;
	VER_4 L4;
	
	initList_1(&L1);
	initList_2(&L2);
	initList_3(&L3);
	initList_4(&L4);
	
	//testing successful initialization
	printf("\nINITIALIZATION \n%d %d %d %d", L1.count, L2->count, L3.count, L4->count);
	
	//insert
	printf("\n\n INSERT LAST \n");
	insertElem_1(&L1, 'a');
	insertElem_1(&L1, 'a');
	insertElem_1(&L1, 'a');
	insertElem_1(&L1, 'b');
	displayList_1(L1);
	
	
	insertElem_2(&L2, 'a');
	insertElem_2(&L2, 'b');
	insertElem_2(&L2, 'd');
	insertElem_2(&L2, 'x');
	displayList_2(L2);
	
	insertElem_3(&L3, 'a');
	insertElem_3(&L3, 'c');
	insertElem_3(&L3, 'c');
	insertElem_3(&L3, 't');
	displayList_3(L3);
	
	insertElem_4(&L4, 'c');
	insertElem_4(&L4, 'c');
	insertElem_4(&L4, 'c');
	insertElem_4(&L4, 'h');
	displayList_4(L4);
	
	printf("\n\n INSERT SORTED \n");
	insertSorted_1(&L1, 'b');
	insertSorted_1(&L1, 'b');
	insertSorted_1(&L1, 'c');
	insertSorted_1(&L1, 'd');
	insertSorted_1(&L1, 'c');
	displayList_1(L1);
	
	printf("\n\n INSERT FIRST \n");
	insertFirst_1(&L1, 'x');
	displayList_1(L1);
	
	//delete
	printf("\n\n DELETE ALL OCCURENCES \n"); //requires shifting!
	deleteElem_1(&L1, 'a');
	displayList_1(L1);
	
	deleteElem_2(&L2, 'x');
	displayList_2(L2);
	
	deleteElem_3(&L3, 'c');
	displayList_3(L3);
	
	deleteElem_4(&L4, 'c');
	displayList_4(L4);
	
	printf("\n\n DELETE LAST \n");
	deleteLast_1(&L1);
	displayList_1(L1);
	
	deleteLast_2(&L2);
	displayList_2(L2);
	
	deleteLast_3(&L3);
	displayList_3(L3);
	
	deleteLast_4(&L4);
	displayList_4(L4);
	
	printf("\n\n DELETE FIRST \n");
	deleteFirst_1(&L1);
	displayList_1(L1);
	
	//isMember
	printf("\n\n MEMBER");
	
	char elem = 'a';
	printf("\n\nIs ' %c ' a member of L1? ", elem);
	(isMember_1(L1, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 'x';
	printf("\n\nIs ' %c ' a member of L2? ", elem);
	(isMember_2(L2, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 'a';
	printf("\n\nIs ' %c ' a member of L3? ", elem);
	(isMember_3(L3, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 'c';
	printf("\n\nIs ' %c ' a member of L4? ", elem);
	(isMember_4(L4, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
}

//VERSION 1
void initList_1(VER_1 *S) {
	S->count = 0;
}

void insertFirst_1(VER_1 *S, char x) {
	int i;
	
	if (S->count != MAX) {
		for (i = S->count; i > 0; i--) {
			S->Elem[i] = S->Elem[i-1];
		}
		S->Elem[0] = x;
		S->count++;
	}
}

void insertElem_1(VER_1 *S, char x) {
	
	if(S->count != MAX) {
		S->Elem[S->count] = x;
		S->count++;
	}
}

void insertSorted_1(VER_1 *S, char x){
	int i,j;
	
	if (S->count != MAX) {
		for (i = 0; i < S->count && S->Elem[i] < x; i++) {}
			if (i != S->count) {
				for (j = S->count; j >= i; j--) {
					S->Elem[j] = S->Elem[j-1];
				}
			}
		S->Elem[i] = x;
		S->count++;		
	}
}

void deleteFirst_1(VER_1 *S) {
	int i;
	
	if (S->count != 0) {
		for (i = 0; i < S->count; i++) {
			S->Elem[i] = S->Elem[i+1];
		}	
		S->count--;
	}
}

void deleteElem_1(VER_1 *S, char x) {
	int i,j; 
	
	if (S->count != 0) {
		for (i = 0; i < S->count;) {
			if (S->Elem[i] == x) {
				for (j = i + 1; j < S->count; j++) {
					S->Elem[j-1] = S->Elem[j];
				}
				S->count--;
			} else {
				i++;
			}	
		}
	}
}

void deleteLast_1(VER_1 *S) {
	
	if (S->count != 0) {
		S->count--;
	}
}

int isMember_1(VER_1 S, char x) {
	int i;
	
	for (i = 0; i < MAX && S.Elem[i] != x ; i++) {}
	
	return (i != MAX)? 0 : 1;
	
}

void displayList_1(VER_1 S) {
	int x;
	
	for (x = 0; x < S.count; x++) {
		printf("%c ", S.Elem[x]);
	}
	
	printf("\n");
}


//VERSION 2
void initList_2(VER_2 *S) {
	*S = (VER_2) malloc (sizeof(struct node2));
	
	if (S != NULL) {
		(*S)->count = 0;
	}
}

void insertFirst_2(VER_2 *S, char x) {
	int i;
	
	if ((*S)->count != MAX) {
		for (i = (*S)->count; i > 0; i--) {
			(*S)->Elem[i] = (*S)->Elem[i-1];
		}
		(*S)->Elem[0] = x;
		(*S)->count++;
	}
}

void insertElem_2(VER_2 *S, char x) {
	
	if ((*S)->count != MAX) {
		(*S)->Elem[(*S)->count] = x;
		(*S)->count++;
	}
}

void insertSorted_2(VER_2 *S, char x){
	int i,j;
	
	if ((*S)->count != MAX) {
		for (i = 0; i < (*S)->count && (*S)->Elem[i] < x; i++) {}
			if (i != (*S)->count) {
				for (j = (*S)->count; j >= i; j--) {
					(*S)->Elem[j] = (*S)->Elem[j-1];
				}
			}
		(*S)->Elem[i] = x;
		(*S)->count++;		
	}
}


void deleteFirst_2(VER_2 *S) {
	int i;
	
	if ((*S)->count != 0) {
		for (i = 0; i < (*S)->count; i++) {
			(*S)->Elem[i] = (*S)->Elem[i+1];
		}	
		(*S)->count--;
	}
}

void deleteElem_2(VER_2 *S, char x){
	int i,j; 
	
	if ((*S)->count != 0) {
		for (i = 0; i < (*S)->count;) {
			if ((*S)->Elem[i] == x) {
				for (j = i + 1; j < (*S)->count; j++) {
					(*S)->Elem[j-1] = (*S)->Elem[j];
				}
				(*S)->count--;
			} else {
				i++;
			}
			
		}	
	}
}


void deleteLast_2(VER_2 *S) {
	
	if ((*S)->count != 0) {
		(*S)->count--;
	}
}

int isMember_2(VER_2 S, char x) {
	int i;
	
	for (i = 0; i < MAX && S->Elem[i] != x; i++) {}
	
	return (i != MAX)? 0 : 1;
}

void displayList_2(VER_2 S) {
	int x;
	
	for (x = 0; x < S->count; x++) {
		printf("%c ", S->Elem[x]);
	}
	
	printf("\n");
}

// VERSION 3
void initList_3(VER_3 *S) {
	S->Elemptr = (char*) malloc (sizeof (char) * MAX);
	
	if (S->Elemptr != NULL) {
		S->count = 0;
	}
}

void insertFirst_3(VER_3 *S, char x) {
	int i;
	
	if (S->count != MAX) {
		for (i = S->count; i > 0; i--) {
			S->Elemptr[i] = S->Elemptr[i-1];
		}
		S->Elemptr[0] = x;
		S->count++;
	}
}
void insertElem_3(VER_3 *S, char x) {
	
	if (S->count != MAX) {
		S->Elemptr[S->count] = x;
		S->count++;
	}
}

void insertSorted_3(VER_3 *S, char x){
	int i,j;
	
	if (S->count != MAX) {
		for (i = 0; i < S->count && S->Elemptr[i] < x; i++) {}
			if (i != S->count) {
				for (j = S->count; j >= i; j--) {
					S->Elemptr[j] = S->Elemptr[j-1];
				}
			}
		S->Elemptr[i] = x;
		S->count++;		
	}
}


void deleteFirst_3(VER_3 *S) {
	int i;
	
	if (S->count != 0) {
		for (i = 0; i < S->count; i++) {
			S->Elemptr[i] = S->Elemptr[i+1];
		}	
		S->count--;
	}
}

void deleteElem_3(VER_3 *S, char x){
	int i,j; 
	
	if (S->count != 0) {
		for (i = 0; i < S->count;) {
			if (S->Elemptr[i] == x) {
				for (j = i + 1; j < S->count; j++) {
					S->Elemptr[j-1] = S->Elemptr[j];
				}
				S->count--;
			} else {
				i++;
			}	
		}
	}
}


void deleteLast_3(VER_3 *S) {
	
	if (S->count != 0) {
		S->count--;
	}
}

int isMember_3(VER_3 S, char x) {
	int i;
	
	for (i = 0; i < MAX && S.Elemptr[i] != x ; i++) {}
	
	return (i != MAX)? 0 : 1;
	
}

void displayList_3(VER_3 S) {
	int x;
	
	for (x = 0; x < S.count; x++) {
		printf("%c ", S.Elemptr[x]);
	}
	
	printf("\n");
}

//VERSION 4
void initList_4(VER_4 *S) {
	(*S) = (VER_4) malloc(sizeof(struct node4));
	
	if (S != NULL) {
		(*S)->Elemptr = (char*) malloc (sizeof(char) * MAX);
		
		if ((*S)->Elemptr != NULL) {
			(*S)->count = 0;
		}
	}
}

void insertFirst_4(VER_4 *S, char x) {
	int i;
	
	if ((*S)->count != MAX) {
		for (i = (*S)->count; i > 0; i--) {
			(*S)->Elemptr[i] = (*S)->Elemptr[i-1];
		}
		(*S)->Elemptr[0] = x;
		(*S)->count++;
	}
}

void insertElem_4(VER_4 *S, char x) {
	
	if ((*S)->count != MAX) {
		(*S)->Elemptr[(*S)->count] = x;
		(*S)->count++;
	}
}

void insertSorted_4(VER_4 *S, char x){
	int i,j;
	
	if ((*S)->count != MAX) {
		for (i = 0; i < (*S)->count && (*S)->Elemptr[i] < x; i++) {}
			if (i != (*S)->count) {
				for (j = (*S)->count; j >= i; j--) {
					(*S)->Elemptr[j] = (*S)->Elemptr[j-1];
				}
			}
		(*S)->Elemptr[i] = x;
		(*S)->count++;		
	}
}

void deleteFirst_4(VER_4 *S) {
	int i;
	
	if ((*S)->count != 0) {
		for (i = 0; i < (*S)->count; i++) {
			(*S)->Elemptr[i] = (*S)->Elemptr[i+1];
		}	
		(*S)->count--;
	}
}

void deleteElem_4(VER_4 *S, char x) {
	int i,j; 
	
	if ((*S)->count != 0) {
		for (i = 0; i < (*S)->count;) {
			if ((*S)->Elemptr[i] == x) {
				for (j = i + 1; j < (*S)->count; j++) {
					(*S)->Elemptr[j-1] = (*S)->Elemptr[j];
				}
				(*S)->count--;
			} else {
				i++;
			}
			
		}	
	}
}

void deleteLast_4(VER_4 *S) {
	
	if ((*S)->count != 0) {
		(*S)->count--;
	}
}

int isMember_4(VER_4 S, char x) {
	int i;
	
	for (i = 0; i < MAX && S->Elemptr[i] != x; i++) {}
	
	return (i != MAX)? 0 : 1;
}

void displayList_4(VER_4 S) {
	int x;
	
	for (x = 0; x < S->count; x++) {
		printf("%c ", S->Elemptr[x]);
	}
	
	printf("\n");
}


