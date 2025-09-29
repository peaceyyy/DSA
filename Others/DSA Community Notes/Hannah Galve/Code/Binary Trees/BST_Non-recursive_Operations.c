// Binary Search Tree - Operations (Non-Recursive)

#include <stdio.h>
#include <stdlib.h>

typedef enum  {FALSE, TRUE} boolean;


typedef struct cell {
	int elem;
	struct cell* LC;
	struct cell* RC;
}*BST;

boolean MEMBER (BST S, int n);
void INSERT (BST *S, int n);
void DELETE (BST *S, int n);
BST MIN(BST S);
BST MAX(BST S);
struct cell* newNode(int n);
void INITIALIZE (BST *S);

// Dispaly - Traversal Functions
void INORDER (BST S);
void PREORDER (BST S);
void POSTORDER (BST S);

void main () {
	BST S;
	
	printf("----- INITIALIZE TREE ------- \n\n");
	INITIALIZE (&S);
	
	printf("\n----- INSERT ELEMENTS ------- \n\n");
	
	printf("Inserting Set S = {10, 5, 14, 12, 7, 18, 15} \n\n");
	INSERT(&S, 10);
	INSERT(&S, 5);
	INSERT(&S, 7);
	INSERT(&S, 14);
	INSERT(&S, 12);
	INSERT(&S, 18);
	INSERT(&S, 15);

	printf("\n----- DISPLAY TREE (Ordering Traversal) ------- \n\n");
	printf("INORDER \n\n");
	INORDER(S); // 5 7 10 12 14 15 18
	printf("\n\nPREORDER \n\n");
	PREORDER(S); // 10 5 7 14 12 18 15
	printf("\n\nPOSTORDER \n\n");
	POSTORDER(S); // 7 5 12 15 18 14 10
	
	printf("\n\n----- DELETING ELEMENTS ------- \n\n");
	
	printf("Delete Element: 7 14 10 \n\n");
	DELETE(&S, 7);
	DELETE(&S, 14);
	DELETE(&S, 10);
	INORDER(S);
	
}

void INITIALIZE (BST *S) {
	*S = NULL;
}

boolean MEMBER (BST S, int n) {
	BST trav;
	
	for(trav = S; trav != NULL && trav->elem != n;) {
		trav = (n < trav->elem) ? trav->LC : trav->RC;
	}
	
	return (trav != NULL) ? TRUE : FALSE;
}


struct cell* newNode(int n) {
	struct cell* temp = (struct cell*) malloc (sizeof(struct cell));
	
	if (temp != NULL) {
		temp->elem = n;
		temp->LC = temp->RC = NULL;
	}
	
	return temp;
}

void INSERT (BST *S, int n) {
	BST *trav;
	
	if (*S != NULL) {
		for (trav = S; (*trav) != NULL;) {
			trav = (n < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC;
		}
		
		*trav = (trav == NULL && n < (*trav)->elem) ? newNode(n) : newNode(n);
		
	}else {
		*S = newNode(n);
	}
	
}

//use two pointers
void DELETE (BST *S, int n) { //check membership
	BST *trav, *trav2, temp;
	
	if (*S != NULL) {
		for(trav = S; (*trav) != NULL && (*trav)->elem != n;) {
			trav = (n < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC;
		}
		
		//check possible cases
		if ((*trav)->LC == NULL) { 		
			temp = *trav;
			*trav = temp->RC;
			free(*trav);
		}
		else if ((*trav)->RC == NULL){  
			temp = *trav; 					  //find inorder successor
			*trav = temp->LC;				  //replace current node with IS
			free(temp);                   					  //delete IS
			
		} else {     									     //one child
			for(trav2 = &(*trav)->RC; (*trav2)->LC != NULL; trav2 = &(*trav2)->LC){}
			temp = *trav2;
			*trav2 = temp->RC;
			(*trav)->elem = temp->elem;
			free(temp);
		} 
	} else {
		(*S) = NULL;
	}
}


BST MIN(BST S) { //look for smallest value in tree (traverse left subtree)
	BST trav;
	
	for (trav = S; trav != NULL && trav->LC != NULL; trav = trav->LC) {}
	
	return trav;	
}

BST MAX(BST S) { //look for biggest value in tree (traverse right subtree)
	BST trav;
	
	for (trav = S; trav != NULL && trav->RC != NULL; trav = trav->RC) {}
	
	return trav;	
}



void INORDER (BST S) {
	if (S != NULL) {
		INORDER(S->LC);
		printf("%d ", S->elem);
		INORDER(S->RC);
	}
}

void PREORDER (BST S) {	
	if (S != NULL) {
		printf("%d ", S->elem);
		PREORDER(S->LC);
		PREORDER(S->RC);
	}
}

void POSTORDER (BST S) {	
	if (S != NULL) {
		POSTORDER(S->LC);
		POSTORDER(S->RC);
		printf("%d ", S->elem);
	}
}



