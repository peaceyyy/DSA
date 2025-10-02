// dictionary - closed hashing (variation 3) operations

/* c visualization links:

 - insert()
https://pythontutor.com/visualize.html#code=//%20dictionary%20-%20closed%20hashing%20%28variation%203%29%20operations%0A%0A%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%0A%23define%20MAX%2020%0A%23define%20EMPTY%200%0A%23define%20DELETED%20-1%0A%0Atypedef%20struct%20node%20%7B%0A%20%20%20%20char%20data%3B%0A%20%20%20%20int%20link%3B%0A%7Dnodetype%3B%0A%0Atypedef%20struct%20%7B%0A%20%20%20%20nodetype%20Nodes%5BMAX%5D%3B%0A%20%20%20%20int%20avail%3B%0A%7DDictionary%3B%0A%0A//function%20prototypes%0Avoid%20initialize%28Dictionary%20*D%29%3B%0Aint%20hash%28char%20x%29%3B%0Aint%20isMember%28Dictionary%20D,%20char%20x%29%3B%0Avoid%20insert%28Dictionary%20*D,%20char%20x%29%3B%0A%0Avoid%20main%20%28%29%20%7B%0A%20%20%20%20%0A%20%20%20%20Dictionary%20D%3B%0A%20%20%20%20initialize%20%28%26D%29%3B%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'a'%29%3B%20%0A%20%20%20%20insert%28%26D,%20'b'%29%3B%20%0A%20%20%20%20insert%28%26D,%20'c'%29%3B%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'k'%29%3B%20//107%0A%20%20%20%20insert%28%26D,%20'l'%29%3B%20//108%0A%20%20%20%20insert%28%26D,%20'm'%29%3B%20//109%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'u'%29%3B%20//117%0A%20%20%20%20insert%28%26D,%20'v'%29%3B%20//118%0A%20%20%20%20insert%28%26D,%20'w'%29%3B%20//119%0A%7D%0A%0Avoid%20initialize%28Dictionary%20*D%29%20%7B%0A%20%20%20%20D-%3Eavail%20%3D%20MAX%20/%202%3B%0A%20%20%20%20int%20index%3B%0A%20%20%20%20%0A%20%20%20%20//initialize%20prime%20data%20area%20to%20EMPTY%0A%20%20%20%20for%20%28index%20%3D%200%3B%20index%20%3C%20D-%3Eavail%3B%20index%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bindex%5D.data%20%3D%20EMPTY%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20//link%20all%20nodes%20in%20synonym%20area%0A%20%20%20%20for%20%28index%20%3D%20D-%3Eavail%3B%20index%20%3C%20MAX%3B%20index%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bindex%5D.link%20%3D%20index%20%2B%201%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20D-%3ENodes%5Bindex-1%5D.link%20%3D%20-1%3B%0A%7D%0A%0Aint%20hash%28char%20x%29%20%7B%0A%20%20%20%20return%20%28x%20%25%2010%29%3B%0A%7D%0A%0Aint%20isMember%20%28Dictionary%20D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp,%20retval%20%3D%20-1%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D.Nodes%5Bhashval%5D.data%20!%3D%20x%29%20%7B%0A%20%20%20%20%20%20%20%20for%20%28temp%20%3D%20D.Nodes%5Bhashval%5D.link%3B%20temp%20!%3D%20-1%20%26%26%20D.Nodes%5Btemp%5D.data%20!%3D%20x%20%3B%20temp%20%3D%20D.Nodes%5Btemp%5D.link%29%20%7B%7D%0A%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20if%20%28temp%20!%3D%20-1%29%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20retval%20%3D%200%3B%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20return%20retval%3B%0A%7D%0A%0Avoid%20insert%28Dictionary%20*D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D-%3ENodes%5Bhashval%5D.data%20%3D%3D%20EMPTY%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.data%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.link%20%3D%20-1%3B%0A%20%20%20%20%7D%20else%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20temp%20%3D%20D-%3ENodes%5BD-%3Eavail%5D.link%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5BD-%3Eavail%5D.data%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5BD-%3Eavail%5D.link%20%3D%20D-%3ENodes%5Bhashval%5D.link%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.link%20%3D%20D-%3Eavail%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3Eavail%20%3D%20temp%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%7D%0A%7D&cumulative=false&curInstr=167&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false

 - delete ()
https://pythontutor.com/visualize.html#code=//%20dictionary%20-%20closed%20hashing%20%28variation%203%29%20operations%0A%0A%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%0A%23define%20MAX%2020%0A%23define%20EMPTY%200%0A%23define%20DELETED%20-1%0A%0Atypedef%20struct%20node%20%7B%0A%20%20%20%20char%20data%3B%0A%20%20%20%20int%20link%3B%0A%7Dnodetype%3B%0A%0Atypedef%20struct%20%7B%0A%20%20%20%20nodetype%20Nodes%5BMAX%5D%3B%0A%20%20%20%20int%20avail%3B%0A%7DDictionary%3B%0A%0A//function%20prototypes%0Avoid%20initialize%28Dictionary%20*D%29%3B%0Aint%20hash%28char%20x%29%3B%0Aint%20isMember%28Dictionary%20D,%20char%20x%29%3B%0Avoid%20insert%28Dictionary%20*D,%20char%20x%29%3B%0Avoid%20deleteElem%20%28Dictionary%20*D,%20char%20x%29%3B%0A%0A%0Avoid%20main%20%28%29%20%7B%0A%20%20%20%20%0A%20%20%20%20Dictionary%20D%3B%0A%20%20%20%20initialize%20%28%26D%29%3B%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'a'%29%3B%20%0A%20%20%20%20insert%28%26D,%20'b'%29%3B%20%0A%20%20%20%20insert%28%26D,%20'c'%29%3B%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'k'%29%3B%20//107%0A%20%20%20%20insert%28%26D,%20'l'%29%3B%20//108%0A%20%20%20%20insert%28%26D,%20'm'%29%3B%20//109%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'u'%29%3B%20//117%0A%20%20%20%20insert%28%26D,%20'v'%29%3B%20//118%0A%20%20%20%20insert%28%26D,%20'w'%29%3B%20//119%0A%20%20%20%20%0A%20%20%0A%20%20%20%20deleteElem%28%26D,%20'a'%29%3B%0A%20%20%20%20deleteElem%28%26D,%20'l'%29%3B%0A%20%20%20%20deleteElem%28%26D,%20'w'%29%3B%0A%7D%0A%0Avoid%20initialize%28Dictionary%20*D%29%20%7B%0A%20%20%20%20D-%3Eavail%20%3D%20MAX%20/%202%3B%0A%20%20%20%20int%20index%3B%0A%20%20%20%20%0A%20%20%20%20//initialize%20prime%20data%20area%20to%20EMPTY%0A%20%20%20%20for%20%28index%20%3D%200%3B%20index%20%3C%20D-%3Eavail%3B%20index%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bindex%5D.data%20%3D%20EMPTY%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20//link%20all%20nodes%20in%20synonym%20area%0A%20%20%20%20for%20%28index%20%3D%20D-%3Eavail%3B%20index%20%3C%20MAX%3B%20index%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bindex%5D.link%20%3D%20index%20%2B%201%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20D-%3ENodes%5Bindex-1%5D.link%20%3D%20-1%3B%0A%7D%0A%0Aint%20hash%28char%20x%29%20%7B%0A%20%20%20%20return%20%28x%20%25%2010%29%3B%0A%7D%0A%0A%0A%0Avoid%20insert%28Dictionary%20*D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D-%3ENodes%5Bhashval%5D.data%20%3D%3D%20EMPTY%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.data%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.link%20%3D%20-1%3B%0A%20%20%20%20%7D%20else%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20temp%20%3D%20D-%3ENodes%5BD-%3Eavail%5D.link%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5BD-%3Eavail%5D.data%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5BD-%3Eavail%5D.link%20%3D%20D-%3ENodes%5Bhashval%5D.link%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.link%20%3D%20D-%3Eavail%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3Eavail%20%3D%20temp%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%7D%0A%7D%0A%0Avoid%20deleteElem%20%28Dictionary%20*D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D-%3ENodes%5Bhashval%5D.data%20!%3D%20EMPTY%29%20%7B%0A%20%20%20%20%20%20%20%20if%20%28D-%3ENodes%5Bhashval%5D.data%20%3D%3D%20x%29%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.data%20%3D%20DELETED%3B%0A%20%20%20%20%20%20%20%20%7D%20else%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20for%20%28temp%20%3D%20D-%3ENodes%5Bhashval%5D.link%3B%20temp%20!%3D%20-1%20%26%26%20D-%3ENodes%5Btemp%5D.data%20!%3D%20x%20%3B%20temp%20%3D%20D-%3ENodes%5Btemp%5D.link%29%20%7B%7D%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20if%20%28temp%20!%3D%20-1%29%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Btemp%5D.data%20%3D%20DELETED%3B%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Btemp%5D.link%20%3D%20D-%3Eavail%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20D-%3Eavail%20%3D%20temp%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%7D%20%20%20%20%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%7D%0A%7D&cumulative=false&curInstr=208&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define EMPTY 0
#define DELETED -1 

typedef struct node {
	char data;
	int link;
}nodetype;

typedef struct {
	nodetype Nodes[MAX];
	int avail;
}Dictionary;

//function prototypes
void initialize(Dictionary *D);
int hash(char x);
int isMember(Dictionary D, char x);
void insert(Dictionary *D, char x);
void deleteElem (Dictionary *D, char x);
void displayDict (Dictionary D);
void main () {
	
	int retval;
	Dictionary D;
	initialize (&D);
	
	
	insert(&D, 'a'); // ASCII 97 -> hash(97) = 7. No collision.
	insert(&D, 'b'); // ASCII 98 -> hash(98) = 8. No collision.
	insert(&D, 'c'); // ASCII 99 -> hash(99) = 9. No collision.
	
	insert(&D, 'k'); // ASCII 107 -> hash(107) = 7. COLLISION with 'a'.
	insert(&D, 'l'); // ASCII 108 -> hash(108) = 8. COLLISION with 'b'.
	insert(&D, 'm'); // ASCII 109 -> hash(109) = 9. COLLISION with 'c'.
	
	insert(&D, 'u'); // ASCII 117 -> hash(117) = 7. COLLISION with 'a' and 'k'.
	insert(&D, 'v'); // ASCII 118 -> hash(118) = 8. COLLISION with 'b' and 'l'.
	insert(&D, 'w'); // ASCII 119 -> hash(119) = 9. COLLISION with 'c' and 'm'.
	

	displayDict(D);
	
	// retval = isMember(D, 'a');
	// printf("%d", retval);
	// retval = isMember(D, 'l');
	// printf("%d", retval);
	// retval = isMember(D, 'w');
	// printf("%d", retval);
	
	// retval = isMember(D, 'd');
	// printf("\n%d", retval);
	// retval = isMember(D, 'h');
	// printf("%d", retval);
	// retval = isMember(D, 'e');
	// printf("%d", retval);
	
	
	// deleteElem(&D, 'a');
	// deleteElem(&D, 'l');
	// deleteElem(&D, 'w');
	
}


void displayDict(Dictionary D){
    int index;
    //prime data area
    for(index = 0; index < D.avail; index++){
        printf("[%d] ", index);
        if(D.Nodes[index].data == EMPTY){
            printf("EMPTY | __");
        } else if(D.Nodes[index].data == DELETED){
            printf("DELETED | %d", DELETED);
        } else{
            printf("%d | %d", D.Nodes[index].data, D.Nodes[index].link);
        }
        printf("\n");
    }
    //synonym area;
    printf("\nSynonym Area:\n");
    for(index = D.avail; index < MAX; index++){
        printf("[%d] %d | %d\n", index, D.Nodes[index].data, D.Nodes[index].link);
    }
    printf("\nCurrent Avail: %d", D.avail);
}

void initialize(Dictionary *D) {
	D->avail = MAX / 2;
	int index;
	
	//initialize prime data area to EMPTY
	for (index = 0; index < D->avail; index++) {
		D->Nodes[index].data = EMPTY;
	}
	
	//link all nodes in synonym area
	for (index = D->avail; index < MAX; index++) {
		D->Nodes[index].link = index + 1;
	}
	
	D->Nodes[MAX-1].link = -1;
}

int hash(char x) {
	return (x % 10);
}


int isMember (Dictionary D, char x) {
	int hashval = hash(x);
	int trav;
	
	// Traverse the chain starting from the home position's link.
	// The element could be in the home position itself or in the synonym chain.
	for (trav = hashval; trav != -1 && D.Nodes[trav].data != x; trav = D.Nodes[trav].link) {
		// This loop handles both the check at the home position (first iteration if it's occupied)
		// and the subsequent synonym chain traversal.
		// Note: We must also check that the data is not DELETED.
	}
	
	// The loop terminates if trav == -1 (end of chain) or if data is found.
	// We also need to ensure the found node isn't a deleted one.
	return (trav != -1 && D.Nodes[trav].data != DELETED) ? 1 : 0; // Return 1 for TRUE, 0 for FALSE
}



void insert(Dictionary *D, char x) {
	int hashval = hash(x);
	int temp;
	
	if (D->Nodes[hashval].data == EMPTY) {
		D->Nodes[hashval].data = x;
		D->Nodes[hashval].link = -1;

					
	} else if (D->avail != -1 && D->Nodes[hashval].data != x) {
		//insertFirst()
		 	temp = D->Nodes[D->avail].link;
		 	
			D->Nodes[D->avail].data = x;

			// this in syn. area	this is in main data area
			D->Nodes[D->avail].link = D->Nodes[hashval].link; // insert first (ish)
			D->Nodes[hashval].link = D->avail; // set new head (not literally)
			D->avail = temp; // move avail
		}
}

void deleteElem (Dictionary *D, char x) {
	int hashval = hash(x);
	int *trav, temp;
	
	if (D->Nodes[hashval].data != EMPTY) {
		// Case 1: Element is in the home position.
		if (D->Nodes[hashval].data == x) {
			temp = D->Nodes[hashval].link; // Get the start of the synonym chain
			if (temp != -1) {
				// If a synonym exists, move it up to the prime area to keep the chain intact.
				D->Nodes[hashval] = D->Nodes[temp];
				// Deallocate the now-empty synonym node
				D->Nodes[temp].link = D->avail;
				D->avail = temp;
			} else {
				// No synonyms, just mark as deleted.
				D->Nodes[hashval].data = DELETED;
			}
		} else {
			// Case 2: Element is in the synonym chain.
			// Use a pointer-to-pointer to find the node and modify the previous node's link.
			for (trav = &D->Nodes[hashval].link; *trav != -1 && D->Nodes[*trav].data != x; trav = &D->Nodes[*trav].link) {}
			
			if (*trav != -1) { // Element found in the synonym chain
				temp = *trav; // The index of the node to delete
				*trav = D->Nodes[temp].link; // Unlink it from the chain
				
				// Deallocate the node by adding it to the front of the avail list.
				D->Nodes[temp].link = D->avail;
				D->avail = temp;
			}
		}
			
	}
}