#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef int SET[MAX];

// function prototypes

// SET OPERATIONS
void initSet(SET A);
void insertSet(SET A, int x);
void deleteSet(SET A, int x);
int isMember(SET A, int x);
void displaySet(SET A);

// UID OPERATIONS
SET *Union(SET A, SET B);
SET *Intersection(SET A, SET B);
SET *Difference(SET A, SET B);
SET *Complement(SET A);
int isSubset(SET A, SET B);

void main()
{
	SET A;
	SET B;

	initSet(A);
	initSet(B);

	// testing successful initialization
	printf("\n ----- INITIALIZATION ------ \n");

	printf("\nSet A \n");
	displaySet(A);
	printf("\n\nSet B \n");
	displaySet(B);

	// inserting elements
	printf("\n\n ----- INSERTING ------ \n");
	printf("\nSet A (Inserting 0, 1, 4, 7)\n");
	insertSet(A, 7);
	insertSet(A, 0);
	insertSet(A, 4);
	insertSet(A, 1);
	displaySet(A);

	printf("\n\nSet B (Inserting 0, 1, 4)\n");
	insertSet(B, 0);
	insertSet(B, 1);
	insertSet(B, 4);
	insertSet(B, 2);
	displaySet(B);

	// UID Ooerations
	printf("\n\n ----- UID Operation: UNION ------ \n");
	printf("\n\nSet A | B -> C \n");
	SET *C = Union(A, B);
	displaySet(A);
	printf("\n");
	displaySet(B);
	printf("\n");
	printf("-------------------\n");
	displaySet(*C);

	printf("\n\n ----- UID Operation: INTERSECTION ------ \n");
	printf("\n\nSet A & B -> C \n");
	C = Intersection(A, B);
	displaySet(*C);

	printf("\n\n ----- UID Operation: DIFFERENCE ------ \n");
	printf("\n\nSet A - B -> C \n");
	displaySet(A);
	printf("\n");
	displaySet(B);
	printf("\n");
	C = Difference(A, B);
	displaySet(*C);

	printf("\n\n ----- UID Operation: COMPLEMENT ------ \n");
	printf("\n\nSet ~A \n");
	C = Complement(A);
	displaySet(A);
	printf("\n");
	displaySet(*C);
	
	printf("\n\n ----- UID Operation: isSubset ------ \n");
	printf("\n\nSet A <- B ? \n");
	insertSet(A, 2);
	insertSet(A, 8);
	insertSet(B, 8);
	displaySet(A);
	printf("\n");
	displaySet(B);
	printf("\n");
	(isSubset(A, B) == 1) ? printf("\nYes, B is a subset of A.") : printf("\nNo, B is not a subset of A");

	// deleting elements
	printf("\n\n ----- DELETING ------ \n");
	printf("\nSet A \n");
	deleteSet(A, 7);
	deleteSet(A, 0);
	displaySet(A);
	
	printf("\n\nSet B \n");
	deleteSet(B, 0);
	deleteSet(B, 4);
	displaySet(B);

	// isMember
	printf("\n\n ----- CHECKING MEMBERSHIP ------ \n");
	printf("\nSet A \n");
	int x = 0;
	(isMember(A, x) == 0) ? printf("\nYes, %d is a member of A.") : printf("\nNo, %d is not a member of A.", x, x);

	printf("\n\nSet B \n");
	x = 1;
	(isMember(B, x) == 0) ? printf("\nYes, %d is a member of B.") : printf("\nNo, %d is not a member of B.", x, x);
}

void initSet(SET A)
{
	int x;

	for (x = 0; x < MAX; x++)
	{
		A[x] = 0;
	}
}

void insertSet(SET A, int x)
{

	if (x < MAX)
	{	
		printf("\nInserted at position: %d\n", x);
		A[x] = 1;
	}
}

void deleteSet(SET A, int x)
{

	if (x < MAX)
	{
		A[x] = 0;
	}
}
int isMember(SET A, int x)
{
	if (x < MAX)
		{
		return A[x] == 1;
}
}

void displaySet(SET A)
{

	for (int i = MAX - 1; i >= 0; i--)
	{
		printf("%d ", A[i]);
	}
}

int isSubset(SET A, SET B)
{
	int ndx;
	int result = 1; // assume subsetivity
	for (ndx = 0; ndx < MAX && result; ndx++){

		if (B[ndx] == 1){
			result = A[ndx] == 1 ? 1 : 0;
		}

	}

	return ndx == MAX ? 1 : 0;
}

SET *Union(SET A, SET B)
{

	SET *C = (SET *)malloc(sizeof(SET));

	for (int i = 0; i < MAX; i++)
	{

		(*C)[i] = A[i] || B[i];
	}

	return C;
}

SET *Intersection(SET A, SET B)
{

	SET *C = (SET *)malloc(sizeof(SET));

	for (int i = 0; i < MAX; i++)
	{

		(*C)[i] = A[i] && B[i];
	}

	return C;
}

SET *Difference(SET A, SET B)
{

	SET *C = (SET *)malloc(sizeof(SET));

	for (int i = 0; i < MAX; i++)
	{

		(*C)[i] = A[i] ;
	}

	return C;
}
SET *Complement(SET A){

	SET *C = (SET *)malloc(sizeof(SET));

	for (int i = 0; i < MAX; i++)
	{

		(*C)[i] = !(A[i]);
	}

	return C;
}