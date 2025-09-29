/*
Write function createSet(). Given a list of unsorted integers, the function will create a Set of integers. 
The set of integers is organized based on the illustration aboe, i.e the integers are grouped according to the one's digit, 
making 10 groups all in all. Each group in the set is a collection of uniquie integers rranged in ascendin order. 
N addition, the function will return the newly created set to the calling function. 
Note: the function will not call/invoke another calling function. 

c visualization: 
https://pythontutor.com/visualize.html#code=%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%0A%23define%20SIZE%2010%0A%0Atypedef%20struct%20node%20%7B%0A%20%20%20%20int%20elem%3B%0A%20%20%20%20struct%20node*%20link%3B%0A%7D*LIST%3B%0A%0Atypedef%20LIST%20Set%5BSIZE%5D%3B%0A%0Avoid%20initList%28LIST%20*L%29%3B%0Avoid%20insertFirst%28LIST%20*L,%20int%20x%29%3B%0A%0Avoid%20display%20%28Set%20D,%20int%20x%29%3B%0ASet*%20createSet%28LIST%20L%29%3B%0A%0Avoid%20main%20%28%29%20%7B%0A%20%20%20%20%0A%20%20%20%20LIST%20L%3B%0A%20%20%20%20initList%28%26L%29%3B%0A%0A%20%20%20%20%0A%20%20%20%20insertFirst%28%26L,%2020%29%3B%0A%20%20%20%20insertFirst%28%26L,%2016%29%3B%0A%20%20%20%20insertFirst%28%26L,%2029%29%3B%0A%20%20%20%20insertFirst%28%26L,%2030%29%3B%0A%20%20%20%20insertFirst%28%26L,%2036%29%3B%0A%20%20%20%20insertFirst%28%26L,%2049%29%3B%0A%20%20%20%20%0A%20%20%20%20Set*%20new%20%3D%20createSet%28L%29%3B%0A%20%20%20%20%0A%7D%0A%0Avoid%20initList%28LIST%20*L%29%20%7B%0A%20%20%20%20%28*L%29%20%3D%20NULL%3B%0A%7D%0Avoid%20insertFirst%28LIST%20*L,%20int%20x%29%20%7B%0A%20%20%20%20LIST%20temp%20%3D%20%28LIST%29%20malloc%20%28sizeof%28struct%20node%29%29%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28temp%20!%3D%20NULL%29%20%7B%0A%20%20%20%20%20%20%20%20temp-%3Eelem%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20temp-%3Elink%20%3D%20*L%3B%0A%20%20%20%20%20%20%20%20*L%20%3D%20temp%3B%0A%20%20%20%20%7D%0A%7D%0A%0ASet*%20createSet%28LIST%20L%29%20%7B%0A%20%20%20%20LIST%20trav,%20temp,%20*setTrav%3B%0A%20%20%20%20int%20x,%20hash%3B%0A%20%20%20%20Set*%20newSet%20%3D%20%28Set*%29%20malloc%28sizeof%28LIST%29*SIZE%29%3B%0A%20%20%20%20%0A%20%20%20%20for%20%28x%20%3D%200%3B%20x%20!%3D%20SIZE%3B%20x%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20%28*newSet%29%5Bx%5D%20%3D%20NULL%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20for%20%28trav%20%3D%20L%3B%20trav%20!%3D%20NULL%3B%29%20%7B%0A%20%20%20%20%20%20%20%20hash%20%3D%20trav-%3Eelem%20%25%20SIZE%3B%0A%20%20%20%20%20%20%20%20temp%20%3D%20trav%3B%0A%20%20%20%20%20%20%20%20if%20%28hash%20%3C%20SIZE%29%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20for%28setTrav%20%3D%20%26%28*newSet%29%5Bhash%5D%3B%20%28*setTrav%29%20!%3D%20NULL%20%26%26%20%28*setTrav%29-%3Eelem%20%3C%20temp-%3Eelem%3B%20setTrav%20%3D%20%26%28*setTrav%29-%3Elink%29%7B%7D%0A%20%20%20%20%20%20%20%20%20%20%20%20trav%20%3D%20trav-%3Elink%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20temp-%3Elink%20%3D%20*setTrav%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20*setTrav%20%3D%20temp%3B%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20return%20newSet%3B%0A%7D%0A%0Avoid%20display%20%28Set%20D,%20int%20x%29%20%7B%0A%20%20%20%20LIST%20trav%3B%0A%20%20%20%20%0A%20%20%20%20for%20%28trav%20%3D%20D%5Bx%5D%3B%20trav%20!%3D%20NULL%3B%20trav%20%3D%20trav-%3Elink%29%20%7B%0A%20%20%20%20%20%20%20%20printf%28%22%25d%20%22,%20trav-%3Eelem%29%3B%0A%20%20%20%20%7D%0A%7D&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node {
	int elem;
	struct node* link;
}*LIST;

typedef LIST Set[SIZE];

void initList(LIST *L);
void insertFirst(LIST *L, int x);

void display (Set D, int x);
Set* createSet(LIST L);

void main () {
	
	LIST L;
	initList(&L);

	
	insertFirst(&L, 20);
    insertFirst(&L, 16);
    insertFirst(&L, 29);
    insertFirst(&L, 30);
    insertFirst(&L, 36);
    insertFirst(&L, 49);
	
	Set* new = createSet(L);
	
}

void initList(LIST *L) {
	(*L) = NULL;
}
void insertFirst(LIST *L, int x) {
	LIST temp = (LIST) malloc (sizeof(struct node));
	
	if (temp != NULL) {
		temp->elem = x;
		temp->link = *L;
		*L = temp;
	}
}

Set* createSet(LIST L) {
	LIST trav, temp, *setTrav;
	int x, hash;
	Set* newSet = (Set*) malloc(sizeof(LIST)*SIZE);
	
	for (x = 0; x != SIZE; x++) {
		(*newSet)[x] = NULL;
	}
	
	for (trav = L; trav != NULL;) {
		hash = trav->elem % SIZE;
		temp = trav;
		if (hash < SIZE) {
			for(setTrav = &(*newSet)[hash]; (*setTrav) != NULL && (*setTrav)->elem < temp->elem; setTrav = &(*setTrav)->link){}
			trav = trav->link
			temp->link = *setTrav;
			*setTrav = temp;
		}
	}
	
	return newSet;
}

void display (Set D, int x) {
	LIST trav;
	
	for (trav = D[x]; trav != NULL; trav = trav->link) {
		printf("%d ", trav->elem);
	}
}
