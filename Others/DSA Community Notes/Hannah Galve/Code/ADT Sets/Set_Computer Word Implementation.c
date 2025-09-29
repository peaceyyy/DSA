// ADT Sets - Computer Word Implementation

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char SET;

// SET OPERATIONS
void initSet(SET* A);
void insertSet(SET* A, int x);
void deleteSet(SET* A, int x);
int isMember (SET* A, int x);
void displaySet(SET A);

// UID OPERATIONS
SET Union (SET A, SET B);
SET Intersection (SET A, SET B);
SET Difference (SET A, SET B);
SET Complement (SET A);
int isSubset (SET A, SET B);


void main () {
	SET A;
	SET B;
	
	initSet(&A);
	initSet(&B);
	
	//testing successful initialization
	printf("\n ----- INITIALIZATION ------ \n");
	printf("\nSet A \n");
	displaySet(A);
	printf("\n\nSet B \n");
	displaySet(B);
	
	//inserting elements
	printf("\n\n ----- INSERTING ------ \n");
	printf("\nSet A \n");
	insertSet(&A, 7);
	insertSet(&A, 0);
	insertSet(&A, 4);
	insertSet(&A, 1);
	displaySet(A);
	
	printf("\n\nSet B \n");
	insertSet(&B, 0);
	insertSet(&B, 1);
	insertSet(&B, 4);
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
	
	printf("\n\n ---------- UID Operation: COMPLEMENT ----------- \n");
	printf("\n\nSet ~A \n");
	C = Complement (A);
	displaySet(C);
	
	printf("\n\n ---------- UID Operation: isSubset ----------- \n");
	printf("\n\nSet A <- B ? \n");
	(isSubset(A, B) == 0)? printf("\nYes, B is a subset of A.") : printf("\nNo, B is not a subset of A");
	
	
	//deleting elements
	printf("\n\n ---------- DELETING ----------- \n");
	printf("\nSet A \n");
	deleteSet(&A, 7);
	deleteSet(&A, 0);
	displaySet(A);
	
	printf("\n\nSet B \n");
	deleteSet(&B, 0);
	deleteSet(&B, 4);
	displaySet(B);
	
	//isMember
	printf("\n\n ---------- CHECKING MEMBERSHIP ----------- \n");
	printf("\nSet A \n");
	int x = 0;
	(isMember(&A, x) == 0)? printf("\nYes, %d is a member of A.") : printf("\nNo, %d is not a member of A.", x, x);

	printf("\n\nSet B \n");
	x = 1;
	(isMember(&B, x) == 0)? printf("\nYes, %d is a member of B.") : printf("\nNo, %d is not a member of B.", x, x);

}

void initSet(SET* A) {
	*A = 0;
}
void insertSet(SET* A, int x){
	if (x < sizeof(*A) * 8) //check if x is withing 0 - 8 range
	*A |= 1 << x;
}
void deleteSet(SET* A, int x) {
	if (x < sizeof(*A) * 8)
	*A ^= 1 << x;
}
int isMember (SET* A, int x) {
	return (x < sizeof(*A) * 8) && (*A & 1 << x) != 0 ? 0 : 1;
}

SET Union (SET A, SET B) {
	return A | B;
}
SET Intersection (SET A, SET B) {
	return A & B;
}
SET Difference (SET A, SET B) {
	return A & ~B;
}
SET Complement (SET A) {
	return ~A;
}
int isSubset (SET A, SET B) {
	return (A & B != 0)? 0 : 1;
}

void displaySet(SET A) {
	int x, SIZE = sizeof(SET) * 8;
	
	for (x = 0; x < SIZE; x++) {
		if ( (A & 1 << x) > 0) {
			printf("%d ", x);
		} else {
			printf(" _ ");
		}
		
	}
}

