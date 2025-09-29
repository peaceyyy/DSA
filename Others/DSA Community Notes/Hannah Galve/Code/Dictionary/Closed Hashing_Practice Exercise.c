// Closed Hashing - Practice Exercise

#include <stdio.h>

#define SIZE 23
#define EMPTY 0
#define DELETED -1

typedef int SET;
typedef int Dictionary [SIZE];
typedef enum {TRUE, FALSE} boolean;

//function prototypes
void initHashTable(Dictionary D);
int hashVal(int x);
void displayHashTable(Dictionary D);
void insertElem(Dictionary D, int x);
void deleteElem(Dictionary D, int x);
boolean isMember(Dictionary D, int val);

void main () {
	
	Dictionary D;
	initHashTable(D);
	
	printf("\n--------------- INITIAL DICTIONARY -------------------\n");
	displayHashTable(D);
	
	SET S[] = { 4057, 3042, 3205,  848, 1864, 987, 3082,  414, 1728, 1400, 1223, 2710, 2486, 2885, 1192, 4057 }; // 16
	
	//inserting SET S to Hash Table
	printf("\n \n--------------- INSERTING ELEMENTS FROM SET S -------------------\n");
	int length = sizeof(S)/sizeof(int);
	int x;
	
	for (x = 0; x < length; x++) {
		insertElem(D, S[x]);
	}
	
	displayHashTable(D);
	
	//deleting SET D from Hash Table
	printf("\n \n--------------- DELETING ELEMENTS IN SET D -------------------\n");
	SET Del[] = {4057, 3205, 1728, 2486, 1192, 5595};
	length = sizeof(Del)/sizeof(int);
	
	for (x = 0; x < length; x++) {
		deleteElem(D, Del[x]);
	}
	
	displayHashTable(D);
	
	//deleting SET S2 from Hash Table
	printf("\n \n--------------- INSERTING ELEMENTS FROM SET S2 -------------------\n");
	SET S2[] = {1400, 5595,  121,  139, 1532,  596, 2800, 1167,  213};
	length = sizeof(S2)/sizeof(int);
	
	for (x = 0; x < length; x++) {
		insertElem(D, S2[x]);
	}
	
	displayHashTable(D);
	
	//check element membership
	printf("\n \n--------------- CHECK IF ELEMENT '5595' & '4057' ARE MEMBERS OF DICTIONARY -------------------\n");
	
	int elem = 5595;
	printf("\nIs ' %d ' a member? ", elem);
	(isMember(D, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 4057;
	printf("\nIs ' %d ' a member? ", elem);
	(isMember(D, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
}
void initHashTable(Dictionary D) {
	int x;
	
	for (x = 0; x < SIZE; x++) {
		D[x]= EMPTY;
	}
}

int hashVal(int x){
	int temp, retval = 0;
	
	// Sum all digits of the number (assumes 4-digit max)
	// This distributes better than simple modulo for similar numbers
	for (temp = 0; temp < 4; temp++) {
		retval = retval + (x % 10);  // Get rightmost digit
		x = x /10;                   // Remove rightmost digit
	}
	return retval % 23;  // Final hash: digit sum mod table size
}

void displayHashTable(Dictionary D) {
	int x;
	
	printf("\n Index     Content     Hash Value     Search Length");
	
	for (x = 0; x < SIZE ; x++) {
		printf("\n  %d", x);
		if (D[x] != EMPTY && D[x] != DELETED) {
			printf("         %d           %d           %d ", D[x], hashVal(D[x]), (x - hashVal(D[x])+ 1));
		} else if (D[x] == EMPTY) {
			printf("         EMPTY");
		} else {
			printf("       DELETED");
		}
	}
}

boolean isMember(Dictionary D, int x) {
	boolean retval;
	int hashval = hashVal(x);
	int temp;
	
	// Check home position first
	if (D[hashval] != x) {
		// Linear probe from next position
		// TERMINATION: Good - stops when temp wraps back to hashval
		for (temp = hashval + 1; temp != hashval && D[temp] != x; temp = (temp+1)%SIZE) {}
	} 
	// LOGIC ISSUE: Think about what temp contains when loop exits
	// What does (temp != hashval) actually tell you?
	// When would temp == hashval? When would temp != hashval?
	return retval = (temp != hashval)? TRUE : FALSE;  // ORIGINAL - analyze this logic
}

// void insertElem(Dictionary D, int x){
// 	int hashval = hashVal(x);
// 	int temp;
	
// 	// Avoid duplicate insertion
// 	if (D[hashval] != x) {
// 		// DANGEROUS CONDITION: What does isMember(D, D[temp]) != FALSE mean?
// 		// Think: You're checking if "the element at position temp" exists somewhere in table
// 		// But temp changes every iteration - what happens if D[temp] doesn't exist?
// 		// What happens if the isMember function has bugs?
// 		// TERMINATION RISK: What stops this loop if table is full of existing elements?
// 		for (temp = hashval; D[temp] != EMPTY && D[temp] != DELETED && isMember(D, D[temp]) != FALSE; temp = (temp + 1) % SIZE) {}
// 			D[temp] = x;
// 	}
// }

void insertElem(Dictionary D, int x){
	int hashval = hashVal(x);
	int temp;
	int count;
	
	// Avoid duplicate insertion
	if (D[hashval] != x) {
		
		for (temp = hashval, count = 0; D[temp] != EMPTY && D[temp] != DELETED; temp = (temp + 1) % SIZE, count++) {}
			if (count < SIZE) D[temp] = x; // it means we didn't reach a full loop
		} else {
			
			D[hashval] = x;
			
	}
}


void deleteElem(Dictionary D, int x) {
	int hashval = hashVal(x);
	int temp;
	
	// Check home position first
	if (D[hashval] == x){
		printf("Element %d deleted. \n", D[hashval]);
		D[hashval] = DELETED;
	} else {
		// Linear probe to find element
		// TERMINATION: Good - temp != hashval prevents infinite loop
		// SEARCH LOGIC: Think - should you continue searching past EMPTY slots?
		// In linear probing, can an element exist beyond an EMPTY slot?
		for (temp = hashval + 1; temp != hashval && D[temp] != x; temp = (temp + 1) % SIZE) {}
			
			// BOUNDARY CHECK: What if temp == hashval here?
			// What if temp stopped because D[temp] == x?
			if (temp != hashval) {
				printf("Element %d deleted. \n", D[temp]);
				D[temp] = DELETED;
			} else {
				printf("Element %d not found! \n", x);
			}
		}
}


