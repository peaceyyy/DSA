// Closed Hashing - Practice Exercise

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 18
#define EMPTY -1
#define DELETED -2

typedef int SET;
typedef int Dictionary[SIZE];
typedef enum
{
	TRUE,
	FALSE
} boolean;

// function prototypes
void initHashTable(Dictionary D);
int getHash(int x);
void displayHashTable(Dictionary D);
void insertElem(Dictionary D, int x);
void deleteElem(Dictionary D, int x);
boolean isMember(Dictionary D, int val);

void main()
{

	Dictionary D;
	initHashTable(D);

	printf("\n--------------- INITIAL DICTIONARY -------------------\n");
	displayHashTable(D);


	SET S[] = {
		101, 111, 121, 131, 141, 151, 161, 171, 181, // All hash to similar values
		201, 211, 221, 231, 241, 251, 261, 271, 281, // More collisions
		391 // Extra value to attempt to fill the table (SIZE=18, so 19 elements)
	};


	// inserting SET S to Hash Table
	printf("\n \n--------------- INSERTING ELEMENTS FROM SET S -------------------\n");
	int length = sizeof(S) / sizeof(int);
	int x;

	for (x = 0; x < length; x++)
	{
		insertElem(D, S[x]);
	}

	displayHashTable(D);

	int elem = 101;
	printf("\nIs ' %d ' a member? ", elem);
	(isMember(D, elem) == 1)? printf("Yes, it's a member.") : printf("No, it's not a member.");

	// deleting SET D from Hash Table
	printf("\n \n--------------- DELETING ELEMENTS IN SET D -------------------\n");
	SET Del[] = {101, 271, 281, 211, 231};
	length = sizeof(Del) / sizeof(int);

	for (x = 0; x < length; x++)
	{
		deleteElem(D, Del[x]);
	}

	displayHashTable(D);


	//check element membership
	printf("\n \n--------------- CHECK IF ELEMENT '101' & '161' ARE MEMBERS OF DICTIONARY -------------------\n");
	
	elem = 101;
	printf("\nIs ' %d ' a member? ", elem);
	(isMember(D, elem) == 1)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 161;
	printf("\nIs ' %d ' a member? ", elem);
	(isMember(D, elem) == 1)? printf("Yes, it's a member.") : printf("No, it's not a member.");
}
void initHashTable(Dictionary D)
{
	int x;

	for (x = 0; x < SIZE; x++)
	{
		D[x] = EMPTY;
	}
}

int getNthDigit(int x, int n)
{

	if (x < 0)
	{
		x = -x;
	}

	static int powersOfTen[] = {1, 10, 100, 1000, 10000};  // Limited to 5-digit numbers - what about larger values?

	return (x / powersOfTen[n - 1]) % 10;
}

int getHash(int x)
{
	if (x < 0)
		x = -x;  // Handle negatives - good defensive programming

	// Count total digits - could use log10() but this is more portable
	int trav = x;
	int digitCount = 0;
	if (x == 0)
		digitCount = 1;  // Edge case: zero has 1 digit
	else
	{
		while (trav > 0)
		{
			digitCount++;
			trav /= 10;
		}
	}

	int firstDigit = getNthDigit(x, 1);				  // Units place - good for distribution
	int mostSignificant = getNthDigit(x, digitCount); // Leftmost - carries most weight
	int middleDigit = 0;

	if (digitCount > 2)
	{
		int middlePos = (digitCount + 1) / 2; // Clever: handles both odd/even lengths
		middleDigit = getNthDigit(x, middlePos);
	}

	// Weighted combination - interesting choice over simple addition
	int hashValue = (mostSignificant * 100 + middleDigit * 10 + firstDigit) % SIZE;

	return hashValue;
}

void displayHashTable(Dictionary D)
{
	int x;

	printf("\n Index     Content     Hash Value     Search Length");

	for (x = 0; x < SIZE; x++)
	{
		printf("\n  %d", x);
		if (D[x] != EMPTY && D[x] != DELETED)
		{
			// Search length calculation assumes no wrap-around - what if element wrapped past SIZE?
			printf("         %d           %d           %d ", D[x], getHash(D[x]), (x - getHash(D[x]) + 1) + x);
		}
		else if (D[x] == EMPTY)
		{
			printf("         EMPTY");
		}
		else
		{
			printf("       DELETED");
		}
	}
}

boolean isMember(Dictionary D, int x)
{
	int hashVal = getHash(x);
	int trav;

	if (D[hashVal] != x)  // Not at home position
	{
		// Follow the same probe sequence as insertion
		for (trav = hashVal + 1; D[trav] != x && D[trav] != EMPTY && trav != hashVal; trav = (trav + 1) % SIZE)
		{
			// EMPTY stops search - element was never inserted past this point
		};

	}
	else
	{
		trav = hashVal;  // Found at home - best case scenario
	}

	return (x == D[trav]) ? 1 : 0;  // Final verification needed
}

void insertElem(Dictionary D, int x)
{
	int hashVal = getHash(x);

	printf("\nInserting: Initial hash value of %d is %d\n", x, hashVal);
	int trav;

	if (D[hashVal] != x)  // Duplicate check - prevents re-insertion
	{
		if (D[hashVal] == EMPTY || D[hashVal] == DELETED)
		{
			D[hashVal] = x;  // Lucky! Home position is available
		}
		else
		{
			// Linear probing starts here - collision resolution
			for (trav = hashVal + 1; D[trav] != x && D[trav] != EMPTY && D[trav] != DELETED && trav != hashVal; trav = (trav + 1) % SIZE)
			{
				// Keep searching... trav != hashVal prevents infinite loops
			};

			if (trav != hashVal) // Found a spot before full circle
			{
				D[trav] = x;
			} else {
				printf("\nDictionary is full!\n");
			}
		}
	}
	// Missing feedback for duplicates - user won't know insertion was skipped
}

void deleteElem(Dictionary D, int x)
{
	int hashVal = getHash(x);
	int trav = hashVal;

	printf("\nDeleting: Initial hash value of %d is %d\n", x, hashVal);

	if (D[hashVal] != x)  // Not at home position
	{
		// Search following insertion's probe sequence
		for (trav = hashVal + 1; D[trav] != x && D[trav] != EMPTY && trav != hashVal; trav = (trav + 1) % SIZE)
		{
			// Same logic as isMember - consistency is key
		};

		if (trav != hashVal) // Found before completing full circle
		{
			D[trav] = DELETED;  // Mark as deleted, not EMPTY
		} else {
			printf("Element not found!");
		}
	} else {
		D[hashVal] = DELETED;  // Found at home position
	}
	// Why DELETED vs EMPTY? Think about probe sequence integrity...
}
