// ADT List Linked List Operations

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char data;
	struct node* link;
}*LIST;

//function prototypes
void initList(LIST *L);
void insertFirst(LIST *L, char x);
void insertLast(LIST *L, char x); 
void insertSorted(LIST *L, char x);
void deleteFirst(LIST *L);
void deleteElem(LIST *L, char x); //deleteAllOccur()
void deleteLast(LIST *L);
int isMember(LIST L, char x);
void displayList(LIST L);

void main () {
	LIST L;
	initList(&L);
	
	printf("----INSERTING ELEMENTS---- \n");
	
	insertFirst(&L, 'a');
	printf("Insert First \n"); displayList(L);
	
	insertLast(&L, 'b');
	printf("\nInsert Last \n"); displayList(L);
	
	insertSorted(&L, 'c');
	insertSorted(&L, 'a');
	insertSorted(&L, 'd');
	insertSorted(&L, 'b');
	printf("\nInsert Sorted \n"); displayList(L);
	
	
	
	printf("\n\n----DELETING ELEMENTS---- \n");
	
	deleteFirst(&L);
	printf("Delete First \n"); displayList(L);
	
	deleteLast(&L);
	printf("\nDelete Last \n"); displayList(L);
	
	deleteElem(&L, 'b');
	printf("\nDelete All Occurences \n"); displayList(L);
	
	
	
	printf("\n\n---- CHECKING MEMBERSHIP---- \n");
	
	char elem = 'a';
	printf("\nIs ' %c ' a member of List? ", elem);
	(isMember(L, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 'b';
	printf("\nIs ' %c ' a member of List? ", elem);
	(isMember(L, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
}

void initList(LIST *L) {
	(*L) = NULL;
}
void insertFirst(LIST *L, char x) {
	LIST temp = (LIST) malloc (sizeof(struct node));
	
	if (temp != NULL) {
		temp->data = x;
		temp->link = *L;
		*L = temp;
	}
}

void insertLast(LIST *L, char x){ //insertLast()
	LIST *trav, temp = (LIST) malloc (sizeof(struct node));
	
	for (trav = L; (*trav) != NULL; trav = &(*trav)->link) {}
	
	if (temp != NULL) {
		temp->data = x;
		temp->link = NULL;
		*trav = temp;
	}
}

void insertSorted(LIST *L, char x){
	LIST *trav, temp = (LIST) malloc (sizeof(struct node));
	
	for (trav = L; (*trav) != NULL && (*trav)->data < x ; trav = &(*trav)->link) {}
	
	if (temp != NULL) {
		temp->data = x;
		temp->link = *trav;
		*trav = temp;
	}
	
}
void deleteFirst(LIST *L) {
	LIST temp;
	if (*L != NULL) {
		temp = *L;
		*L = temp->link;
		free(temp);
	}
}
void deleteElem(LIST *L, char x){ //deleteAllOccur()
	LIST *trav, temp;
	
	if (*L != NULL) {
		for (trav = L; (*trav) != NULL;) {
			if ((*trav)->data == x) {
				temp = *trav;
				*trav = temp->link;
				free(temp);
			}else {
				trav = &(*trav)->link;
			}
		}
	}
}
void deleteLast(LIST *L) {
	LIST *trav, temp;
	
	if (*L != NULL) {
		for (trav = L; (*trav)->link != NULL; trav = &(*trav)->link){}
		
		temp = *trav;
		*trav = temp->link;
		free(temp);
		
	}
}
int isMember(LIST L, char x){
	LIST trav;
	
	for (trav = L; trav != NULL && trav->data != x; trav = trav->link) {}
	
	return (trav != NULL)? 0 : 1;
}
void displayList(LIST L){
	LIST trav;
	
	for (trav = L; trav != NULL; trav = trav->link) {
		printf("%c ", trav->data);
	}
}
