// ADT Sets - Array Implementation

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

//VERSION 1
typedef struct node {
	int Elem[MAX];
	int count;
}SET;

//function prototypes

// SET OPERATIONS
void initSet(SET *A);
void insertSet(SET *A, int x);
void deleteSet(SET *A, int x);
int isMember (SET A, int x);
void displaySet(SET A);

// UID OPERATIONS
SET Union (SET A, SET B);
SET Intersection (SET A, SET B);
SET Difference (SET A, SET B);
int isSubset (SET A, SET B);

void main () {
	SET A;
	SET B;
	
	initSet(&A);
	initSet(&B);
	
	//testing successful initialization
	printf("\n ----- INITIALIZATION ------ \n");
	
	printf("\nSet A -> count = %d \n", A.count);
	printf("\nSet B -> count = %d \n", B.count);
	
	//inserting elements
	printf("\n\n ----- INSERTING ------ \n");
	printf("\nSet A \n");
	insertSet(&A, 1);
	insertSet(&A, 2);
	insertSet(&A, 3);
	insertSet(&A, 4);
	insertSet(&A, 5);
	displaySet(A);
	
		printf("\n\nSet B \n");
	insertSet(&B, 1);
	insertSet(&B, 2);
	insertSet(&B, 6);
	insertSet(&B, 5);
	insertSet(&B, 8);
	displaySet(B);
	
	// UID Ooerations
	printf("\n\n ----- UID Operation: UNION ------ \n");
	printf("\n\nSet A | B -> C \n");
	SET C = Union(A, B);
	displaySet(C);
	
	printf("\n\n ----- UID Operation: INTERSECTION ------ \n");
	printf("\n\nSet A & B -> C \n");
	C = Intersection(A, B);
	displaySet(C);
	
	printf("\n\n ---------- UID Operation: DIFFERENCE ----------- \n");
	printf("\n\nSet A - B -> C \n");
	C = Difference(A, B);
	displaySet(C);
	
	printf("\n\n ---------- UID Operation: isSubset ----------- \n");
	printf("\n\nSet A <- B ? \n");
	(isSubset(A, B) == 0)? printf("\nYes, B is a subset of A.") : printf("\nNo, B is not a subset of A");
	
	
	//deleting elements
	printf("\n\n ---------- DELETING ----------- \n");
	printf("\nSet A \n");
	deleteSet(&A, 3);
	deleteSet(&A, 5);
	displaySet(A);
	
	printf("\n\nSet B \n");
	deleteSet(&B, 6);
	deleteSet(&B, 8);
	displaySet(B);
	
	//isMember
	printf("\n\n ---------- CHECKING MEMBERSHIP ----------- \n");
	printf("\nSet A \n");
	int x = 0;
	(isMember(A, x) == 0)? printf("\nYes, %d is a member of A.") : printf("\nNo, %d is not a member of A.", x, x);

	printf("\n\nSet B \n");
	x = 1;
	(isMember(B, x) == 0)? printf("\nYes, %d is a member of B.") : printf("\nNo, %d is not a member of B.", x, x);

	
	
}

void initSet(SET* A) {
	A->count = 0;
}
void insertSet(SET* A, int x) {
	int index, temp; 
   		
   	//no shifting bcs order doesnt matter BUT better if sorted for the UID operations later
	for (index = 0; A->count < MAX && index < A->count && A->Elem[index] < x; index++) {}
		
	if (A->count > 0) {    //if list isnt empty, shift elements to make space for new elem
		if (index < MAX && x != A->Elem[A->count-1]) {    //check if elem is at the last index
			for (temp = index, index = A->count + 1; index > temp; index--) {
				A->Elem[index] = A->Elem[index - 1];
			}
		}
	}
	A->Elem[index] = x;
	A->count++;
}
void deleteSet(SET* A, int x) {
	int index;
	
	for (index = 0; index < A->count && A->Elem[index] != x; index++) {}
	
	for (; index != A->count; index++) {
		A->Elem[index] = A->Elem[index + 1];
	}
	
	A->count--;
	
}
int isMember (SET A, int x) {
	int index;
	
	for (index = 0; index < A.count && A.Elem[index] != x; index++) {}
	
	return (index != A.count)? 0 : 1;
	
}
void displaySet(SET A) {
	int index;
	
	for (index = 0; index < A.count; index++) {
		printf("%d ", A.Elem[index]);
	}
	
}

SET Union (SET A, SET B) {
	int ctrA, ctrB;
	SET C;         //no need for malloc bcs a whole structure can be returned without expiring
	C.count = 0;
	
	for (ctrA = ctrB = 0; ctrA < A.count && ctrB < B.count;) {
		if (A.Elem[ctrA] != B.Elem[ctrB]) { 
			C.Elem[C.count++] = (A.Elem[ctrA] < B.Elem[ctrB]) ? A.Elem[ctrA++] : B.Elem[ctrB++];
		}else {
			C.Elem[C.count++] = A.Elem[ctrA++];
			ctrB++;
		}
	}
	
	for (; ctrA < A.count; ctrA++) {
			C.Elem[C.count++] = A.Elem[ctrA];
	}
		
	for (; ctrB < B.count; ctrB++) {
			C.Elem[C.count++] = B.Elem[ctrB];
	}	
	
	return C;
}
SET Intersection (SET A, SET B) {
	int ctrA, ctrB;
	SET C;
	C.count = 0;
	
	for (ctrA = ctrB = 0; ctrA < A.count && ctrB < B.count;) {
		if (A.Elem[ctrA] == B.Elem[ctrB]) {
			C.Elem[C.count++] = A.Elem[ctrA++];
			ctrB++;
 		} else {
 			(A.Elem[ctrA] < B.Elem[ctrB]) ? ctrA++ : ctrB++;
		 }
	}
	
	return C;
}
SET Difference (SET A, SET B) {
	int ctrA, ctrB;
	SET C;
	C.count = 0;
	
	for (ctrA = ctrB = 0; ctrA < A.count && ctrB < B.count;) {
		if (A.Elem[ctrA] == B.Elem[ctrB]) {
			ctrA++;
			ctrB++;
		}else{
			(A.Elem[ctrA] < B.Elem[ctrB])? C.Elem[C.count++] =  A.Elem[ctrA++] : ctrB++;
		}
		
	}
	
	if (ctrA < A.count) {
		for (; ctrA < A.count; ctrA++) {
			C.Elem[C.count++] = A.Elem[ctrA];
		}
	}
	
	return C;
}
int isSubset (SET A, SET B) {
	int ctrA, ctrB;
	
	for (ctrA = ctrB = 0; ctrA < A.count && ctrB < B.count;) {
		(A.Elem[ctrA] == B.Elem[ctrB])? ctrA++: ctrB++;
	}
	
	return (ctrB == B.count)? 0: 1; 
}


